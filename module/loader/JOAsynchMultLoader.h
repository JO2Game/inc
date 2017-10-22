#ifndef __JOASYNCHMULTLOADER_H__
#define __JOASYNCHMULTLOADER_H__

#include <string>
#include "module/loader/JOAsynchBaseLoader.h"
#include "utils/JOSingleton.h"

namespace cocos2d
{
	class Texture2D;
}

NS_JOFW_BEGIN

class JO_DLL JOAsynchMultLoader : public JOAsynchBaseLoader, public JOSingleton< JOAsynchMultLoader >
{
public:
	JOAsynchMultLoader();
	inline void setAsynchMaxNum(unsigned short maxNum){ asynchMaxNum = maxNum; };
	
protected:
	virtual void startLoadImg();
	virtual void asyncLoadCompleteCall(cocos2d::Texture2D* tex, const std::string& imgPath);
	
private:
	
	int loadedImgNum;
	unsigned short asynchMaxNum;
};

NS_JOFW_END
#endif //__JOASYNCHMULTLOADER_H__