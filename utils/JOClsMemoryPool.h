
#ifndef __JO_CLS_MEMORY_POOL_H__
#define __JO_CLS_MEMORY_POOL_H__

#include <unordered_map>
#include <list>
//#include <iostream>
#include <ctime>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOLog.h"

NS_JOFW_BEGIN

class JO_DLL JOClsMemoryVO
{
public:
	JOClsMemoryVO();
	~JOClsMemoryVO();

public:		
	//unsigned short m_limitCount;
	//unsigned short m_maxCount;
	bool m_bOpen;
	std::string m_clsname;
};

class JO_DLL JOClsMemoryPool : public JOSingleton<JOClsMemoryPool>
{
public:
	JOClsMemoryPool();
	virtual ~JOClsMemoryPool();

public:
	void* getPtr(size_t cacheSize, const std::string& clsname);
	void recover(void* ptr, size_t cacheSize);
	inline void setCheckInterval(unsigned int interval){ m_checkInterval = interval; };
	void clearAllPool();

	inline void setDebug(bool bDebug){ m_bDebug = bDebug; }
public:
	/************************************************************************/
	/* work in debug
	/************************************************************************/
	bool setPoolSwitch(const std::string& clsname, bool beOn);
	//bool setPoolLimit(const std::string& clsname, unsigned int count);
	void clearPool(const std::string& clsname);
	
public:
	void tick();
private:
	struct __MemoryPoolCacheInfo
	{
		__MemoryPoolCacheInfo() :m_noQuoteTime(0), m_tatolQuoteCount(0), m_maxCount(0){};
		clock_t m_noQuoteTime;
		int m_tatolQuoteCount;
		unsigned int m_maxCount;
		std::list<void*> m_pool;
	};
	typedef std::unordered_map<size_t, __MemoryPoolCacheInfo*> POOL_MAP; 
	POOL_MAP m_poolMap;
	unsigned short m_checkInterval;

	typedef std::unordered_map<std::string, JOClsMemoryVO*> CLS_VO_MAP;
	typedef std::unordered_map< size_t, CLS_VO_MAP > CLS_MAP;
	CLS_MAP m_clsMap;
	bool m_bDebug;

};

#define JO_CLSPOOL_GET_PTR(T,size) JOClsMemoryPool::Instance()->getPtr(size,#T);


#define JO_CLS_MPOOL_DECLARE(T)											\
public:																	\
	static void* operator new(size_t size)								\
	{															\
	T* ptr = (T*)JO_CLSPOOL_GET_PTR(T,size);				 	\
	if (ptr)												\
					{														\
		/*T* cls = (T*)ptr;*/									\
		ptr->setCacheSize(size);							\
		return ptr;											\
					}														\
	/*throw std::bad_alloc();*/									\
	return ::malloc(size);									\
}	\
	static void* operator new(size_t size, const std::nothrow_t&)		\
	{															\
	return operator new(size);								\
}															\
	static void operator delete(void* ptr)								\
	{															\
	T* cls = (T*)ptr;										\
	if (cls == nullptr) return;								\
	JOClsMemoryPool::Instance()->recover(ptr, cls->getCacheSize());	\
}															\
	static void operator delete(void* ptr, const std::nothrow_t&)		\
	{															\
	operator delete(ptr);									\
}\
																		\
	inline void setCacheSize(size_t size){m_pool_cacheSize = size;};	\
	inline size_t getCacheSize(){return m_pool_cacheSize;};				\
protected:																\
	size_t m_pool_cacheSize;

#define JO_CLS_MPOOL_IMPLEMENT(T)
/*

#define JO_CLS_MPOOL_IMPLEMENT(T)							\
void* T::operator new(size_t size)							\
{															\
	T* ptr = (T*)JO_CLSPOOL_GET_PTR(T,size);				 	\
	if (ptr)												\
		{														\
		//T* cls = (T*)ptr;									\
		ptr->setCacheSize(size);							\
		return ptr;											\
		}														\
	//throw std::bad_alloc();									\
	LOG_WARN("JOClsMemoryPool", "get pool size[%d] fail "); \
	return ::malloc(size);									\
}															\
void* T::operator new(size_t size, const std::nothrow_t&)	\
{															\
	return operator new(size);								\
}															\
void T::operator delete(void* ptr)							\
{															\
	//if (ptr == nullptr) return;								\
	T* cls = (T*)ptr;										\
	if (cls == nullptr) return;								\
	JOClsMemoryPool::Instance()->recover(ptr, cls->getCacheSize());	\
}															\
void T::operator delete(void* ptr, const std::nothrow_t&)	\
{															\
	operator delete(ptr);									\
}
*/
NS_JOFW_END

#endif //__JO_CLS_MEMORY_POOL_H__