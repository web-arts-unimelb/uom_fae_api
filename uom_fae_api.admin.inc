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

  $cache = variable_get('cache_lifetime', 0);
  if (!empty($cache)) {
    $form['uom_fae_api_cache'] = array(
      '#markup' => t('Caching is enabled. Drupal will cache API responses for at least @interval.', array('@interval' => format_interval($cache))),
    );
  }
  else {
    $form['uom_fae_api_cache'] = array(
      '#markup' => t('Caching is disabled. You can enable it by setting a minimum cache lifetime at !link.', array('!link' => l('performance settings', 'admin/config/development/performance'))),
    );
  }

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
