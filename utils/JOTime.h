#ifndef __JOTIME_H__
#define __JOTIME_H__

#include <chrono>
#include <time.h>

#include "utils/JOMacro.h"
NS_JOFW_BEGIN

class JO_DLL JODuration
{
public:
	JODuration();
	/*
	重置计时
	*/
	void reset();
	/*
	秒 为double类型
	*/
	std::chrono::seconds::rep seconds();
	/*
	毫秒 为double类型
	*/
	std::chrono::milliseconds::rep milli_seconds();
	/*
	微秒 为double类型
	*/
	std::chrono::microseconds::rep micro_seconds();
	/*
	纳秒 为double类型
	*/
	std::chrono::nanoseconds::rep nano_seconds();

private:
	std::chrono::system_clock::time_point start_time_;
};

class JO_DLL JOTime
{
public:
	
	/*
	获取当前时间
	*/
	static clock_t getTimeofday();
	static void getTimeofday(struct timeval* tp);
	
};

NS_JOFW_END

#endif //__JOTIME_H__