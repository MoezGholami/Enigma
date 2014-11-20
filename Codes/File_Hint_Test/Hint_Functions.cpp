#include "Hint_Functions.h"

bool HasHint(const string &url)
{
	if(!IsOurs(url))
		throw Exception(File_Not_Ours);

	fstream f;
	f.open(url.c_str(), ios::in | ios::binary);
	SkipSign(f);

	BigInt Result = ReadAFloatNum(f);

	f.close();

	return Result!=0;
}




void ImportHint(ostream &fo, const string &hinturl)
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




void ExportHint(const string &EngimaFileUrl)
{
	if(!HasHint(EngimaFileUrl))
		throw Exception(File_No_Hint);

	fstream ho, ei;

	ei.open(EngimaFileUrl.c_str(), ios::in | ios::binary);
	SkipSign(ei);

	string hint_file_name=ReadAString_Float(ei);

	ho.open(hint_file_name.c_str(), ios::out | ios::binary);
	if(!ho)
	{
		ei.close();
		throw Exception(File_Unable_To_Write);
	}

	BigInt hint_file_size=ReadAFloatNum(ei);

	PasteAStreamToAStream(ei, hint_file_size, ho);

	ho.close();
	ei.close();

	return ;
}
