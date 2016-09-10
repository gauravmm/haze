/*
 *
 */
#include <iostream>
#include "config.h"
#include "cmd.h"
#include "hazecalc.h"

using namespace std;

int main(int argc, char **argv) {
	// Prepare the default options
	int parserr = option_parse(argc, argv);
	if (parserr > 0) {
		return parserr;
	} else if (parserr < 0) { // If help is printed.
		return 0;
	}


	// HazeCalc hc;

	return 0;
}

