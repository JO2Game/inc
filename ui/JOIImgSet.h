#ifndef __JOIMGSET_INTERFACE_H__
#define __JOIMGSET_INTERFACE_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"

NS_JOFW_BEGIN


class JO_DLL JOIImgSet
{
	JO_CLS_MPOOL_DECLARE(JOIImgSet);
public:
	JOIImgSet();
	virtual ~JOIImgSet();

public:
	void setSource(const std::list<std::string>& srcList, bool isAsyn = true, const std::unordered_map<std::string, short>* pixelMap=nullptr);

	/************************************************************************/
	/* 折构时由子类调用
	/************************************************************************/
	void clearSource();

	inline unsigned int getSn(){ return m_sn; }

public:
	void _loadComplete(Texture2D* tex, std::string source, short resType, JODataCoder* dataCoder, int index, int totalCount);
	
protected:
	void _clearTmp();

protected:
	virtual void _loadStart() = 0;
	virtual void _loadEnd() = 0;
	virtual bool _isLoading() = 0;
	virtual void _loadCancel() = 0;
	virtual void _emptyTexture() = 0;

protected:
	std::list<std::string> m_srcList;
	std::list<std::string> m_tmpSrcList;
protected:
	CompLeteCall m_comLeteCall;
	
	unsigned int m_sn;
};

NS_JOFW_END

#endif //__JOIMGSET_INTERFACE_H__