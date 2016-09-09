/* 
 * config.h
 * 
 * Basic options for haze.
 */

#include <map>
#include <string>
#include <vector>

using namespace std;

#define HAZE_API_URL "http://api.nea.gov.sg/api/WebAPI/?dataset=psi_update&keyref=%s"
#define HAZE_CONFIG  "~/.config/haze"

#define NEA_HAZE_TABLE_ENTRIES 6
extern map<string, vector<float>> NEA_HAZE_TABLE;

#define NEA_PSI_TYPE "NPSI"
