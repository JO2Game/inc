#ifndef __JO_FUNCTION_BINDER_H__
#define __JO_FUNCTION_BINDER_H__

#include <set>
#include <unordered_map>
#include <functional>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JODataCoder;
//class JODataBundle;
class JOEventBindVO;

class JO_DLL JOFunctionBinder{	
public:	
	~JOFunctionBinder();
	/************************************************************************/
	/* c function
	/************************************************************************/
	void bind(unsigned int sn, unsigned int eventId, const std::function<void(unsigned int, void*, short)> &cFunc);
	/************************************************************************/
	/* lua function
	/************************************************************************/
	void bind(unsigned int sn, unsigned int eventId, LUA_FUNCTION luaFunc);

	void unbind(unsigned int sn, unsigned int eventId);
	void unbind(unsigned int sn);

	void exec(unsigned int eventId, JODataCoder* dataCoder, int socketId=-1);
	//void exec( unsigned int eventId, JODataBundle *dataBundle );
	
	void removeAllFunctions();

public:
	void tick();

protected:
	void _bind(unsigned int sn, unsigned int eventId, JOEventBindVO* vo);
	void _removeListVO(unsigned int sn, unsigned int eventId);
private:	
	typedef std::unordered_map<unsigned int, JOEventBindVO*> VO_MAP;
	typedef std::list<JOEventBindVO*> VO_LIST;
	typedef std::unordered_map< unsigned int, VO_MAP > SN_VO_MAP;
	typedef std::unordered_map< unsigned int, VO_LIST > EVENTID_VOs_MAP;
	
	SN_VO_MAP sn_vo_map;
	EVENTID_VOs_MAP eventId_vos_map;
	std::list<JOEventBindVO*> removeList;
	VO_LIST::iterator vo_list_itr;
	bool			vo_remove_flag;
	
};

NS_JOFW_END

#endif //__JO_FUNCTION_BINDER_H__