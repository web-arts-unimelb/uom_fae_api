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
PREFIX vitro: <http://vitro.mannlib.cornell.edu/ns/vitro/0.7#>
PREFIX vitro-public: <http://vitro.mannlib.cornell.edu/ns/vitro/public#>
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
 * Note: it doesn't have <:uri> rdf:type vivo:FacultyMember.
 */
define('UOM_FAE_PERSON_CONTACT', '
SELECT
  ?email ?phone ?supervisor ?thumbnail ?image ?actualFilePart ?room ?building
WHERE {
  OPTIONAL { <:uri> vivo:email ?email. }
  OPTIONAL { <:uri> fae:webpage ?webpage. }
  OPTIONAL { <:uri> vivo:phoneNumber ?phone. }
  OPTIONAL { <:uri> fae:availableForSupervision ?supervisor. }
  OPTIONAL {
    <:uri> vitro-public:mainImage ?file.
    ?file vitro-public:thumbnailImage ?thumbnail.
		?thumbnail vitro-public:directDownloadUrl ?actualFilePart.
    ?file vitro-public:downloadLocation ?image.
  }
  OPTIONAL {
    <:uri> fae:hasWorkLocation ?location.
    ?location vivo:roomWithinBuilding ?bldg .
    ?location rdfs:label ?room .
    ?bldg rdfs:label ?building .
  }
} LIMIT 1');

// Note: remove <http://www.findanexpert.unimelb.edu.au/individual/person625285> rdf:type vivo:FacultyMember
// It doesn't have vivo:FacultyMember
define('UOM_FAE_PERSON_OVERVIEW', '
SELECT
  ?overviewText1 ?overviewText2 ?overviewText3 ?overviewText4
WHERE {
  <:uri>  fae:overviewText1 ?overviewText1

	OPTIONAL {
    <:uri>  fae:overviewText2 ?overviewText2
  }
	OPTIONAL {
    <:uri>  fae:overviewText3 ?overviewText3
  }
	OPTIONAL {
    <:uri>  fae:overviewText4 ?overviewText4
  }
} LIMIT 1');

/*
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
*/


define('UOM_FAE_PERSON_AFFILIATION', '

SELECT
  ?org_label ?role_label ?the_start_time ?the_end_time
WHERE {
  <:uri> vivo:hasMemberRole ?role .
  ?role vivo:roleIn ?role_org .
  ?role rdfs:label ?role_label .
  ?role_org rdfs:label ?org_label .
  
  OPTIONAL {
  	?role vivo:dateTimeInterval ?date_time_value .
  
		OPTIONAL {	
  		?date_time_value vivo:start ?start_time .
  		?start_time vivo:dateTime ?the_start_time .
		}

		OPTIONAL {
			?date_time_value vivo:end ?end_time .
  		?end_time vivo:dateTime ?the_end_time .
		}
  }
}

');


/*
define('UOM_FAE_PERSON_PUBLICATIONS', '
SELECT DISTINCT
  ?publication ?article ?targetPersonName ?title ?type ?dateValue ?publishOrg ?doi ?edition ?parent ?isbn13 ?volume ?issueNum ?myIssueNum
WHERE {
  <:uri> vivo:authorInAuthorship ?authorship .
	<:uri> rdfs:label ?targetPersonName .
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
    ?article bibo:edition ?edition
  }
	OPTIONAL {
		?article fae:parentTitle ?parent
	}
  OPTIONAL {
    ?article bibo:isbn13 ?isbn13
  }
  OPTIONAL {
    ?article bibo:volume ?volume
  }
	OPTIONAL {
    ?article bibo:number ?issueNum
  }
	OPTIONAL {
    ?article bibo:issue ?myIssueNum
  }
  FILTER regex(?type, "findanexpert")
}');
*/


define('UOM_FAE_PERSON_PUBLICATIONS', '

SELECT
	(SAMPLE(?title) AS ?the_title)
	(SAMPLE(?article) AS ?pub_uri)
	(SAMPLE(?type) AS ?the_type)
	(SAMPLE(?date_value) AS ?the_date_value)

	(SAMPLE(?publish_org) AS ?the_publish_org)
	(SAMPLE(?published_in) AS ?the_published_in)
	(SAMPLE(?parent_title) AS ?the_parent_title)
	(SAMPLE(?doi) AS ?the_doi)

	(SAMPLE(?edition) AS ?the_edition)
	(SAMPLE(?isbn13) AS ?the_isbn13)
	(SAMPLE(?volume) AS ?the_volume)
	(SAMPLE(?issue_num) AS ?the_issue_num)

	(SAMPLE(?issue) AS ?the_issue)
	(SAMPLE(?page_start) AS ?the_page_start)
	(SAMPLE(?page_end) AS ?the_page_end)

	(group_concat(distinct ?author_label ; separator="|" ) as ?the_author_label)
	(group_concat(distinct ?author_posi_uri ; separator="|" ) as ?authors)
	(group_concat(distinct ?the_author_link ; separator="|" ) as ?the_author_links)

	(group_concat(distinct ?editor_label ; separator="|" ) as ?the_editor_label)
	(group_concat(distinct ?editor_posi_uri ; separator="|" ) as ?editors)
	(group_concat(distinct ?the_editor_link ; separator="|" ) as ?the_editor_links)

where { 
	<:uri> vivo:authorInAuthorship ?authorship .
	?authorship vivo:linkedInformationResource ?article .
	?article rdfs:label ?title.
	?article vitro:mostSpecificType ?type .

	?article vivo:dateTimeValue ?date_time_value .
	?date_time_value vivo:dateTime ?date_value .	
	
	OPTIONAL {
		?article vivo:publisher ?publisher .
  	?publisher rdfs:label ?publish_org .
	}

	OPTIONAL {
    ?article vivo:hasPublicationVenue ?pub_venue .
    ?pub_venue rdfs:label ?published_in .
  }

	OPTIONAL {
		?article fae:parentTitle ?parent_title
	}
	
	OPTIONAL {
    ?article bibo:doi ?doi
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
    ?article bibo:number ?issue_num
  }
	OPTIONAL {
    ?article bibo:issue ?issue
  }
	OPTIONAL {
    ?article bibo:pageStart ?page_start
  }
  OPTIONAL {
    ?article bibo:pageEnd ?page_end
  }  

	# Get authors
	?article vivo:informationResourceInAuthorship ?author_posi_uri .
	FILTER regex(STR(?author_posi_uri), "Y$", "i") .
	?author_posi_uri rdfs:label ?author_label .

	optional {
		?author_posi_uri vivo:linkedAuthor ?author_link .
	}
	BIND ( IF( !bound(?author_link), "empty", STR(?author_link)) AS ?the_author_link ) .

	# Get editors
	optional {
		?article vivo:informationResourceInAuthorship ?editor_posi_uri .
		FILTER regex(STR(?editor_posi_uri), "N$", "i") .	
		
		optional {
			?editor_posi_uri rdfs:label ?editor_label .
		}

		optional {
			?editor_posi_uri vivo:linkedAuthor ?editor_link .   
		}
	}
	BIND ( IF( !bound(?editor_link), "empty", STR(?editor_link)) AS ?the_editor_link ) .

}
group by ?article

');



// http://stackoverflow.com/questions/5161568/how-to-properly-use-sparql-optional-to-retrieve-attributes-for-a-resource-that-m
// http://www.cambridgesemantics.com/semantic-university/sparql-nuts-and-bolts
/*
define('UOM_FAE_PUBLICATION_AUTHOR_PUB_POSIS', '
SELECT
  ?pubPosi
WHERE {
  <:uri> vivo:informationResourceInAuthorship ?pubPosi.
}
ORDER BY ?pubPosi 
');
*/

/*
define('UOM_FAE_PUBLICATION_AUTHOR_PERSON_LINK', '
SELECT
  ?personLink
WHERE {
  <:uri> vivo:linkedAuthor ?personLink.
}
');
*/

/*
define('UOM_FAE_PUBLICATION_AUTHOR_NAME_LABEL', '
SELECT
  ?personLabel
WHERE {
  <:uri> rdfs:label ?personLabel.
}   
');
*/

/*
define('UOM_FAE_PUBLICATION_AUTHOR_NAME_LABEL_1', '
SELECT
  ?personLabel
WHERE {
  <:uri> vivo:authorNameAsListed ?personLabel.
}   
');
*/

/*
define('UOM_FAE_PUBLICATION_EDITOR_NAME', '
SELECT
	?editorName
WHERE {
	<:uri> rdfs:label ?editorName .
}  
');
*/

// http://answers.semanticweb.com/questions/3245/convert-string-to-number
/*
define('UOM_FAE_PUBLICATION_PAGE_START_END', '
SELECT
  ?pageStart ?pageEnd
WHERE {
  OPTIONAL {
    <:uri> bibo:pageStart ?pageStart .
  }
  OPTIONAL {
    <:uri> bibo:pageEnd ?pageEnd .
  }
}
');
*/

define('UOM_FAE_PERSON_RESEARCH', '
SELECT
  ?grant ?grantLabel ?grantScheme ?roleLabel ?orgLabel ?dateStart ?dateEnd
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


define('UOM_FAE_PERSON_EXTRA_GRANT', '
SELECT
	?extraGrantText1 ?extraGrantText2 ?extraGrantText3 ?extraGrantText4
WHERE {
	<:uri> fae:extraGrantText1 ?extraGrantText1

	OPTIONAL {
		<:uri> fae:extraGrantText2 ?extraGrantText2
	}
	OPTIONAL {
		<:uri> fae:extraGrantText3 ?extraGrantText3
	}
	OPTIONAL {
		<:uri> fae:extraGrantText4 ?extraGrantText4
	}
}');


define('UOM_FAE_PERSON_AWARDS', '
SELECT
  ?award ?awardLabel ?orgLabel ?dateValue
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

/*
define('UOM_FAE_PERSON_LINKAGES', '
SELECT
  ?org ?orgLabel ?roleLabel ?dateValue
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
*/

define('UOM_FAE_PERSON_LINKAGES_NO_ORG_LABEL', '
SELECT
	?org ?roleLabel ?dateValue	
WHERE {
	<:uri> fae:internationalLinkageRole ?role .
	?role rdfs:label ?roleLabel .
	?role vivo:roleIn ?org .
	OPTIONAL {
    ?role vivo:dateTimeValue ?dateTimeValue .
    ?dateTimeValue vivo:dateTime ?dateValue .
  }
}');

define('UOM_FAE_PERSON_LINKAGES_ORG_LABEL', '
SELECT
  ?orgLabel  
WHERE {
  <:uri> rdfs:label ?orgLabel . 
}');


/*
 * Fetch supervision information for a specific person.
 * Note: it doesn't have <:uri> rdf:type vivo:FacultyMember.
 */
define('UOM_FAE_PERSON_SUPERVISION', '
SELECT
  ?supervisor ?supervisorText1
WHERE {
  OPTIONAL { <:uri> fae:availableForSupervision ?supervisor. }
  OPTIONAL { <:uri> fae:supervisorText1 ?supervisorText1. }
}');

define('UOM_FAE_ORGANISATION_GRANTS', '
SELECT
  ?grant ?grantLabel ?grantScheme ?dateStart ?dateEnd ?orgLabel ?person ?personLabel
WHERE {
  ?grant a vivo:Grant .
  ?grant vivo:administeredBy <:uri> .
  ?grant rdfs:label ?grantLabel .
  ?grant fae:scheme ?grantScheme .
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
  OPTIONAL {
    ?grant vivo:contributingRole ?role .
    ?role vivo:investigatorRoleOf ?person .
    ?person rdfs:label ?personLabel .
  }
}');

/*
 * Fetch qualification information for a specific person.
 */
define('UOM_FAE_PERSON_QUALIFICATIONS', '
SELECT
  ?orgLabel ?degreeLabel ?dateEnd
WHERE {
  ?training vivo:educationalTrainingOf <:uri> .

  ?training vivo:trainingAtOrganization ?org .
  ?training vivo:degreeEarned ?degree .

  ?org rdfs:label ?orgLabel .
  ?degree rdfs:label ?degreeLabel .

  OPTIONAL {
		?training vivo:dateTimeInterval ?dateTimeInterval .
    ?dateTimeInterval vivo:end ?dateTimeEnd .
    ?dateTimeEnd vivo:dateTime ?dateEnd .
  }
}
ORDER BY ASC(?dateTimeEnd)');
