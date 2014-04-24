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

/**
 * Publications by people associated with a given organisation.
 */
define('UOM_FAE_BLOCKS_ORGANISATION_PUBLICATIONS', '
SELECT
  ?authorName ?authorRank ?person ?personLabel ?positionLabel ?orgLabel ?dateValue ?publication ?article ?parentTitle ?title ?publishOrg ?doi ?pageStart ?pageEnd ?edition ?isbn13 ?volume ?type ?myIssueNum
WHERE {
  ?person vivo:personInPosition ?position .
  ?position vivo:positionInOrganization <:uri> .
  <:uri> rdfs:label ?orgLabel .
  ?position rdfs:label ?positionLabel .
  ?person rdfs:label ?personLabel .
  ?person vivo:authorInAuthorship ?authorship .

  ?authorship vivo:authorNameAsListed ?authorName .
  ?authorship vivo:authorRank ?authorRank .

  ?authorship vivo:linkedInformationResource ?article .
  ?article rdfs:label ?title .
  ?article rdf:type ?type .

  ?article vivo:dateTimeValue ?dateTimeValue .
  ?dateTimeValue vivo:dateTime ?dateValue .

  ?article vivo:publisher ?publisher .
  ?publisher rdfs:label ?publishOrg .

	OPTIONAL {
		?article fae:parentTitle ?parentTitle .
	}
  OPTIONAL {
    ?article vivo:hasPublicationVenue ?pubVenue .
    ?pubVenue rdfs:label ?publication .
  }
  OPTIONAL {
    ?article bibo:doi ?doi
  }
  OPTIONAL {
    ?article bibo:pageStart ?pageStart
  }
  OPTIONAL {
    ?article bibo:pageEnd ?pageEnd
  }
  OPTIONAL {
    ?article bibo:edition ?edition
  }
  OPTIONAL {
    ?article bibo:isbn13 ?isbn13
  }
  OPTIONAL {
    ?article bibo:volume ?volume
  }
  OPTIONAL {
    ?article bibo:issue ?myIssueNum
  }

  FILTER (?dateValue >= ":prevYear-01-01T00:00:00Z"^^xsd:dateTime)
  FILTER (?dateValue  < ":currYear-01-01T00:00:00Z"^^xsd:dateTime)
  FILTER regex(?type, "findanexpert")
}
ORDER BY ASC(?title)');
