#include "Key.h"

Key::Key(unsigned int S_BY, bool sym, bool pri)
{
		InitWithSize_ForConstructor(S_BY, sym, pri);
}

Key::Key(const string &K, bool sym, bool pri)	//From a 01 string.
{
	InitWithString_ForConstructor(K, sym, pri);
}

Key::Key(const string &K, unsigned int S_BY, bool sym, bool pri)	//From a 01 string.
{
	InitWithStringAndSize_ForConstructor(K, S_BY, sym, pri);
}

Key::Key(const Key &A)
{
	InitWithSize_ForConstructor(Default_Key_Length, true, true);
	Copy(A);
}

Key::~Key(void)
{
	Close();
}

void Key::SetBy01String(const string &K)
{
	if(!IsAGood01StringKey(K))
		throw Exception(Key_String_NoSupportedChar);
	vector<uByte> Prepared = CapsulateA01String(K);
	HashAuByteContainerToTheKeyArray(Prepared, Prepared.size());

	return ;
}

void Key::SetByHexString(const string &K)
{
	if(!IsAGoodHexStringKey(K))
		throw Exception(Key_String_NoSupportedChar);
	vector<uByte> Prepared = CapsulateAHexString(K);
	HashAuByteContainerToTheKeyArray(Prepared, Prepared.size());

	return ;
}

void Key::SetByAskiString(const string &K)
{
	if(IsAGoodAskiStringKey(K))
		throw Exception(Key_String_NoSupportedChar);
	HashAuByteContainerToTheKeyArray(K, K.size());

	return ;
}

void Key::SetSymmetry(bool in)
{
	Symmetric=in;
	Private=Private || in;
	return ;
}

void Key::SetItIsPrivate(bool in)
{
	Private=in;
	Symmetric=Symmetric || !in;
	return ;
}

void Key::Resize(unsigned int New_Size)
{
	if(New_Size==0)
		throw Exception(Length_Zero);

	if(New_Size == Length)
		return ;

	uByte *Tmp = new uByte[New_Size];
	unsigned int TLength = Length;
	Length = New_Size;

	swap(Bytes, Tmp);
	HashAuByteContainerToTheKeyArray(Tmp, TLength);

	delete[] Tmp;

	return ;
}

const uByte* Key::USign_Key(void) const
{
	return Bytes;
}

uByte* Key::USign_Key_Changable(void)
{
	return Bytes;
}

unsigned int Key::Size(void) const
{
	return Length;
}

string Key::ToString_Hex(void) const
{
	string Result="";
	uByte T;
	for(unsigned int i=0; i < Length; ++i)
	{
		T=Bytes[i];
		Result+=( (((unsigned int)T)/16) < 10 ? (char)(((unsigned int)T)/16)+'0': (char)(((unsigned int)T)/16 - 10)+'A');
		Result+=( (((unsigned int)T)%16) < 10 ? (char)(((unsigned int)T)%16)+'0': (char)(((unsigned int)T)%16 - 10)+'A');
		Result+=' ';
	}
	return Result;
}

string Key::ToString_Bin(void) const
{
	string Result="";
	uByte T;
	for(unsigned int i=0; i < Length; ++i)
	{
		T=Bytes[i];
		for(unsigned int j=1,k=2; j < 256; j*=2, k*=2)
			Result+= ( (char)( ( ((unsigned int)T)%k )/j) +'0') ;
	}
	return Result;
}

bool Key::IsSymmetric(void) const
{
	return Symmetric;
}

bool Key::IsPrivate(void) const
{
	return Private;
}

Key& Key::operator=(const Key &A)
{
	if(this == &A)
		return *this;
	Copy(A);
	return *this;
}

void Key::Close(void)
{
	if(Bytes != NULL)
	{
		delete[] Bytes;
		Bytes = NULL;
	}
	Length = 0;
	return ;
}

template<typename Container_With_Brackets>
void Key::HashAuByteContainerToTheKeyArray(const Container_With_Brackets &Prepared, unsigned int Selected_Length_From_Begining)
{
	for(unsigned int i=0; i < Length; ++i)
		Bytes[i]=Prepared[ ( i%Selected_Length_From_Begining ) ];
	return ;
}

inline void Key::InitWithSize_ForConstructor(unsigned int S_BY, bool sym, bool pri)
{
	if(S_BY==0)
		throw Exception(Length_Zero);

	Bytes = new uByte[S_BY];
	Length = S_BY;

	for(unsigned int i=0; i < S_BY; ++i)
		Bytes[i] = 0;

	SetSymmetry(sym);
	SetItIsPrivate(pri);
	return ;
}

inline void Key::InitWithStringAndSize_ForConstructor(const string &K, unsigned int S_BY, bool sym, bool pri)
{
	InitWithSize_ForConstructor(S_BY, sym, pri);
	SetBy01String(K);
	return ;
}

inline void Key::InitWithString_ForConstructor(const string &K, bool sym, bool pri)
{
	InitWithStringAndSize_ForConstructor(K, K.size(), sym, pri);
	return ;
}

