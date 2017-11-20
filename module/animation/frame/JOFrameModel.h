#ifndef __JOFRAME_MODEL_H__
#define __JOFRAME_MODEL_H__

#include <unordered_map>
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
	
	/************************************************************************/
	/* 停止播放帧动画                                                                     */
	/************************************************************************/
	void stop();
	/************************************************************************/
	/* 设置播放速度                                                                     */
	/************************************************************************/
	void setSpeed(float speed);

	/************************************************************************/
	/* 设置总共的节点数                                                                     */
	/* 默认首个为root根视图														*/		
	/************************************************************************/
	void initAnimations(size_t count);
	
	/************************************************************************/
	/* 设置对应节点的颜色                                                                     */
	/************************************************************************/
	bool setAnimationColor(unsigned int idx, Color3B color);
	/************************************************************************/
	/* 设置对应节点的Zorder                                                                     */
	/************************************************************************/
	void setAnimationZorder(unsigned int idx, int zorder);
	/************************************************************************/
	/* 判断是否是有效范围的节点                                                                     */
	/************************************************************************/
	bool isAnimValidate(unsigned int idx);
	void setAnimationVisible(unsigned int idx, bool visible);
	/************************************************************************/
	/* 统一设置节点的描点, 一般为(0.5, 0)                                                                     */
	/************************************************************************/
	void setFrameAnchor(cocos2d::Point anchor);
public:
	/************************************************************************/
	/* 获取根视图                                                                     */
	/************************************************************************/
	JOFrameSprite* getRoot();
	/************************************************************************/
	/* 设置点中的回调                                                                     */
	/************************************************************************/
	inline void setTouchCall(std::function<void(JOFrameModel*)> touchCall){ m_touchCall = touchCall; };
	/************************************************************************/
	/* 设置动画类型对应的回调 
	/* frameIdx为对应第几帧动画时触发, 默认为-1即动画播放结束后回调
	/************************************************************************/
	void setAniCall(std::string& aniName, std::function<void(JOFrameModel*)> call, short frameIdx=-1);	
	void removeAniCall(std::string& aniName);
	void removeAniCall(std::string& aniName, short frameIdx);
	void removeAllCall();
	/************************************************************************/
	/* 播放动画
	/* aniType动画类型, 
	/* bRepeat是否循环
	/************************************************************************/
	void playAni(std::string& aniName, bool bRepeat = true);
	/************************************************************************/
	/* 保存动画类型对应的方向和部位的动画配置信息                                                                     
	/* aniName动画名, 比喻run, attack, idle...
	/* dir方向
	/* partIdx部位下标
	/* aniKey动画配置数据key
	/************************************************************************/
	void setAniData(std::string& aniName, unsigned short dir, unsigned short partIdx, std::string& aniKey);
	/************************************************************************/
	/* 设置主部位, 以此部位作为点击范围和动画回调基准
	/************************************************************************/
	void setMainPart(unsigned short partIdx);
public:
	/************************************************************************/
	/* 方向, 以时钟表示                                                                     */
	/************************************************************************/
	enum{
		CLOCK_00 = 1, //up
		CLOCK_15, //r_up
		CLOCK_30, //right
		CLOCK_45, //r_down
		CLOCK_60, //down
		CLOCK_75, //l_down
		CLOCK_90, //left
		CLOCK_105 //l_up
	};
	void setDir(unsigned short clockType);
	
protected:
	///以下为保留方法,不建议使用////////////////////////////////////////////////////////////////////////
	/************************************************************************/
	/* 播放帧动画                                                                     */
	/************************************************************************/
	bool playRoot(const std::string& aniName, bool bRepeat = true);
	/*
	idx为组件对应下标id
	*/
	bool playPart(const std::string& aniName, unsigned int idx, bool bRepeat = true);
	/************************************************************************/
	/* 设置对应节点的数据                                                                     */
	/************************************************************************/
	bool setAnimation(unsigned int idx, const std::string& aniKey);
public:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	
	
protected:
	void _clearAnimations();
	bool _inTouchRect(Touch* pTouch);

	void _frameSpriteLoadCall(cocos2d::Node* sender, std::string& aniKey, std::string& aniName);
	void _frameEventCall(JOFrameSprite* frameSpr, std::string& aniName, short frameIdx);
	

protected:
	unsigned short		m_aniSpriteCount;
	std::vector<JOFrameSprite*> m_aniSprites;
	
	std::function<void(JOFrameModel*)> m_touchCall;
		
	bool				m_bRepeat;
	float				m_aniSpeed;		
	bool				m_isPlaying;

	std::string		    m_aniName; //当前动作类型	
	unsigned short		m_aniDir;	//当前方向
	unsigned short		m_aniLastDir;	//记录上一次play时的方向
	bool				m_bPicFlip; //是否X反转
	unsigned short		m_mainPartIdx; //主部位下标, 默认为0
	
	/************************************************************************/
	/* 保存动画类型对应的方向和部位的动画配置信息                                                                     */
	/************************************************************************/
	typedef unordered_map<unsigned short, std::string> PART_ANI_MAP;
	typedef unordered_map<unsigned short, PART_ANI_MAP > DIR_ANI_MAP;
	typedef unordered_map<std::string, DIR_ANI_MAP > ANI_NAME_MAP;
	ANI_NAME_MAP m_aniDataMap;
	unsigned short m_needLoadCount;
	unsigned short m_loadingIdx;

	unordered_map<std::string, unordered_map<short, std::function<void(JOFrameModel*)> > > m_eventCallMap;

public:
	/************************************************************************/
	/* 为动画数据中没有统一配置动画名而设计的方法, 尽量使用统一命名, 以下方法也不建议使用                                                                     */
	/************************************************************************/
	/************************************************************************/
	/* 这方法就是动画命名跟配置数据中不一置而用的
	/* aniName动画名, 比喻run, attack, idle...
	/* dir方向
	/* partIdx部位下标
	/* realAniName 动画配置所设置的动画名,
	/************************************************************************/
	void setAniNamePair(std::string& aniName, unsigned short dir, unsigned short partIdx, std::string& realAniName);
	void clearAniNamePair();
protected:
	std::string getRealAniName(std::string& aniName, unsigned short dir, unsigned short partIdx);
	ANI_NAME_MAP m_aniNamePair;
};

NS_JOFW_END

#endif //__JOFRAME_MODEL_H__