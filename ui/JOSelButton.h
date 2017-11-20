#ifndef __JOSELBUTTON_H__
#define __JOSELBUTTON_H__

#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "ui/JOButton.h"

NS_JOFW_BEGIN


class JO_DLL JOSelButton : public JOButton
{	
public:
	static JOSelButton* create(const std::string& key, BUTTON_CALL call, const std::string& title = "");
	
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);

protected:
	short			m_shouldState;
	
};

NS_JOFW_END

#endif //__JOSELBUTTON_H__