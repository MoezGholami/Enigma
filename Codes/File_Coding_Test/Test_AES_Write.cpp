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
void Write(void);

int main(void)
{
	ExceptionDescriber Knower;
	bool NoError=true;
	try
	{
		Write();
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

void Write(void)
{
	ImportHint(COMPLEXFILE, HINTFILE);

	Key Kelid; Kelid.SetByAskiString(PASSWORD); Kelid.Resize(32);
	EN_AES RamzKon(COMPLEXFILE, CONTENTFILE, 1, Kelid);
	RamzKon.Encode();
}
