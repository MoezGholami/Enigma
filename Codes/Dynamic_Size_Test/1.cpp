#include <fstream>
using namespace std;

int main(void)
{
	char A[]={
		'E','N','G','I','M','A','_','M','O','E','Z','_','S','I','G','N'
		,-127,127,-127,127
		};

	fstream f;
	f.open("A.hhh", ios::binary | ios::out);

	f.write(A, sizeof(A)/sizeof(char));

	f.close();

	return 0;
}
