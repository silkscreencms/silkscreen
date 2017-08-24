<?php

/**
 * Defines the database storage controller.
 */
class ConfigDatabaseStorage implements ConfigStorageInterface {

  /**
   * The name of the storage class.
   * @var string
   */
  static $storage_class = 'Database';

  protected $immutable = FALSE;

  /**
   * {@inheritdoc}
   */
  public function isImmutable() {
    return $this->immutable;
  }

  /**
   * {@inheritdoc}
   */
  public static function urlPrefix() {
    return 'db';
  }

  /**
   * The database table to use for configuration objects.
   *
   * @var string
   */
  protected $table = '';

  /**
   * The database connection to use.
   *
   * @var string
   */
  protected $database = '';

  protected function schema($name) {
    $schema = array(
      'description' => 'Stores the configuration of the site in database tables.',
      'fields' => array(
        'name' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'The top-level name for the full key.  Would be the filename in the ConfigFileStore, minus the .json extension',
        ),
        'data' => array(
          'type' => 'text',
          'not null' => TRUE,
          'description' => 'The JSON encoded value for the key.',
        ),
        'ctime' => array(
          'type' => 'int',
          'not null' => TRUE,
          'default' => 0,
          'description' => 'The node changed time (see stat(2) for details.)',
        ),
      ),
      'primary key' => array('name'),
    );

