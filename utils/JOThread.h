
#ifndef __JOTHREAD_H__
#define __JOTHREAD_H__

#include "utils/JOMacro.h"
#include "utils/JOLock.h"
NS_JOFW_BEGIN


class JOThread;
class JO_DLL IJOThreadDelegate
{
public:
	virtual void onThreadCreate(JOThread *pThread) = 0;
	virtual void onThreadProcess(JOThread *pThread) = 0;
	virtual void onThreadDestroy(JOThread *pThread) = 0;
};

class JO_DLL JOThread
{
public:
	/*
	nWorkInterval为微秒级
	*/
	static JOThread* createThread(IJOThreadDelegate* delegate, bool bSuspend = false, unsigned int nWorkInterval = 500);
	static void destroThread(JOThread* pThread);

public:
	JOThread();
	~JOThread();
	bool init(IJOThreadDelegate* pDelegate, bool bSuspend = false, unsigned int nWorkInterval = 500);
public:
	void resume();
	void suspend();
	void work();
	bool isSuspend();
	void close();

private:
	enum { STATUS_CLOSE, STATUS_RUNING, STATUS_SUSPEND, };

#ifdef JOUSE_STD_THREAD
	static void _runThread(JOThread* pthread);
#else
	static void _runThread(void* pThreadParam);
#endif // JOUSE_STD_THREAD
	static void _clean(void* pThreadParam);

private:
	unsigned char m_ucStatus;
	unsigned int m_nWorkInterval;
	JOLock m_lock;

#ifdef JOUSE_STD_THREAD
	std::thread m_thread;
	std::condition_variable m_TCond;
	std::condition_variable m_TWorkCond;
#else
	pthread_t m_thread;
	pthread_cond_t m_TCond;
	pthread_cond_t m_TWorkCond;
#endif // JOUSE_STD_THREAD

	IJOThreadDelegate* m_pDelegate;
};

NS_JOFW_END

#endif //__JOTHREAD_H__