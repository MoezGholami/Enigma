#ifndef __Enigma__Moez__Decoder
#define __Enigma__Moez__Decoder

#include "Coder.h"
#include "UnitsAndBasicTypes.h"
#include "UtilityFunctions.h"
#include "File_Functions.h"
#include "Hint_Functions.h"
#include <vector>
using namespace std;

//Abstract class
class Decoder
	: public Coder
{
	public:
		Decoder(BigInt m = Default_Algorithm_Mode); /* Exs: . */
		Decoder(const string &CmplxURL, const Key &Kelid, BigInt m = Default_Algorithm_Mode); /* Exs: . */
		~Decoder(void); /* Exs: . */

		virtual void Decode(unsigned int BffBlcksNum = Default_Code_Buffer_Length); /* Exs: Coding_Wrong_Password, Length_Zero, Coding_Unsuitable_Key, File_Unable_To_Write, Coding_Cannot_Decode. ios_base::failure */

		bool ChecksPassword(void); /* Exs: Coding_Unsuitable_Key, File_Unable_To_Write, Coding_Cannot_Decode. ios_base::failure */
		bool CorrectPassword(void); /* Exs: Coding_Unsuitable_Key, File_Unable_To_Write, Coding_Cannot_Decode. ios_base::failure */
		bool Is_CmplxUrl_Good(void) const; /* Exs: . */
		bool Can_Decode_Cipher(void) const; /* Exs: File_Not_Exist, File_Not_Ours, File_Not_An_Enigma_Complex, File_No_Cipher. ios_base::failure */
		bool Is_Purl_Good(void) const; /* Exs: . */

		void Reset(const string &CmplxURL, const BigInt &Op, const Key &Kelid); /* Exs: . */

	protected:
		virtual void Prepare(void); /* Exs: Coding_Unsuitable_Key, File_Unable_To_Write, Coding_Cannot_Decode. ios_base::failure */
		void LoadSampleBlock(void); /* Exs: . ios_base::failure */
		void DeleteSampleBlock(void); /* Exs: . */

	private:
		vector<Byte> SPlain;
		vector<Byte> SCipher;
};

BigInt CodingModeOfAComplexFile(const string &CmplxURL); /* Exs: File_Not_Exist, File_Not_Ours, File_Not_An_Enigma_Complex, File_No_Cipher. ios_base::failure */

#endif
