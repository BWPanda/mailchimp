<?php
/**
 * Implements hook_entity_info().
 */
function mailchimp_lists_entity_info() {
  $return = array(
    'mailchimp_list' => array(
      'label' => t('MailChimp List'),
      'controller class' => 'EntityAPIController',
      'base table' => 'mailchimp_lists',
      'uri callback' => 'mailchimp_list_uri',
      'fieldable' => FALSE,
      'entity keys' => array(
        'id' => 'id',
        'label' => 'label',
      ),
      'bundle keys' => array(
        'bundle' => 'type',
      ),
      'bundles' => array(
        'mailchimp_list'=> array(
          'label' => 'MailChimp List',
        ),
      ),
      'view modes' => array(
        'full' => array(
          'label' => t('Complete List'),
          'custom settings' => FALSE,
        ),
      ),
    ),
  );

  return $return;
}


/**
 * Loads a list by ID.
 */
function mailchimp_lists_load($list_id) {
  $lists = mailchimp_lists_load_multiple(array($list_id), array());
  return $lists ? reset($lists) : FALSE;
}

/**
 * Loads multiple registrations by ID or based on a set of matching conditions.
 *
 * @see entity_load()
 *
 * @param $list_ids
 * @param $conditions
 *   An array of conditions on the {redhen_contact} table in the form
 *     'field' => $value.
 * @param $reset
 *   Whether to reset the internal contact loading cache.
 *
 * @return
 *   An array of contact objects indexed by registration_id.
 */
function mailchimp_lists_load_multiple($list_ids = array(), $conditions = array(), $reset = FALSE) {
  if (empty($list_ids)) {
    $list_ids = FALSE;
  }

  return entity_load('mailchimp_list', $list_ids, $conditions, $reset);
}

/**
 * Deletes multiple lists by ID.
 *
 * @param $list_ids
 *   An array of contact IDs to delete.
 *
 * @return
 *   TRUE on success, FALSE otherwise.
 */
function mailchimp_lists_delete_multiple($list_ids) {
  return entity_get_controller('mailchimp_list')->delete($list_ids);
}

/**
 * Saves a registration.
 *
 * @param $registration
 *   The full contact object to save.
 *
 * @return
 *   The saved registration object.
 */
function mailchimp_lists_save($list) {
  $list->updated = REQUEST_TIME;
  // Set the creation timestamp if not set.
  if (!isset($list->created) || empty($list->created)) {
    $list->created = REQUEST_TIME;
  }
  return entity_get_controller('mailchimp_list')->save($list);
}