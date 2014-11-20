#ifndef __Engima__Moez__Units_And_Basic_Types
#define __Engima__Moez__Units_And_Basic_Types

#include <string>
using std::string;

typedef char Byte;
typedef long int BigInt;

const string FILESIGN="ENGIMA_MOEZ_SIGN";
const char Url_Directory_Tokenizer='/';

const Byte Float_Num_End	=		127;
const int Float_Num_Base	=		128+(int)Float_Num_End;

const int Default_Buffer_Length	=		1024;	//Unit: Byte
#endif
