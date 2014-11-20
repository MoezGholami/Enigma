#ifndef __Enigma__Moez__File_Functions
#define __Enigma__Moez__File_Functions

#include "UnitsAndBasicTypes.h"
#include <fstream>
#include <string>
#include "Exception.h"
#include <vector>
#include "UtilityFunctions.h"

#include <iostream>
using namespace std;

bool FileExist(const string &url); /* Exs: . */
bool Url_Writable(const string &url); /* Exs: . */
inline bool CanBeRead_N_Bytes(fstream &fin, size_t N); /* Exs: . */
bool IsOurs(const string &url); /* Exs: File_Not_Exist. */
bool IsAnEnigmaComplexFile(const string &url); /* Exs: File_Not_Exist, File_Not_Ours. */
bool IsAnEnigmaKeyFile(const string &url); /* Exs: File_Not_Exist, File_Not_Ours. */
size_t SizeOfAFile(const string &url); /* Exs: . ios_base::failure */
size_t SizeOfAFstream(fstream &f); /* Exs: . ios_base::failure */

void SkipSign_Complex(fstream &fin); /* Exs: . ios_base::failure */
void SkipSign_Key(fstream &fin); /* Exs: . ios_base::failure */
void SkipAFloatSizedBlock(fstream &f); /* Exs: . ios_base::failure */
void IgnoreReadingNBytes(istream &in, unsigned char N); /* Exs: . ios_base::failure */
void IgnoreReadingAFloatNum(istream &f); /* Exs: . ios_base::failure */
void IgnoreUntilEOFOrASpecificCharacter(istream &in, char c); /* Exs: . ios_base::failure */
void GoToNextLine(istream &in); /* Exs: . ios_base::failure */
void GoToHeadOfStartOfCipther(istream &in); /* Exs: . ios_base::failure */

void ImportHeadOfEnigmaComplexFile(ostream &f); /* Exs: . ios_base::failure */
void ImportHeadOfBinKeyFile(ostream &f); /* Exs: . ios_base::failure */
void ImportHeadOfStartOfCipther(ostream &f); /* Exs: . ios_base::failure */

void PasteAStreamToAStream(istream &in, size_t RemaindToCopy, ostream &out, size_t BufferSize = Default_Buffer_Length);  /* Exs: Length_Zero. ios_base::failure */


BigInt ReadAFloatNum(istream &f); /* Exs: . ios_base::failure */
string ReadAString_Float(istream &in); /* Exs: . ios_base::failure */
string ReadAString(istream &in, size_t Size); /* Exs: . ios_base::failure */


void WriteAFloatNum(ostream &f, BigInt A); /* Exs: . ios_base::failure */
void ImportAnString(ostream &fo, const string &Str); /* Exs: . ios_base::failure */


string NameFromUrl(string url); /* Exs: Bad_File_Url. ios_base::failure */
void MakeAWritableUrlOfThisIfNot(string &url); /* Exs: . */
	void SetHeadAndTailOfAString_FirsGivenString(const string &Name, string &Head, string &Tail, const string &T); /* Exs: . */
#endif
