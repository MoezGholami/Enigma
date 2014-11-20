#include "File_Functions.h"

bool FileExist(const string &url)
{
	fstream f;
	try
	{
		f.open(url.c_str(), ios::in | ios::binary);
		if(f.good())
		{
			f.close();
			return true;
		}
	}
	catch(const fstream::failure &E)
	{
		return false;
	}
	return false;
}

bool Url_Writable(const string &url)
{
	if(!FileExist(url))
		return true;
	bool Result=false;
	try
	{
		fstream f;
		f.open(url.c_str(), ios::in | ios::out | ios::binary);
		Result= !(!f);
		f.close();
	}
	catch(const fstream::failure &E)
	{
		Result=false;
	}
	return Result;
}

inline bool CanBeRead_N_Bytes(fstream &fin, size_t N)
{
	try
	{
		return SizeOfAFstream(fin) >= N;
	}catch(const fstream::failure &E)
	{
		return false;
	}
}

bool IsOurs(const string &url)
{
	if(!FileExist(url))
		throw Exception(File_Not_Exist);
	fstream fin(url.c_str(), ios::in | ios::binary);
	if(!CanBeRead_N_Bytes(fin, FILESIGN.size()))
		return false;
	string S = ReadAString(fin, FILESIGN.size());
	fin.close();
	return S == FILESIGN;
}

bool IsAnEnigmaComplexFile(const string &url)
{
	if(!IsOurs(url))
		throw Exception(File_Not_Ours);
	fstream fin(url.c_str(), ios::in | ios::binary);
	if(!CanBeRead_N_Bytes(fin, FILESIGN_COMPLEX.size()))
		return false;
	string S = ReadAString(fin, FILESIGN_COMPLEX.size());
	fin.close();
	return S == FILESIGN_COMPLEX;
}

bool IsAnEnigmaKeyFile(const string &url)
{
	if(!IsOurs(url))
		throw Exception(File_Not_Ours);
	fstream fin(url.c_str(), ios::in | ios::binary);
	if(!CanBeRead_N_Bytes(fin, FILESIGN_KEY.size()))
		return false;
	string S = ReadAString(fin, FILESIGN_KEY.size());
	fin.close();
	return S == FILESIGN_KEY;
}

size_t SizeOfAFile(const string &url)
{
	if(!FileExist(url))
		throw Exception(File_Not_Exist);
	fstream f(url.c_str(), ios::binary | ios::in);
	size_t Result;
	Result=SizeOfAFstream(f);
	f.close();

	return Result;
}

size_t SizeOfAFstream(fstream &f)
{
	// /*
	size_t Tmp = f.tellg();
	f.seekg(0, ios::end);
	size_t Result = f.tellg();
	f.seekp(Tmp);
	return Result;
	// */
	//return f.end;
}

void SkipSign_Complex(fstream &fin)
{
	fin.seekp(FILESIGN_COMPLEX.size());
	IgnoreReadingAFloatNum(fin);//version
	IgnoreReadingAFloatNum(fin);//Meta-Data
}

void SkipSign_Key(fstream &fin)
{
	fin.seekp(FILESIGN_KEY.size());
	IgnoreReadingAFloatNum(fin);//Meta-Data
}

void SkipAFloatSizedBlock(fstream &f)
{
	BigInt NextStation;

	NextStation=ReadAFloatNum(f);
	f.seekp((BigInt)f.tellg()+NextStation);
}

void IgnoreReadingAFloatNum(istream &f)
{
	Byte Tmp[1] = {((Float_Num_End+1)%10)};
	while(Tmp[0]!=Float_Num_End)
		f.read(Tmp,1);
}

void IgnoreReadingNBytes(istream &in, unsigned char N)
{
	/*	
	*	Caution: Since the class istream has no method for seeking and because of low performance,
	*	this function has been designed only for low values of N (here: <256)
	*/

	if(N==0)
		return ;

	Byte *Buffer = new Byte[((unsigned int)N)];
	in.read(Buffer, (unsigned int)N);
	delete[] Buffer;
	return ;
}

void IgnoreUntilEOFOrASpecificCharacter(istream &in, char c)
{
	char Tmp=' ';
	while(in>>Tmp)
		if(Tmp==c)
			break ;

	return ;
}

void GoToNextLine(istream &in)
{
	string Tmp;
	getline(in, Tmp);
	return ;
}

void GoToHeadOfStartOfCipther(istream &in)
{
	string Tmp="";
	while(Tmp!=Head_Of_Chipher_Sign)
		getline(in, Tmp);
	//char T=0; in.read(&T, 1);//Skipping the last \n
	return ;
}

