//
//  GlobalData.h
//  Twilight-cocos2dx
//
//  Created by mac on 12-7-6.
//  Copyright (c) 2012??? __MyCompanyName__. All rights reserved.
//

#ifndef _JO_DATA_UTILS_H_
#define _JO_DATA_UTILS_H_

#include "utils/JOMacro.h"

NS_JOFW_BEGIN
class JOData;


class JO_DLL JODataUtils {
public:
    // byte - interger conventer
    // int16(2 bytes)
    static short shortFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormShort(short s, bool bigendian=false);

    static unsigned short unsignedShortFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormUnsignedShort(unsigned short s, bool bigendian=false);
    
    // int32(4 bytes)
    static int intFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormInt(int n, bool bigendian=false);
    
    static unsigned int unsignedIntFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormUnsignedInt(unsigned int n, bool bigendian=false);

	static float floatFormData(JOData* data, bool bigendian=false);
	static JOData* dataFormfloat(float f, bool bigendian=false);
    
    // int64(8 bytes)
    static long long longLongFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormLongLong(long long l, bool bigendian=false);
    
    static unsigned long long unsignedLongLongFormData(JOData* data, bool bigendian=false);
    static JOData* dataFormUnsignedLongLong(unsigned long long l, bool bigendian=false);
    
    
    
    static short shortFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormShort(short s, unsigned char* buff, bool bigendian=false);
    
    static unsigned short unsignedShortFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormUnsignedShort(unsigned short s, unsigned char* buff, bool bigendian=false);
    
    // int32(4 bytes)
    static int intFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormInt(int n, unsigned char* buff, bool bigendian=false);
    
    static unsigned int unsignedIntFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormUnsignedInt(unsigned int n, unsigned char* buff, bool bigendian=false);
    
    static float floatFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormfloat(float f, unsigned char* buff, bool bigendian=false);
    
    // int64(8 bytes)
    static long long longLongFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormLongLong(long long l, unsigned char* buff, bool bigendian=false);
    
    static unsigned long long unsignedLongLongFormData(unsigned char* buff, bool bigendian=false);
    static void dataFormUnsignedLongLong(unsigned long long l, unsigned char* buff, bool bigendian=false);
    
};

NS_JOFW_END

#endif //_JO_DATA_UTILS_H_
