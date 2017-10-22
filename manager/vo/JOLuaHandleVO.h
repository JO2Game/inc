#ifndef __JO_LUA_HANDLE_VO_H__
#define __JO_LUA_HANDLE_VO_H__

#include "utils/JOMacro.h"
#include <functional>

NS_JOFW_BEGIN

class JO_DLL JOLuaHandleVO
{
public:
	JOLuaHandleVO();
	virtual ~JOLuaHandleVO();

	void init(LUA_FUNCTION luaHandle, unsigned int handleType);
    
protected:
	
	LUA_FUNCTION m_handle;
	unsigned int m_handleType;
};

NS_JOFW_END

#endif  //__JO_LUA_HANDLE_VO_H__