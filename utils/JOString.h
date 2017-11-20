/********************************************************************
CREATED: 25/1/2014   11:54
FILE: 	 JOString.h
AUTHOR:  James Ou 
*********************************************************************/

#ifndef __JO_STRING_H__
#define __JO_STRING_H__

#include "utils/JOMacro.h"

#include <string>
#include <vector>

NS_JOFW_BEGIN
using namespace std;

class JO_DLL JOString
{
private:
	JOString();

public:     
	
    /****************************************************************************
	 函数名称: str_to_hex
	 函数功能: 字符串转换为十六进制
	 输入参数: string 字符串 cbuf 十六进制 len 字符串的长度。
	 输出参数: 无
     *****************************************************************************/
	static int str_to_hex(char *string, unsigned char *cbuf, int len);
    
    /****************************************************************************
	 函数名称: hex_to_str
	 函数功能: 十六进制转字符串
	 输入参数: ptr 字符串 buf 十六进制 len 十六进制字符串的长度。
	 输出参数: 无
     *****************************************************************************/
	static void hex_to_str(char *ptr, unsigned char *buf, int len);
    
    /** 
	移除空白符（包括空格和Tab）
	可以选择性地移除前或后的，默认两边都去除
    */
    static void trim( string& str, bool left = true, bool right = true );

    /**
	分隔字符串
	str：为要分隔的字符串
	delims：分隔符，默认为：\t\n
	maxSplits：分隔次数，0表示分完为止
    */
	static vector< string > split( const string& str, const string& delims = "\t\n ", unsigned int maxSplits = 0);
	
	/**
	合并字符串数组
	vs：为要字符数组
	delims：连接符，默认为：""
	*/
	static string concat(vector<string> vs, const string& delims = "");

	/************************************************************************/
	/* 判断src是否包含子串sub
	/************************************************************************/
	static bool isContains(const string& src, const string& sub);
    /** 
	转成小写字母
    */
    static void toLowerCase( string& str );

    /** 
	转成大写字母
    */
    static void toUpperCase( string& str );
	
    /** 
	判断字符串是否以什么开头
	str：为要判断的字符串
	pattern：为判断参数
	lowerCase：是否统一以小写方式判断
    */
    static bool startsWith(const string& str, const string& pattern, bool lowerCase = true);

    /**
	判断字符串是否以什么结尾
	str：为要判断的字符串
	pattern：为判断参数
	lowerCase：是否统一以小写方式判断
    */
    static bool endsWith(const string& str, const string& pattern, bool lowerCase = true);

	/**
	把字符串里面的\n转换为换行符
	*/
	static string convertBreakLine(const char* pszText);

	/**
	把pszText的所有的pszSrc替换为pszDest
	*/
	static string replaceAll(const char* pszText, const char* pszSrc, const char* pszDest, bool bAll=true);
	/**
	两字符串是否内容相等
	*/
	static bool isEqual(const char* str1, const char* str2);
	
	static string	 formatString(const char* fmt , ...);		

	/**
	基本类型转字符串
	*/
	static string iToa(int value);
	static string llToa(long long value);
	static string boolToa(bool value);
	static string floatToa(float value);
	static string doubleToa(double value);

	/**
	字符串转基本类型
	不成功全部返0，bool的返回false
	*/
	static unsigned char toUChat(const char* str);
	static char toChat(const char* str);
	static int toInt( const char* str );
	static unsigned toUnsigned( const char* str );
	/*
	str内必须为true或false
	*/
	static bool toBool( const char* str );
	static float toFloat( const char* str );
	static double toDouble( const char* str );
	static long long toLongLong( const char* str );
	/**
	返回UTF8的位长度
	return the length of one utf8 character
	*/
	static int getUTF8CharacterLength(const char* p, int len);

	/**
	返回pText中每一个UTF8字符在字符串中的位置
	*/
	static vector<int> getUTF8StringSplitInfo(const char* pText);

	/**
	?????????
	*/
	static int stringCount(const char* pTex);
	/************************************************************************/
	/* 把二进制转换成字符串形式, 一般用于输出查看
	/************************************************************************/
	static string data2String(const unsigned char* pData, unsigned int len);

	/************************************************************************/
	/* ffffff转成COLOR， 不成功时返回ccc3b(0,0,0)
	/************************************************************************/
	//static ccColor3B string2Color(const char* pColorText);
		

private:
	static unsigned char convertFromHex(string hex);
};

NS_JOFW_END

#endif // __JO_STRING_H__