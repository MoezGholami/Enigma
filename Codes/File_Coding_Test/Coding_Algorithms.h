#ifndef __Enigma__Moez__Coding_Algorithms
#define __Enigma__Moez__Coding_Algorithms

#include "UnitsAndBasicTypes.h"
#include <string>
#include <map>
#include "Coder.h"
using namespace std;

const BigInt AES_256	=	2;

class AlgorithmDescriber
{
	public:
		AlgorithmDescriber(void);
		AlgorithmDescriber(const AlgorithmDescriber &C);
		~AlgorithmDescriber(void);

		string Describe(const BigInt &M);
		string Describe(const Coder &C);
	private:
		map <BigInt, string> Dcls;
};

#endif
