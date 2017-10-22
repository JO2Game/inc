#ifndef __JO_LUA_SCRIPT_MGR_H__
#define __JO_LUA_SCRIPT_MGR_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include <unordered_map>

NS_JOFW_BEGIN

class JO_DLL JOLuaScriptMgr : public JOSingleton<JOLuaScriptMgr>
{
public:
	enum{ UI_BTN, UI_SPRITE, UI_INPUT, 
		ASYNCH_LOADER, DISPATCHER_ACTION, DISPATCHER_EVENT, 
		COMMAND_HANDLE, TICK_CALL
	};
public:
	JOLuaScriptMgr();
	virtual ~JOLuaScriptMgr();

	void addHandler(void* cObj, LUA_FUNCTION handle, unsigned short handleType);
	bool removeHandler(void* cObj, unsigned short handleType);
	void removeAll(void* cObj);

	LUA_FUNCTION getHandle(void* cObj, unsigned short handleType);

	void clear();

protected:	
	void _handle(void* cObj, LUA_FUNCTION handle, unsigned short handleType);

protected:
	typedef std::unordered_map<unsigned short, LUA_FUNCTION> LUA_HANDLE_MAP;
	typedef std::unordered_map<void*, LUA_HANDLE_MAP > LUA_C_OBJ_MAP;
	LUA_C_OBJ_MAP m_cObjMap;
};

NS_JOFW_END

#ifndef TOLUA_API
#define TOLUA_API extern
#endif

TOLUA_API int JO_DLL tolua_JOLuaScriptMgr_open(lua_State* tolua_S);


//#include "dragonBones/DragonBonesHeaders.h"

//extern void JO_DLL db_Transform_to_luaval(lua_State* L, const dragonBones::Transform& trans);



#endif //__JO_LUA_SCRIPT_MGR_H__
