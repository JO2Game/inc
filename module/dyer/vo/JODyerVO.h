#ifndef __JODYER_VO_H__
#define __JODYER_VO_H__

#include "utils/JOMacro.h"

namespace cocos2d
{
	class Sprite;
}

NS_JOFW_BEGIN

class JOSprite;
class DyerData;

class JO_DLL JODyerBlockVO{
public:	
	JODyerBlockVO();
	~JODyerBlockVO();
	void init(cocos2d::Sprite* spr, double time, const std::string& srcPath);

	void done();

public:
	cocos2d::Sprite* m_block;
	std::string m_srcPath;
	double m_time;
};

class JO_DLL JODyerVO{
public:	
	JODyerVO();
	~JODyerVO();
	void init(cocos2d::Sprite* spr, DyerData* dd, const std::string& srcPath);
	void done();

public:
	cocos2d::Sprite* m_ori;
	DyerData* m_dd;
	std::string m_srcPath;
};

	
NS_JOFW_END

#endif //__JODYER_VO_H__