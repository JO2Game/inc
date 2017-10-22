
#ifndef __JOSINGLETON_H__
#define __JOSINGLETON_H__

#include <list>
#include <algorithm>

#include "utils/JOMacro.h"
#include "utils/JOLock.h"
//#include "utils/JOLog.h"

NS_JOFW_BEGIN
/*
class JO_DLL JOSingletonBase
{
	class InstanceTable : public std::list < JOSingletonBase * >
	{
	public:
		InstanceTable();
		~InstanceTable();
	public:
		bool is_cleared_;
	};

protected:
	JOSingletonBase();	
	virtual ~JOSingletonBase();
	
private:
	static InstanceTable s_instance_table_;
};
*/
//static JOLock s_singleLock;

template <typename T>
class JOSingleton //: public JOSingletonBase
{
public:
	static T* Instance()
	{
		if (s_singleton_ == nullptr)
		{
            JOLock s_singleLock;
			s_singleLock.lock();//借用其它类来实现，如boost
			if (nullptr == s_singleton_){
				s_singleton_ = new (std::nothrow) T();
			}
			s_singleLock.unlock();
			
			//s_singleton_ = new (std::nothrow) T();
		}
		return s_singleton_;
	}

	static void Destroy()
	{
		if (s_singleton_)
		{
			delete s_singleton_;
		}
	}

protected:
	JOSingleton() = default;

	virtual ~JOSingleton()
	{
		s_singleton_ = nullptr;
	};

private:
	static T* s_singleton_;
    
	
};

template<typename T> T* JOSingleton<T>::s_singleton_ = nullptr;

/*
#define SINGLETON(_class_name_)					\
	private:									\
		_class_name_();							\
		~_class_name_();						\
		friend class Singleton<_class_name_>

*/
NS_JOFW_END
#endif //__JOSINGLETON_H__