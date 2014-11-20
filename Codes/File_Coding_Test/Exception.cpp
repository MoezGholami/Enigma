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
	Dcls [	File_Not_Exist			]	=	"This file does not exist.";
	Dcls [	File_Not_Ours			]	=	"This file is not related to the Enigma.";
	Dcls [	File_Not_An_Enigma_Complex	]	=	"This file is not an Enigma complex file.";
	Dcls [	File_Not_An_Enigma_Key_File	]	=	"This file is not an Enigma key file.";
	Dcls [	File_Unable_To_Write		]	=	"Could not write in file.";
	Dcls [	Bad_File_Url			]	=	"Bad file url.";
	Dcls [	File_No_Hint			]	=	"This file has not hint file.";
	Dcls [	File_No_Cipher			]	=	"Could not find any encrypted data.";
	Dcls [	Length_Zero			]	=	"The size should be more than (equal to) one byte.";
	Dcls [	Key_String_NoSupportedChar	]	=	"Not supported character has been entered int the key";
	Dcls [	Coding_Unsuitable_Key		]	=	"The key does not fit to this process.";
	Dcls [	Coding_Wrong_Password		]	=	"Incorrect password.";
	Dcls [	Coding_Cannot_Decode		]	=	"This cipher has been created with another algorithm and cannot be decrypted with this algorithm.";
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

string ExceptionDescriber::Describe(const Exception &E)
{
	return Describe(E.Number());
}
