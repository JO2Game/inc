#ifndef __JORESMGR_H__
#define __JORESMGR_H__

#include <unordered_map>
#include <string>
#include <time.h>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

namespace cocos2d
{
	class Texture2D;
}

NS_JOFW_BEGIN
class JOResRecordVO;

/************************************************************************/
/* 需要有方法通过srcKey,获取源文件/plist及动画配置文件
/************************************************************************/

class JO_DLL JOResMgr : public JOSingleton< JOResMgr >
{
public:
	JOResMgr();
	virtual ~JOResMgr();
public:
	
	void setRecord(std::string& srcPath, cocos2d::Texture2D* tex, short resType);

	bool isResLoaded(std::string& resKey);
	void quoteRes(std::string& resKey);
	void unQuoteRes(std::string& resKey);

public:
	inline void setCheckInterval(float interval){ checkInterval = interval; };
	void tick();
protected:
	void _checkDispose();
	float checkInterval;

	typedef std::unordered_map<std::string, JOResRecordVO*> RECORD_MAP;
	RECORD_MAP recordMap;

};


NS_JOFW_END
#endif //__JORESMGR_H__