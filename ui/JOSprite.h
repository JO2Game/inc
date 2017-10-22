#ifndef __JOSPRITE_H__
#define __JOSPRITE_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"
#include "ui/JOIImg.h"

NS_JOFW_BEGIN


class JO_DLL JOSprite : public Sprite, public JOIImg
{
	JO_CLS_MPOOL_DECLARE(JOSprite)
public:
	JOSprite();
	virtual ~JOSprite();
public:
	static JOSprite* create();

	static JOSprite* create(const std::string& srcKey, bool isAsyn = true, LoadSpriteCall call = nullptr);
	static JOSprite* create(const std::string& filePath, const std::string& imgName, bool isAsyn = true, short pixelFormat = (short)Texture2D::PixelFormat::RGBA8888, LoadSpriteCall call = nullptr);
	

	void setCallback(LoadSpriteCall call);
protected:
	virtual void _loadStart();
	virtual void _loadEnd();
	virtual bool _isLoading();
	virtual void _loadCancel();
	virtual void _emptyTexture();

protected:
	
	LoadSpriteCall m_loadCall;	
};

NS_JOFW_END

#endif //__JOSPRITE_H__