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
/*
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
*/

define('UOM_FAE_BLOCKS_ORGANISATION_PUBLICATIONS', '
SELECT
	?article
	(SAMPLE(?title) AS ?the_title)
	(SAMPLE(?type) AS ?the_type)

	(group_concat(distinct ?author_label ; separator="|" ) as ?the_author_label)
	(group_concat(distinct ?author_posi_uri ; separator="|" ) as ?authors)

	(group_concat(distinct ?editor_label ; separator="|" ) as ?the_editor_label)
	(group_concat(distinct ?editor_posi_uri ; separator="|" ) as ?editors)
		
WHERE {
	<http://www.findanexpert.unimelb.edu.au/individual/org94> rdfs:label ?org_label .
  ?position vivo:positionInOrganization <:uri> .
  ?person_uri vivo:personInPosition ?position .
  ?person_uri vivo:authorInAuthorship ?pub_posi . 
  
  ?pub_posi vivo:linkedInformationResource ?article .
  ?article rdfs:label ?title .
  ?article vitro:mostSpecificType ?type .
  
  ?article vivo:dateTimeValue ?date_time_value .
  ?date_time_value vivo:dateTime ?date_value .	
  
	# Get authors
	?article vivo:informationResourceInAuthorship ?author_posi_uri .
	FILTER regex(STR(?author_posi_uri), "Y$", "i")
	?author_posi_uri rdfs:label ?author_label .
  
  optional {
		?author_posi_uri vivo:linkedAuthor ?author_link .
	}

  # Get editors
  optional {
		?article vivo:informationResourceInAuthorship ?editor_posi_uri .
		FILTER regex(STR(?editor_posi_uri), "N$", "i") .
		?editor_posi_uri rdfs:label ?editor_label .
	}
	
  FILTER (?date_value >= ":prevYear-01-01T00:00:00Z"^^xsd:dateTime)
  FILTER (?date_value  < ":currYear-01-01T00:00:00Z"^^xsd:dateTime)
}
GROUP BY ?article

');
