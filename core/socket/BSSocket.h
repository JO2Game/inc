#ifndef _NET_BSSOCKET_H_
#define _NET_BSSOCKET_H_

#ifdef WIN32
#include <winsock.h>
#include <windows.h>
typedef int				socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
typedef int				SOCKET;

//#pragma region define win32 const variable in linux
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1
//#pragma endregion
#endif

#include "pthread/pthread.h"
#include <iostream>
#include <vector>

class BSSocket;
using namespace std;

static BSSocket* bsSocket = NULL;

const int MAX_BSSOCKETMSG_BUFF = 1024 * 64;
class BSSocket {

private:
	
	static unsigned char socketBuff[MAX_BSSOCKETMSG_BUFF];
	static unsigned long socketBuffLen;

	bool need_quit;
	bool isConnected;

	char* connectIp;
	unsigned int connectPort;
	// Send socket
	
public:
	int Send(const char* buf, int len, int flags = 0);
	BSSocket(SOCKET sock = INVALID_SOCKET);
	static BSSocket* getInstance();
	void initConnect(const char* ip, unsigned short port);

	~BSSocket();

	// Create socket object for snd/recv data
	bool Create(int af, int type, int protocol = 0);

	// Connect socket
	bool Connect(const char* ip, unsigned short port);
	bool ConnectSyn(const char* ip, unsigned short port);
	//#region server
	// Bind socket
	bool Bind(unsigned short port);

	// Listen socket
	bool Listen(int backlog = 5); 

	// Accept socket
	bool Accept(BSSocket& s, char* fromip = NULL);
	//#endregion

	// Recv socket
	int Recv(char* buf, int len, int flags = 0);

	// Close socket
	int Close();

	// Get errno
	int GetError();

	//#pragma region just for win32
	// Init winsock DLL 
	static int Init();	
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion



	BSSocket& operator = (SOCKET s);

	operator SOCKET ();

	int		m_nRecvBufLen;	         
	char	m_szRecvBuf[MAX_BSSOCKETMSG_BUFF + 1];	/*Ω” ’ª∫¥Ê«¯*/ 

	int getFd() { return m_sock; };
	SOCKET m_sock;
	

};

#endif // !_NET_BSSOCKET_H_

