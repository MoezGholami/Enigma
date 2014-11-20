#ifndef __Engima__Moez__File_Functions
#define __Engima__Moez__File_Functions

#include "UnitsAndBasicTypes.h"
#include <fstream>
#include <string>
#include "Exception.h"
#include <vector>
using namespace std;

bool FileExist(const string &url);
bool IsOurs(const string &url);
BigInt SizeOfAFile(const string &url);

void SkipSign(fstream &fin);
void SkipSignAndHint(fstream &fin);
void SkipAFloatSizedBlock(fstream &f);
void IgnoreReadingAFloatNum(istream &f);

void ImportHeadOfEngimaFile(ostream &f);

void PasteAStreamToAStream(istream &in, BigInt RemaindToCopy, ostream &out, int BufferSize = Default_Buffer_Length);


BigInt ReadAFloatNum(istream &f);
string ReadAString_Float(istream &in);
string ReadAString(istream &in, BigInt Size);


void WriteAFloatNum(ostream &f, BigInt A);
void ImportAnString(ostream &fo, const string &Str);


string NameFromUrl(string url);
#endif
