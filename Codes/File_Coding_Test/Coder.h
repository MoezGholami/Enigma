#ifndef __Enigma__Moez__Coder
#define __Enigma__Moez__Coder

#include "UnitsAndBasicTypes.h"
#include "File_Functions.h"
#include "Hint_Functions.h"
#include "Key.h"
#include "UtilityFunctions.h"
#include "Exception.h"
using namespace std;

//Abstract class
class Coder
{
	public:
		virtual void Set_Key(const Key &_k); /* Exs: Coding_Unsuitable_Key. */
		bool Set_CmplxUrl(const string &CmplxURL); /* Exs: . */
			virtual bool Is_CmplxUrl_Good(void) const = 0;
		bool Set_Purl(const string &PURL); /* Exs: . */
			virtual bool Is_Purl_Good(void) const = 0;

		BigInt ID(void) const; /* Exs: . */
		string CmplxUrl(void) const; /* Exs: . */
		string Purl(void) const; /* Exs: . */
		BigInt Opt(void) const; /* Exs: . */
		Key _Key(void) const; /* Exs: . */

		virtual bool KeyIsSuitable(const Key &_K) = 0;


	protected:
		void EnDeCodeAll(ostream &o, unsigned int BffBlcksNum); /* Exs: Length_Zero. ios_base::failure */
		void CodeAndWriteSomeBlocks(ostream &o, unsigned int BffBlcksNum); /* Exs: . ios_base::failure */
		void CodeSomeBlocks(Byte *FileBuffer, uByte* OperationBuffer, unsigned int BffBlcksNum); /* Exs: . */ //OperationBuffer is only to prevent memory allocating many times and is not an out put or input, it's just a temporary template.
		virtual void CodeABlock(uByte* i) = 0;
		void CopyTheRemaineds(ostream &o); /* Exs: . */
		virtual void Close(void); /* Exs: . */
		bool IsPasswordCheckingRequired(void); /* Exs: . */
		virtual void Prepare(void) = 0;
		virtual void PrepareKey(void) = 0;
		virtual void Set_Block_Length(void) = 0; /* Exs: . */
		virtual void Set_Option(const BigInt &Opt); /* Exs: . */

		virtual void Reset(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid); /* Exs: . */
		bool ResetDataSize(const size_t &s); /* Exs: . */

	protected:
		unsigned int Block_Length;
		BigInt Mode;

		fstream out;
		fstream in;
		string ComplexUrl;
		string PlainUrl; 
		BigInt Option;
		Key K;

		bool Prepared;

	private:
		size_t DataSize;
		size_t index;
};

bool HasCipher(const string &CmplxUrl); /* Exs: . */

#endif
