#ifndef __JOIMG_INTERFACE_H__
#define __JOIMG_INTERFACE_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "module/loader/JOAsynchBaseLoader.h"

NS_JOFW_BEGIN


class JO_DLL JOIImg
{
	JO_CLS_MPOOL_DECLARE(JOIImg);
public:
	JOIImg();
	virtual ~JOIImg();

public:
	virtual void setKey(const std::string& imgName, bool isAsyn = true);
	virtual void setSource(const std::string& filePath, const std::string& imgName, bool isAsyn = true, short pixelFormat = (short)Texture2D::PixelFormat::RGBA8888);

	/************************************************************************/
	/* 折构时由子类调用
	/************************************************************************/
	void clearSource();

	/************************************************************************/
	/* 如果是图集这里应该为空字符串
	/************************************************************************/
	inline std::string getImgName(){ return m_imgName; };
	inline std::string getSourcePath(){ return m_sourcePath; }

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
	CompLeteCall m_comLeteCall;
	
	std::string m_sourcePath;
	std::string m_imgName;

	std::string m_tmpSourcePath;
	std::string m_tmpImgName;

	unsigned int m_sn;

};
/*
class JO_DLL JOIImgSprite : public Sprite, public JOIImg
{
protected:
	virtual void _loadStart(){};
	virtual void _loadEnd(){};
	virtual bool _isLoading(){ return false; };
	virtual void _loadCancel(){};
	virtual void _emptyTexture(){};
};

class JO_DLL JOIImgScale9Sprite : public ui::Scale9Sprite, public JOIImg
{
protected:
	virtual void _loadStart(){};
	virtual void _loadEnd(){};
	virtual bool _isLoading(){ return false; };
	virtual void _loadCancel(){};
	virtual void _emptyTexture(){};
};
*/
NS_JOFW_END

#endif //__JOIMG_INTERFACE_H__