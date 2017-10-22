
#ifndef __JOMAP_PRG_TILE_VO_H__
#define __JOMAP_PRG_TILE_VO_H__

#include <string>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOMapRPGTileVO
{
public:
	JOMapRPGTileVO();
	~JOMapRPGTileVO();

	/*
	像素坐标
	*/
	short x;
	short y;
	/*
	属于哪一行哪一列，对应的是纹理块
	*/	
	unsigned short colX;
	unsigned short rowY;
	/*
	坐标对应的下标
	*/	
	unsigned int index;
	
	/*
	地图id
	*/
	unsigned short mapId;
	/*
	纹理图key
	*/
	std::string key;

	/*
	记录是否需要本轮加载
	*/
	bool bCurRound;

	/*
	记录是否已加载图块
	*/
	bool bLoaded;
};

NS_JOFW_END

#endif //__JOMAP_PRG_TILE_VO_H__
