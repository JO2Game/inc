#ifndef __JO_SN_MGR_H__
#define __JO_SN_MGR_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include <unordered_set>
#include <list>

NS_JOFW_BEGIN

class JO_DLL JOSnMgr : public JOSingleton<JOSnMgr>
{
public:
	JOSnMgr();
	virtual ~JOSnMgr();

	unsigned int getSn();
	void dispose(unsigned int sn);

private:
	void _createSnCap();

private:
	unsigned int snApplyNum;
	unsigned short maxSnAmount;
	std::list<unsigned int> snDepotList;
	std::unordered_set<unsigned int> snDepotSet;	

};

NS_JOFW_END

#endif //__JO_SN_MGR_H__