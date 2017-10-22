#ifndef __JOLAYER_COLOR_H__
#define __JOLAYER_COLOR_H__

#include "cocos2d.h"
USING_NS_CC;

#include "utils/JOMacro.h"
#include "utils/JOClsMemoryPool.h"
#include "ui/JOButton.h"

NS_JOFW_BEGIN


class JO_DLL JOLayerColor : public LayerColor
{	
	JO_CLS_MPOOL_DECLARE(JOLayerColor);
public:
	JOLayerColor();
	virtual ~JOLayerColor();

	static JOLayerColor* create();
	static JOLayerColor* create(const Color4B& color);
	
	virtual void setLayerColor(const Color4B& color);
	
};

NS_JOFW_END

#endif //__JOLAYER_COLOR_H__