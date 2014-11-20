#include "Hint_Functions.h"
#include "Exception.h"
#include "AES.h"
#include <iostream>
#include <string>
using namespace std;

const string COMPLEXFILE	=	"A.Enigma";
const string HINTFILE		=	"Hint.zip";
const string CONTENTFILE	=	"Content.zip";
const string PASSWORD		=	"F14 TOMCAT";

int main(void);
void Read(void);

int main(void)
{
	ExceptionDescriber Knower;
	bool NoError=true;
	try
	{
		Read();
	}
	catch(const Exception &E)
	{
		cout<<Knower.Describe(E)<<endl;
		NoError=false;
	}

	if(NoError)
		cout<<"Finished with no error.\n";

	return 0;
}

void Read(void)
{
	ExportHint(COMPLEXFILE);

	Key Kelid; Kelid.SetByAskiString(PASSWORD); Kelid.Resize(32);
	DE_AES RamzGosha(COMPLEXFILE, Kelid);
	RamzGosha.Decode();
}
