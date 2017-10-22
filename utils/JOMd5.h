/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 FileUtilsEx.h
 AUTHOR:  James Ou
 *********************************************************************/

#ifndef __FILE_UTILS_EX_H__
#define __FILE_UTILS_EX_H__

#include <string>
#include <fstream>


#include "utils/JOMacro.h"
NS_JOFW_BEGIN
/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;
using std::string;
using std::ifstream;
/* MD5 declaration. */
class JO_DLL JOMd5 {
public:
	JOMd5();
	JOMd5(const void* input, size_t length);
	JOMd5(const string& str);
	JOMd5(ifstream& in);
    void update(const void* input, size_t length);
    void update(const string& str);
    void update(ifstream& in);
    const byte* digest();
    string toString();
    void reset();
private:
    void update(const byte* input, size_t length);
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
    string bytesToHexString(const byte* input, size_t length);
    /* class uncopyable */
	JOMd5(const JOMd5&);
	JOMd5& operator=(const JOMd5&);
private:
    uint32 _state[4]; /* state (ABCD) */
    uint32 _count[2]; /* number of bits, modulo 2^64 (low-order word first) */
    byte _buffer[64]; /* input buffer */
    byte _digest[16]; /* message digest */
    bool _finished;   /* calculate finished ? */
    static const byte PADDING[64]; /* padding for calculate */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };
};

NS_JOFW_END

#endif // __FILE_UTILS_EX_H__
