#ifndef __JOASYNCHQUEUELOADER_H__
#define __JOASYNCHQUEUELOADER_H__

#include <string>
#include "module/loader/JOAsynchBaseLoader.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN

class JO_DLL JOAsynchQueueLoader : public JOAsynchBaseLoader, public JOSingleton < JOAsynchQueueLoader >
{
protected:
	virtual void startLoadImg();

};

NS_JOFW_END
#endif //__JOASYNCHQUEUELOADER_H__