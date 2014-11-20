#ifndef __Enigma__Moez__Key
#define __Enigma__Moez__Key

#include "UnitsAndBasicTypes.h"
#include "UtilityFunctions.h"
#include "Exception.h"
#include <string>
#include <vector>
#include "File_Functions.h"
#include <iostream>
using namespace std;

//	Caution: This function only supports keys with size multiple of 8 bits. (64, 128, 192, etc.)
//	All units are in bytes.
class Key
{
	public:
		Key(unsigned int S_BY = Default_Key_Length, bool sym = true, bool pri = true); /* Exs: Length_Zero. */
		Key(const string &K, bool sym = true, bool pri = true);	 /* Exs: Length_Zero, Key_String_NoSupportedChar. */ //From a 01 string.
		Key(const string &K, unsigned int S_BY, bool sym = true, bool pri = true); /* Exs: Length_Zero, Key_String_NoSupportedChar. */ //From a 01 string.
		Key(const Key &A); /* Exs: . */
		~Key(void); /* Exs: . */

		void SetBy01String(const string &K); /* Exs: Key_String_NoSupportedChar. */
		void SetByHexString(const string &K); /* Exs: Key_String_NoSupportedChar. */
		void SetByAskiString(const string &K); /* Exs: Key_String_NoSupportedChar. */

		void SetSymmetry(bool in); /* Exs: . */
		void SetItIsPrivate(bool in); /* Exs: . */

		void Resize(unsigned int New_Size); /* Exs: Length_Zero. */

		const uByte* USign_Key(void) const; /* Exs: . */
		uByte* USign_Key_Changable(void); /* Exs: . */

		unsigned int Size(void) const; /* Exs: . */

		string ToString_Hex(void) const; /* Exs: . */
		string ToString_Bin(void) const; /* Exs: . */

		bool IsSymmetric(void) const; /* Exs: . */
		bool IsPrivate(void) const; /* Exs: . */

		Key& operator=(const Key &A);

		void Close(void); /* Exs: . */



	private:
		inline void InitWithSize_ForConstructor(unsigned int S_BY, bool sym, bool pri); /* Exs: Length_Zero. */
		inline void InitWithStringAndSize_ForConstructor(const string &K, unsigned int S_BY, bool sym, bool pri); /* Exs: Length_Zero, Key_String_NoSupportedChar. */
		inline void InitWithString_ForConstructor(const string &K, bool sym, bool pri); /* Exs: Length_Zero, Key_String_NoSupportedChar. */
		template<typename Container_With_Brackets>
		void HashAuByteContainerToTheKeyArray(const Container_With_Brackets &Prepared, unsigned int Selected_Length_From_Begining); /* Exs: . */
		void Copy(const Key &A);

	private:
		uByte *Bytes;
		unsigned int Length;
		bool Symmetric;
		bool Private;
};

istream& operator>>(istream &sin, Key &input); /* Exs: Length_Zero, Key_String_NoSupportedChar. ios_base::failure */
ostream& operator<<(ostream &sout, const Key &output); /* Exs: . ios_base::failure */

/*
*	Caution: these operators write binary numbers, and may write eof character.
*	Therefore the operators >>= and <<= have been overloaded.
*/
istream& operator>>=(istream &sin, Key &input); /* Exs: . ios_base::failure */
ostream& operator<<=(ostream &sout, const Key &output); /* Exs: . ios_base::failure */

inline vector<uByte> CapsulateA01String(const string &K); /* Exs: . */
inline bool IsAGood01StringKey(const string &K); /* Exs: . */

inline vector<uByte> CapsulateAHexString(const string &K); /* Exs: . */
bool IsAGoodHexStringKey(const string &K); /* Exs: . */
void GetNextHexDig(const string &K, int &i); /* Exs: . */

inline bool IsAGoodAskiStringKey(const string &K);
#endif
