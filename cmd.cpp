// cmd.cpp
// Commandline options
#include "cmd.h"
#include "config.h"
#include <iostream>
#include <getopt.h>


string *apikey = &API_KEY_DEFAULT;
string *region = &NEA_REGION_DEFAULT;
bool compute = false;

// Commandline arguments
void print_options() {
	cout << "haze, gets the latest PSI using the NEA API." << endl;
	cout << "Prints the 3-hour average by default." << endl;
	cout << "Usage: haze [OPTIONS]" << endl;
	cout << "" << endl;
	cout << "OPTIONS:" << endl;
	cout << "  -k --api-key=KEY   Use this API key." << endl;
	cout << "  -r --region=REGION The region to report. One of: ";
	for(const string s: NEA_REGIONS) {
		cout << s << " ";
	}
	cout << endl;
	cout << "  -c --calculated    Calculate from first principles instead of using the 3-hour average." << endl;
	cout << "  -h --help          Print this and exit." << endl;
}

void print_options_err(const string& errstr) {
	cout << errstr << endl << endl;
	print_options();
}


extern char *optarg;
extern int optind, opterr, optopt;
char short_options[] = "hk::r:c";
struct option long_options[] = {
	{"api-key",    optional_argument, NULL, 'k'},
	{"region",     required_argument, NULL, 'r'},
	{"calculated", no_argument,       NULL, 'c'},
	{"help",       no_argument,       NULL, 'h'},
	{NULL,         0,                 NULL,  0 }
};

bool NEA_REGION_VALID(string *s) {
	for(string c : NEA_REGIONS) {
		if(s->compare(c) == 0)
			return true;
	}
	return false;
}

int option_parse(int argc, char **argv) {
	opterr = 0;
	int c;
	while((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
		switch(c) {
			case 'k':
				if(!optarg) {
					print_options_err("Unrecognized argument for -k");
					return 3;
				}
				apikey = new string(optarg);
				break;

			case 'r':
				if(!optarg) {
					print_options_err("Unrecognized argument for -r");
					return 2;
				}

				region = new string(optarg);
				if(!NEA_REGION_VALID(region)) {
					print_options_err("Invalid region specified.");
					return 4;
				}
				
				break;

			case 'c':
				compute = true;
				break;

			case 'h':
				print_options();
				return -1;
				break;

			default:
				print_options_err("haze -- unrecognized option.");
				return 1;
		}
	}

	// Check apikey
	if(apikey->empty()) {
		cout << "No api key provided. Use -k or specify in config.cpp" << endl;
		return 5;
	}

	return 0;
}
