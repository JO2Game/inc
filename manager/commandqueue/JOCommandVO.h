#ifndef __JO_Command_H__
#define __JO_Command_H__

#include "utils/JOMacro.h"
#include <functional>

NS_JOFW_BEGIN

class JO_DLL JOCommandVO
{
public:
	JOCommandVO();
	
	void init(unsigned int id, std::function<bool(void)> cRunFun);
	void init(unsigned int id, LUA_FUNCTION luaRunFun);
    
	/************************************************************************/
	/* return true mean run finish 
	/* else next tick will run again
	/************************************************************************/
    bool run() ;
	
	inline bool isCancel(){ return m_bCancel; };
	inline void setCancel(bool bCancel){ m_bCancel = bCancel; };    
	inline bool isId(unsigned int id){ return m_id == id; }
protected:
        
    bool m_bCancel;

protected:
	std::function<bool(void)> c_runFunct;
	LUA_FUNCTION lua_runFunct;
	unsigned int m_id;
};

NS_JOFW_END

#endif  //__JO_Command_H__