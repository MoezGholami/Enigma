#ifndef __Enigma__Moez__Coder_AES
#define __Enigma__Moez__Coder_AES

#include "Encoder.h"
#include "Decoder.h"
#include "Coding_Algorithms.h"
#include "UnitsAndBasicTypes.h"
using namespace std;

/*  
*   Byte-oriented AES-256 implementation.
*   All lookup tables replaced with 'on the fly' calculations. 
*
*   Copyright (c) 2007-2009 Ilya O. Levin, http://www.literatecode.com
*   Other contributors: Hal Finney
*
*   Permission to use, copy, modify, and distribute this software for any
*   purpose with or without fee is hereby granted, provided that the above
*   copyright notice and this permission notice appear in all copies.
*
*   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
*   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
*   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
*   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
*   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
*   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef uint8_t
#define uint8_t uByte 
#endif

#ifdef __cplusplus
extern "C" { 
#endif

    typedef struct {
        uint8_t key[32]; 
        uint8_t enckey[32]; 
        uint8_t deckey[32];
    } aes256_context; 


    void aes256_init(aes256_context *, /* Adding "const" is Moez's change. */ const uint8_t * /* key */);
    void aes256_done(aes256_context *);
    void aes256_encrypt_ecb(aes256_context *, uint8_t * /* plaintext */);
    void aes256_decrypt_ecb(aes256_context *, uint8_t * /* cipertext */);

#ifdef __cplusplus
}
#endif

class EN_AES
	:public Encoder
{
	public:
		EN_AES(void);
		EN_AES(const string &CmplxURL, const string &PURL, const BigInt &Op, const Key &Kelid);
		~EN_AES(void);
		bool KeyIsSuitable(const Key &_K);
		void Set_Block_Length(void);

	protected:
		void CodeABlock(uByte* in);
		void PrepareKey(void);
    		aes256_context ctx;
};

class DE_AES
	:public Decoder
{
	public:
		DE_AES(void);
		DE_AES(const string &CmplxURL, const Key &Kelid);
		~DE_AES(void);
		bool KeyIsSuitable(const Key &_K);
		void Set_Block_Length(void);

	protected:
		void CodeABlock(uByte* in);
		void PrepareKey(void);
    		aes256_context ctx;
};

bool KeyForAES256(const Key &K);

#endif
