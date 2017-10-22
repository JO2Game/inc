#ifndef __JOASYNCHLOADERVO_H__
#define __JOASYNCHLOADERVO_H__

#include <unordered_map>
#include <list>
#include <string>
#include <functional>
#include "utils/JOMacro.h"
#include "module/loader/JOAsynchBaseLoader.h"

namespace cocos2d
{
	class Texture2D;	
}

NS_JOFW_BEGIN

//class JODataBundle;
class JODataCoder;

class JO_DLL JOAsynchLoaderVO
{
public:
	static void asynchExecLuaCall(int luaHandle, cocos2d::Texture2D* tex, std::string source, int resType, JODataCoder* dataCoder, unsigned int index, unsigned int totalCount);
public:
	JOAsynchLoaderVO(){};
	
	void setData(const std::string src, int resType, cocos2d::Texture2D::PixelFormat pixel, int luaHandle, JODataCoder* dataCoder, unsigned int sn, unsigned int totalCount = 1);
	void setData(const std::string src, int resType, cocos2d::Texture2D::PixelFormat pixel, CompLeteCall handle, JODataCoder* dataCoder, unsigned int sn, unsigned int totalCount = 1);
	void unBindCall();
	void init();
	void exec(cocos2d::Texture2D* tex, unsigned int index = 1);

public:
	
	std::string source;
	std::string baseFileName;
	std::string plist;	

	cocos2d::Texture2D::PixelFormat pixel;
	short resType;
	unsigned int sn;
	unsigned int totalCount;
	int luaLoadComplete;	
	CompLeteCall loadComplete;
	JODataCoder* dataCoder;
	std::list<JOAsynchLoaderVO*> samePathList;
};

NS_JOFW_END
#endif //__JOASYNCHLOADERVO_H__