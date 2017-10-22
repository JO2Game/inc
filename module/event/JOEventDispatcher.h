#ifndef _JOEventDispatcher_h__
#define _JOEventDispatcher_h__

#include <string>
#include <list>
#include <functional>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
NS_JOFW_BEGIN

class JODataCoder;
//class JODataBundle;
class JOFunctionBinder;

class JO_DLL JOEventDispatcher : public JOSingleton<JOEventDispatcher>
{
public:
    JOEventDispatcher();
	virtual ~JOEventDispatcher();
	
	void regAction(unsigned int sn, unsigned int actId, const std::function<void(unsigned int, void*, short)> &onEvent);
	void regEvent(unsigned int sn, unsigned int eveId, const std::function<void(unsigned int, void*, short)> &onEvent);
	/*
	void regAction(unsigned int sn, unsigned int actId, LUA_FUNCTION luaEvent);
	void regEvent(unsigned int sn, unsigned int eveId, LUA_FUNCTION luaEvent);
	*/
	void unRegAction(unsigned int sn);
	void unRegAction(unsigned int sn, unsigned int actId);
	void unRegEvent(unsigned int sn);
	void unRegEvent(unsigned int sn, unsigned int eveId);
	void unRegAll(unsigned int sn);
    
	//void dispatchAction(JODataCoder *dataCoder, short socketId = -1);
    //void dispatchEvent(JODataBundle *dataBundle);
	void dispatchEvent(unsigned int eveId, JODataCoder *dataCoder=nullptr);

	void g2cAction(JODataCoder* dataCoder, int socketId = -1);
	void c2gAction(JODataCoder* dataCoder, int socketId = -1);

    void clearAll();

public:
    void tick();

private:

	JOFunctionBinder* _pEBinder;
	JOFunctionBinder* _pABinder;
};


NS_JOFW_END
#endif // _JOEventDispatcher_h__