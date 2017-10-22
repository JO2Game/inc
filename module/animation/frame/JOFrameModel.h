#ifndef __JOFRAME_MODEL_H__
#define __JOFRAME_MODEL_H__

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"

#include "cocos2d.h"
USING_NS_CC;


NS_JOFW_BEGIN

class JOFrameSprite;

/************************************************************************/
/* 一个动画配置对应一个图集, 一个动画配置里可以有多组动作组合
/************************************************************************/

class JO_DLL JOFrameModel : public Node
{
	JO_CLS_MPOOL_DECLARE(JOFrameModel);
public:
	JOFrameModel();
	virtual ~JOFrameModel();

public:
	static JOFrameModel* create();
	bool init();
	
	bool playRoot(const std::string& aniName, bool bRepeat = true, std::function<void(JOFrameModel*)> finishCall = nullptr);
    /*
    idx为组件对应下标id
    */
	bool playPart(const std::string& aniName, unsigned int idx, bool bRepeat = true);

	void stop();
	
	void setSpeed(float speed);

	/************************************************************************/
	/* 首个为root根视图
	/************************************************************************/
	void initAnimations(size_t count);
	bool setAnimation(unsigned int idx, const std::string& aniKey);
	bool setAnimationColor(unsigned int idx, Color3B color);
	void setAnimationZorder(unsigned int idx, int zorder);
	bool isAnimValidate(unsigned int idx);

public:
	JOFrameSprite* getRoot();

	void setTouchCall(std::function<void(JOFrameModel*)> touchCall);

public:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	
protected:
	void _clearAnimations();
	void _onPlayFinish(JOFrameSprite* fsprite);
	bool _inTouchRect(Touch* pTouch);

protected:
	unsigned short		m_aniSpriteCount;
	std::vector<JOFrameSprite*> m_aniSprites;
	std::function<void(JOFrameModel*)> m_finishCall;
	std::function<void(JOFrameModel*)> m_touchCall;
	std::function<void(JOFrameSprite*)> m_tmpCallVal;
	bool				m_touchRectDirty;
	Rect				m_touchRect;
	bool				m_bRepeat;
	float				m_aniSpeed;		
	std::string         m_rootAniName;
	
	
};

NS_JOFW_END

#endif //__JOFRAME_MODEL_H__