#ifndef __JOFRAME_ANIMATION_CACHE_H__
#define __JOFRAME_ANIMATION_CACHE_H__

#include <unordered_map>
#include <string>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

#include "cocos2d.h"
USING_NS_CC;

NS_JOFW_BEGIN
class JOFrameAnimationVO;

class JO_DLL JOFrameAnimationCache : public JOSingleton<JOFrameAnimationCache>
{
public:
	JOFrameAnimationCache();
	virtual ~JOFrameAnimationCache();

public:
	void quoteRes(std::string& aniKey);
	void unQuoteRes(std::string& aniKey);
	void addAnimationsWithKey(const std::string& aniKey);
	void removeAnimationsWithKey(const std::string& aniKey);
	cocos2d::Animation* getAnimation(const std::string& name);
	bool getAnimationsWithAniKey(const std::string& aniKey, std::unordered_map<std::string, cocos2d::Animation*> &outMap);
	bool haveAnimationsWithAniKey(const std::string& aniKey);

public:
	void tick();

private:
    void _checkDispose();
	void _parseVersion1(const ValueMap& animations, std::unordered_map<std::string, cocos2d::Animation*> &outMap);
	void _parseVersion2(const ValueMap& animations, std::unordered_map<std::string, cocos2d::Animation*> &outMap);
    
protected:
    float m_checkInterval;
	std::unordered_map<std::string, cocos2d::Animation*> m_animations;
	std::unordered_map<std::string, JOFrameAnimationVO*> m_aniMap;
};

NS_JOFW_END

#endif //__JOFRAME_ANIMATION_CACHE_H__