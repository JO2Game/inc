/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 JOFileMgr.h
 AUTHOR:  James Ou
 *********************************************************************/

#ifndef __JOFILEMGR_H__
#define __JOFILEMGR_H__

#include <string>
#include <list>
#include <vector>
#include <functional>

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "core/datautils/JOData.h"

NS_JOFW_BEGIN

class JOFileCacheVO;

class JO_DLL JOFileMgr : public JOSingleton<JOFileMgr>
{
public:
	JOFileMgr();
	virtual ~JOFileMgr();

public:
	JOData* getFileData(const std::string& fPath);
	void clearFileCache();
	inline void setCheckInterval(float interval){ m_checkInterval = interval; };
	inline void setRemoveInterval(float interval){ m_removeInterval = interval; };

	void tick();
protected:
	void _checkFileCache();
public:
	/*
	创建多级目录函数
	*/
	static bool MkMulDir(const std::string& pPath);
	static bool isFileExist(const std::string& pPath);
	static void setFileExistCall(const std::function<bool(const std::string&)> call);
	/*
	把resData二进制数据， copy到destPath
	*/
    static bool copyData( unsigned char* resData, unsigned int dataLen, const char* destPath );
    static bool copyFile( const char* srcPath, const char* destPath );
    static bool moveFile( const char* resPath, const char* destPath );
    static bool removeFile( const char* filePath );
    static bool removeAllFileInPath(const char* path);
	static bool wirteFile(const char* srcPath, const unsigned char* data, const unsigned int dataLen);
    static void getFilePathInDIR( const char* dirPath, std::list<std::string> &fileList, const char* suffix="" );
	static void setGetFileDataCall(const std::function<JOData*(const std::string&)> call);
	/*
	获取文件的Md5
	*/
	static void setFile2Md5Function(const std::function<std::string(const std::string&)> fileData2Md5Fun);
	static std::string fileMd5(const std::string& filePath);
    static std::string stringMd5(const std::string& str);
    
	/*
	zip相关
	返回的char* 需要free
	*/
    static char * ungzip(std::vector<char> *source, int *len);
    
    static bool zip_buffer(const char *src_buffer, const unsigned int src_len, std::vector<char> &result_buffer);
    static unsigned int get_temp_buffer_size(const unsigned int src_length);
    static bool unzip_buffer(const char *src_buffer, const unsigned int src_len, std::vector<char> &result_buffer);

	/************************************************************************/
	/* 打开文件管理器 选定目录
	/************************************************************************/
	static std::string getFileExplorerDir(std::string rootPath="");
private:
    typedef std::list<std::string> FILELIST;
    static bool _haveSuffix( const char* fileName, const char* suffix );
    static void _getFilePathInDIR( const char* dirPath, FILELIST &fileList, const char* suffix="");
    static void _makeDir(const char *strPath);
    static int testdir(char *path);
    
	static std::function<std::string(const std::string&)> s_fileData2Md5Fun;
	static std::function<JOData*(const std::string&)> s_getFileDataCall;
	static std::function<bool(const std::string&)> s_isFileExistCall;
private:
	std::unordered_map<std::string, JOFileCacheVO*> m_fileDataMap;

	float m_checkInterval;
	float m_removeInterval;
};

NS_JOFW_END

#endif // __JOFILEMGR_H__