    return $schema;
  }

  /**
   * Constructs a new ConfigDatabaseStorage controller.
   *
   * @param string $dburl
   *   A URL that references a backdrop connection (optional) and table. The
   *   string has a format of db:/<database connection>/<database table>. If
   *   no database connection is specified, then the 'default' connection is
   *   used.
   *
   *   Examples:
   *    * db:/default/config_active
   *    * db:config_active
   *    * db://config_active
   *    * db:/config_store/config_stage
   */
  public function __construct($dburl) {
    $matches = array();
    preg_match('/^db:(\/(\w*)\/)?(\w+)$/', trim($dburl), $matches);
    if (count($matches) != 4) {
      throw new ConfigStorageException(t('Invalid database specifier: @db', array('@db' => $dburl)));
    }
    $this->table = $matches[3];
    $this->database = $matches[2] ? $matches[2] : 'default';

    // Bootstrap the database if it is not yet available.
    if (!function_exists('db_query') || backdrop_get_bootstrap_phase() < BACKDROP_BOOTSTRAP_DATABASE) {
      require_once BACKDROP_ROOT . '/core/includes/database/database.inc';
    }
  }

  /**
   * Create the database table it does not already exist.
   *
   * @return bool
   *   TRUE on success, FALSE in case of an error.
   *
   * @throws ConfigStorageException
   */
  public function initializeStorage() {
    if (!db_table_exists($this->table, array('target' => $this->database))) {
      try {
        db_create_table($this->table, $this->schema($this->table));
      }
      catch (\Exception $e) {
        throw new ConfigStorageException(format_string('The database table %table could not be created: @error', array(
          '%table' => $config_directory,
          '@error' => $e->getMessage(),
        )), 0, $e);
      }
    }
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function isInitialized() {
    return db_table_exists($this->table, array('target' => $this->database));
  }

  /**
   * Returns the path to the configuration file.
   *
   * @return string
   *   The path to the configuration file.
   */
  public function getFilePath($name) {
    return 'db:/' . $this->database . '/' . $this->table . '/' . $name;
  }

  /**
   * {@inheritdoc}
   */
  public function exists($name) {
    try {
      $query = db_select($this->table, 'c', array('target' => $this->database))
        ->condition('c.name', $name);
      $query->addExpression('1');
      $value =  $query->execute()
        ->fetchField();
    }
    catch (\Exception $e) {
      // Happens where there is no database.  Return FALSE
      $value = FALSE;
    }

    return $value ? TRUE : FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function read($name) {
    if (!$this->exists($name)) {
      return FALSE;
    }
    $data = db_select($this->table, 'c', array('target' => $this->database))
      ->fields('c', array('data'))
      ->condition('c.name', $name)
      ->execute()
      ->fetchField();
    try {
      $data = $this->decode($data);
      // Remove the config name from the read configuration.
      if (isset($data['_config_name'])) {
        unset($data['_config_name']);
      }
    }
    // If an error occurs, catch and rethrow with the file name in the message.
    catch (ConfigStorageException $e) {
      throw new ConfigStorageReadException(format_string("The configuration file \"@filename\" is not properly formatted JSON.\n\nContents:\n<pre>@contents</pre>\n", array('@filename' => $name, '@contents' => $data)));
    }
    return $data;
  }

  /**
   * {@inheritdoc}
   */
  public function readMultiple(array $names) {
    $list = array();
    foreach ($names as $name) {
      if ($data = $this->read($name)) {
        $list[$name] = $data;
      }
    }
    return $list;
  }

  /**
   * {@inheritdoc}
   */
  public function write($name, array $data) {
    // Ensure that the config name is included in the written file.
    $data = array_merge(array('_config_name' => $name), $data);
    $data = $this->encode($data) . "\n";
    $file_path = $this->getFilePath($name);
    try {
      $result = db_merge($this->table, array('target' => $this->database))
        ->key(array('name' => $name))
        ->fields(array(
          'name' => $name,
          'data' => $data,
        ))
        ->execute();
      if ($result == MergeQuery::STATUS_INSERT) {
        db_update($this->table, array('target' => $this->database))
          ->fields(array('ctime' => time()))
          ->condition('name', $name)
          ->condition('ctime', 0)
          ->execute();
      }
    }
    catch (\Exception $e) {
      throw new ConfigStorageException('Failed to write configuration file: ' . $this->getFilePath($name), 0, $e);
    }
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function delete($name) {
    if (!$this->exists($name)) {
      return FALSE;
    }
    db_delete($this->table, array('target' => $this->database))
      ->condition('name', $name)
      ->execute();
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function rename($name, $new_name) {
    try {
      db_delete($this->table, array('target' => $this->database))
        ->condition('name', $new_name)
        ->execute();
      db_update($this->table, array('target' => $this->database))
        ->fields(array('name' => $new_name))
        ->condition('name', $name)
        ->execute();
    }
    catch (\Exception $e) {
      throw new ConfigStorageException('Failed to rename configuration file from: ' . $this->getFilePath($name) . ' to: ' . $this->getFilePath($new_name), 0, $e);
    }
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function getModifiedTime($name) {
    $data = db_select($this->table, 'c', array('target' => $this->database))
      ->fields('c', 'ctime')
      ->condition('c.name', $name)
      ->execute()
      ->fetchField();

    return empty($data) ? FALSE : $data;
  }

  /**
   * {@inheritdoc}
   */
  public function encode($data) {
    $contents = backdrop_json_encode($data, TRUE);
    if ($contents === FALSE) {
      throw new ConfigStorageException(t('The configuration string could not be parsed.'));
    }
    return $contents;
  }

  /**
   * {@inheritdoc}
   */
  public function decode($raw) {
    // Use json_decode() directly for efficiency.
    $contents = json_decode($raw, TRUE);
    if (is_null($contents)) {
      throw new ConfigStorageException('The configuration string could not be parsed.');
    }
    return $contents;
  }

  /**
   * {@inheritdoc}
   */
  public function listAll($prefix = '') {
    $results = db_select($this->table, 'c', array('target' => $this->database))
      ->fields('c', array('name'))
      ->condition('c.name', $prefix . '%', 'LIKE')
      ->execute()
      ->fetchAllAssoc('name', PDO::FETCH_ASSOC);
    return array_column($results, 'name');
  }

  /**
   * {@inheritdoc}
   */
  public function deleteAll($prefix = '') {
    $query = db_delete($this->table, array('target' => $this->database));
    if ($prefix) {
      $query->condition('name', $prefix . '%', 'LIKE');
    }
    $query->execute();
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function importArchive($file_uri) {
    $realpath = backdrop_realpath($file_uri);

    try {
      $archiver = new ArchiverTar($realpath);
      $archiver->extract($this->directory, $archiver->listContents());
    }
    catch (\Exception $e) {
      watchdog('config', 'Could not extract the archive @uri: @error', array('@uri' => $file_uri, '@error' => $e->getMessage()), WATCHDOG_ERROR);
      throw new ConfigStorageException($e->getMessage(), 0, $e);
    }
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function exportArchive($archive_file_uri) {
    $tmp_config_dir_path = file_create_filename('config', file_directory_temp());
    file_prepare_directory($tmp_config_dir_path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    $data = db_select($this->table, 'c', array('target' => $this->database))
      ->fields('c')
      ->execute()
      ->fetchAllAssoc('name', PDO::FETCH_ASSOC);
    foreach($data as $config_name => $row) {
      file_put_contents($tmp_config_dir_path . '/' . $config_name . '.json', $row['data']);
    }

    // And tar it up.
    $realpath = backdrop_realpath($archive_file_uri);
    $archiver = new ArchiverTar($archive_file_uri);
    $config_files = array();
    foreach (array_keys($data) as $config_name) {
      $config_files[] = $tmp_config_dir_path . '/' . $config_name . '.json';
    }
    $archiver->getArchive()->createModify($config_files, '', $tmp_config_dir_path);
  }
}
