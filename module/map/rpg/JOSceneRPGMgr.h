#ifndef __JOSCENE_RPG_MGR_H__
#define __JOSCENE_RPG_MGR_H__

#include <unordered_map>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "datastruct/JOPoint.h"
#include "datastruct/JOSize.h"

NS_JOFW_BEGIN

class JOMapRPGTileVO;

class JO_DLL JOSceneRPGMgr : public JOSingleton<JOSceneRPGMgr>
{
public:	
	JOSceneRPGMgr();
	virtual ~JOSceneRPGMgr();

public:
	/*
	设置显示区域
	*/
	void setDisplaySize(unsigned short w, unsigned short h);
	inline JOSize getDisplaySize() { return displaySize; };
	/*
	设置显示中心点
	*/
	void setOrigin(float x, float y);
	inline JOPoint getOrigin(){ return origin; };
	
	/*
	移除所有图块数据
	*/
	void clearAllTile();

	/*
	设置回调
	*/
	void setRemoveTileCall(std::function<void(unsigned short)>& call);
	void setLoadTileCall(std::function<void(void*, float, float, unsigned short)>& call);
	void setDebugCall(std::function<void(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned char)>& call);

private:
	void _load();
	void _refreshRect();

private:
	JOPoint origin;
	JOSize displaySize;	

private:
	typedef std::unordered_map<unsigned short, JOMapRPGTileVO*> TILE_MAP;
	TILE_MAP tileMap;

	/*
	移除图块回调 参数为要移除的下标
	*/
	std::function<void(unsigned short)> _removeTileCall;
	/*
	加载图块回调 参数1纹理,2坐标x,3坐标y,4加载的下标
	*/
	std::function<void(void*, float, float, unsigned short)> _loadTileCall;
	/*
	加载格状态的回调
	参数1下标,2坐标x,3坐标y,4w,5h,6格状态
	w\h为0,表示移除对应下标
	*/
	std::function<void(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned char)> _debugCall;
	TILE_MAP debugTileMap;
    
    unsigned int m_sn;
};

NS_JOFW_END

#endif	//__JOSCENE_RPG_MGR_H__