istream& operator>>(istream &sin, Key &input)
{
	unsigned int TSize=0;
	bool B=false;
	string H="";

	IgnoreUntilEOFOrASpecificCharacter(sin, ':');
	sin>>TSize;
	input.Resize(TSize);

	IgnoreUntilEOFOrASpecificCharacter(sin, ':');
	sin>>B;
	input.SetSymmetry(B);

	IgnoreUntilEOFOrASpecificCharacter(sin, ':');
	sin>>B;
	input.SetItIsPrivate(B);

	for(unsigned int i=0; i<10000 && H!="Here is the key in Hex bytes:"; ++i)
		getline(sin, H);
	input.SetByHexString(H);

	return sin;
}

ostream& operator<<(ostream &sout, const Key &output)
{
	sout<<FILESIGN_KEY_ASKI_HEX<<endl;
	sout<<"Meta-data for other programs=\t"<<Default_MetaData<<endl;
	sout<<"The key length:\t"<<output.Size()<<endl;
	sout<<"Is this for a symmetric encryption algorithm:\t"<<output.IsSymmetric()<<endl;
	sout<<"Is this a private key (Rather than public):\t"<<output.IsPrivate()<<endl;
	sout<<"Here is the key in Hex bytes:"<<endl;
	sout<<output.ToString_Hex();

	return sout;
}

istream& operator>>=(istream &sin, Key &input)
{
	IgnoreReadingNBytes(sin, (unsigned char)FILESIGN_KEY_BIN.size());
	IgnoreReadingAFloatNum(sin);
	BigInt Options = ReadAFloatNum(sin);
	BigInt lngth = ReadAFloatNum(sin);
	input.Resize((unsigned int)lngth);
	input.SetSymmetry( GetTheNthBit_FromRight_FromZero(Options, 0) );
	input.SetItIsPrivate( GetTheNthBit_FromRight_FromZero(Options, 1) );

	Byte *Buffer = new Byte[input.Size()];
	sin.read(Buffer, input.Size());
	Byte2uByte(Buffer, input.USign_Key_Changable(), lngth);

	delete[] Buffer;

	return sin;
}

ostream& operator<<=(ostream &sout, const Key &output)
{
	ImportHeadOfBinKeyFile(sout);
	BigInt Options = 0;
	SetTheNthBit_FromRight_FromZero(Options, 0, output.IsSymmetric());
	SetTheNthBit_FromRight_FromZero(Options, 1, output.IsPrivate());
	WriteAFloatNum(sout, Options);
	WriteAFloatNum(sout, output.Size());

	Byte *Buffer = new Byte[output.Size()];
	uByte2Byte(output.USign_Key(), Buffer, output.Size());
	sout.write(Buffer, output.Size());

	delete[] Buffer;

	return sout;
}

inline vector<uByte> CapsulateA01String(const string &K)
{
	uByte T=0;
	vector<uByte> Result( (K.size()/8)+(unsigned int)( (K.size()%8)!=0 ) );
	for(unsigned int i=0, index=0; i < K.size(); T=0, ++index)
	{
		for(int j=0; j<8 && i < K.size(); ++i, ++j)
			T+=((uByte)( Pow(2, (unsigned int)(8-1-j) ) )) * (uByte)(((char)K[i]-'0')%2);
		Result[index]=T;
	}
	return Result;
}

inline bool IsAGood01StringKey(const string &K)
{
	for(unsigned int i=0; i < K.size(); ++i)
		if(!(K[i]=='0' || K[i]=='1'))
			return false;

	return K.size()!=0;
}

inline vector<uByte> CapsulateAHexString(const string &K)
{
	vector<uByte> Result;
	uByte T=0;
	int i=-1;
	for(; i!=-2; T=0)
	{
		GetNextHexDig(K, i);
		if(i!=-2)
			T+=(uByte)(16*HexDig(K[i]));
		else
			continue ;
		GetNextHexDig(K, i);
		if(i!=-2)T+=(uByte)(HexDig(K[i]));
		Result.push_back(T);
	}
	return Result;
}

bool IsAGoodHexStringKey(const string &K)
{
	for(unsigned int i=0; i < K.size(); ++i)
		if(IsAHexDigit(K[i]))
			return true;

	return false;
}

void GetNextHexDig(const string &K, int &i)
{
	if(i==(int)K.size())
	{
		i=-2;
		return ;
	}
	do
	{
		++i;
	}while(i < (int)K.size() && !IsAHexDigit(K[i]));
	if(!IsAHexDigit(K[i]))
		i=-2;

	return ;
}

inline bool IsAGoodAskiStringKey(const string &K)
{
	return K.size()==0;
}

void Key::Copy(const Key &A)
{
	Close();
	Bytes=new uByte[A.Length];
	for(unsigned int i=0; i < A.Length; ++i)
		Bytes[i]=A.Bytes[i];
	Symmetric=A.Symmetric;
	Private=A.Private;
	Length=A.Length;
}
