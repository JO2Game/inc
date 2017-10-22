#ifndef __JOASYNCHSOUNDVO_H__
#define __JOASYNCHSOUNDVO_H__

#include <string>
#include <functional>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOAsynchSoundVO
{
public:
	bool isMusic;
	std::string filepath;
	std::function<void(void)> callback;
};

NS_JOFW_END
#endif //__JOASYNCHSOUNDVO_H__