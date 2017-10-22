#ifndef __ASYNCHBASELOADER_H__
#define __ASYNCHBASELOADER_H__

#include <unordered_map>
#include <list>
#include <string>
#include <functional>
#include "utils/JOMacro.h"


namespace cocos2d
{
	class Texture2D;
	class Node;
};


NS_JOFW_BEGIN

//class JODataBundle;
class JODataCoder;
class JOAsynchLoaderVO;
typedef std::function<void(cocos2d::Texture2D*, std::string, short, JODataCoder*, unsigned short, unsigned short)> CompLeteCall;

/*
用于异步加载精灵回调
*/
typedef std::function<void(cocos2d::Node*, std::string, std::string)> LoadSpriteCall;

class JO_DLL JOAsynchBaseLoader
{
public:
	enum { RES_FRAME = 1/*图集*/, RES_IMG/*单图*/, RES_ANIMATION/*帧动画*/, RES_ARMATURE/*骨骼动画*/, RES_MUSIC/*背景音乐*/, RES_SOUND/*音效*/ };
	enum { QUEUE = 1, MULT };
public:
	JOAsynchBaseLoader();
	~JOAsynchBaseLoader();
	/*
	参数1是加载的文件路径或集合， 参数2是加载完的回调， 参数3、4是逻辑传入，用于回调的参数
	*/
	
	void load(unsigned int sn, const std::string srcPath, short resType, const CompLeteCall loadCompleteCall, JODataCoder* dataCoder = nullptr, cocos2d::Texture2D::PixelFormat pixel = cocos2d::Texture2D::PixelFormat::NONE);
	void load(unsigned int sn, std::list<std::string> srcPathList, short resType, const CompLeteCall loadCompleteCall, JODataCoder* dataCoder = nullptr, cocos2d::Texture2D::PixelFormat pixel = cocos2d::Texture2D::PixelFormat::NONE);

	void cancelLoad(unsigned int sn);
	/*
	void load(const std::string srcPath, short resType, LUA_FUNCTION luaCompleteCall, JODataBundle* dataBundle = nullptr);
	void load(std::list<std::string> srcPathList, short resType, LUA_FUNCTION luaCompleteCall, JODataBundle* dataBundle = nullptr);
	*/
protected:
	virtual void startLoadImg() = 0;	
	virtual void asyncLoadCompleteCall(cocos2d::Texture2D* tex, const std::string& imgPath);
	/*
	返回nullptr是正常流程,否则即需要加入allLoadList
	*/
	void _load(JOAsynchLoaderVO* vo);
	
	void _handleCallAsynch(JOAsynchLoaderVO* vo);
	void _handleComple(cocos2d::Texture2D* tex, JOAsynchLoaderVO* vo);

	bool _loadVo(const std::string srcPath, short resType, CompLeteCall loadCompleteCall, LUA_FUNCTION luaCompleteCall, JODataCoder* dataCoder, unsigned short idx, unsigned short total);
	unsigned int _snFindCurIdx(unsigned int sn, unsigned int total);

	void _addSnVoRecord(JOAsynchLoaderVO* vo);
	void _removeSnVoRecord(JOAsynchLoaderVO* vo);
protected:
	
	std::list<JOAsynchLoaderVO*> allLoadList;
	typedef std::unordered_map<std::string, JOAsynchLoaderVO*> LOADERVO_MAP;
	LOADERVO_MAP curLoadMap;

	/************************************************************************/
	/* 用于管理列表加载时,加载返回的当前数
	/************************************************************************/
	typedef std::unordered_map<unsigned int, unsigned int> SN_CURIDX_MAP;
	SN_CURIDX_MAP sn_curIdx_map;

	typedef std::unordered_map<unsigned int, std::list<JOAsynchLoaderVO*> > SN_LOADERVOs_MAP;
	SN_LOADERVOs_MAP sn_loaderVos_map;
	
};


NS_JOFW_END
#endif //__ASYNCHBASELOADER_H__