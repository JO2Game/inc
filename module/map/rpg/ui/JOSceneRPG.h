#ifndef __JOSCENE_RPG_H__
#define __JOSCENE_RPG_H__

#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
NS_JOFW_BEGIN

class JO_DLL JOSceneRPG : public Node
{
public:	
	JOSceneRPG();
	virtual ~JOSceneRPG();
	static JOSceneRPG * create();
	virtual bool init();
	void setDebug(bool bDebug);
public:
	void loadMap(unsigned short mapId);
	void setViewCenter(int x, int y);

public:
	virtual void onEnter();
	virtual void onExit();
	void update(float dt);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

private:
	void _load();
	void _refreshRect();

private:
	bool m_bDebug;
	Node* m_debugLayer;

private:

	unsigned int centerX;
	unsigned int centerY;
	
	Node* bgLayer;
	Node* playerLayer;	
	Node* hero;
};

NS_JOFW_END

#endif	//__JOSCENE_RPG_H__
