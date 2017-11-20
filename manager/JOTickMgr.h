/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 JOTickMgr.h
 AUTHOR:  James Ou
 *********************************************************************/

#ifndef __JO_TICK_MGR_H__
#define __JO_TICK_MGR_H__

#include <list>
#include <unordered_map>
#include <functional>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOLock.h"

NS_JOFW_BEGIN

class JO_DLL JOTickVO
{
public:
	JOTickVO();
	void init();
	void run();
public:
	std::function<void(void)> c_funct;
	LUA_FUNCTION lua_funct;
	bool beRemove = false;
};

class JO_DLL TickFunctInThreadVO
{
public:
	TickFunctInThreadVO();
	void init();
	void run();
public:
	std::function<void(void)> c_funct;
	bool beRemove;
	unsigned int sn;
};

class JO_DLL JOTickMgr : public JOSingleton<JOTickMgr>
{
public:
	JOTickMgr();
	virtual ~JOTickMgr();

public:    
	void registerTick(unsigned int sn, std::function<void(void)> cFunct);
	void registerTick(unsigned int sn, LUA_FUNCTION luaFunct);
	void unRegisterTick(unsigned int sn);

    void clear();

	inline float deltaTime(){ return m_deltaTime; };
	inline unsigned int tickCount(){ return m_tickCount; };
public:
    void tick(float dt);

public:
	void runInMainThread(unsigned int sn, const std::function<void()> &function);
	void cancelInMainRun(unsigned int sn);
    
private:
	typedef std::unordered_map<unsigned int, JOTickVO*> TICK_MAP;
	TICK_MAP tickMap;
	
	float m_deltaTime;
	unsigned int m_tickCount;

private:
	
	std::list< TickFunctInThreadVO* >  _functionsToPerform;
	JOLock _performMutex;

};


NS_JOFW_END

#endif // __JO_TICK_MGR_H__
