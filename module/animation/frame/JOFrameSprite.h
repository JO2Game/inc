#ifndef __JOFRAME_SPRITE_H__
#define __JOFRAME_SPRITE_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"

#include "ui/JOIImgSet.h"
#include "utils/JOClsMemoryPool.h"

NS_JOFW_BEGIN

class JO_DLL JOFrameSprite : public Sprite, public JOIImgSet
{
	JO_CLS_MPOOL_DECLARE(JOFrameSprite);
public:
	JOFrameSprite();
	virtual ~JOFrameSprite();

public:
	static JOFrameSprite* create();
	static JOFrameSprite* create(const std::string& aniKey, bool isAsyn = true, LoadSpriteCall call = nullptr);
	void setAniKey(const std::string& aniKey, bool isAsyn = true);
	void setCallback(LoadSpriteCall call);

	bool play(const std::string& aniName, bool bRepeat = true, std::function<void(JOFrameSprite*)> finishCall = nullptr);
	void setSpeed(float speed);
	Rect getTouchRect();
	float getHeadTitleOffsetY();
  
protected:	
	virtual void _loadStart();
	virtual void _loadEnd();
	virtual bool _isLoading();
	virtual void _loadCancel();
	virtual void _emptyTexture();

protected:
	bool _play(const std::string& aniName, bool bRepeat = true);
	void _finish();

protected:
	LoadSpriteCall m_loadCall;
	std::string m_aniKey;
	std::string m_tmpAniKey;
    
protected:
	bool				m_bValidate;
	bool				m_bRepeat;
	float				m_aniSpeed;		
	std::string         m_aniName;
	std::function<void(JOFrameSprite*)> m_finishCall;
	ActionInterval*		m_curAct;

	Rect				m_touchRect;
	float				m_headTitleOffsetY;
};

NS_JOFW_END

#endif //__JOFRAME_SPRITE_H__