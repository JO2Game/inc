
#ifndef __JOJSONHELPER_H__
#define __JOJSONHELPER_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "external/json/document.h"
//#include "utils/rapidjson/document.h"


NS_JOFW_BEGIN

class JO_DLL JOJsonHelper : public JOSingleton<JOJsonHelper>
{
public:
	bool getFileDictionary(RAPIDJSON_NAMESPACE::Document &root, const char* jsonFilePath);
	bool getStringDictionary(RAPIDJSON_NAMESPACE::Document &root, const char* jsonString);

	const RAPIDJSON_NAMESPACE::Value& getSubDictionary(const RAPIDJSON_NAMESPACE::Value &root, const char* key);
    const RAPIDJSON_NAMESPACE::Value& getSubDictionary(const RAPIDJSON_NAMESPACE::Value &root, const char* key, int idx);
    const RAPIDJSON_NAMESPACE::Value& getSubDictionary(const RAPIDJSON_NAMESPACE::Value &root, int idx);
    
	int   getIntValue(const RAPIDJSON_NAMESPACE::Value& root, const char* key, int def = 0);
	float getFloatValue(const RAPIDJSON_NAMESPACE::Value& root,const char* key, float def = 0.0f);
    bool  getBooleanValue(const RAPIDJSON_NAMESPACE::Value& root,const char* key, bool def = false);
    const char* getStringValue(const RAPIDJSON_NAMESPACE::Value& root,const char* key, const char *def = NULL);
    int   getArrayCount(const RAPIDJSON_NAMESPACE::Value& root,const char* key, int def = 0);
	
    int   getIntValueFromArray(const RAPIDJSON_NAMESPACE::Value& root,const char* arrayKey,int idx, int def = 0);
	float getFloatValueFromArray(const RAPIDJSON_NAMESPACE::Value& root,const char* arrayKey,int idx, float def = 0.0f);
	bool  getBoolValueFromArray(const RAPIDJSON_NAMESPACE::Value& root,const char* arrayKey,int idx, bool def = false);
	const char* getStringValueFromArray(const RAPIDJSON_NAMESPACE::Value& root,const char* arrayKey,int idx, const char *def = NULL);
	const RAPIDJSON_NAMESPACE::Value &getDictionaryFromArray(const RAPIDJSON_NAMESPACE::Value &root, const char* key,int idx);
	bool checkObjectExist(const RAPIDJSON_NAMESPACE::Value &root);
    bool checkObjectExist(const RAPIDJSON_NAMESPACE::Value &root, const char* key);
    bool checkObjectExist(const RAPIDJSON_NAMESPACE::Value &root, int index);
};

NS_JOFW_END

#endif //__JOJSONHELPER_H__
