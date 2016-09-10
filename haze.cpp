/*
 *
 */

#include <iostream>
#include <curl/curl.h>

#include "config.h"
#include "cmd.h"
#include "hazecalc.h"

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

	float val;
	int dlerr = run(&val);
	if (dlerr)
		return dlerr;

	return 0;
}

int run(float *valptr) {
	// Prepare the API call URL	
	string api_call = string(HAZE_API_URL).append(*apikey);

	// Configure curl with the api URL
	curl_global_init(CURL_GLOBAL_ALL ^ CURL_GLOBAL_SSL);
	CURL *curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, api_call.c_str());

	// Prepare the XML parser

	// Configure the parser
	// curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, parseStreamCallback);
	// curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)parser);
	
	// 
	CURLcode res = curl_easy_perform(curl_handle);
	if(res != CURLE_OK) {
		cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
	}

	// Clean up the request
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();

	return 0;
}
