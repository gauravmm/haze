// apiparser.cpp
// API Parser

#include<iostream>
#include<string>
#include "apiparser.h"
#include "tinyxml2.h"
#include "hazecalc.h"

using namespace std;
using namespace tinyxml2;

#define CHECK_ELT(pR) if(!pR) { *err = 0xF0000 | XML_ERROR_FILE_READ_ERROR; return NULL; }

HazeData *parse_api(string *xmldata, string *region, int *err) {
	HazeData *rv = new struct HazeData();
	rv->region = region;
	XMLDocument doc;
	XMLError xmlerr = doc.Parse(xmldata->c_str());
	if(xmlerr) {
		*err = 0xF0000 | xmlerr;
		return NULL;
	}
	
	XMLNode *pRoot = doc.FirstChild();
	CHECK_ELT(pRoot)

	XMLElement *pItem = pRoot->FirstChildElement("item");
	CHECK_ELT(pItem)

	// Now we loop over the regions inside item

	XMLElement *pRegion = pItem->FirstChildElement("region");
	CHECK_ELT(pRegion)
	while(pRegion) {
		XMLElement *pId = pRegion->FirstChildElement("id");
		CHECK_ELT(pId)

		// If this is the region we want, then we go to the trouble of parsing the thingy
		if(!region->compare(pId->GetText())) {
			XMLElement *pRecord = pRegion->FirstChildElement("record");
			CHECK_ELT(pRecord)
			
			rv->timestamp = new string(pRecord->Attribute("timestamp"));

			HazeCalc hc = HazeCalc();

			XMLElement *pReading = pRecord->FirstChildElement("reading");
			CHECK_ELT(pReading)
			while(pReading) {
				const string type = string(pReading->Attribute("type"));
				float value = pReading->FloatAttribute("value");

				if(!NEA_PSI_TYPE.compare(type)) {
					rv->psi_read = value;
				}
				hc.take(type, value);

				pReading = pReading->NextSiblingElement("reading");
			}

			rv->psi_calc = hc.getAndReset();
		}
		pRegion = pRegion->NextSiblingElement("region");
	} 

	return rv;
}

void HazeData_free(HazeData *v) {
	delete v->timestamp;
	delete v;
}