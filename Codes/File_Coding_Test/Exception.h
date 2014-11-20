#ifndef __Engima__Moez__Exceptions
#define __Engima__Moez__Exceptions

#include <string>
#include <map>
using namespace std;

class Exception
{
	public:
		Exception(int C);
		int Number(void) const;

	protected:
		int Code;
};

//Codes of errors:
const int File_Not_Exist		=		1;
const int File_Unable_To_Write		=		2;
const int File_Not_Ours			=		6;
const int File_Not_An_Enigma_Complex	=		7;
const int File_Not_An_Enigma_Key_File	=		8;

const int Bad_File_Url			=		11;
const int File_No_Hint			=		21;
const int File_No_Cipher		=		26;

const int Length_Zero			=		31;

const int Key_String_NoSupportedChar	=		36;

const int Coding_Unsuitable_Key		=		41;
const int Coding_Wrong_Password		=		42;
const int Coding_Cannot_Decode		=		46;

class ExceptionDescriber
{
	public:
		ExceptionDescriber(void);
		ExceptionDescriber(const ExceptionDescriber &C);
		~ExceptionDescriber(void);

		string Describe(int Code);
		string Describe(const Exception &E);

	private:
		map<int, string> Dcls;
};

#endif
