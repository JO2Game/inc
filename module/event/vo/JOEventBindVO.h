#ifndef __JO_EVENT_BINDVO_H__
#define __JO_EVENT_BINDVO_H__

#include <functional>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JODataCoder;

class JO_DLL JOEventBindVO{

public:
	JOEventBindVO();	
	~JOEventBindVO();
	void init(unsigned int sn, unsigned int eventId, const std::function<void(unsigned int, void*, short)> cFunc);
	void init(unsigned int sn, unsigned int eventId, LUA_FUNCTION luaFunc);
	void clear();
	bool exec(unsigned int id, JODataCoder* dataCoder, short socketId);
	//bool exec(JODataBundle* dataBundle);

	inline bool isSn(unsigned int sn){ return sn == m_sn; }
	
private:
	unsigned int m_sn;
	unsigned int m_eventId;
	
	std::function<void(unsigned int, void*, short)> m_cFunc;
	LUA_FUNCTION	m_luaFunc;
};

NS_JOFW_END

#endif //__JO_EVENT_BINDVO_H__