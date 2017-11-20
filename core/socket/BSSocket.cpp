#include "BSSocket.h"

#ifdef WIN32
	#pragma comment(lib, "wsock32")
#endif


BSSocket::BSSocket(SOCKET sock)
	:need_quit(false),isConnected(false), connectIp(NULL), connectPort(0)
{
	m_sock = sock;
}

BSSocket::~BSSocket()
{
}

int BSSocket::Init()
{
#ifdef WIN32
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
//		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int BSSocket::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

BSSocket& BSSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

BSSocket::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool BSSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	std::cout << "the errro info" << GetError();
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}

bool BSSocket::Connect(const char* ip, unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	std::cout << "you are connected" << std::endl;	
	isConnected = true;
	return true;
}

bool BSSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}
//for server
bool BSSocket::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool BSSocket::Accept(BSSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}

	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int BSSocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len ) {
		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 ) {
			std::cout << "the send errro info" << GetError();
			return -1;
		}
		count += bytes;
	} 

	return count;
}

int BSSocket::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

int BSSocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int BSSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}



void BSSocket::initConnect( const char* ip, unsigned short port )
{
	 connectIp = new char[sizeof(ip)];
	 strcpy(connectIp, ip);
	 connectPort = port;
	 pthread_t initThread;
}



BSSocket* BSSocket::getInstance()
{
	if(bsSocket == NULL) {
		bsSocket = new BSSocket;
	}
	return bsSocket;
}



bool BSSocket::ConnectSyn( const char* ip, unsigned short port )
{
	Init();
	Create(AF_INET, SOCK_STREAM, 0);
    bool success = Connect(ip, port);
    std::cout << "connect status is = " << success << std::endl;
    return success;
}
