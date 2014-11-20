#include "Hint_Functions.h"

bool HasHint(const string &url)
{
	if(!IsAnEnigmaComplexFile(url))
		throw Exception(File_Not_An_Enigma_Complex);
	fstream f(url.c_str(), ios::in | ios::binary);
	SkipSign_Complex(f);

	BigInt Result = ReadAFloatNum(f);

	f.close();

	return Result!=0;
}

void ImportHint(const string &CmplxURL, const string &hinturl)
{
	if(!Url_Writable(CmplxURL))
		throw Exception(File_Unable_To_Write);
	fstream f;
	f.open(CmplxURL.c_str(), ios::out | ios::binary);
	ImportHeadOfEnigmaComplexFile(f);
	InsertHint(f, hinturl);
	f.close();

	return ;
}

void InsertHint(ostream &fo, const string &hinturl)
{
	if(!FileExist(hinturl))
		throw Exception(File_Not_Exist);

	ImportAnString(fo, NameFromUrl(hinturl));
	WriteAFloatNum(fo, SizeOfAFile(hinturl));

	fstream hi(hinturl.c_str(), ios::in | ios::binary);
	PasteAStreamToAStream(hi, SizeOfAFile(hinturl) ,fo);

	hi.close();

	return ;
}

void ExportHint(const string &EnigmaFileUrl)
{
	if(!HasHint(EnigmaFileUrl))
		throw Exception(File_No_Hint);

	fstream ho, ei;

	ei.open(EnigmaFileUrl.c_str(), ios::in | ios::binary);
	SkipSign_Complex(ei);

	string hint_file_name=ReadAString_Float(ei);
	MakeAWritableUrlOfThisIfNot(hint_file_name);

	ho.open(hint_file_name.c_str(), ios::out | ios::binary);
	if(!ho)
	{
		ei.close();
		throw Exception(File_Unable_To_Write);
	}

	size_t hint_file_size=(size_t)ReadAFloatNum(ei);

	PasteAStreamToAStream(ei, hint_file_size, ho);

	ho.close();
	ei.close();

	return ;
}

void SkipSignAndHint(fstream &f)
{
	SkipSign_Complex(f);
	BigInt hntnamesize=ReadAFloatNum(f);
	if(hntnamesize==0)
		return ;
	f.seekp((BigInt)f.tellg()+hntnamesize);
	SkipAFloatSizedBlock(f);
}
