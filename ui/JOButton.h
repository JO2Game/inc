#ifndef __JOBUTTON_H__
#define __JOBUTTON_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"

NS_JOFW_BEGIN

class JOButton;
class JOSprite;
class JOScale9Sprite;
class JOLabel;

typedef std::function<void(JOButton*, short, Touch*)> BUTTON_CALL;

class JO_DLL JOButton : public Node
{
	JO_CLS_MPOOL_DECLARE(JOButton);
	static short		s_zoomMode;
	static std::string	s_norShaderKey;
	static std::string	s_selShaderKey;
	static std::string	s_disShaderKey;
	static float		s_fsize;
	static std::string	s_falias;
	static Color3B		s_fcolor;
	static short		s_boldsize;
	static Color4B		s_outcolor;
public:
	static void setDefaultBase(short zoomMode);
	static void setDefaultShader(const std::string& norKey, const std::string& selKey, const std::string& disKey);
	static void setDefaultTitleBase(float fsize, const std::string& falias, Color3B fcolor);
	static void setDefaultTitleOutline(short boldsize, Color4B outcolor);

public:
	enum{BTN_NOR=1, BTN_SEL, BTN_DIS};
	enum{ZOOM_NONE=1, ZOOM_BIG, ZOOM_SMALL};
	JOButton();
	virtual ~JOButton();
public:
	static JOButton* create(const std::string& key = "");
	static JOButton* create(const std::string& key, BUTTON_CALL call, bool bScale = false, const std::string& title = "");
	bool init(const std::string& key, BUTTON_CALL call, bool bScale = false, const std::string& title = "");
	inline void setCall(BUTTON_CALL call){ m_call = call; };

	void setKey(const std::string& key);
	
	void setScaleEnable(bool enable);
	void setZoomMode(short zoomMode);
	void setOtherStateKey(const std::string& selKey, const std::string& disKey);

	void setNorShaderKey(const std::string& key, std::function<void(Node*, cocos2d::GLProgramState*)> setValCall = nullptr);
	void setSelShaderKey(const std::string& key, std::function<void(Node*, cocos2d::GLProgramState*)> setValCall = nullptr);
	void setDisShaderKey(const std::string& key, std::function<void(Node*, cocos2d::GLProgramState*)> setValCall = nullptr);

	void setBtnState(short state);
	inline short getBtnState(){ return m_curState; };
	inline void setHandleAllTouch(bool bHandle){ m_bHandleAllTouch = bHandle; };

	void setTitle(const std::string& title);
	void setTitleArg(const std::string& fName, short fSize, Color3B fColor = s_fcolor, short blodSize = s_boldsize, Color4B outColor = s_outcolor);
	std::string getTitleString();
public:
	virtual void setContentSize(const Size& contentSize);
	
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	
protected:
	void _setShader(const std::string& key, bool bRestore, std::function<void(Node*, cocos2d::GLProgramState*)> setValCall = nullptr);
	void _setKey(std::string& key);
	void _touchScaleBeginHandle();
	void _touchScaleEndHandle();
	void _touchScaleCancelHandle();

	void _layout();

protected:
	BUTTON_CALL		m_call;
	JOSprite*		m_img;
	JOScale9Sprite* m_scaleImg;
	JOLabel*		m_title;
	bool			m_bScale;
	bool			m_bHandleAllTouch;
	
	short			m_curState;
	std::string		m_curKey;
	std::string		m_norKey;
	std::string		m_selKey;
	std::string		m_disKey;

	std::string		m_norShaderKey;
	std::string		m_selShaderKey;
	std::string		m_disShaderKey;
	std::function<void(Node*, cocos2d::GLProgramState*)> m_norShaderValCall;
	std::function<void(Node*, cocos2d::GLProgramState*)> m_selShaderValCall;
	std::function<void(Node*, cocos2d::GLProgramState*)> m_disShaderValCall;

	short			m_zoomMode;
	bool			m_bCanTouch;
	float			m_fTouchOrgScaleX;
	float			m_fTouchOrgScaleY;
	ActionInterval* m_zoomBegan;
	ActionInterval* m_zoomEnd;
};

NS_JOFW_END

#endif //__JOBUTTON_H__