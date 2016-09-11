// config.h
// Defines for haze. Options are in config.cpp

#ifndef __CONFIG_H
#define __CONFIG_H

#include<vector>
#include<string>

using namespace std;

#define HAZE_API_URL "http://api.nea.gov.sg/api/WebAPI/?dataset=psi_update&keyref="

// Type of value to pull
extern const string NEA_PSI_TYPE;

// Valid region checker
extern string NEA_REGION_DEFAULT;
extern const vector<string> NEA_REGIONS;

// The default API key to use. Leave null to require an API key.
extern string API_KEY_DEFAULT;

#endif