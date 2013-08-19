<?php
/**
 * @file
 * Define canned queries for FAE SparQL.
 */

define('FAE_QUERY_PREFIX', 'PREFIX dc:    <http://purl.org/dc/elements/1.1/>
PREFIX rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
PREFIX rdfs:  <http://www.w3.org/2000/01/rdf-schema#>
PREFIX xsd:   <http://www.w3.org/2001/XMLSchema#>
PREFIX owl:   <http://www.w3.org/2002/07/owl#>
PREFIX fn:    <http://www.w3.org/2005/xpath-functions#>
PREFIX ouext: <http://oracle.com/semtech/jena-adaptor/ext/user-def-function#>
PREFIX oext:  <http://oracle.com/semtech/jena-adaptor/ext/function#>
PREFIX ORACLE_SEM_FS_NS: <http://oracle.com/semtech#timeout=:timeout,qid=:qid,STRICT_DEFAULT=F,GRAPH_MATCH_UNNAMED=T>
PREFIX fae:   <http://www.findanexpert.unimelb.edu.au/ontology/>
PREFIX vivo:  <http://vivoweb.org/ontology/core#>
PREFIX bibo:  <http://purl.org/ontology/bibo/>
PREFIX foaf:  <http://xmlns.com/foaf/0.1/>');

define('FAE_ORGANISATION_QUERY', '
SELECT
  ?org ?orgLabel
WHERE {
  ?org rdf:type vivo:Department. ?org rdfs:label ?orgLabel.
}');

define('FAE_ORGANISATION_PEOPLE_QUERY', '
SELECT
  ?person ?personLabel ?positionLabel  ?orgLabel ?vstart ?vend
WHERE {
  ?person vivo:personInPosition ?position .
  ?position vivo:positionInOrganization <:uri>.
  <:uri> rdfs:label ?orgLabel.
  ?position rdfs:label ?positionLabel.
  ?person rdfs:label ?personLabel
  OPTIONAL {
    ?person vivo:dateTimeInterval ?dateTimeInterval.
    ?dateTimeInterval vivo:start ?vstartI.
    ?vstartI vivo:dateTime ?vstart
  }
  OPTIONAL {
    ?person vivo:dateTimeInterval ?dateTimeInterval.
    ?dateTimeInterval vivo:end ?vendI.
    ?vendI vivo:dateTime ?vend
  }
}');

/*
 * Fetch contact information for a specific person, so it can be
 * displayed in a block.
 */
define('UOM_FAE_PERSON_CONTACT', '
SELECT
  ?image ?email ?phone ?room ?building ?supervisor
WHERE {
  <:uri> rdf:type vivo:FacultyMember.
  OPTIONAL { <:uri> vivo:email ?email. }
  OPTIONAL { <:uri> fae:webpage ?webpage. }
  OPTIONAL { <:uri> vivo:phoneNumber ?phone. }
  OPTIONAL { <:uri> fae:availableForSupervision ?supervisor. }
  OPTIONAL {
    <:uri> fae:mainImage ?file.
    ?file fae:downloadLocation ?image.
  }
  OPTIONAL {
    <:uri> fae:hasWorkLocation ?roomItem.
    ?roomItem rdfs:label ?room.
  }
  OPTIONAL {
    ?location vivo:roomWithinBuilding ?buildingItem.
    ?buildingItem rdfs:label ?building.
  }
} LIMIT 1');

define('UOM_FAE_PERSON_OVERVIEW', '
SELECT
  ?overviewText1
WHERE {
  <:uri> rdf:type vivo:FacultyMember.
  OPTIONAL {
    <:uri>  fae:overviewText1 ?overviewText1
  }
}');

define('UOM_FAE_PERSON_AFFILIATION', '
SELECT
  ?orgLabel ?roleLabel ?dateValue
WHERE {
  <:uri> vivo:hasMemberRole ?role .
  ?role vivo:roleIn ?roleOrg .
  ?role rdfs:label ?roleLabel .
  ?roleOrg rdfs:label ?orgLabel .
  OPTIONAL {
    ?role vivo:dateTimeValue ?dateTimeValue .
    ?dateTimeValue vivo:dateTime ?dateValue .
  }
}');

define('UOM_FAE_PERSON_PUBLICATIONS', '
SELECT DISTINCT
  ?publication ?article ?title ?type ?dateValue ?publishOrg ?doi ?pageStart ?pageEnd ?edition ?isbn13 ?volume
WHERE {
  <:uri> vivo:authorInAuthorship ?authorship .
  ?authorship vivo:linkedInformationResource ?article .
  ?article rdfs:label ?title .
  ?article rdf:type ?type .
  ?article vivo:dateTimeValue ?dateTimeValue .
  ?dateTimeValue vivo:dateTime ?dateValue .
  ?article vivo:publisher ?publisher .
  ?publisher rdfs:label ?publishOrg .
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
  FILTER regex(?type, "findanexpert")
}');

define('UOM_FAE_PERSON_RESEARCH', '
SELECT
  ?grantLabel ?grantScheme ?roleLabel ?orgLabel ?dateStart ?dateEnd
WHERE {
  ?grant a vivo:Grant .
  ?grant vivo:contributingRole ?role .
  ?role vivo:investigatorRoleOf <:uri> .
  ?grant rdfs:label ?grantLabel .
  ?grant fae:scheme ?grantScheme .
  OPTIONAL {
    ?role rdfs:label ?roleLabel .
  }
  OPTIONAL {
    ?grant vivo:dateTimeInterval ?dateTimeInterval .
    ?dateTimeInterval vivo:start ?dateTimeStart .
    ?dateTimeInterval vivo:end ?dateTimeEnd .
    ?dateTimeStart vivo:dateTime ?dateStart .
    ?dateTimeEnd vivo:dateTime ?dateEnd .
  }
  OPTIONAL {
    ?grant vivo:grantAwardedBy ?org .
    ?org rdfs:label ?orgLabel .
  }
}');

define('UOM_FAE_PERSON_AWARDS', '
SELECT
  ?awardLabel ?orgLabel ?dateValue
WHERE {
  <:uri> vivo:awardOrHonor ?award .
  ?award rdfs:label ?awardLabel .
  ?award vivo:awardConferredBy ?org .
  ?org rdfs:label ?orgLabel .
  OPTIONAL {
    ?award vivo:dateTimeValue ?dateTimeValue .
    ?dateTimeValue vivo:dateTime ?dateValue .
  }
}');

define('UOM_FAE_PERSON_LINKAGES', '
SELECT
  ?orgLabel ?roleLabel ?dateValue
WHERE {
  <:uri> fae:internationalLinkageRole ?role .
  ?role rdfs:label ?roleLabel .
  ?role vivo:roleIn ?org .
  ?org rdfs:label ?orgLabel .
  OPTIONAL {
    ?role vivo:dateTimeValue ?dateTimeValue .
    ?dateTimeValue vivo:dateTime ?dateValue .
  }
}');

/*
 * Fetch supervision information for a specific person.
 */
define('UOM_FAE_PERSON_SUPERVISION', '
SELECT
  ?supervisor ?supervisorText1
WHERE {
  <:uri> rdf:type vivo:FacultyMember.
  OPTIONAL { <:uri> fae:availableForSupervision ?supervisor. }
  OPTIONAL { <:uri> fae:supervisorText1 ?supervisorText1. }
}');
