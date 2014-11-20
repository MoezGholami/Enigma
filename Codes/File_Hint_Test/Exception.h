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

	private:
		int Code;
};

//Codes of errors:
const int File_Not_Exist	=		1;
const int File_Not_Ours		=		2;
const int File_Unable_To_Write	=		3;

const int Bad_File_Url		=		11;
const int File_No_Hint		=		21;

class ExceptionDescriber
{
	public:
		ExceptionDescriber(void);
		ExceptionDescriber(const ExceptionDescriber &C);
		~ExceptionDescriber(void);

		string Describe(int Code);

	private:
		map<int, string> Dcls;
};

#endif
