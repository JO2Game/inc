#ifndef __JODYER_PARSER_H__
#define __JODYER_PARSER_H__

#include <string>
#include <vector>
#include <unordered_map>
//#include "jo_utils/JOSingleton.h"

#include "cocos2d.h"
USING_NS_CC;


namespace cocos2d
{
	class Sprite;
	class Texture2D;
}

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN
class JOSprite;
class JODyerVO;
class JODyerBlockVO;

class JO_DLL DyerData
{
public:
	DyerData(char lenght);
	DyerData(char lenght, float* h, float* s, float* l);
	~DyerData();

	//三个数组必须同等长度, 长度少于char即127
	char len;
	
	float *harr;
	float *sarr;
	float *larr;
};

typedef std::vector<DyerData*> DyerCaseVec;


class JO_DLL JODyerParser : public JOSingleton<JODyerParser>
{
public:
	JODyerParser();
	virtual ~JODyerParser();
public:
	static void saveToFile(const std::string& path, DyerCaseVec& vec);
	static bool getDataFromFile(const std::string& path, DyerCaseVec& vec);

	
	bool dyer(cocos2d::Sprite* sprite, const std::string& srcPath, unsigned char solutionId);
	bool dyer(JOSprite* sprite, unsigned char solutionId);
	void unDyer(cocos2d::Sprite* sprite, const std::string& srcPath);
	void unDyer(JOSprite* sprite);
	
public:
	void tick();
	void clear();
protected:
	bool _setDyer(cocos2d::Sprite* spr, cocos2d::Texture2D* tex, DyerData* dd);
	void _checkBlockCache();
private:
	
	typedef std::unordered_map< std::string, std::vector<DyerData*> > DYER_SOLUTION_MAP;
	DYER_SOLUTION_MAP dyer_solution_map;

	typedef std::unordered_map<std::string, JODyerBlockVO*> BLOCK_MAP;
	BLOCK_MAP m_blockMap;

	typedef std::unordered_map< std::string, std::list<JODyerVO*> > DYERs_MAP;
	DYERs_MAP m_dyersMap;

	std::list<std::string> m_blockDoneList;
};
	
NS_JOFW_END

#endif //__JODYER_PARSER_H__