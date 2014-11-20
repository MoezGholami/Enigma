#include "UtilityFunctions.h"

BigInt Pow(BigInt Base, unsigned int Power)
{
	int Result=1;
	for(unsigned int i=0; i < Power; Result*=Base, ++i);
	return Result;
}

void uByte2Byte(const uByte *in, Byte *out, size_t Size)
{
	for(size_t i=0; i < Size; ++i)
		out[i] = (Byte)((int)in[i]-128);
}

void Byte2uByte(const Byte *in, uByte *out, size_t Size)
{
	for(size_t i=0; i < Size; ++i)
		out[i] = (uByte)((int)in[i]+128);
}

template<typename T>
void Vector2DynamicArr(const vector<T> &V, T* &Arr)
{
	if(V.size()==0)
	{
		Arr=NULL;
		return ;
	}
	Arr = new T[V.size()];
	for(unsigned int i=0; i < V.size(); ++i)
		Arr[i]=V[i];
	return ;
}
	template void Vector2DynamicArr<Byte>(const vector<Byte> &V, Byte* &Arr);

template<typename T>
void Arr2Vector(T *Arr, vector<T> &V, unsigned int Size)
{
	V.clear();
	if(Size==0)
		return ;
	V.resize(Size);
	if(Size != V.size())	throw bad_alloc();
	for(unsigned int i=0; i < Size; ++i)
		V[i]=Arr[i];
}
	template void Arr2Vector<Byte>(Byte *Arr, vector<Byte> &V, unsigned int Size);

bool GetTheNthBit_FromRight_FromZero(const BigInt &A, unsigned int DigNum)
{
	return (bool)((A/Pow(2, DigNum))%2);
}

void SetTheNthBit_FromRight_FromZero(BigInt &A, unsigned int DigNum, bool in)
{
	A = ( Pow(2, DigNum+1)*(A/Pow(2, DigNum+1)) ) + ( ((BigInt)((int)(in)))*Pow(2, DigNum) ) + ( A%(Pow(2,DigNum)) );
	return ;
}

bool IsAHexDigit(char A)
{
	return ('A'<=A && A<='F') || ('a'<=A && A<='f') || ('0'<=A && A<='9');
}

unsigned int HexDig(char A)
{
	if('A'<=A && A<='F')
		return ((unsigned int)(A-'A')+10);
	if('a'<=A && A<='f')
		return ((unsigned int)(A-'a')+10);
	if('0'<=A && A<='9')
		return (unsigned int)(A-'0');

	return 0;
}

void InitRandom(unsigned int seed)
{
	srand(seed);
}

int Random(int Min, int Max)
{
	if(Min>Max)
		swap(Min,Max);
	if((Max-Min)==0)
		Min=0, Max=100;
	return ( (rand()%(Max-Min)) + Min);
}

string operator+(const string &S, const float &N)
{
	ostringstream o;
	o<<N;
	return (S+o.str());
}

string operator+(const float &N, const string &S)
{
	string T="";
	T=T+N;
	return (T+S);
}
