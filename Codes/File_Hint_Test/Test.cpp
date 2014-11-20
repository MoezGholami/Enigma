#include "UnitsAndBasicTypes.h"
#include "Hint_Functions.h"
#include "Exception.h"
#include <iostream>
using namespace std;

int main(void);
void ImportOptions(BigInt Opt, ostream &f);
int main(void)
{
	ExceptionDescriber Knower;

	try
	{
		string EngFile="A.Engima";

		 /*
			string HintFile="Hint.zip";
			fstream eo(EngFile.c_str(), ios::out | ios::binary);
			ImportHeadOfEngimaFile(eo);
			ImportHint(eo, HintFile);
			eo.close();
		// */

		// /*
			ExportHint(EngFile);
		// */
	}
	catch(const Exception &E)
	{
		cout<<Knower.Describe(E.Number())<<endl;
	}

	return 0;
}
void ImportOptions(BigInt Opt, ostream &f)
{
	WriteAFloatNum(f, Opt);
}