void ImportHeadOfEnigmaComplexFile(ostream &f)
{
	f.write(FILESIGN_COMPLEX.c_str(), FILESIGN_COMPLEX.size());
	WriteAFloatNum(f, SOFTWARE_VERSION);
	WriteAFloatNum(f, Default_MetaData);

	return ;
}

void ImportHeadOfBinKeyFile(ostream &f)
{
	f.write(FILESIGN_KEY_BIN.c_str(), FILESIGN_KEY_BIN.size());
	WriteAFloatNum(f, Default_MetaData);
}

void ImportHeadOfStartOfCipther(ostream &f)
{
	f<<endl<<Head_Of_Chipher_Sign<<endl;
	return ;
}

void PasteAStreamToAStream(istream &in, size_t RemaindToCopy, ostream &out, size_t BufferSize)
{
	if(BufferSize < 1)
		throw Exception(Length_Zero);

	Byte *Buffer = new Byte[BufferSize];
	for(; BufferSize < RemaindToCopy; RemaindToCopy -= BufferSize)
	{
		in.read(Buffer, BufferSize);
		out.write(Buffer, BufferSize);
	}
	if(RemaindToCopy != 0)
	{
		in.read(Buffer, (int)RemaindToCopy);
		out.write(Buffer, (int)RemaindToCopy);
	}
	delete[] Buffer;
	return ;
}

BigInt ReadAFloatNum(istream &f)
{
	Byte Tmp[1];
	Tmp[0]=0;
	BigInt Result=0;
	while(Tmp[0]!=Float_Num_End)
	{
		f.read(Tmp,1);
		if( Tmp[0] != Float_Num_End)
			Result= ((BigInt)Tmp[0]+128) +Float_Num_Base*Result;
	}
	return Result;
}

string ReadAString_Float(istream &in)
{
	size_t NameSize = (size_t)ReadAFloatNum(in);
	return ReadAString(in, NameSize);
}

string ReadAString(istream &in, size_t Size)
{
	string Result="";
	 /*
	char Tmp[1];
	for(BigInt i=0; i<Size; ++i)
	{
		in.read(Tmp,1);
		Result+=Tmp[0];
	} // */
	// /*
	char *Tmp = new char [Size+1], T[1]="";
	in.read(Tmp, Size);
	Tmp[Size]=T[0];
	Result=Tmp;
	delete[] Tmp;
	// */
	return Result;
}

void WriteAFloatNum(ostream &f, BigInt A)
{
	vector<Byte> Digs(1, Float_Num_End);
	Byte Tmp[1];
	do
	{
		Digs.push_back( (Byte)( (A%Float_Num_Base)-128 ) );
		A=A/Float_Num_Base;
	} while(A != 0);

	for(int i=Digs.size()-1; i>=0; --i)
	{
		Tmp[0]=Digs[i];
		f.write(Tmp, 1);
	}

	return ;
}

void ImportAnString(ostream &fo, const string &Str)
{
	WriteAFloatNum(fo, (BigInt) Str.size());
	fo.write(Str.c_str(),Str.size());

	return ;
}

string NameFromUrl(string url)
{
	if(url.size()==0)
		throw Exception(Bad_File_Url);

	string Result="";
	int i=0;

	if(url[url.size()-1]==Url_Directory_Tokenizer)
		url=url.substr(0, url.size()-1);

	for(i=url.size()-1; i>=0 && url[i]!=Url_Directory_Tokenizer; --i);

	if(i==0)
		Result=url;
	else
		Result=url.substr(i+1, url.size()-(i+1));

	if(Result.size()==0)
		throw Exception(Bad_File_Url);

	return Result;
}

void MakeAWritableUrlOfThisIfNot(string &url)
{
	string Head="", Tail="";
	SetHeadAndTailOfAString_FirsGivenString(url, Head, Tail, ".");
	for(unsigned long int i=2; !Url_Writable(url); ++i)
		url=Head+"_"+i+Tail;
}

void SetHeadAndTailOfAString_FirsGivenString(const string &Name, string &Head, string &Tail, const string &T)
{
	Head="", Tail="";

	size_t TPos=Name.find(T);

	if(Name.size()==0)
		return ;

	if(TPos==string::npos)
		Head=Name;
	else
	{
		Tail=Name.substr(TPos, Name.size()-TPos);//Tail will include T
		if(TPos!=0)
			Head=Name.substr(0, TPos);
	}

	return ;
}
