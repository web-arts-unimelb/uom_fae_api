<?php
/**
 * @file
 * Define canned queries for FAE SparQL.
 */

define('FAE_QUERY_PREFIX', '
PREFIX dc:    <http://purl.org/dc/elements/1.1/>
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
  ?image ?email ?phone ?roomLabel ?buildingLabel ?supervisor
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
    <:uri> fae:hasWorkLocation ?room.
    ?room rdfs:label ?roomLabel.
  }
  OPTIONAL {
    ?location vivo:roomWithinBuilding ?building.
    ?building rdfs:label ?buildingLabel.
  }
} LIMIT 1');

define('FAE_PERSON_QUERY', '
SELECT
  ?availableForSup ?supervisorText1 ?overviewText1 ?webpage ?researchOverview ?hasMediaOnlyContact ?email
WHERE {
  <:uri> rdf:type vivo:FacultyMember.
  OPTIONAL {
   <:uri> fae:availableForSupervision ?availableForSup
  }
  OPTIONAL {
    <:uri>  fae:supervisorText1 ?supervisorText1
  }
  OPTIONAL {
    <:uri>  fae:overviewText1 ?overviewText1
  }
  OPTIONAL {
    <:uri>  fae:webpage ?webpage
  }
  OPTIONAL {
    <:uri>  vivo:researchOverview ?researchOverview
  }
  OPTIONAL {
    <:uri>  fae:hasMediaOnlyContact ?hasMediaOnlyContact
  }
  OPTIONAL {
    <:uri>  vivo:email ?email
  }
}');

define('FOA_PUBLICATIONS_QUERY', '
SELECT DISTINCT
  ?publication ?pubtitle ?pubtype ?dateValue ?doi ?pageStart ?pageEnd ?edition ?isbn13 ?volume
WHERE {
  <:uri> vivo:authorInAuthorship ?authorship .
  ?authorship vivo:linkedInformationResource ?publication .
  ?publication rdfs:label ?pubtitle .
  ?publication rdf:type ?pubtype .
  ?publication vivo:dateTimeValue ?dateTimeValue .
  ?dateTimeValue vivo:dateTime ?dateValue .
  OPTIONAL {
    ?publication bibo:doi ?doi
  }
  OPTIONAL {
    ?publication bibo:pageStart ?pageStart
  }
  OPTIONAL {
    ?publication bibo:pageEnd ?pageEnd
  }
  OPTIONAL {
    ?publication bibo:edition ?edition
  }
  OPTIONAL {
    ?publication bibo:isbn13 ?isbn13
  }
  OPTIONAL {
    ?publication bibo:volume ?volume
  }
  FILTER regex(?pubtype, "findanexpert")
}');
