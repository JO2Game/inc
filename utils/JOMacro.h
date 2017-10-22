//
//  Created by James on 15/3/12.
//  Copyright (c) 2015???dream. All rights reserved.
//

#ifndef __JOMACRO_H__
#define __JOMACRO_H__

#include "platform/CCPlatformConfig.h"
#include "cocos2d.h"

#ifdef __cplusplus
#define NS_JOFW_BEGIN                     namespace sophia_framework {
#define NS_JOFW_END                       }
#define USING_NS_JOFW                     using namespace sophia_framework
#else
#define NS_JOFW_BEGIN                     
#define NS_JOFW_END
#define USING_NS_JOFW                     
#endif 

/************************************************************************/
/* 平台相关                                                                     */
/************************************************************************/

#if (defined(WIN32) && defined(_WINDOWS)) || defined(WINRT) || defined(WP8)
	#if defined(_USRJOFWSTATIC)
		#define JO_DLL
		#define JO_DLL_TEMPLATE
	#else
		#if defined(_USRJOFWDLL)
			#define JO_DLL     __declspec(dllexport)
			#define JO_DLL_TEMPLATE		__declspec(dllexport)
		#else         /* use a DLL library */
			#define JO_DLL     __declspec(dllimport)
			#define JO_DLL_TEMPLATE		
		#endif
	#endif
#elif defined(_SHARED_)
	#define JO_DLL     __attribute__((visibility("default")))
	#define JO_DLL_TEMPLATE		__attribute__((visibility("default")))
#else
	#define JO_DLL
	#define JO_DLL_TEMPLATE
#endif

#if defined WIN32 || defined WP8 || defined COCOS3_4 
	#include <Windows.h>
	#define JOUSE_STD_THREAD 1
	#define THREAD_SLEEP(msec) Sleep(msec/1000.0f);
#else
	#include <unistd.h>
	#define THREAD_SLEEP(msec) usleep(msec);
#endif

/************************************************************************/
/* 快速属性处理                                                                     */
/************************************************************************/
#define JO_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define JO_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

#define JO_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: virtual varType get##funName(void) const { return varName; } \
public: virtual void set##funName(varType var)   \
{ \
if (varName != var) \
{ \
CC_SAFE_RETAIN(var); \
CC_SAFE_RELEASE(varName); \
varName = var; \
} \
}
#define JO_BREAK_IF(cond)           if(cond) break
#define JO_SAFE_DELETE(p)           do { if(p) { delete (p); (p) = nullptr; } } while(0)
#define JO_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define JO_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)

/************************************************************************/
/* 函数绑定                                                                     */
/************************************************************************/
#define JO_CBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define JO_CBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define JO_CBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define JO_CBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
#define JO_CBACK_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)
#define JO_CBACK_5(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, ##__VA_ARGS__)
#define JO_CBACK_6(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6 ##__VA_ARGS__)

/************************************************************************/
/* 数据大小端                                                                     */
/************************************************************************/
#define jo_host_is_big_endian (bool)(*(unsigned short *)"\0\xff" < 0x100)
#define swap_16Bit(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)
#define swap_32Bit(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define swap_64Bit(i) (i & 0xff) << 56 | (i >> 8 & 0xff) << 48 | (i >> 16 & 0xff) << 40 | (i >> 24 & 0xff) << 32 | (i >>32 & 0xff) << 24 | (i  >> 40 & 0xff) << 16 | (i  >> 48 & 0xff) << 8 | (i >> 56 & 0xff)

#define HOST2NET_16(val)  ((jo_host_is_big_endian == true)? (val) : swap_16Bit(val) )
#define NET2HOST_16(val)  ((jo_host_is_big_endian == true)? (val) : swap_16Bit(val) )
#define HOST2NET_32(val)  ((jo_host_is_big_endian == true)? (val) : swap_32Bit(val) ) //hton_32(val)
#define NET2HOST_32(val)  ((jo_host_is_big_endian == true)? (val) : swap_32Bit(val) ) //ntoh_32(val)
#define HOST2NET_64(val)  ((jo_host_is_big_endian == true)? (val) : swap_64Bit(val) ) //hton_64(val)
#define NET2HOST_64(val)  ((jo_host_is_big_endian == true)? (val) : swap_64Bit(val) ) //ntoh_64(val)

// limits
#ifndef SHRT_MAX
#define SHRT_MAX                        32767
#endif

#ifndef SHRT_MIN
#define SHRT_MIN                        -SHRT_MAX-1
#endif

#ifndef USHRT_MAX
#define USHRT_MAX                       SHRT_MAX*2+1
#endif

#ifndef USHRT_MIN
#define USHRT_MIN                       0
#endif

#ifndef INT_MAX
#define INT_MAX                         2147483647 
#endif

#ifndef UINT_MAX
#define UINT_MAX                        INT_MAX*2+1
#endif

#ifndef INT_MIN
#define INT_MIN                         -INT_MAX-1
#endif

#ifndef UINT_MIN
#define UINT_MIN                        0
#endif

#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX                   9223372036854775807
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX                  LONG_LONG_MAX*2+1
#endif

#ifndef LONG_LONG_MIN
#define LONG_LONG_MIN                   -LONG_LONG_MAX-1
#endif

#ifndef ULONG_LONG_MIN
#define ULONG_LONG_MIN                  0
#endif

NS_JOFW_BEGIN
typedef int LUA_FUNCTION;
typedef int lua_Object;
NS_JOFW_END

#define JO_EMTYP_STRING ""
#define JO_TEMPLATE_STR(T) #T 
#define JOUSE_STD_THREAD 1

#define  JO_SIZEOF_FLOAT sizeof(float)


#endif // !__JOMACRO_H__