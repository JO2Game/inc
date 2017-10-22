#ifndef __JOFRAME_UNPACK_PNG_H__
#define __JOFRAME_UNPACK_PNG_H__

#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"

NS_JOFW_BEGIN


class JO_DLL JOFrameUnpackPng : public JOSingleton<JOFrameUnpackPng>
{
public:
	JOFrameUnpackPng();
	virtual ~JOFrameUnpackPng();

public:
	void unPack(const std::string& src, const std::string& dest);
	inline bool isUnPacking(){ return m_isUnPacking; };

	void cancelUnPack();
public:
	void tick();

protected:
	std::list<std::string> m_fileList;
	std::string m_destPath;
	bool m_isUnPacking;
};

NS_JOFW_END

#endif //__JOFRAME_UNPACK_PNG_H__