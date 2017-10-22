#ifndef __JORES_CONFIG_H__
#define __JORES_CONFIG_H__

#include <unordered_map>
#include <string>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "module/loader/JOAsynchBaseLoader.h"

NS_JOFW_BEGIN
class JOResConfigVO;

class JOResSrcVO;
class JOResAnimationVO;
class JOResArmatureVO;

class JODataCoder;
class JOData;
/************************************************************************/
/* 需要有方法通过srcKey,获取源文件/plist及动画配置文件
/************************************************************************/

class JO_DLL JOResConfig : public JOSingleton< JOResConfig >
{
public:
	JOResConfig();
	virtual ~JOResConfig();
public:
	void clear();
	/************************************************************************/
	/* 用于加载资源配置时, 检查完整性, 发布时可去除debug, 增加加载效率
	/************************************************************************/
	inline void setDebug(bool bDebug){ m_isDebug = bDebug; };
	//for debug
	void description();
	std::string randomKey();

public:	
	/************************************************************************/
	/* 图片资源加载配置文件 
	/************************************************************************/
	bool loadSrcConfig(const std::string& fPath, const std::string& basePath);
	/************************************************************************/
	/* 手动添加图片配置
	/************************************************************************/
	bool addSrcKey(const std::string& imgKey, const std::string& basePath, const std::string& srcPath, short pf = PF_565, const std::string& plistPath = JO_EMTYP_STRING);
    
	/************************************************************************/
	/* 获取配置信息
	/************************************************************************/
	const JOResSrcVO* srcVOWithKey(const std::string& imgKey);
	const JOResSrcVO* srcVOWithSrc(const std::string& srcName);
	const JOResSrcVO* srcVOWithPlist(const std::string& plistName);

	void clearSrc();

public:
	/************************************************************************/
	/* 添加ani配置文件的搜索路径
	/************************************************************************/
	void addAniBasePath(const std::string& aniPath);
	/************************************************************************/
	/* 通过aniKey获取所需要图集plist信息
	/************************************************************************/
	bool srcPlistWithAniKey(const std::string& aniKey, std::list<std::string>& outList);
	/************************************************************************/
	/* 通过aniKey获取ani配置数据
	/************************************************************************/
	JOData* getAniDataWithAniKey(const std::string& aniKey);
	void clearAni();

    //void setAniPath(const std::string& aniPath);
    //inline std::string getAniPath(){return m_aniBasePath;}
    
	
public:
	bool loadArmConfig(const std::string& fPath, const std::string& basePath);    
	
	const JOResArmatureVO* armVOWithSrc(const std::string& srcName);
	const JOResArmatureVO* armVOWithArm(const std::string& armName);

public:
	/************************************************************************/
	/* 生成相关配置文件
	/* srcPath 源路径 destPath 目标路径 ellipsis 省略路径 
	/* outName 配置的文件名 (包括后缀)
	/************************************************************************/
	bool generateSrcConfig(const std::string& srcPath, const std::string& destPath, const std::string& ellipsis, const std::string& outName);	
	bool generateAniConfig(const std::string& srcPath, const std::string& destPath, const std::string& ellipsis, const std::string& outName);

	enum {PF_565=1,PF_4444,PF_5551,PF_8888};
	void setPFVal(short pf, short val);
	short getPFVal(short pf);

public:
	/************************************************************************/
	/* 生成文件路径处理配置
	/************************************************************************/
	void generateFilePathMap1(const std::string& filepath);
	void generateFilePathMap2(const std::string& filepath);
	std::string getRealFilePath(const std::string& filepath);
protected:
	/************************************************************************/
	/* 生成配置相关
	/************************************************************************/
	bool _setSrcKey(std::list<std::string> &list, std::unordered_map<std::string, std::string> &checkSrcMap, std::unordered_map<std::string, std::string> &checkKeyMap, JODataCoder* srcCoder, JODataCoder* keyCoder);
	bool _setPlistMap(std::unordered_map< std::string, std::list<std::string> > &pFrameMap, std::unordered_map< std::string, std::string > &pMap, std::unordered_map<std::string, std::string> &checkSrcMap, std::unordered_map<std::string, std::string> &checkKeyMap, JODataCoder* srcCoder, JODataCoder* keyCoder);

protected:	
	typedef std::unordered_map<short, short> PIX_FORMAT_MAP;	
	PIX_FORMAT_MAP pfMap;
	bool m_isDebug;

protected:	
	typedef std::unordered_map<std::string, JOResSrcVO*> RES_SRC_MAP;
	typedef std::unordered_map<std::string, JOResArmatureVO*> RES_ARM_MAP;

	RES_SRC_MAP m_src_srcMap;
	RES_SRC_MAP m_plist_srcMap;
	RES_SRC_MAP m_key_srcMap;

protected:
	//std::string m_aniBasePath;
	typedef std::unordered_map< std::string, std::list<std::string> > RES_ANI_MAP;
	RES_ANI_MAP m_aniMap;
	std::list<std::string> m_aniPaths;

protected:
	RES_ARM_MAP m_arm_armMap;
	RES_ARM_MAP m_src_armMap;

protected:
	/************************************************************************/
	/* 生成文件路径处理配置
	/************************************************************************/
	std::unordered_map<std::string, std::string> m_selfFilecodeMap;
	std::unordered_map<std::string, std::string> m_norFilecodeMap;
    
};


NS_JOFW_END
#endif //__JORES_CONFIG_H__