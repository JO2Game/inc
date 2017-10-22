#ifndef __JOLABEL_H__
#define __JOLABEL_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"

NS_JOFW_BEGIN

class JO_DLL JOLabel : public Label
{
	JO_CLS_MPOOL_DECLARE(JOLabel);
protected:
	static float			s_fontSize;
	static std::string		s_fontAlias;
	static Color3B			s_fontColor;

	static short			s_boldSize;
	static Color4B			s_outColor;

	static Size				s_shadowOffset;
	static Color4B			s_shadowColor;
public:
	static void setDefaultBase(float fsize, const std::string& falias, Color3B fcolor);
	static void setDefaultOutline(int boldsize, Color4B outcolor);
	static void setDefaultShadow(Size offset, Color4B shadowcolor);

public:
	JOLabel();
	virtual ~JOLabel();
public:
	/************************************************************************/
	/* use default font
	/************************************************************************/
	static JOLabel* create(const std::string& str = "", float fSize = s_fontSize, Color3B fColor = s_fontColor, const std::string& alias = s_fontAlias);
	bool init(const std::string& str = "", float fSize = s_fontSize, Color3B fColor = s_fontColor, const std::string& alias = s_fontAlias);
protected:
	void _loadEffectStatus();
public:
	// not supported CHARMAP
	void setFontName(const std::string& fName);
	void setFontSize(float fSize);
	// not supported CHARMAP BMF
	void setOutline(int boldSize, Color4B color = s_outColor);
	//////////////////////////////////////////////////////////////////////////
	void setLabelColor(Color3B color);	
	void setShadow(Color4B color, Size offset, int blurRadius = 0);

public:
	virtual bool setCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);
	virtual bool setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);
	virtual bool setCharMap(const std::string& plistFile);

protected:
	enum { TTF, BMF, NOR, CHARMAP };
	short			m_labelType;
	
	float			m_fontSize;
	std::string		m_fontAlias;
	Color3B			m_fontColor;

	short			m_boldSize;
	Color4B			m_outColor;

	Size			m_shadowOffset;
	Color4B			m_shadowColor;	
};


NS_JOFW_END

#endif //__JOLABEL_H__