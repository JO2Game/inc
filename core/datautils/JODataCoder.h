#ifndef __JO_DATA_CODER_H__
#define __JO_DATA_CODER_H__
#include <string>
#include <vector>
#include "utils/JOMacro.h"
#include "utils/JOLock.h"

NS_JOFW_BEGIN

class JOData;

/************************************************************************/
/* 协议头不能大于 unsigned short(65535)
/* 总数据长度 (包括协议头) 同样不能大于 unsigned short(65535)
/* 其实一条协议的数据量有 unsigned short(65535)的情况下，应该就是协议设计存在问题
/************************************************************************/
class JO_DLL JODataCoder {
protected:
	unsigned short			m_op;	

	unsigned char*			m_pReadPointer;
	JOData*					m_pData;	
	unsigned int			m_uReadPos;
	bool					m_bBigEndian;

	/************************************************************************/
	/*协议头占用长度
	/*全数据长度占用的长度                                                    
	/************************************************************************/
	unsigned short			m_opOccupyLen;
	unsigned short			m_allOccupyLen; 

	void _init();
public:
	/*
	occupy 为占位数据，不是真实的数据 !!!!
	主要用于网络数据包, 2位长度, 2位协议头
	*/

	JODataCoder(unsigned int opOccupyLen=0, unsigned int allOccupyLen=0);
	JODataCoder(unsigned char* bytes, unsigned int len, unsigned int opOccupyLen = 0, unsigned int allOccupyLen = 0);
	virtual ~JODataCoder();
	
	void init(unsigned int opOccupyLen = 0, unsigned int allOccupyLen = 0);
	void init(unsigned char* bytes, unsigned int len, unsigned int opOccupyLen = 0, unsigned int allOccupyLen = 0);
	
	inline void setOp(unsigned short op){ m_op = op; };
	inline unsigned short getOp(){ return m_op; };

	// return byte data;
	JOData* data() const;
	// seek the byte array position
	void seek(unsigned int pos);//{if(m_pData->length()<pos)return;m_pReadPointer = (unsigned char*)(m_pData->bytes()+pos);}

	/************************************************************************/
	/* 加入数据长度和op数据 unsigned short单位进包头
	/************************************************************************/
	JOData*             netPack();

	/************************************************************************/
	/* 输出十六进制数据内容(字符串形式)(不包括数据长度单位和协议头)
	/************************************************************************/
	std::string description();
	/************************************************************************/
	/* 内容数据长度(不包括数据长度单位和协议头)
	/************************************************************************/
	unsigned int length();

	inline void setBigEndian(bool bigEndian){ m_bBigEndian = bigEndian; };
	
public:
	/************************************************************************/
	/* 为Lua提供统一接口
	/************************************************************************/

    char getByte();
    short getShort();
    int getInt();
    bool getBool();
    std::string getLong();
    std::string getString();
    std::string getFloat();
    
    void putByte(char c);
    void putShort(short s);
    void putInt(int i);
    void putBool(bool b);
    void putLong(std::string ll);
	void putString(const std::string& str);
    void putFloat(float f);
    
public:
	bool wirte2File(const std::string& filename);
	bool readFile(const std::string& filename);
	
public:

	// reader function
	unsigned char       readUByte();
	char                readByte();
	unsigned short      readUShort();
	short               readShort();
	unsigned int        readUInt();
	int                 readInt();
	unsigned long long  readULLong();
	long long           readLLong();
	std::string         readString();
	float				readFloat();

	// writer function
	void                writeUByte(unsigned char byte);
	void                writeByte(char byte);
	void                writeUShort(unsigned short s);
	void                writeShort(short s);
	void                writeUInt(unsigned int i);
	void                writeInt(int i);
	void                writeULLong(unsigned long long l);
	void                writeLLong(long long l);
	/************************************************************************/
	/* 写入的字符串长度不要超过unsigned short(65535)
	/************************************************************************/
	void                writeString(const std::string& str);
	void				writeFloat(float f);

};

NS_JOFW_END
#endif // __JO_DATA_CODER_H__