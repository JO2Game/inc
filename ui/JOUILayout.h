#ifndef __JOUI_LAYOUT_H__
#define __JOUI_LAYOUT_H__

#include <list>

#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN

class JOUILayoutVO;

class JO_DLL JOUILayout : public JOSingleton<JOUILayout>
{
public:
	enum{NONE=1, CENTER,
		IN_T,IN_L,IN_B,IN_R,
		IN_TL,IN_TR,IN_BL,IN_BR,
		OUT_T,OUT_L,OUT_B,OUT_R,
		OUT_TL,OUT_TR,OUT_BL,OUT_BR,
		OUT_T_IN_L,OUT_T_IN_R,OUT_B_IN_L,OUT_B_IN_R,
		OUT_L_IN_T,OUT_L_IN_B,OUT_R_IN_T,OUT_R_IN_B
	};

	JOUILayout();
	virtual ~JOUILayout();

	void tick();
	bool relativePos(Node* src, Node* target, unsigned int layoutType = JOUILayout::CENTER, cocos2d::Point pos = cocos2d::Point::ZERO);
	inline void setDirect(bool beDirect){ m_beDirect = beDirect; };
public:
	void _rp(Node* src, Node* target, unsigned int layoutType, cocos2d::Point& pos);
	
	
private:
	cocos2d::Point _setPostionBase(Size &srcSize, cocos2d::Point &srcAnchor, Size &targetSize, cocos2d::Point &targetAnchor, cocos2d::Point &targetPos, cocos2d::Point &offset, unsigned int relative);
	std::list<JOUILayoutVO*> m_layoutList;
	bool m_beDirect;
};

NS_JOFW_END

#endif //__JOUI_LAYOUT_H__