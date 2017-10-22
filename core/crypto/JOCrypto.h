//
//  JOCrypto.h
//
//  Created by James on 15/3/12.
//  Copyright (c) 2015??? dream. All rights reserved.
//
#ifndef __JO_CRYPTO_H__
#define __JO_CRYPTO_H__

#include "utils/JOMacro.h"
NS_JOFW_BEGIN

class JO_DLL JOCrypto
{
public:
    
    // set crypto key
	/************************************************************************/
	/* key的长度不能大于 unsigned short(65535)
	/************************************************************************/
    static void setKey(const char* pKey);
    
    //
    static unsigned char *encode(unsigned char *data, unsigned int data_len, unsigned int *ret_length);
    //
    static unsigned char *decode(unsigned char *data, unsigned int data_len, unsigned int *ret_length, bool orgReturn=false);
    
	static void encodeFile(const char *key, const char *filePath, const char *outPath);
    static void decodeFile(const char *key, const char *filePath, const char *outPath);
    
};

NS_JOFW_END
#endif  //__JO_CRYPTO_H__