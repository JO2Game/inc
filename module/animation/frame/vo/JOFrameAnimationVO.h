#ifndef __JOFRAME_ANIMATIONVO_H__
#define __JOFRAME_ANIMATIONVO_H__

#include <unordered_map>
#include <string>
#include "utils/JOMacro.h"
#include "utils/JOTime.h"

#include "cocos2d.h"
USING_NS_CC;

NS_JOFW_BEGIN

class JO_DLL JOFrameAnimationVO
{
public:
	JOFrameAnimationVO();
	~JOFrameAnimationVO();
    
public:
    void increase();
    void decrease();
	void addAnimation(const std::string &key, cocos2d::Animation* ani);
    void clear();
	std::unordered_map<std::string, cocos2d::Animation*> getAnimations();

public:
    int m_count;
    clock_t m_noQuoteTime;
	std::unordered_map<std::string, cocos2d::Animation*> m_aniMap;
};


NS_JOFW_END

#endif //__JOFRAME_ANIMATIONVO_H__