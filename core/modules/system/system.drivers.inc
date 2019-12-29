<?php

function system_admin_drivers_page() {

  $drivers = silkscreen_driver_list();

  $driver_types = array(
    'database' => t('Database'),
    'cache' => t('Cache'),
    'config' => t('Config storage'),
  );


  $headers = array(
    t('Machine Name'),
    t('Driver Name'),
    t('Description'),
    t('Version'),
    t('Driver Type'),
  );

  foreach ($drivers as $machine_name => $driver) {
    $driver_info = $driver->info;
    if ($driver_info['hidden']) {
      continue;
    }

    $types = array();
    foreach($driver_types as $dtype => $dname) {
      if (array_key_exists($dtype . '_backend', $driver_info)) {
        $types[] = $dname;
      }
    }

    if (empty($types)) {
      continue;
    }

    $rows[$machine_name] = array(
      empty($driver_info['configure']) ? $machine_name : l($machine_name, $driver_info['configure']),
      $driver_info['name'],
      $driver_info['description'],
      $driver_info['version'],
      implode(', ', $types),
    );
  }

  ksort($rows);

  $render = array(
    '#theme' => 'table',
    '#header' => $headers,
    '#rows' => $rows,
    '#empty' => t('No drivers present.'),
  );

  return $render;
}
