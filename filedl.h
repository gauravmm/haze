// filedl.h
// Download a file via CURL

#include <string>

using namespace std;

// NOTE: the returned pointer has to be deleted upon completion.
string *download_file(string url, int *status);
