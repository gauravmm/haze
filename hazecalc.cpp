// hazecalc.cpp
// Here we calculate the haze using NEA Haze tables.

#include <iostream>
#include "hazecalc.h"

const map<string, const vector<float>> HazeCalc::NEA_HAZE_TABLE = {
	{ "PM25_24HR",  {  0,  12,  55,  150,  250,  350,  500   } },
	{ "PM10_24HR",  {  0,  50, 150,  350,  420,  500,  600   } },
	{ "SO2_24HR",   {  0,  80, 365,  800, 1600, 2100, 2620   } },
	{ "CO_8HR_MAX", {  0,   5,  10,   17,   34,   46,   57.5 } },
	{ "O3_8HR_MAX", {  0, 118, 157,  235,  785,  980, 1180   } },
	{ "NO2_1HR_MAX",{ -1,  -1,  -1, 1130, 2260, 3000, 3750   } }
};

const vector<float> HazeCalc::NEA_HAZE_TABLE_PSI = {
	0, 50, 100, 200, 300, 400, 500
};

// Constructor
HazeCalc::HazeCalc() {
	this->currentPSI = 0;
}

// Takes a key and a value, updates the internal
// state with the new PSI.
void HazeCalc::take(const string& key, float value) {
	if(key.empty())
		return;

	// Search for this key in the table
	auto it = NEA_HAZE_TABLE.find(key);
	if(it == NEA_HAZE_TABLE.end()) {
		// If we don't have a corresponding entry, we drop it.
		return;
	}
	const vector<float> column = it->second;

	// Now we find which slot the entry corresponds to.
	auto j = NEA_HAZE_TABLE_PSI.rbegin();
	auto i = column.rbegin();
	while (i != column.rend()) {
		if (value > *i) {
			break;
		}
		++i;
		++j;
	}

	if (i == column.rend()) {
		// The value is too low, so we assume zero, and so
		// the value of currentPSI is unchanged.
		return;
	} else if (i == column.rbegin()) {
		// The value is too high, so we set the current PSI.
		// to the maximum
		this->currentPSI = *j;
		return;
	}
	
	// Now we get the current and previous table entries and perform linear
	// interpolation.
	float currEntry = *(i - 1);
	float prevEntry = *i;
	float currPSI   = *(j - 1);
	float prevPSI   = *j;

	// Make sure that we are allowed to calculate the haze for this interval.
	// This handles the NO2 case
	if (prevEntry < 0)
		return;

	float val = (value - prevEntry)/(currEntry - prevEntry) * (currPSI - prevPSI) + prevPSI;

	this->currentPSI = max(val, this->currentPSI);
}

float HazeCalc::getAndReset() {
	float temp = this->currentPSI;
	this->currentPSI = 0;
	return temp;
}
