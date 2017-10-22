#ifndef __JO_LOCK_H__
#define __JO_LOCK_H__

#include "utils/JOMacro.h"
NS_JOFW_BEGIN


#ifdef JOUSE_STD_THREAD
#include <thread>
#include <mutex>
#include <condition_variable>
#else
#include <pthread.h>
#endif


class JO_DLL JOLock
{
public:
	JOLock(void);
	~JOLock();
	inline bool isLocked() const{ return (m_nRef > 0); };

#ifdef JOUSE_STD_THREAD
	inline std::mutex& getMutex(){ return m_Mutex; };
#else
	inline pthread_mutex_t& getMutex(){ return m_Mutex;};
#endif // JOUSE_STD_THREAD

	void lock();
	void unlock();	

private:
	int m_nRef;

#ifdef JOUSE_STD_THREAD
	std::mutex m_Mutex;
#else
	pthread_mutex_t m_Mutex;
#endif

};

/************************************************************************/
/*直接的临时锁
/************************************************************************/
class JO_DLL JOLockGuard
{
public:	
	JOLockGuard(JOLock& rlock);
	~JOLockGuard();
private:
	JOLock& m_lock;	
};
/************************************************************************/
/*判断是否加临时锁, 为了逻辑调用格式统一
/************************************************************************/
class JO_DLL JOLockJudgeGuard
{
public:
	JOLockJudgeGuard(JOLock& rlock, bool beIgnore = false);
	~JOLockJudgeGuard();
private:
	JOLock& m_lock;
	bool	m_ignoreLock;
};


NS_JOFW_END

#endif //__JOLOCK_H__