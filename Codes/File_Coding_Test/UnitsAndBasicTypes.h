#ifndef __Enigma__Moez__Units_And_Basic_Types
#define __Enigma__Moez__Units_And_Basic_Types

#include <string>
using std::string;

typedef char Byte;
typedef unsigned char uByte;
typedef long int BigInt;

const BigInt SOFTWARE_VERSION			=		1;

const string FILESIGN			=	"ENIGMA_MOEZ_SIGN";
const string FILESIGN_COMPLEX		=	FILESIGN+"_COMPLEX";
const string FILESIGN_KEY		=	FILESIGN+"_KEY";
const string FILESIGN_KEY_BIN		=	FILESIGN_KEY+"_BIN";
const string FILESIGN_KEY_ASKI_HEX	=	FILESIGN_KEY+"_ASKI_HEX";
const BigInt Default_MetaData		=	0;
const string Head_Of_Chipher_Sign	=	"Cipher_Head";
const char Url_Directory_Tokenizer='/';

const Byte Float_Num_End			=		127;
const unsigned int Float_Num_Base		=		128+(int)Float_Num_End;

const unsigned int Default_Buffer_Length	=		1024;	//Unit: Byte
const unsigned int Default_Key_Length		=		32;
const unsigned int Default_Block_Length		=		16;
const unsigned int Default_Code_Buffer_Length	=		Default_Buffer_Length/Default_Block_Length;

const BigInt Default_Code_Option		=		0;

const BigInt Default_Algorithm_Mode		=		0;
#endif
