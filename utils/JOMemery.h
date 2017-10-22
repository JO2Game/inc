
#ifndef __JOMEMERY_H__
#define __JOMEMERY_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOLock.h"
NS_JOFW_BEGIN

#include <unordered_map>

class JO_DLL JOMemery : public JOSingleton< JOMemery >
{
public:
	/*
	分配内存
	*/
	void* allocBytes(size_t sCount, const char* lpszFile = NULL, unsigned int nLine = 0);
	/*
	释放内存
	*/
	void deallocBytes(void* lpPtr);
	/*
	是否启用输出内存泄露
	*/
	void enableDumpMemeryLeak(bool bDump);
	/*
	报告内存泄露
	*/
	void reportLeaks();

public:
	JOMemery();
	virtual ~JOMemery();

private:
	void recordAlloc(void* lpPtr, size_t sCount, const char* lpszFile, unsigned int nLine);
	void recordDeallooc(void* lpPtr);
protected:

	struct ALLOC_INFO
	{
		ALLOC_INFO() :sBytes(0), nLine(0){}
		ALLOC_INFO(size_t sCount, const char* lpszFile, unsigned int nLine) :sBytes(sCount), strFile(lpszFile), nLine(nLine){}
		size_t sBytes;
		std::string strFile;
		unsigned int nLine;
	};

	typedef std::unordered_map<void*, ALLOC_INFO> ALLOC_MAP;
	bool m_bDump;

	JOLock m_lock;
	ALLOC_MAP m_mapAllocs;
};

namespace JOMemerynamespace{
	template <class T> void _TDestructor(T* t){ if (t){ t->~T(); }; }
}


#define JOMEM_NEW(T) new( JOMemery::Instance()->allocBytes(sizeof(T), __FILE__, __LINE__) ) T()
#define JOMEM_DELETE(ptr) {JOMemerynamespace::_TDestructor(ptr); JOMemery::Instance()->deallocBytes(ptr); ptr = NULL;}

#define JOMEM_ALLOC(T) static_cast<T*>(JOMemery::Instance()->allocBytes(sizeof(T), __FILE__, __LINE__)) 
#define JOMEM_FREE(ptr) {if(ptr) JOMemery::Instance()->deallocBytes(ptr); ptr = NULL; }


NS_JOFW_END

#endif //__JOMEMERY_H__