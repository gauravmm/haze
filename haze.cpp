/* haze
 * PSI publisher
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "config.h"
#include "cmd.h"
#include "hazecalc.h"
#include "filedl.h"
#include "apiparser.h"

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
	struct HazeData *rv;
	
	if (err)
		goto err_label;

	rv = parse_api(xmldata, region, &err);

	// Produce output.
	if (!err)
		cout << fixed << setprecision(0) << ((compute)?rv->psi_calc:rv->psi_read) << endl;
	
	HazeData_free(rv);

err_label:
	delete xmldata;
	return err;
}
