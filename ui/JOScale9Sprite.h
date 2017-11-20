#ifndef __JOSCALE9SPRITE_H__
#define __JOSCALE9SPRITE_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;
#include "ui/UIScale9Sprite.h"

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"
#include "ui/JOIImg.h"

NS_JOFW_BEGIN

class JOSprite;

class JO_DLL JOScale9Sprite : public ui::Scale9Sprite, public JOIImg
{
	JO_CLS_MPOOL_DECLARE(JOScale9Sprite);
public:
	JOScale9Sprite();
	virtual ~JOScale9Sprite();
public:
	static JOScale9Sprite* create();

	static JOScale9Sprite* create(const std::string& srcKey, bool isAsyn = true, LoadSpriteCall call = nullptr);
	static JOScale9Sprite* create(const std::string& filePath, const std::string& imgName, bool isAsyn = true, short pixelFormat = (short)Texture2D::PixelFormat::RGBA8888, LoadSpriteCall call = nullptr);

	void setCallback(LoadSpriteCall call);
	//true即每次通过setKey后,九宫格都会保持原来大小
	//false的话,九宫格会是新设置图片的原始大小
	inline void beFitSize(bool beFit){ m_beFit = beFit; };
protected:
	virtual void _loadStart();
	virtual void _loadEnd();
	virtual bool _isLoading();
	virtual void _loadCancel();
	virtual void _emptyTexture();

	void _resetInset(Rect& org);
protected:
	
	LoadSpriteCall	m_loadCall;	
	JOSprite*		m_srcSprite;
	bool			m_beFit;
};

NS_JOFW_END

#endif //__JOSCALE9SPRITE_H__
