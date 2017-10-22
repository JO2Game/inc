/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 JOCommandMgr.h
 AUTHOR:  James Ou
 *********************************************************************/

#ifndef __JO_COMMAND_MGR_H__
#define __JO_COMMAND_MGR_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "manager/commandqueue/JOCommandQueue.h"

#include <unordered_set>
#include <unordered_map>

NS_JOFW_BEGIN

class JO_DLL JOCommandMgr : public JOSingleton<JOCommandMgr>
{
public:
	JOCommandMgr();
	virtual ~JOCommandMgr();
	
public:	
    void tick(); 

public:  
	/************************************************************************/
	/* 添加命令队列
	/************************************************************************/
	void appendCommandTail(unsigned int id, std::function<bool(void)> cRunFun, bool beAsyn = false);
	void insertCommandFront(unsigned int id, std::function<bool(void)> cRunFun, bool beAsyn = false);

	/************************************************************************/
	/* Lua的调用
	/************************************************************************/
	void appendLuaCommandTail(unsigned int id, LUA_FUNCTION luaRunFun, bool beAsyn = false);
	void insertLuaCommandFront(unsigned int id, LUA_FUNCTION luaRunFun, bool beAsyn = false);
    
  
    void removeCommand(unsigned int id);  
    void clear();

private:
    JOCommandQueue m_commandQueue;
	JOCommandQueue m_asynCommandQueue;
};

NS_JOFW_END

#endif // __JO_COMMAND_MGR_H__
