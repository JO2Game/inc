
#ifndef __JO_LUA_UTILS_H__
#define __JO_LUA_UTILS_H__

#include <functional>
#include <list>
#include <string>

#include "utils/JOMacro.h"
NS_JOFW_BEGIN

enum JOLuaArgBaseType{
    eJOLUA_ARGS_TYPE_INT = 1,
    eJOLUA_ARGS_TYPE_BOOL,
    eJOLUA_ARGS_TYPE_FLOAT,
    eJOLUA_ARGS_TYPE_DOUBLE,
    eJOLUA_ARGS_TYPE_STRING,
    eJOLUA_ARGS_TYPE_OBJ,
    eJOLUA_ARGS_TYPE_NULL,
};
struct JOLuaArgs
{
    
    JOLuaArgs():_argBaseType(eJOLUA_ARGS_TYPE_NULL),_argBase(""),_argObjType(""),_argObj(NULL){};
    JOLuaArgBaseType _argBaseType;
    std::string _argBase;
    std::string _argObjType;
    void* _argObj;
};
/*
type为string, int, float, bool时，base通过string取值
其它用指针point来转换取值
 */
struct JOLuaResult
{
    JOLuaArgBaseType  _resultType;
    std::string _resultBase;
    void* _resultObj;
};

class JO_DLL JOLuaUtils
{
public:
    JOLuaUtils();
    ~JOLuaUtils(){};
public:
	    
    static const void* luaNewThreadState();
    static const void* lua2Pointer(lua_Object pointerIdx);
    static const void* lua2Function(LUA_FUNCTION luaFunction);
    
    static void executeFunctionInThread(LUA_FUNCTION luaFunction, const void* luaThreadState);
    static void executeFunction(LUA_FUNCTION luaFunction, std::string argBase, JOLuaArgBaseType argBaseType);
    static void executeFunction(LUA_FUNCTION luaFunction, void* argObj, std::string argObjType);

    static void executeFunction(LUA_FUNCTION luaFunction, std::list<JOLuaArgs> argList, bool bNewThread = false);
    static void executeFunctionWithResult(LUA_FUNCTION luaFunction, std::list<JOLuaArgs> argList, short resultNum, std::list<JOLuaResult> &resultList);
    static void stackDump();
    
    static void setExecuteFunctionInThreadCall(const std::function<void(LUA_FUNCTION, const void*)> &exeFunCall);
    static void setExecuteFunctionCall(const std::function<void(LUA_FUNCTION, std::list<JOLuaArgs>, short, std::list<JOLuaResult>&, bool)> &exeFunCall);
    static void setStackDumpCall(const std::function<void(void)> &dumpCall);
    static void setLua2Pointer(const std::function<const void*(lua_Object)> &toPointer);
    static void setLua2Function(const std::function<const void*(LUA_FUNCTION)> &toFunction);
    static void setLuaNewThreadState(const std::function<const void*(void)> &luaNewThreadState);
private:
    static std::function<void(LUA_FUNCTION, std::list<JOLuaArgs>, short, std::list<JOLuaResult>&, bool)> _executeFunCall;
    static std::function<void(void)> _dumpCall;
    static std::function<const void*(lua_Object)> _toPointerCall;
    static std::function<const void*(LUA_FUNCTION)> _toFunctionCall;
    static std::function<const void*(void)> _luaNewThreadStateCall;
    static std::function<void(LUA_FUNCTION, const void*)> _executeInThreadCall;

};
/************************************************************************
注册C++的功能实现来扩展Lua的功能,
如果需要扩展其他Lua功能,也在本LuaUtil中实现,勿直接修改Cocos2d,liblua,toLua++等的第3方库的源码.
包括:
println(str)
************************************************************************/
//class lua_State;
//void luaopen_JOLuaUtil(lua_State *L);

NS_JOFW_END
#endif