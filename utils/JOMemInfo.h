#ifndef __JOMEMINFO_H__
#define __JOMEMINFO_H__

#include "JOMacros.h"
#ifdef JOUSE_STD_THREAD

#else
#include <mach/mach.h>
#include <sys/sysctl.h>
#endif // JOUSE_STD_THREAD



struct MEM_INFO{
	unsigned int uMemUsed;
	unsigned int uMemVirtual;
	unsigned int uMemAvailble;
	unsigned int uMemTotal;
	int nWarningLv;
	float fCpuUsage;
};

class JOMemInfo
{
public:
	JOMemInfo();
	~JOMemInfo();
	const MEM_INFO* memoryInfo();
	
	const char* getDeviceName();
	const char* getMacAddress();
protected:
	float _cpu_usage();
#ifdef JOUSE_STD_THREAD
#else
	bool _memoryInfo(vm_statistics_data_t *vmStats);
	bool _taskMemoryInfo(task_basic_info& info);
#endif
private:
	MEM_INFO *mem_info;
};

#endif //__JOMEMINFO_H__