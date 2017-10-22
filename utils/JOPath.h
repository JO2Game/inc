/********************************************************************
CREATED: 25/1/2014   11:54
FILE: 	 JOPath.h
AUTHOR:  James Ou 
*********************************************************************/

#ifndef __JO_PATH_H__
#define __JO_PATH_H__

#include "utils/JOMacro.h"
#include <string>

using namespace std;
NS_JOFW_BEGIN

class JO_DLL JOPath
{
private:
	JOPath();

public:
	/************************************************************************/
	/* 把传入的字符串传为标准的路径
	/************************************************************************/
	static string standardisePath(const string &init, bool endSlash=true);

	/************************************************************************/
	/* 获取文件路径 去除文件名
	/************************************************************************/
	static string getFileBasePath(const string &path);
	/************************************************************************/
	/* 获取文件名 默认带后缀
	/************************************************************************/
	static string getFileName(const string &path, bool withSuffix=true);
	/************************************************************************/
	/* 获取文件后缀名
	/************************************************************************/
	static string getFileSuffix(const string &path);

	static string getFileWithoutSuffix(const string &path);

    /** 
	传入路径，分别输出路径的文件名及其所在目录
	qualifiedName：路径
	outBasename：文件名
	outPath：目录
	ext: 后缀
    */
    static void splitFilename(const string& qualifiedName,
        string& outBasename, string& outPath);

	static void splitFilename(const string& qualifiedName,
		string& outBasename, string& outPath, string& ext);

	
};

NS_JOFW_END

#endif // __JO_PATH_H__