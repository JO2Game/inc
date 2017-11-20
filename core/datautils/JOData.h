#ifndef __JOData_H__
#define __JOData_H__

#include <string>
#include "utils/JOMacro.h"

NS_JOFW_BEGIN

class JO_DLL JOData
{
public:
    JOData();
	JOData(unsigned char *pBytes, unsigned int size);
	JOData(JOData* data);	

    ~JOData();

	void setData(unsigned char *pBytes, unsigned int size);
	void setData(JOData* data);	
	
	//clear data
	void reset();
    const unsigned char* bytes();
	inline unsigned int length(){ return m_nLength; };
	inline unsigned int capacity(){ return m_nTotalLength; };
	
	std::string description();
	
	void getBytes(void* buffer, unsigned int len);
	bool isEqualToData(JOData* data);
	
public:
   
	void setLength(unsigned int len);	

	// Adding Data
	void appendBytes(const unsigned char *pBytes, unsigned int size);
	void appendData(JOData* data);
    
    void insertBytes(const unsigned char* pBytes, unsigned int size, unsigned int begin = 0);

	/************************************************************************/
	/* Modifying Data
	/* not include end
	/************************************************************************/
	void replaceBytesInRange(int begin, int end, void* pBytes, unsigned int size);
	void resetBytes(unsigned int begin, unsigned int end);

private:
	void _initData();
    
private:
    unsigned char*	m_pData;
	// buffer len
	unsigned int	m_nLength;
	// real data len (alway m_nTotalLength<=m_nLength)
	unsigned int	m_nTotalLength;
};

NS_JOFW_END

#endif //__JOData_H__
