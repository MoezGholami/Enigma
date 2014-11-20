#include "Encoder.h"

Encoder::Encoder(BigInt m)
{
	Mode=m;
	Reset("","",Default_Code_Option,Key());
}

Encoder::Encoder(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid, BigInt m)
{
	Mode=m;
	Reset(CmplxURL, PURL, Op, Kelid);
}

Encoder::~Encoder(void)
{
	Close();
}

void Encoder::Encode(unsigned int BffBlcksNum)
{
	Prepare();
	EnDeCodeAll(out, BffBlcksNum);
	Reset(ComplexUrl, PlainUrl, Default_Code_Option, K);
}

bool Encoder::Is_CmplxUrl_Good(void) const
{
	if(!FileExist(ComplexUrl))
		return true;
	else if(!Url_Writable(ComplexUrl))
		return false;
	else if(!IsOurs(ComplexUrl))
		return false;
	else if(!IsAnEnigmaComplexFile(ComplexUrl))
		return false;
	return true;
}

bool Encoder::Is_Purl_Good(void) const
{
	return FileExist(PlainUrl);
}

void Encoder::Set_Option(const BigInt &Op)
{
	Coder::Set_Option(Op);
}

void Encoder::Reset(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid)
{
	Coder::Reset(CmplxURL, PURL, Op, Kelid);
}

void Encoder::Prepare(void)
{
	if(Prepared)
		return ;

	Set_Block_Length();
	Set_Key(K);
	if(!Is_Purl_Good())
		throw Exception(File_Not_Exist);
	if(!Is_CmplxUrl_Good())
		throw Exception(File_Unable_To_Write);
	in.open(PlainUrl.c_str(), ios::in | ios::binary);
	SetTheOfstream(out);
	WriteAFloatNum(out, Mode);
	ImportAnString(out, NameFromUrl(PlainUrl));
	ResetDataSize(SizeOfAFile(PlainUrl));
	WriteAFloatNum(out, SizeOfAFile(PlainUrl));
	WriteAFloatNum(out, Option);
	WritePassCheckingIfRequired();
	ImportHeadOfStartOfCipther(out);

	Prepared=true;
	return ;
}
		
void Encoder::SetTheOfstream(fstream &out)
{
	out.close();
	if(!FileExist(ComplexUrl))
	{
		out.open(ComplexUrl.c_str(), ios::out | ios::binary);
		ImportHeadOfEnigmaComplexFile(out);
		WriteAFloatNum(out, 0);
	}
	else
	{
		out.open(ComplexUrl.c_str(), ios::in | ios::out | ios::binary);
		SkipSignAndHint(out);
	}
	return ;
}

void Encoder::WritePassCheckingIfRequired(void)
{
	if (!(IsPasswordCheckingRequired()) )
                return ;

	InitRandom();
        Byte *fTmp = new Byte[Block_Length];
        uByte *oTmp = new uByte[Block_Length];
        for(unsigned int i=0; i < Block_Length; ++i)
                fTmp[i]=Random(-120,120);
        out.write(fTmp, Block_Length);
        CodeSomeBlocks(fTmp, oTmp, 1);
        out.write(fTmp, Block_Length);

        delete[] fTmp;
        delete[] oTmp;
        return ;

}
