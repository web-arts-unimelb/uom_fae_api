<?php
/**
 * @file
 */

/**
 * Module settings.
 */
function uom_fae_api_admin_form() {
  $form = array();

  $form['uom_fae_api_endpoint'] = array(
    '#title' => t('SparQL Endpoint'),
    '#description' => t('Enter the URL for the SparQL endpoint that provides Find an Expert information.'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => variable_get('uom_fae_api_endpoint', UOM_SPARQL_ENDPOINT),
  );

  $period = drupal_map_assoc(array(0, 60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval');
  $period[0] = '<' . t('none') . '>';
  $form['uom_fae_api_cache'] = array(
    '#type' => 'select',
    '#title' => t('SparQL query cache lifetime'),
    '#default_value' => variable_get('uom_fae_api_cache', 0),
    '#options' => $period,
    '#description' => t('Cached queries will not be re-sent to the configured endpoint until this much time has elapsed.')
  );

  $form['#validate'][] = 'uom_foa_api_admin_form_validate';
  $form['#submit'][] = 'uom_foa_api_admin_form_submit';

  return system_settings_form($form);
}

/**
 * Validate the settings form.
 */
function uom_foa_api_admin_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['uom_fae_api_endpoint']) && !valid_url($form_state['values']['uom_fae_api_endpoint'], TRUE)) {
    form_set_error('uom_fae_api_endpoint', t('Please enter a valid endpoint URL or leave the field blank to use the default.'));
  }
}

/**
 * Rebuild the menu cache on submit.
 */
function uom_foa_api_admin_form_submit($form, &$form_state) {
  variable_set('menu_rebuild_needed', TRUE);
}
