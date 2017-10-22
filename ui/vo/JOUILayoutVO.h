#ifndef __JOUI_LAYOUT_VO_H__
#define __JOUI_LAYOUT_VO_H__

#include <string>
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "ui/JOUILayout.h"
NS_JOFW_BEGIN

class JO_DLL JOUILayoutVO
{
public:
	JOUILayoutVO();
	~JOUILayoutVO();
	
public:	
	bool init(Node* src, Node* target, unsigned int layoutType = JOUILayout::CENTER, cocos2d::Point pos = cocos2d::Point::ZERO);
	bool isLoaded();
	void exec();
	void done();
private:
	Node* m_src;
	Node* m_target;
	unsigned short m_layoutType;
	cocos2d::Point m_offset;
};

NS_JOFW_END

#endif //__JOUI_LAYOUT_VO_H__