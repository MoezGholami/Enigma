#include "Exception.h"

Exception::Exception(int C)
{
	Code=C;
}

int Exception::Number(void) const
{
	return Code;
}

ExceptionDescriber::ExceptionDescriber(void)
{
	Dcls [	File_Not_Exist		]	=	"This file does not exist.";
	Dcls [	File_Not_Ours		]	=	"This file is not related to the Engima.";
	Dcls [	File_Unable_To_Write	]	=	"Could not write in file.";
	Dcls [	Bad_File_Url		]	=	"Bad file url.";
	Dcls [	File_No_Hint		]	=	"This file has not hint file.";
}

ExceptionDescriber::ExceptionDescriber(const ExceptionDescriber &C)
{
	Dcls=C.Dcls;
}

ExceptionDescriber::~ExceptionDescriber(void)
{
	Dcls.clear();
}

string ExceptionDescriber::Describe(int Code)
{
	if(Dcls.find(Code)==Dcls.end())
		return "We have no exception with this code.";
	return Dcls[Code];
}
