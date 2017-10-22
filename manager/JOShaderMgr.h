#ifndef __JO_SHADER_MGR_H__
#define __JO_SHADER_MGR_H__

#include <vector>
#include <unordered_map>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

namespace cocos2d{
	class Node;
	class GLProgramState;
};

NS_JOFW_BEGIN
class JOData;

class JO_DLL JOShaderMgr : public JOSingleton< JOShaderMgr >
{
public:
	JOShaderMgr();
	virtual ~JOShaderMgr();
	void addShaderSearchPath(const char* path);
	void clearShaderSearchPath();

	void setDefaultVsh(const char* key);
	void setDefaultOriginal(const char* key);

	cocos2d::GLProgramState* shader(cocos2d::Node* node, const char* key, std::function<void(cocos2d::Node*, cocos2d::GLProgramState*)> setValCall = nullptr);
	void restore(cocos2d::Node* node);
    
protected:    
    std::string _getShaderBuffer(std::string key);
	JOData* _getShaderData(std::string& key);

private:
	cocos2d::GLProgramState* m_glStateOriginal;

	std::string		m_defaultVsh;
	std::vector<std::string>	m_shaderPaths;
    std::unordered_map<std::string, std::string> m_shaderBufferMap;
};

NS_JOFW_END

#endif //__JO_SHADER_MGR_H__