#ifndef __JOASYNCHSOUNDLOADER_H__
#define __JOASYNCHSOUNDLOADER_H__

#include <string>
#include <queue>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "utils/JOLock.h"
#include "utils/JOThread.h"

NS_JOFW_BEGIN

class JOAsynchSoundVO;

class JO_DLL JOAsynchSoundLoader : public JOSingleton < JOAsynchSoundLoader >, public IJOThreadDelegate
{
public:
	JOAsynchSoundLoader();
	virtual ~JOAsynchSoundLoader();
	/*
	回调格为了跟纹理的一致， 用了Texture2D
	type分为音效和音乐
	*/
	void addSoundAsync(const std::string &filepath, bool isMusic,  const std::function<void(void)>& callback);	

public:
	virtual void onThreadCreate(JOThread *pThread){};
	virtual void onThreadProcess(JOThread *pThread);
	virtual void onThreadDestroy(JOThread *pThread){};

	void update(float dt);

private:
	
	std::queue<JOAsynchSoundVO*> soundQueue;
	JOLock mLock;
	JOThread *m_pthread;

	int asyncRefCount;
};

NS_JOFW_END
#endif //__JOASYNCHSOUNDLOADER_H__