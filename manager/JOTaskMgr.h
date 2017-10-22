/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 FileUtilsEx.h
 AUTHOR:  James Ou
 *********************************************************************/

#ifndef __JO_TASK_MGR_H__
#define __JO_TASK_MGR_H__

#include <list>
#include <functional>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "manager/JOTickMgr.h"

NS_JOFW_BEGIN

class JOITask
{
public:
    JOITask();
    JOITask(const std::function<void(void)> &taskHandle);
    virtual void run();
    bool isAvailable();
private:
    std::function<void(void)> _taskHandle;
protected:
    bool _bAvailable;
};

class JOLuaTask : public JOITask
{
public:
    JOLuaTask(LUA_FUNCTION luaFun, const void* luaState = nullptr);
    virtual void run();
private:
    LUA_FUNCTION _luaFun;
    const void* _luaState;
};


typedef std::list<JOITask*> TaskList;

class JOTaskMgr : public JOSingleton<JOTaskMgr>
{
public:
	JOTaskMgr();
    virtual ~JOTaskMgr();

    void addAsynTask(JOITask *task);
    void addMainTask(JOITask *task);
    
    void addAsynLuaTask(LUA_FUNCTION luaFun);
    void addMainLuaTask(LUA_FUNCTION luaFun);
    
    virtual void tick();

    
    void clearAsynTask();
    void clearMainTask();
    
    JOITask* popAsynTask();
    JOITask* popMainTask();
    
protected:
    void _lazyInitAsyn();
    void _lazyInitMain();
    
private:    
	int _sn;
    TaskList _mainTaskList;
    TaskList _asynTaskList;
};

NS_JOFW_END

#endif // __JO_TASK_MGR_H__
