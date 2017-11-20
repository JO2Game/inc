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
	/* ���ü��صĶ����������ݺͼ�����ɻص�                                                                     */
	/************************************************************************/
	void setAniKey(const std::string& aniKey, bool isAsyn = true);
	/************************************************************************/
	/* �жϵ�ǰ�Ƿ����aniKey��Ӧ������                                                                     */
	/************************************************************************/
	bool isSetupAniKey(const std::string& aniKey);
	void setCallback(LoadSpriteCall call);
	/************************************************************************/
	/* �ж��Ƿ��ܲ���aniName����                                                                     */
	/************************************************************************/
	bool isCanPlay(const std::string& aniName);
	/************************************************************************/
	/* ���Ŷ���aniName                                                                     */
	/************************************************************************/
	bool play(const std::string& aniName, bool bRepeat = true);
	void restart();
	/************************************************************************/
	/* ֹͣ����                                                                     */
	/************************************************************************/
	inline void stop(){ m_isPlaying = false; };
	/************************************************************************/
	/* ���ò����ٶ�                                                                      */
	/************************************************************************/
	inline void setSpeed(float speed){ m_aniSpeed = speed; };

public:
	/************************************************************************/
	/* ������                                                                     */
	/************************************************************************/
	Rect getTouchRect();
	float getHeadTitleOffsetY();

public:	
	/************************************************************************/
	/* ���֡�¼�
	/* ֡����0��ʼ, -1��ʾ���һ֡                                                                     */
	/************************************************************************/
	void setEventCall(const std::string& aniName, FrameEventCall call, short frameIdx = -1);
	/************************************************************************/
	/* �Ƴ�֡�¼�
	/************************************************************************/
	void removeCall(const std::string& aniName, short frameIdx);
	/************************************************************************/
	/* �Ƴ���Ӧ����������֡�¼�
	/************************************************************************/
	void removeCall(const std::string& aniName);
	/************************************************************************/
	/* �Ƴ�����֡�¼�
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
	LoadSpriteCall m_loadCall; //������ɻص�
	std::string m_aniKey; //������������
	std::string m_tmpAniKey;
    
protected:

	bool				m_bRepeat; 
	float				m_aniSpeed;		
	std::string         m_aniName; //����һ������
	
	
	Rect				m_touchRect; //�������
	float				m_headTitleOffsetY;

	std::unordered_map<std::string, std::unordered_map<short, FrameEventCall > > m_callMap; //ע��Ĺؼ�֡�¼�

	cocos2d::Animation*			m_curAnimation; //���غ�Ķ�������
	std::vector<float>			m_splitTimes; //����������ʱ��
	unsigned short				m_curFrameIdx; //��ǰ֡
	float						m_elapseTime; //��ȥ��ʱ��
	bool						m_isPlaying; //�ж��Ƿ񲥷���
	
};

NS_JOFW_END

#endif //__JOFRAME_SPRITE_H__