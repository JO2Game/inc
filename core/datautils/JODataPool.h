#ifndef __JO_DATA_POOL_H__
#define __JO_DATA_POOL_H__

#include <list>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOLock.h"

NS_JOFW_BEGIN

class JOData;
class JODataCoder;
//class JODataBundle;

class JO_DLL JODataPool : public JOSingleton < JODataPool > {
public:
	JODataPool();
	virtual ~JODataPool();

public:
	/************************************************************************/
	/* beOccupy是否采用占位符
	/* bigEndian是否大小端
	/* isAsyn是否在异步需要
	/* 一般用于本地消息的, 所有参数用默认值即可
	/************************************************************************/
	JODataCoder* getDataCoder(bool beOccupy = false, bool bigEndian = false, bool isAsyn = false);	
	void recover(JODataCoder* coder, bool isAsyn=false);
	void clearCoder();
	/*
	JODataBundle* getDataBundle(bool isAsyn = false);
	void recover(JODataBundle* bundle, bool isAsyn = false);
	void clearBundle();
	*/
public:
	void tick();

private:
	void _checkCoderList();
	//void _checkBundleList();

private:
	std::list<JODataCoder*> m_coderList;
	std::list<JODataCoder*> m_coderAsynList;

	//std::list<JODataBundle*> m_bundleList;
	//std::list<JODataBundle*> m_bundleAsynList;

	JOLock m_coderLock;
	//JOLock m_bundleLock;

	float elapsedTime;
	float checkInterval;

};


NS_JOFW_END

#endif // __JO_DATA_POOL_H__