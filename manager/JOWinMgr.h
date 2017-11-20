#ifndef __JO_WIN_MGR_H__
#define __JO_WIN_MGR_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include <unordered_set>
#include <list>

#include "cocos2d.h"
USING_NS_CC;

NS_JOFW_BEGIN

class JO_DLL JOWinMgr : public JOSingleton<JOWinMgr>
{
public:
	JOWinMgr();
	virtual ~JOWinMgr();
	//LAYER TAG
	enum{SCENE=1,HOME,WIN,ALERT,TIPS,GUIDE,WAIT,NOTICE,DEBUG_L, END};
	
	/************************************************************************/
	/* 必须初始这方法,创建初始场景
	/************************************************************************/
	void init(Scene* s = nullptr);
	inline Scene* getRoot(){ return m_root; };
	void tick();
public:
	Node* getLayer(int layerTag);
	
	void showWin(Node* win, int layerTag, bool isCenter=true);
	void clear(int layerTag);
	void clearAll();

	/************************************************************************/
	/* 以下方法只对逻辑窗口层处理
	/************************************************************************/
	void showSingleWin(Node* win);
	void removeWin(Node* win);
	void removeTopWin();

	/************************************************************************/
	/* 以下方法只对Alert窗口层处理
	/************************************************************************/
	void removeAlert(Node* win);
	void removeTopAlert();

public:
	/************************************************************************/
	/* 窗口注册,主要用于id管理
	/************************************************************************/
	void reg(unsigned int key, Node* win);
	void unReg(unsigned int key);
	Node* getWin(unsigned int key);
	void clearReg();

public:
	void _refreshGrayBg(Node* win);
	void __refreshGrayBg();
	void reSize();

protected:
	unsigned int	m_sn;
	Scene*			m_root;
	typedef std::unordered_map<short, Node*> LAYER_MAP;
	LAYER_MAP		m_layerMap;

	Node*			m_grayBgLayer;
	bool			m_grayDirty;

	Node*			m_curScene;
	Node*			m_curHome;

	Node*			m_debugWait;
	typedef std::list<Node*> WIN_LIST;
	WIN_LIST		m_logicWinList;
	WIN_LIST		m_alertWinList;

	typedef std::unordered_map<unsigned short, Node*> WIN_MAP;
	WIN_MAP			m_winMap;

	std::unordered_map<unsigned short, unsigned long long> m_winZorderMap;
};

#define SHOW_WIN(key) JOWinMgr::Instance()->showWin(JOWinMgr::Instance()->getWin(key), JOWinMgr::WIN);
#define SHOW_S_WIN(key) JOWinMgr::Instance()->showSingleWin(JOWinMgr::Instance()->getWin(key));
#define REMOVE_WIN(key) JOWinMgr::Instance()->removeWin(JOWinMgr::Instance()->getWin(key));

#define SHOW_ALERT(key) JOWinMgr::Instance()->showWin(JOWinMgr::Instance()->getWin(key), JOWinMgr::ALERT);
#define REMOVE_ALERT(key) JOWinMgr::Instance()->removeAlert(JOWinMgr::Instance()->getWin(key));

NS_JOFW_END

#endif //__JO_WIN_MGR_H__