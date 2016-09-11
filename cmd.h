// cmd.h
// Commandline options

#include <string>

using namespace std;

extern string *apikey;
extern string *region;
extern bool compute;

int option_parse(int argc, char **argv);
