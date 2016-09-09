// config.cpp
// Here we store the values in the tables we need.

#include "config.h"

// All entries in the table indicate the MAX value in the cell.
// we assume that all tables begin at 0
map<string, vector<float>> NEA_HAZE_TABLE = {
	{ "PM25_24HR", {   12,  55, 150,  250,  350,  500  } },
	{ "PM10_24HR", {   50, 150, 350,  420,  500,  600  } },
	{ "SO2_24HR",  {   80, 365, 800, 1600, 2100, 2620  } },
	{ "CO_8HR_MAX",{    5,  10,  17,   34,   46,   57.5 } },
	{ "O3_8HR_MAX",{  118, 157, 235,  785,  980, 1180  } },
	{ "NO2_1HR_MAX",{   0,  0, 1130, 2260, 3000, 3750  } }
};
