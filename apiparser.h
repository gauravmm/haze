// apiparser.h
// API Parser

#include<string>
#include"config.h"

using namespace std;

struct HazeData {
	float psi_read;
	float psi_calc;
	string *timestamp;
	string *region;
};

HazeData *parse_api(string *data, string *region, int *rv);
void HazeData_free(HazeData *);