#ifndef __JOPASS_BUTTON_H__
#define __JOPASS_BUTTON_H__

#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "ui/JOButton.h"

NS_JOFW_BEGIN

class JOSprite;

class JO_DLL JOPassButton : public JOButton
{	
public:
	JOPassButton();
	virtual ~JOPassButton();
	enum{PASS_LEFT=1, PASS_RIGHT, PASS_TOP, PASS_BOTTOM};
public:
	static JOPassButton* create(const std::string& key, const std::string& passKey, BUTTON_CALL call, bool bScale = false, const std::string& title = "");
	
	void setDirect(short direct);
	void setPassImgKey(const std::string& key);

	inline void setPassTime(float passTime){ m_passTime = passTime; };
	inline void setCurTime(float curTime){ m_curTime = curTime; };

	void startPassing();
	void stopPassing();

public:
	virtual void onContentSizeChange();
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);

protected:
	void _passHandle();
	void _passTick();
protected:
	unsigned int m_sn;
	short	m_direct;
	float	m_passTime;
	float	m_curTime;
	bool	m_bPassing;
	ClippingNode*	m_clip;
	JOSprite*		m_stencil;
	JOSprite*		m_passImg;
};

NS_JOFW_END

#endif //__JOPASS_BUTTON_H__