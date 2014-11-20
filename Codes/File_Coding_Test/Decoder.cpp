#include "Decoder.h"

Decoder::Decoder(BigInt m)
{
	Mode=m;
	Reset("",Default_Code_Option,Key());
}

Decoder::Decoder(const string &CmplxURL, const Key &Kelid, BigInt m)
{
	Mode=m;
	Reset(CmplxURL, Default_Code_Option, Kelid);
}

Decoder::~Decoder(void)
{
	Close();
}

void Decoder::Decode(unsigned int BffBlcksNum)
{
	Prepare();
	if(!CorrectPassword())
		throw Exception(Coding_Wrong_Password);

	DeleteSampleBlock();
	MakeAWritableUrlOfThisIfNot(PlainUrl);
	out.open(PlainUrl.c_str(), ios::out | ios::binary);
	EnDeCodeAll(out, BffBlcksNum);
	Reset(ComplexUrl, Default_Code_Option, Key());
}

bool Decoder::ChecksPassword(void)
{
	Prepare();
	return IsPasswordCheckingRequired();
}

bool Decoder::CorrectPassword(void)
{
	Prepare();
	if(!IsPasswordCheckingRequired())
		return true;
	Byte *OutPlain=NULL;
	uByte *OperationBuffer = new uByte[Block_Length];
	Vector2DynamicArr(SCipher, OutPlain);
	CodeSomeBlocks(OutPlain, OperationBuffer, 1);
	bool Same=true;
	for(unsigned int i = 0; i < Block_Length && Same; ++i)
		Same=( OutPlain[i]==SPlain[i] );

	delete[] OutPlain;
	delete[] OperationBuffer;
	return Same;
}

bool Decoder::Is_CmplxUrl_Good(void) const
{
	try
	{
		return Can_Decode_Cipher();
	}
	catch(const Exception &E)
	{
		return false;
	}
	catch(const fstream::failure &E)
	{
		return false;
	}
}

bool Decoder::Can_Decode_Cipher(void) const
{
	BigInt SM=CodingModeOfAComplexFile(ComplexUrl);
	return Mode==SM;
}

bool Decoder::Is_Purl_Good(void) const
{
	return Url_Writable(PlainUrl);
}

void Decoder::Reset(const string &CmplxURL, const BigInt &Op, const Key &Kelid)
{
	Coder::Reset(CmplxURL,"",Op,Kelid);
}

void Decoder::Prepare(void)
{
	if(Prepared)
		return ;

	Set_Block_Length();
	Set_Key(K);
	if(!Is_Purl_Good())
		throw Exception(File_Unable_To_Write);
	if(!Can_Decode_Cipher())
		throw Exception(Coding_Cannot_Decode);
	in.open(ComplexUrl.c_str(), ios::in | ios::binary);
	SkipSignAndHint(in);
	IgnoreReadingAFloatNum(in);//Skiping the ID of cryptography algorithm
	PlainUrl=ReadAString_Float(in);
	/*ResetDataSize((size_t)ReadAFloatNum(in));*/ size_t DS=(size_t)ReadAFloatNum(in); ResetDataSize(DS);
	Set_Option(ReadAFloatNum(in));
	if(IsPasswordCheckingRequired())
		LoadSampleBlock();
	GoToHeadOfStartOfCipther(in);

	Prepared=true;
	return ;
}

void Decoder::LoadSampleBlock(void)
{
	if(SPlain.size()!=0 || SCipher.size()!=0)
		return ;

	Byte *Tmp = new Byte[Block_Length];

	in.read(Tmp, Block_Length);
	Arr2Vector(Tmp, SPlain, Block_Length);

	in.read(Tmp, Block_Length);
	Arr2Vector(Tmp, SCipher, Block_Length);

	delete[] Tmp;
	return ;
}

void Decoder::DeleteSampleBlock(void)
{
	SPlain.clear();
	SCipher.clear();
}

BigInt CodingModeOfAComplexFile(const string &CmplxURL)
{
	if(!IsAnEnigmaComplexFile(CmplxURL))
		throw Exception(File_Not_An_Enigma_Complex);
	if(!HasCipher(CmplxURL))
		throw Exception(File_No_Cipher);
	fstream i;
	i.open(CmplxURL.c_str(), ios::in | ios::binary);
	SkipSignAndHint(i);
	BigInt Result=ReadAFloatNum(i);
	i.close();
	return Result;
}
