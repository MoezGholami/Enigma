#ifndef __Enigma__Moez__Encoder
#define __Enigma__Moez__Encoder

#include "Coder.h"
#include "UnitsAndBasicTypes.h"
#include "File_Functions.h"
#include "Hint_Functions.h"
#include "Key.h"
#include "Exception.h"
#include "UtilityFunctions.h"
#include <string>
using namespace std;

//Abstract class
class Encoder
	: public Coder
{
	public:
		Encoder(BigInt m = Default_Algorithm_Mode); /* Exs: . */
		Encoder(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid, BigInt m = Default_Algorithm_Mode); /* Exs: . */
		~Encoder(void); /* Exs: . */

		virtual void Encode(unsigned int BffBlcksNum = Default_Code_Buffer_Length); /* Exs: Length_Zero, File_Not_Exist, File_Unable_To_Write. ios_base::failure */

		bool Is_CmplxUrl_Good(void) const; /* Exs: . */
		bool Is_Purl_Good(void) const; /* Exs: . */

		void Set_Option(const BigInt &Op);
		void Reset(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid); /* Exs: . */

	protected:
		virtual void Prepare(void); /* Exs: File_Not_Exist, File_Unable_To_Write. ios_base::failure */
		void SetTheOfstream(fstream &out); /* Exs: . ios_base::failure */
		void WritePassCheckingIfRequired(void); /* Exs: . ios_base::failure */
};

#endif
