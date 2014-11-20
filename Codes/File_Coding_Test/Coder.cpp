#include "Coder.h"

void Coder::Set_Option(const BigInt &Op)
{
	Option=Op;
	return ;
}

void Coder::Set_Key(const Key &_K)
{
	if(!KeyIsSuitable(_K))
		throw Exception(Coding_Unsuitable_Key);
	K=_K;
	PrepareKey();
}

bool Coder::Set_CmplxUrl(const string &CmplxURL)
{
	ComplexUrl=CmplxURL;
	return Is_CmplxUrl_Good();
}

bool Coder::Set_Purl(const string &PURL)
{
	PlainUrl=PURL;
	return Is_Purl_Good();
}

void Coder::CodeAndWriteSomeBlocks(ostream &o, unsigned int BffBlcksNum)
{
	size_t Buffer_Size = BffBlcksNum*Block_Length;
	Byte *fBuffer = new Byte[Buffer_Size];
	uByte *oBuffer = new uByte[Buffer_Size];
	for(; index + Buffer_Size <= DataSize; index+=Buffer_Size)
	{
		in.read(fBuffer, Buffer_Size);
		CodeSomeBlocks(fBuffer, oBuffer, BffBlcksNum);
		o.write(fBuffer, Buffer_Size);
	}

	delete[] fBuffer;
	delete[] oBuffer;
	return ;
}

void Coder::CodeSomeBlocks(Byte *FileBuffer, uByte* OperationBuffer, unsigned int BffBlcksNum)
{
	Byte2uByte(FileBuffer, OperationBuffer, BffBlcksNum*Block_Length);
	for(unsigned int i=0; i<BffBlcksNum; ++i)
		CodeABlock(OperationBuffer+ i*Block_Length);
	uByte2Byte(OperationBuffer, FileBuffer, BffBlcksNum*Block_Length);
}

void Coder::CopyTheRemaineds(ostream &o)
{
	if(DataSize - index == 0)
		return ;

	PasteAStreamToAStream(in, DataSize-index, o, DataSize - index);
	return ;
}

void Coder::EnDeCodeAll(ostream &o, unsigned int BffBlcksNum)
{
	if(BffBlcksNum<1)
		throw Exception(Length_Zero);

	CodeAndWriteSomeBlocks(o, BffBlcksNum);
	CodeAndWriteSomeBlocks(o, 1);
	CopyTheRemaineds(o);
}

void Coder::Close(void)
{
	Mode=Default_Algorithm_Mode;
	Reset("","",Default_Code_Option,Key());
}

bool Coder::IsPasswordCheckingRequired(void)
{
	return GetTheNthBit_FromRight_FromZero(Option, 0);
}

void Coder::Reset(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid)
{
	Set_CmplxUrl(CmplxURL);
	Set_Purl(PURL);
	Set_Option(Op);
	K=Kelid;
	in.close();
	out.close();
	ResetDataSize(0);
	Prepared=false;
}

bool Coder::ResetDataSize(const size_t &s)
{
	if(s<0)
		return false;
	index=0;
	DataSize=s;
	return true;
}

BigInt Coder::ID(void) const {return Mode;}
string Coder::CmplxUrl(void) const {return ComplexUrl;}
string Coder::Purl(void) const {return PlainUrl;}
BigInt Coder::Opt(void) const {return Option;}
Key Coder::_Key(void) const {return K;}

bool HasCipher(const string &CmplxUrl)
{
	if(!FileExist(CmplxUrl))
		return false;
	if(!IsOurs(CmplxUrl))
		return false;
	if(!IsAnEnigmaComplexFile(CmplxUrl))
		return false;
	size_t size = SizeOfAFile(CmplxUrl), i=0;
	fstream f;
	f.open(CmplxUrl.c_str(), ios::in | ios::binary);
	SkipSignAndHint(f);
	i=f.tellg();
	f.close();
	return (!(size==i));
}
