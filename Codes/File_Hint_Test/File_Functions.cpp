#include "File_Functions.h"

bool FileExist(const string &url)
{
	fstream f;
	f.open(url.c_str(), ios::in | ios::binary);
	if(f.good())
	{
		f.close();
		return true;
	}
	return false;
}

bool IsOurs(const string &url)
{
	if(!FileExist(url))
		throw Exception(File_Not_Exist);

	if(SizeOfAFile(url) < (BigInt)FILESIGN.size())
		return false;
	
	fstream f(url.c_str(), ios::in | ios::binary);

	string S=ReadAString(f, FILESIGN.size());

	f.close();

	return S==FILESIGN;
}

BigInt SizeOfAFile(const string &url)
{
	if(!FileExist(url))
		throw Exception(File_Not_Exist);

	BigInt Result;
	fstream f(url.c_str(), ios::in | ios::binary | ios::ate);
	Result=f.tellg();
	f.close();

	return Result;
}




void SkipSign(fstream &fin)
{
	fin.seekp(FILESIGN.size());
	IgnoreReadingAFloatNum(fin);
}

void SkipSignAndHint(fstream &fin)
{
	SkipSign(fin);
	SkipAFloatSizedBlock(fin);
	SkipAFloatSizedBlock(fin);
}

void SkipAFloatSizedBlock(fstream &f)
{
	BigInt NextStation;

	NextStation=ReadAFloatNum(f);
	f.seekp((BigInt)f.tellg()+NextStation);
}

void IgnoreReadingAFloatNum(istream &f)
{
	Byte Tmp[1];
	while(Tmp[0]!=Float_Num_End)
		f.read(Tmp,1);
}




void ImportHeadOfEngimaFile(ostream &f)
{
	f.write(FILESIGN.c_str(), FILESIGN.size());
	WriteAFloatNum(f, (BigInt)1);

	return ;
}




void PasteAStreamToAStream(istream &in, BigInt RemaindToCopy, ostream &out, int BufferSize)
{
	Byte *Buffer = new Byte[BufferSize];

	for(RemaindToCopy=RemaindToCopy; BufferSize < RemaindToCopy; RemaindToCopy -= BufferSize)
	{
		in.read(Buffer, BufferSize);
		out.write(Buffer, BufferSize);
	}

	in.read(Buffer, (int)RemaindToCopy);
	out.write(Buffer, (int)RemaindToCopy);

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
	BigInt NameSize = ReadAFloatNum(in);
	return ReadAString(in, NameSize);
}

string ReadAString(istream &in, BigInt Size)
{
	string Result="";
	char Tmp[1];
	for(BigInt i=0; i<Size; ++i)
	{
		in.read(Tmp,1);
		Result+=Tmp[0];
	}
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
