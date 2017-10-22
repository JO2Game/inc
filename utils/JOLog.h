#ifndef __JO_LOG_H__
#define __JO_LOG_H__
#include <string>
#include <functional>
#include <queue>
#include <unordered_map>

#include "utils/JOMacro.h"
#include "utils/JOString.h"
NS_JOFW_BEGIN

class JO_DLL JOLog
{
public:
	static void output( const char* logLevel, const char* logTag, const char* msg);
	static std::string format_file_name(const char* file);
	static std::string format_function_name(const char* fun);
	static void setLogConfig(bool bShow, std::string title, std::string &logLv, bool bInTick);
    static void addExclusive(std::string key);
    static void setLogFunction(const std::function<void(const char*)> logfun);
    static void tick();
private:
	static void _output(const char* logLevel, const char* logTag, const char* msg);
    static short getLogLevelN(const char* logLevel);
    static const char* getLogIgnoreKey(const char* logLevel);
    
    static std::function<void(const char*)> _logfun;
	static std::unordered_map<std::string, bool> _exclusiveMap;
    
    static bool bJOLogShow;
    static std::string _logLevel;
    static short gLogLevel;
    static bool beShowInTick;
    static std::string logTitle;
    static unsigned int logCount;
    
	JOLog(void);
	~JOLog(void){};
    struct LogData{
        LogData(std::string lv, std::string ms):level(lv),msg(ms){}
        std::string level;
        std::string msg;
    };
    
    static std::queue<LogData> logDataQueue;
};

/************************************************************************/
/* JOLog提供4个相关的宏,用于规范Log的输出								*/
/* 应该注意以下几点:													*/
/* CCLOG,printf,cout等缺乏良好的日志等级,分类,配置管理等.请勿再使用!	*/
/* JOLog内部使用CCLOG的分平台实现,所以也受CCLOG的宏配置约束			*/
/* JOLog使用 Config.lua 作为配置,具体配置规则见 Config.lua			*/
/* JOLog还提供一个Lua版本的配套实现,来保证编程模式上的统一			*/
/************************************************************************/

#if 0 //!defined(COCOS2D_DEBUG) || COCOS2D_DEBUG == 0
	#define LOG_DEBUG(...)  do {} while (0)
	#define LOG_INFO(...)   do {} while (0)
	#define LOG_WARN(...)   do {} while (0)
	#define LOG_ERROR(...)  do {} while (0)
#else
/*
	#define _LOG_OUTPUT(logTag,logLevel,dateTime,fileName,line,functionName,msg) \
	JOLog::output(logLevel,logTag,JOString::formatString("[C++ %5s] %s %-22s > %s ... in funct '%s' (%s)",\
		logLevel,dateTime,(JOString::formatString("%s:%d",fileName,line).c_str()),msg,functionName,logTag).c_str())
 */
    #define _LOG_OUTPUT(logTag,logLevel,dateTime,fileName,line,functionName,msg) \
    JOLog::output(logLevel,logTag,JOString::formatString("[C++ %5s] %s %-18s > %s ... in funct '%s'",\
    logLevel,dateTime,(JOString::formatString("%s:%d",fileName,line).c_str()),msg,functionName).c_str())

	#define LOG_DEBUG(logTag,format, ...) _LOG_OUTPUT( logTag , "DEBUG" , __TIME__, JOLog::format_file_name(__FILE__).c_str() , __LINE__ , JOLog::format_function_name(__FUNCTION__).c_str(),\
		JOString::formatString(format, ##__VA_ARGS__).c_str() )
	#define LOG_INFO(logTag,format, ...) _LOG_OUTPUT( logTag , "INFO" , __TIME__, JOLog::format_file_name(__FILE__).c_str() , __LINE__ , JOLog::format_function_name(__FUNCTION__).c_str(),\
		JOString::formatString(format, ##__VA_ARGS__).c_str() )
	#define LOG_WARN(logTag,format, ...) _LOG_OUTPUT( logTag , "WARN" , __TIME__, JOLog::format_file_name(__FILE__).c_str() , __LINE__ , JOLog::format_function_name(__FUNCTION__).c_str(),\
		JOString::formatString(format, ##__VA_ARGS__).c_str() )
	#define LOG_ERROR(logTag,format, ...) _LOG_OUTPUT( logTag , "ERROR" , __TIME__, JOLog::format_file_name(__FILE__).c_str() , __LINE__ , JOLog::format_function_name(__FUNCTION__).c_str(),\
		JOString::formatString(format, ##__VA_ARGS__).c_str() )

#endif

/*
typedef void (JOLogFunction)(const char *format, ...);

class LogFunction
{
public:	
	static void JOLOG(const char *format, ...);	
	static void setLogFunction(JOLogFunction logfun);
private:
	static JOLogFunction *_pLogFun;	
};

void LogFunction::setLogFunction( JOLogFunction *logfun )
{	
	_pLogFun = logfun;
}

void LogFunction::JOLOG( const char *format, ... )
{
	va_list args;

	if (_pLogFun)	{			

		(_pLogFun)(format, args);
		(*_pLogFun)(format, args);
	}	
}

#define JJO_LOG_INFO(format, ...) LogFunction::JOLOG(format, ##__VA_ARGS__);
#define JJO_LOG_DEBUG(format, ...) LogFunction::JOLOG(format, ##__VA_ARGS__);
#define JJO_LOG_WARN(format, ...) LogFunction::JOLOG(format, ##__VA_ARGS__);
#define JJO_LOG_ERROR(format, ...) LogFunction::JOLOG(format, ##__VA_ARGS__);
*/

NS_JOFW_END

#endif //__JO_LOG_H__