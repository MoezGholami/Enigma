#ifndef __Enigma__Moez__Hint_Functions
#define __Enigma__Moez__Hint_Functions

#include "UnitsAndBasicTypes.h"
#include "File_Functions.h"
#include "Exception.h"
#include <string>
using namespace std;

bool HasHint(const string &url); /* Exs: File_Not_Exist, File_Not_Ours File_Not_An_Enigma_Complex. */

void ImportHint(const string &CmplxURL, const string &hinturl); /* Exs: File_Unable_To_Write, File_Not_Exist. ios_base::failure*/
void InsertHint(ostream &fo, const string &hinturl); /* Exs: File_Not_Exist. ios_base::failure*/

void ExportHint(const string &EnigmaFileUrl); /* Exs: File_Not_Exist, File_Not_Ours File_Not_An_Enigma_Complex, File_No_Hint. ios_base::failure*/

void SkipSignAndHint(fstream &f); /* Exs: . ios_base::failure*/
#endif
