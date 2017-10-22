
#ifndef __JOMAP_RPG_ASSET_H__
#define __JOMAP_RPG_ASSET_H__

#include <unordered_map>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "datastruct/JOPoint.h"
#include "datastruct/JOAStar.h"

NS_JOFW_BEGIN

class JOMapRPGVO;

class JO_DLL JOMapRPGAsset : public JOSingleton<JOMapRPGAsset>
{
public:	
	JOMapRPGAsset();
	virtual ~JOMapRPGAsset();
public:
	inline void setMapConfigPath(std::string& path){ mapPath = path; };
	inline const std::string getMapConfigPath(){ return mapPath; };
	JOMapRPGVO* loadMap(unsigned short mapId);

	inline JOMapRPGVO* getMapVO(){ return curMapVO; };

	/*
	格坐标转地图坐标 返回Point coord2Map
	地图坐标转格坐标 返回Point map2Coord
	*/
	JOPoint coord2Map(unsigned short cellx, unsigned short celly);	
	JOPoint map2Coord(unsigned short mapx, unsigned short mapy);

	/*
	图块坐标转地图坐标 返回Point slice2Map
	地图坐标转图块坐标 返回Point map2slice
	*/
	JOPoint slice2Map(unsigned short slicex, unsigned short slicey);
	JOPoint map2slice(unsigned short mapx, unsigned short mapy);

	/*
	根据图片块\格的行列，获取当前图片块的下标
	*/
	unsigned short getSliceTileIdx(unsigned short tileRow, unsigned short tileCol);
	unsigned short getCellTileIdx(unsigned short tileRow, unsigned short tileCol);

	/*
	格状态相关
	*/	
	unsigned char cellStateWithIndex(unsigned short index);
	unsigned char cellStateWithCoord(unsigned short cellx, unsigned short celly);
	unsigned char cellStateWithMapXY(unsigned short mapx, unsigned short mapy);

	/*
	返回路径点
	*/
	bool createPath(JOPoint& pos, JOPoint& targetPos, std::deque<JOPoint>& path);

	/*
	过滤同一直线上的点
	*/
	void filterSameLine(std::deque<JOPoint>& oldPath, std::deque<JOPoint>& newPath);

private:
	JOMapRPGVO* _getMapVO(unsigned short mapId);	

private:
	unsigned short maxSliceLen;
	unsigned short maxCellLen;
	JOMapRPGVO* curMapVO;
	std::string mapPath;
	typedef std::unordered_map<unsigned short, JOMapRPGVO*> VO_MAP;
	VO_MAP voMap;

	JOAStar astarMachine;
};

NS_JOFW_END

#endif //__JOMAP_RPG_ASSET_H__
