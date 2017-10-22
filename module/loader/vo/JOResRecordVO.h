#ifndef __JORESRECORDVO_H__
#define __JORESRECORDVO_H__

#include <time.h>
#include <string>
#include "utils/JOMacro.h"

namespace cocos2d
{
	class Texture2D;
}

NS_JOFW_BEGIN

class JO_DLL JOResRecordVO
{
public:
	void setRecord(const std::string srcPath, cocos2d::Texture2D *texture, int resType);
	void dispose();

	void increase();
	void decrease();
public:
	int count;
	short resType;
	clock_t noQuoteTime;
	std::string srcPath;
	cocos2d::Texture2D *tex;
};

NS_JOFW_END

#endif //__JORESRECORDVO_H__