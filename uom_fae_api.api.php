<?php
/**
 * @file
 * Hooks provided by the Find an Expert API module.
 */

/**
 * @defgroup uom_fae_api_hooks Find an Expert API hooks
 * @{
 * Hooks that can be implemented by other modules in order to implement the
 * Find an Expert API.
 */

/**
 * Allows the query and query args to be modified.
 *
 * This hook is executed before the query args are replaced into the
 * inline placeholders in the query.
 *
 * @param $query
 *   The SparQL query string with placeholders.
 * @param $args
 *   A keyed array of query arguments where the array key is the placeholder
 *   string in the query and the array value is the data that should be
 *   substituted for it in the query.
 *
 * @see uom_fae_api_uom_fae_api_query_alter()
 */
function hook_uom_fae_api_query_alter(&$query, &$args) {
  $query = $query . '# Just adding a :comment.';

  $args += array(':comment' => t('comment'));
}

/**
 * Allows the query result to be modified.
 *
 * This hook is executed after the query has run and before the results are
 * returned to the caller.
 *
 * @param $result
 *   A keyed array of query arguments where the array key is the placeholder
 *   string in the query and the array value is the data that should be
 *   substituted for it in the query.
 */
function hook_uom_fae_api_query_result_alter(&$result) {
  unset($result['result']['rows'][0]);
}

/**
 * Describes callback functions to Find an Expert API.
 *
 * @return
 *   An associative array describing the callback functions. Primary key is
 *   the name of the function that should be called to retrieve and theme
 *   data from Find an Expert. The value for the key entry is a translated
 *   string describing the callback function.
 */
function hook_uom_fae_api_callbacks() {
  $callbacks['uom_fae_api_research'] = t('Research Grants');
  return $callbacks;
}

/**
 * @}
 */

/**
 * @TODO: Add examples.
 *
 * @defgroup uom_fae_api About UoM FaE API
 * @{
 * @TODO: Explanation
 *
 * @code
 * function mymodule_uom_fae_api_callbacks(() {
 *   return array('mymodule_expert_info' => t('Information about a person'));
 * }
 *
 * function mymodule_expert_info() {
 *   $query = ...;
 *
 *   $data = uom_fae_api_query($query, $args);
 *   return theme('mymodule_theme_hook, $data['result']);
 * }
 * @endcode
 *
 * @}
 */
