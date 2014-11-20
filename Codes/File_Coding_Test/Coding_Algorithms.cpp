#include "Coding_Algorithms.h"

AlgorithmDescriber::AlgorithmDescriber(void)
{
	Dcls[			AES_256			]	=	"A strong and fast symmetric block cipher with 256 bit key.";
}

AlgorithmDescriber::AlgorithmDescriber(const AlgorithmDescriber &C)
{
	Dcls=C.Dcls;
}

AlgorithmDescriber::~AlgorithmDescriber(void)
{
	Dcls.clear();
}

string AlgorithmDescriber::Describe(const BigInt &M)
{
	if(Dcls.find(M)==Dcls.end())
		return "There is no coding algorithm with this ID.";
	return Dcls[M];
}

string AlgorithmDescriber::Describe(const Coder &C)
{
	return Describe(C.ID());
}
