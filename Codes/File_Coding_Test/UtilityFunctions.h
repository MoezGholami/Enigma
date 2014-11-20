#ifndef __Enigma__Moez__Utility_Functions
#define __Enigma__Moez__Utility_Functions

#include "UnitsAndBasicTypes.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <new>

#include <iostream>
using namespace std;

BigInt Pow(BigInt Base, unsigned int Power); /* Exs: . */

void uByte2Byte(const uByte *in, Byte *out, size_t Size); /* Exs: . */
void Byte2uByte(const Byte *in, uByte *out, size_t Size); /* Exs: . */

template<typename T>
void Vector2DynamicArr(const vector<T> &V, T* &Arr); /* Exs: . bad_alloc */
	//template void Vector2DynamicArr<Byte>(const vector<Byte> &V, Byte* &Arr);

template<typename T>
void Arr2Vector(T *Arr, vector<T> &V, unsigned int Size); /* Exs: . bad_alloc */
	//template void Arr2Vector<Byte>(Byte *Arr, vector<Byte> &V, unsigned int Size);

bool GetTheNthBit_FromRight_FromZero(const BigInt &A, unsigned int DigNum); /* Exs: . */
void SetTheNthBit_FromRight_FromZero(BigInt &A, unsigned int DigNum, bool in); /* Exs: . */

bool IsAHexDigit(char A); /* Exs: . */
unsigned int HexDig(char A); /* Exs: . __ returns 0 when cannot convert*/

void InitRandom(unsigned int seed = time(NULL)); /* Exs: . */
int Random(int Min, int Max); /* Exs: . */

string operator+(const string &S, const float &N); /* Exs: . ios_base::failure */ //N: Decimal
string operator+(const float &N, const string &S); /* Exs: . ios_base::failure */ //N: Decimal
#endif
