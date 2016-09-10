/*
 *
 */

#include <iostream>
#include <string>

#include "config.h"
#include "cmd.h"
#include "hazecalc.h"
#include "filedl.h"

using namespace std;

int run(float *valptr);

int main(int argc, char **argv) {
	// Prepare the default options
	int parserr = option_parse(argc, argv);
	if (parserr > 0) {
		return parserr;
	} else if (parserr < 0) { // If help is printed.
		return 0;
	}

	int err = 0;
	string api_call = string(HAZE_API_URL).append(*apikey);
	string *xmldata = download_file(api_call, &err);
	
	if (!err) {
		
	}

	delete xmldata;
	return err;
}
