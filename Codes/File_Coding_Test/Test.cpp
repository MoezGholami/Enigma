#include <string>
#include <iostream>
using namespace std;

int main(void);
void XXX(void);

int main(void)
{
	try
		{XXX();}
	catch(const int A)
		{cout<<A<<" has been catched\n";}

	return 0;
}

void XXX(void)
{
	cout<<"before throwing a number\n";
	throw 1;
}
