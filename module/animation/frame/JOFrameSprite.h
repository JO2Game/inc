#ifndef __JOFRAME_SPRITE_H__
#define __JOFRAME_SPRITE_H__

#include <string>
#include <functional>
#include <unordered_map>

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
	typedef std::function<void(JOFrameSprite*, std::string&, short)> FrameEventCall;
	JOFrameSprite();
	virtual ~JOFrameSprite();

public:
	static JOFrameSprite* create();
	static JOFrameSprite* create(const std::string& aniKey, bool isAsyn = true, LoadSpriteCall call = nullptr);
	/************************************************************************/
	/* 设置加载的动画配置数据和加载完成回调                                                                     */
	/************************************************************************/
	void setAniKey(const std::string& aniKey, bool isAsyn = true);
	/************************************************************************/
	/* 判断当前是否加载aniKey对应的数据                                                                     */
	/************************************************************************/
	bool isSetupAniKey(const std::string& aniKey);
	void setCallback(LoadSpriteCall call);
	/************************************************************************/
	/* 判断是否能播放aniName动画                                                                     */
	/************************************************************************/
	bool isCanPlay(const std::string& aniName);
	/************************************************************************/
	/* 播放动画aniName                                                                     */
	/************************************************************************/
	bool play(const std::string& aniName, bool bRepeat = true);
	void restart();
	/************************************************************************/
	/* 停止播放                                                                     */
	/************************************************************************/
	inline void stop(){ m_isPlaying = false; };
	/************************************************************************/
	/* 设置播放速度                                                                      */
	/************************************************************************/
	inline void setSpeed(float speed){ m_aniSpeed = speed; };

public:
	/************************************************************************/
	/* 保留项                                                                     */
	/************************************************************************/
	Rect getTouchRect();
	float getHeadTitleOffsetY();

public:	
	/************************************************************************/
	/* 添加帧事件
	/* 帧数从0开始, -1表示最后一帧                                                                     */
	/************************************************************************/
	void setEventCall(const std::string& aniName, FrameEventCall call, short frameIdx = -1);
	/************************************************************************/
	/* 移除帧事件
	/************************************************************************/
	void removeCall(const std::string& aniName, short frameIdx);
	/************************************************************************/
	/* 移除对应动画的所有帧事件
	/************************************************************************/
	void removeCall(const std::string& aniName);
	/************************************************************************/
	/* 移除所有帧事件
	/************************************************************************/
	void removeAllCall();


public:
	//over write======================================
	virtual void setVisible(bool visible);
	virtual void onEnter();
	virtual void onExit();

protected:
	void _tick();
  
protected:	
	virtual void _loadStart();
	virtual void _loadEnd();
	virtual bool _isLoading();
	virtual void _loadCancel();
	virtual void _emptyTexture();	

protected:
	LoadSpriteCall m_loadCall; //加载完成回调
	std::string m_aniKey; //动画数据配置
	std::string m_tmpAniKey;
    
protected:

	bool				m_bRepeat; 
	float				m_aniSpeed;		
	std::string         m_aniName; //具体一个动画
	
	
	Rect				m_touchRect; //点击区域
	float				m_headTitleOffsetY;

	std::unordered_map<std::string, std::unordered_map<short, FrameEventCall > > m_callMap; //注册的关键帧事件

	cocos2d::Animation*			m_curAnimation; //加载后的动画数据
	std::vector<float>			m_splitTimes; //动画间隔间的时间
	unsigned short				m_curFrameIdx; //当前帧
	float						m_elapseTime; //逝去的时间
	bool						m_isPlaying; //判断是否播放中
	
};

NS_JOFW_END

#endif //__JOFRAME_SPRITE_H__