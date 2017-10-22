#ifndef __JO_FILE_CACHE_VO_H__
#define __JO_FILE_CACHE_VO_H__

#include "utils/JOMacro.h"
#include "utils/JOTime.h"

NS_JOFW_BEGIN

class JOData;

class JO_DLL JOFileCacheVO
{
public:
	JOFileCacheVO();
	virtual ~JOFileCacheVO();

	void init(JOData* d, clock_t time);
    
	JOData*		m_fileData;
	clock_t		m_useTime;
};

NS_JOFW_END

#endif  //__JO_FILE_CACHE_VO_H__