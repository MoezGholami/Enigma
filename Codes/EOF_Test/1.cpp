#include <fstream>
#include <string>
using namespace std;

int main(void);

int main(void)
{
	char A[256];

	for(int i=-128; i<128; ++i)
		A[i+128]=(char)i;

	fstream fout;
	fout.open("Testfile", ios::out | ios::binary);
	fout.write(A,256);
	fout.close();

	return 0;
}
