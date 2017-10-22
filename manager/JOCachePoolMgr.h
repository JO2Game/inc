#ifndef __JOCACHEPOOL_H__
#define __JOCACHEPOOL_H__

#include <string>
#include <unordered_map>
#include <functional>
#include <time.h>

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN


class JO_DLL JOCachePoolMgr : public JOSingleton<JOCachePoolMgr>
{
public:	
	JOCachePoolMgr();
	virtual ~JOCachePoolMgr();
	/*
	从缓存池中获取对象
	*/
	void* getObj(const std::string& clsName, const std::string& refPath);
	/*
	回收对象
	*/
	void recover(void* obj, const std::string& clsName, const std::string& refPath);
	/*
	注册创建方法, 用于getObj处调用
	*/
	void registerCls(const std::string& clsname, const std::function<void*(void)>& call, const std::function<void(void*)>& deletelCall=nullptr);
	/*
	检查间隔时间 单位秒
	*/
	inline void setCheckInterval(float interval){ checkInterval = interval; };
	inline void setDebugMode(bool bDebug){ isDebug = bDebug; };
	void tick();
protected:
	struct JOPoolCacheInfo
	{
		JOPoolCacheInfo() :noQuoteTime(0), totalQuoteCount(0){};
		typedef std::unordered_map<std::string, int> QUOTE_MAP;

		/*
		0 未被引用时间, 便于在未被引用的一段时间内统一GC
		*/
		clock_t noQuoteTime;
		/*
		引用记录对象
		*/
		QUOTE_MAP quoteRecord;
		/*
		储存对象缓存池
		*/
		std::vector<void*> pool;
		/*
		0 总共引用数量
		*/
		int totalQuoteCount;
	};
	/*
	检查引用信息并处理回收数据
	*/
	void _checkQuoteClass();

private:
	/*
	缓存池记录对象
	*/
	typedef std::unordered_map<std::string, JOPoolCacheInfo*> POOL_MAP;
	POOL_MAP mPool;

	float checkInterval;
	bool isDebug;

private:
	typedef std::unordered_map<std::string, std::function<void*(void)> > CLS_CREAT_MAP;
	CLS_CREAT_MAP clsCreateMap;
	typedef std::unordered_map<std::string, std::function<void(void*)> > CLS_DELETE_MAP;
	CLS_DELETE_MAP clsDeleteMap;


	/*
	管理TextureCahe的纹理缓存的大小
	*/
public:
	//set collect arg
	void setCollectCondition(unsigned int size);
	void onAddCacheCallback(unsigned int addSize);
	void registerAddCollectCallback(const std::function<unsigned int()> &collectCallback);
protected:
	void _recycleCollect();

private:
	std::function<unsigned int(void)> _collectCallback;	
	//collect limit
	unsigned int _limitSize;	
	unsigned int _curSize;
};

#define POOL_REG(T) JOCachePoolMgr::Instance()->registerCls(#T, []()->void*{ return new T(); });
#define POOL_GET(T, refPath) (T*)JOCachePoolMgr::Instance()->getObj(#T, refPath);
#define POOL_RECOVER(obj, T, refPath) JOCachePoolMgr::Instance()->recover(obj, #T, refPath);


NS_JOFW_END

#endif //__JOCACHEPOOL_H__
