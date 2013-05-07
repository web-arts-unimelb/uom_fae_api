<?php
/**
 * @file
 * Hooks provided by the Find an Expert API module.
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
