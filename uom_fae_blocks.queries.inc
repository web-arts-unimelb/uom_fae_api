<?php
/**
 * @file
 * Define canned queries for FAE Blocks SparQL.
 */

/**
 * Current research grants for a given organisation.
 */
define('UOM_FAE_BLOCKS_ORGANISATION_GRANTS_CURRENT', '
SELECT
  ?grant ?grantLabel ?grantScheme ?dateStart ?dateEnd ?orgLabel ?person ?personLabel
WHERE {
  ?grant a vivo:Grant .
  ?grant vivo:administeredBy <:uri> .
  ?grant rdfs:label ?grantLabel .
  ?grant fae:scheme ?grantScheme .

  ?grant vivo:dateTimeInterval ?dateTimeInterval .
  ?dateTimeInterval vivo:start ?dateTimeStart .
  ?dateTimeInterval vivo:end ?dateTimeEnd .
  ?dateTimeStart vivo:dateTime ?dateStart .
  ?dateTimeEnd vivo:dateTime ?dateEnd .

  FILTER (?dateEnd >= ":dateEndT00:00:00Z"^^xsd:dateTime)

  OPTIONAL {
    ?grant vivo:grantAwardedBy ?org .
    ?org rdfs:label ?orgLabel .
  }
  OPTIONAL {
    ?grant vivo:contributingRole ?role .
    ?role vivo:investigatorRoleOf ?person .
    ?person rdfs:label ?personLabel .
  }
}

ORDER BY ASC(?dateTimeStart) ASC(?dateTimeEnd)');

/**
 * Past research grants for a given organisation.
 */
define('UOM_FAE_BLOCKS_ORGANISATION_GRANTS_PAST', '
SELECT
  ?grant ?grantLabel ?grantScheme ?dateStart ?dateEnd ?orgLabel ?person ?personLabel
WHERE {
  ?grant a vivo:Grant .
  ?grant vivo:administeredBy <:uri> .
  ?grant rdfs:label ?grantLabel .
  ?grant fae:scheme ?grantScheme .

  ?grant vivo:dateTimeInterval ?dateTimeInterval .
  ?dateTimeInterval vivo:start ?dateTimeStart .
  ?dateTimeInterval vivo:end ?dateTimeEnd .
  ?dateTimeStart vivo:dateTime ?dateStart .
  ?dateTimeEnd vivo:dateTime ?dateEnd .

  FILTER (?dateEnd <= ":dateEndT00:00:00Z"^^xsd:dateTime)

  OPTIONAL {
    ?grant vivo:grantAwardedBy ?org .
    ?org rdfs:label ?orgLabel .
  }
  OPTIONAL {
    ?grant vivo:contributingRole ?role .
    ?role vivo:investigatorRoleOf ?person .
    ?person rdfs:label ?personLabel .
  }
}

ORDER BY DESC(?dateTimeEnd) ASC(?dateTimeStart)');
