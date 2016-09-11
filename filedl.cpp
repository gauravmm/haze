// filedl.cpp
// Download a file via CURL

#include "filedl.h"
#include <curl/curl.h>

static size_t callback(void *contents, size_t size, size_t nmemb, void *userp){
	string *s = (string *)userp;
	size_t realsize = size * nmemb;
	s->append((char *)contents, realsize);
	return realsize;
}

string *download_file(string url, int *status) {
	string *rv = new string();

	// Configure curl with the api URL
	curl_global_init(CURL_GLOBAL_ALL ^ CURL_GLOBAL_SSL);
	CURL *curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)rv);

	CURLcode res = curl_easy_perform(curl_handle);
	if(res != CURLE_OK) {
		*status = 11;
		// cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
	}

	// Clean up the request
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();

	return rv;
}