#ifndef __Engima__Moez__Hint_Functions
#define __Engima__Moez__Hint_Functions

#include "UnitsAndBasicTypes.h"
#include "File_Functions.h"
#include "Exception.h"
#include <string>
using namespace std;

bool HasHint(const string &url);

void ImportHint(ostream &fo, const string &hinturl);

void ExportHint(const string &EngimaFileUrl);
#endif
