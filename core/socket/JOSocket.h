//
//  JOSocket.h
//  Twilight-cocos2dx
//
//  Created by James Ou on 12-6-25.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __JOSocket_H__
#define __JOSocket_H__

#ifdef _WIN32
//#pragma comment(lib, "pthreadVCE2.lib")
#endif

#include <thread>
//#include <mutex>
//#include <stdlib.h>
//#include "pthread.h"
//#endif
#if _WIN32
//#pragma comment(lib, "ws2_32.lib")
#endif

#include <string>
#include <functional>
#include "utils/JOMacro.h"
#include "utils/JOLock.h"
#include "core/datautils/JORingBuffer.h"

NS_JOFW_BEGIN
class JODataCoder;

using namespace std;

#define READALL_CHUNKSIZE	256         // Incremental increase in buffer size
#define WRITE_CHUNKSIZE     (1024 * 4)   // Limit on size of each write pass


enum JOSocketFlags
{
    kEnablePreBuffering      = 1 << 0,  // If set, pre-buffering is enabled
    kDidPassConnectMethod    = 1 << 1,  // If set, disconnection results in delegate call
    kDidCompleteOpenForRead  = 1 << 2,  // If set, open callback has been called for read stream
    kDidCompleteOpenForWrite = 1 << 3,  // If set, open callback has been called for write stream
    kStartingTLS             = 1 << 4,  // If set, we're waiting for TLS negotiation to complete
    kForbidReadsWrites       = 1 << 5,  // If set, no new reads or writes are allowed
    kDisconnectAfterReads    = 1 << 6,  // If set, disconnect after no more reads are queued
    kDisconnectAfterWrites   = 1 << 7,  // If set, disconnect after no more writes are queued
    kClosingWithError        = 1 << 8,  // If set, the socket is being closed due to an error
};

enum JOSocketError
{
    kJOSocketError = -1,
    kJOSocketTimeout = -2,
    kJOSocketNoError = 0,					// Never used.
    kJOSocketCanceledError,					// onSocketWillConnect: returned NO.
    kJOSocketConnectTimeoutError,
    kJOSocketHandleError,
    kJOSocketReadError,
    kJOSocketWriteError
};

class JOSocket;

#pragma mark -
#pragma mark JOSocketDelegate
class JO_DLL JOSocketDelegate {
public:
    virtual void onSocketWillConnect(JOSocket* socket){};
    virtual void onSocketConnected(JOSocket* socket,const char* ip,unsigned int port){};
	virtual void onSocketConnectFail(JOSocket* socket){};
	virtual void onSocketDidDisconnected(JOSocket* socket){ };

    virtual void onSocketDidReadData(JOSocket* socket,JODataCoder* dataCoder){};
	virtual JODataCoder* onSocketDidReadPartialData(JOSocket* socket, unsigned char* pData, unsigned int size, unsigned int* len){ return nullptr; };
    virtual void onSocketDidWriteData(JOSocket* socket){};

	virtual void onSocketWithError(JOSocket* socket, JOSocketError error){};
};

/************************************************************************/
/* 网络数据包,包头信息
/* 可能根据需要会改变, 但结束都是size和op
/************************************************************************/
struct NetPacketHeader
{
	unsigned short wDataSize;
	short wOpcode; // -10 ~ 10
};

#pragma mark -
#pragma mark JOSocket
class JO_DLL JOSocket {	
public:	
	JOSocket(short id, JOSocketDelegate* socketDelegate);
	JOSocket();
	virtual ~JOSocket();

	inline void setSocketId(short id){ m_socketId = id; }
	inline short getSocketId(){ return m_socketId; }	
protected:
	static void _clearThread();

	short				m_socketId;	

    string              m_szIP;
    int                 m_nPort;
    int                 m_nSocketHandle;
    
    JOSocketDelegate*   m_pDelegate;
	JOLock	m_delegateLock;
	JOLock	m_socketLock;
	std::mutex m_sendMutex;
	std::condition_variable m_sendCV;
	
public:
        
	JOSocketDelegate*   getDelegate();
	void setDelegate(JOSocketDelegate* delegate);
    
    int connect(const char* ip, unsigned int port, bool async = true);
    void disconnect();
	void writeData(JODataCoder* dataCoder);

    void clearBuffer();
    bool isConnect();
    
protected:    
    void closeWithError(JOSocketError error);    
        
#pragma mark JOSocket Reading    
protected:
    void _popReadData();
    
#pragma mark JOSocket ReadWritestream
protected:
    
    static bool m_bWriteStreamCreated;    
	static bool m_bReadStreamCreated;
    // thread function
    void writeStreamThread();
	void readStreamThread();
    
    JORingBuffer<JODataCoder *> *m_send_buffer;
    JORingBuffer<JODataCoder *> *m_recv_buffer;
    
#pragma mark -
#pragma mark Thread Function
protected:    
    void connectThread();
	void _createStream();
    
protected:
    bool bConnect_;
};

NS_JOFW_END
#endif
