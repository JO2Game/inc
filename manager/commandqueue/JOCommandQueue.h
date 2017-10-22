/********************************************************************
 CREATED: 18/1/2014   14:54
 FILE: 	 JOCommandQueue.h
 AUTHOR:  James Ou
 *********************************************************************/
#ifndef __JOCommandQueue_H__
#define __JOCommandQueue_H__
#include <list>

#include "utils/JOMacro.h"
#include "utils/JOLock.h"
NS_JOFW_BEGIN

class JOCommandVO;

class JO_DLL JOCommandQueue
{
public:
	JOCommandQueue();
	~JOCommandQueue();

	void pushBack(JOCommandVO* pCommand);
	void pushFront(JOCommandVO* pCommand);
	bool removeCommand(unsigned int sn);
    void update();
    void clearAll();
    bool isEmpty() { return m_vCommands.empty();}

public:
	void setAsynchronousMode(bool beAsyn);

private:
	void _clearRemoveList();

private:
	std::list<JOCommandVO*>		m_vCommands;
	std::list<JOCommandVO*>		m_removeList;

private:
	JOLock						m_lock;
	bool						m_bAsyn;
};
NS_JOFW_END

#endif // __JOCommandQueue_H__
