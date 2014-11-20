#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{
	char A[256], B[256];

	for(int i=-128; i<128; ++i)
		A[i+128]=(char)i;

	ifstream fin;
	fin.open("Testfile", ios::binary | ios::in);
	fin.read(B,256);
	fin.close();

	int i=0;
	for(i=0; i<256; i=i)
		if(B[i]==A[i])
		{
			cout<<B[i]<<' '<<i<<endl;
			++i;
		}

	cout<<endl<<i<<endl;

	return 0;
}
