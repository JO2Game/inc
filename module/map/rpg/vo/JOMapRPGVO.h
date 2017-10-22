
#ifndef __JOMAP_PRG_VO_H__
#define __JOMAP_PRG_VO_H__

#include <unordered_map>
#include "external/json/document.h"
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOMapRPGVO
{
public:
	JOMapRPGVO();
	~JOMapRPGVO();

	void setMapVal(rapidjson::Document &root, unsigned short id);
	/*
	PASS可通行, BLOCK阻挡点, OBSCURE可通行并半透遮挡点
	*/
	enum { PASS='0', BLOCK='1', OBSCURE='2' };

public:	
	inline const unsigned short getMapId(){ return mapId; };
	/*
	格的宽高
	*/
	inline const unsigned short cellWidth(){ return cellW; };
	inline const unsigned short cellHeight(){ return cellH; };
	/*
	根据格子的大小的行列数
	*/
	inline const unsigned short rows(){ return row; };
	inline const unsigned short cols(){ return col; };
	/*
	整地图的宽高
	*/
	inline const unsigned int mapWidth(){ return mapW; };
	inline const unsigned int mapHeight(){ return mapH; };
	/*
	地图纹理块宽高
	*/
	inline const unsigned short sliceWidth(){ return sliceW; };
	inline const unsigned short sliceHeight(){ return sliceH; };
	/*
	地图纹理块横列向数量
	*/
	inline const unsigned short sliceWidthC(){ return sliceWC; };
	inline const unsigned short sliceHeightC(){ return sliceHC; };
	/*
	每个格的属性信息
	*/
	inline const unsigned char* cellDatas(){ return cellData; };
	unsigned char cellDataWithIndex(unsigned short index);
	void addBlock(unsigned int index);
	void removeBlock(unsigned int index);
	void restoreDatas();

private:
	unsigned short mapId;

	unsigned short cellW;
	unsigned short cellH;
	unsigned short row;
	unsigned short col;
	unsigned int mapW;
	unsigned int mapH;
	unsigned short sliceW;
	unsigned short sliceH;
	unsigned short sliceWC; //col
	unsigned short sliceHC; //row

	unsigned char* cellData;
	unsigned int cellDataSize;

	typedef std::unordered_map<unsigned int, unsigned char> ORG_FLAG_MAP;
	ORG_FLAG_MAP orgFlagMap;
};

NS_JOFW_END

#endif //__JOMAP_PRG_VO_H__
