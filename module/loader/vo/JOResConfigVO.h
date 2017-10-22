#ifndef __JORES_CONFIG_VO_H__
#define __JORES_CONFIG_VO_H__

#include <string>
#include "utils/JOMacro.h"
#include "module/loader/JOAsynchBaseLoader.h"
#include "module/loader/JOResConfig.h"

NS_JOFW_BEGIN

class JO_DLL JOResConfigVO
{
public:
	void setConfig(const std::string srcPath, int resType = JOAsynchBaseLoader::RES_IMG, int pFormat = JOResConfig::PF_565, const std::string plist = JO_EMTYP_STRING, const std::string aniPlist = JO_EMTYP_STRING);
	
public:
	short resType;//资源类型(IMG, FRAME, ANIMAT)
	short pixelFormat;//纹理格式	
	std::string srcPath;//图片资源路径
	std::string plistPath;//图集配置路径
	std::string aniPlistPath;//序列动作配置路径

};

/************************************************************************/
/* src和plist必须在同一目录下
/************************************************************************/
class JO_DLL JOResSrcVO
{
public:
	void setData(const std::string& srcPath, const std::string& srcKey, const std::string& basePath, int pFormat = JOResConfig::PF_565, const std::string& plist = JO_EMTYP_STRING);
	std::string getSrc() const;
	std::string getPlist() const;
public:
	short pixelFormat;//纹理格式
	std::string srcKey;//图片资源名
	std::string srcPath;//图片资源相对路径
	std::string plist;//图集配置相对路径
	std::string basePath; //资源统一前路径
};


class JO_DLL JOResArmatureVO
{
public:
	void setData(const std::string& arm, const std::string& basePath, const std::string& srcKey);

	std::string getArmPath() const;
public:
	std::string armature;//骨骼配置xml相对路径
	std::string basePath; //资源统一前路径
	std::string srcKey;//图片资源名
};

NS_JOFW_END

#endif //__JORES_CONFIG_VO_H__