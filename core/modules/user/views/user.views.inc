<?php
/**
 * @file
 * Provide views data and handlers for user.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function user_views_data() {
  // ----------------------------------------------------------------
  // users table

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['users']['table']['group']  = t('User account');

  $data['users']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('User account'),
    'help' => t('Users who have created accounts on your site.'),
    'access query tag' => 'user_access',
  );
  $data['users']['table']['entity type'] = 'user';


  $data['users']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
    'file' => array(
      'table' => 'file',
      'field' => 'uid',
    ),
  );

  // uid
  $data['users']['uid'] = array(
    'title' => t('Uid'),
    'help' => t('The user account ID.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // display this field in the summary
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'title' => t('Content authored'),
      'help' => t('Relate content to the user account of its creator. This relationship will create one record for each content item created by the user account.'),
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'uid',
      'field' => 'uid',
      'label' => t('nodes'),
    ),
  );

  // uid_raw
  $data['users']['uid_raw'] = array(
    'help' => t('The raw numeric user account ID.'),
    'real field' => 'uid',
    'filter' => array(
      'title' => t('The user account ID'),
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // uid
  $data['users']['uid_representative'] = array(
    'relationship' => array(
      'title' => t('Representative node'),
      'label'  => t('Representative node'),
      'help' => t('Obtains a single representative node for each user account, according to a chosen sort criterion.'),
      'handler' => 'views_handler_relationship_groupwise_max',
      'relationship field' => 'uid',
      'outer field' => 'users.uid',
      'argument table' => 'users',
      'argument field' =>  'uid',
      'base'   => 'node',
      'field'  => 'nid',
    ),
  );

  // uid
  $data['users']['uid_current'] = array(
    'real field' => 'uid',
    'title' => t('Current'),
    'help' => t('Filter the view to the currently logged in user account.'),
    'filter' => array(
      'handler' => 'views_handler_filter_user_current',
      'type' => 'yes-no',
    ),
  );

  // name
  $data['users']['name'] = array(
    'title' => t('Username'), // The item it appears as on the UI,
    'help' => t('The username for the user account or author.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user_name',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'title' => t('Name (raw)'),
      'help' => t('The username for the user account or author. This filter does not check if the user account exists and allows partial matching. Does not utilize autocomplete.')
    ),
  );

  // mail
  // Note that this field implements field level access control.
  $data['users']['mail'] = array(
    'title' => t('Email'), // The item it appears as on the UI,
    'help' => t('Email address for a given user account. This field is normally not disclosed, so be cautious when using it.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user_mail',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // language
  $data['users']['language'] = array(
    'title' => t('Language'), // The item it appears as on the UI,
    'help' => t('The language for the user account.'),
    'field' => array(
      'handler' => 'views_handler_field_user_language',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_node_language',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_language',
    ),
  );

  // picture
  $data['users']['picture_fid']['moved to'] = array('users', 'picture');
  $data['users']['picture'] = array(
    'title' => t('Picture'),
    'help' => t("The user account picture, if allowed."), // The help that appears on the UI,
    // Information for displaying the uid
    'field' => array(
      'handler' => 'views_handler_field_user_picture',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has avatar'),
      'type' => 'yes-no',
    ),
  );

  // link
  $data['users']['view_user'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the user account.'),
      'handler' => 'views_handler_field_user_link',
    ),
  );

  // created field
  $data['users']['created'] = array(
    'title' => t('Created date'), // The item it appears as on the UI,
    'help' => t('The date the user account was created.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['users']['created_fulldate'] = array(
    'title' => t('Created date'),
    'help' => t('Date in the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['users']['created_year_month'] = array(
    'title' => t('Created year + month'),
    'help' => t('Date in the form of YYYYMM.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['users']['timestamp_year']['moved to'] = array('users', 'created_year');
  $data['users']['created_year'] = array(
    'title' => t('Created year'),
    'help' => t('Date in the form of YYYY.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['users']['created_month'] = array(
    'title' => t('Created month'),
    'help' => t('Date in the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['users']['created_day'] = array(
    'title' => t('Created day'),
    'help' => t('Date in the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['users']['created_week'] = array(
    'title' => t('Created week'),
    'help' => t('Date in the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  // Changed field.
  $data['users']['changed'] = array(
    // The item it appears as on the UI.
    'title' => t('Changed date'),
    // The help that appears on the UI.
    'help' => t('The date the user was changed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['users']['changed_fulldate'] = array(
    'title' => t('Changed date'),
    'help' => t('Date in the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['users']['changed_year_month'] = array(
    'title' => t('Changed year + month'),
    'help' => t('Date in the form of YYYYMM.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['users']['changed_year'] = array(
    'title' => t('Changed year'),
    'help' => t('Date in the form of YYYY.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['users']['changed_month'] = array(
    'title' => t('Changed month'),
    'help' => t('Date in the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['users']['changed_day'] = array(
    'title' => t('Changed day'),
    'help' => t('Date in the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['users']['changed_week'] = array(
    'title' => t('Changed week'),
    'help' => t('Date in the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  // access field
  $data['users']['access'] = array(
    'title' => t('Last access'), // The item it appears as on the UI,
    'help' => t("The user account's last access date."), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // login field
  $data['users']['login'] = array(
    'title' => t('Last login'), // The item it appears as on the UI,
    'help' => t("The user account's last login date."), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // active status
  $data['users']['status'] = array(
    'title' => t('Active'), // The item it appears as on the UI,
    'help' => t('Whether a user account is active or blocked.'), // The help that appears on the UI,
     // Information for displaying a title as a field
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'active-blocked' => array(t('Active'), t('Blocked')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'active-blocked',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // log field
  $data['users']['signature'] = array(
    'title' => t('Signature'), // The item it appears as on the UI,
    'help' => t("The user account's signature."), // The help that appears on the UI,
     // Information for displaying a title as a field
    'field' => array(
      'handler' => 'views_handler_field_markup',
      'format' => filter_fallback_format(),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['users']['edit_node'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the user account.'),
      'handler' => 'views_handler_field_user_link_edit',
    ),
  );

  $data['users']['cancel_node'] = array(
    'field' => array(
      'title' => t('Cancel link'),
      'help' => t('Provide a simple link to cancel the user account.'),
      'handler' => 'views_handler_field_user_link_cancel',
    ),
  );

  $data['users']['data'] = array(
    'title' => t('Data'),
    'help' => t('Provide serialized data of the user account'),
    'field' => array(
      'handler' => 'views_handler_field_serialized',
    ),
  );

  $data['users']['bulk_form'] = array(
    'title' => t('Bulk operations'),
    'help' => t('Provides a checkbox on each row and a form for executing bulk actions on user accounts.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'views_handler_field_bulk_form',
      'click sortable' => FALSE,
    ),
  );

  // ----------------------------------------------------------------------
  // users_roles table

  $data['users_roles']['table']['group']  = t('User account');

  // Explain how this table joins to others.
  $data['users_roles']['table']['join'] = array(
     // Directly links to users table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['users_roles']['table']['default_relationship'] = array(
    'node' => array(
      'table' => 'node',
      'field' => 'uid',
    ),
    'node_revision' => array(
      'table' => 'node_revision',
      'field' => 'uid',
    ),
  );

  $data['users_roles']['role'] = array(
    'title' => t('Roles'),
    'help' => t('Roles that a user account has been assigned.'),
    'field' => array(
      'handler' => 'views_handler_field_user_roles',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_roles',
      'numeric' => TRUE,
      'allow empty' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_users_roles',
      'empty field name' => t('No role'),
      'zero is null' => TRUE,
      'numeric' => TRUE,
    ),
  );

  $data['users_roles']['permissions'] = array(
    'title' => t('Permissions'),
    'help' => t('The user account permissions.'),
    'real field' => 'role',
    'field' => array(
      'handler' => 'views_handler_field_user_permissions',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_permissions',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function user_views_plugins() {
  return array(
    'module' => 'views', // This just tells our themes are elsewhere.
    'row' => array(
      'user' => array(
        'title' => t('User accounts'),
        'help' => t('Display the user accounts with standard user account view.'),
        'handler' => 'views_plugin_row_user_view',
        'base' => array('users'), // only works with 'users' as base.
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-users',
      ),
    ),
    'argument default' => array(
      'user' => array(
        'title' => t('User account ID from URL'),
        'handler' => 'views_plugin_argument_default_user',
        'path' => backdrop_get_path('module', 'views') . '/modules/user', // not necessary for most modules
      ),
      'current_user' => array(
        'title' => t('User account ID from logged in person'),
        'handler' => 'views_plugin_argument_default_current_user',
        'path' => backdrop_get_path('module', 'views') . '/modules/user', // not necessary for most modules
      ),
    ),
    'argument validator' => array(
      'user' => array(
        'title' => t('User account'),
        'handler' => 'views_plugin_argument_validate_user',
        'path' => backdrop_get_path('module', 'views') . '/modules/user', // not necessary for most modules
      ),
    ),
  );
}

/**
 * Allow replacement of current user ID so we can cache these queries.
 */
function user_views_query_substitutions($view) {
  global $user;
  return array('***CURRENT_USER***' => intval($user->uid));
}
