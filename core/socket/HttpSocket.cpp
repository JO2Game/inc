// HttpSocket.cpp: implementation of the CHttpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "HttpSocket.h"
#include <string>
#include <fstream>

using namespace std;

/************************************************************************/
/* utils                                                                     */
/************************************************************************/

void splitStr(vector<string> &gRet, string cStr ,const char* cSplit ){
	gRet.clear();
	int comma_n = 0;
	do
	{
		string tmp_s = "";
		comma_n = cStr.find( cSplit );
		if( -1 == comma_n )
		{
			tmp_s = cStr.substr( 0, cStr.length() );
			gRet.push_back( tmp_s );
			break;
		}
		tmp_s = cStr.substr( 0, comma_n );
		cStr.erase( 0, comma_n+1 );
		gRet.push_back( tmp_s );
	} 
	while(true);
}


char *  strrevX (char * str)
{
	char *start = str;
	char *left = str;
	char ch;

	while (*str++)                 /* find end of string */
		;
	str -= 2;

	while (left < str)
	{
		ch = *left;
		*left++ = *str;
		*str-- = ch;
	}

	return(start);
}


char* rtrim(char* str)
{
	int n = strlen(str)-1;
	while(n>0)
	{
		if(*(str+n)==' ')
		{
			*(str+n)= '\0';
			n--;
		}
		else
		{
			break;
		}
	}
	return str;
}

char *ltrim(char* str)
{
	strrevX(str);
	rtrim(str);   //调用上面的rtrim()函数
	strrevX(str);
	return str;
}

char* trim(char* str)
{
	return rtrim(ltrim(str));
}


#define MAXHEADERSIZE 1024
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHttpSocket::CHttpSocket()
{
	//m_s= BSSocket::getInstance();
	m_s= new BSSocket;
	m_s->Init();
	m_phostent=NULL;
	m_port=80;

	m_bConnected=FALSE;

	for(int i=0;i<256;i++)
		m_ipaddr[i]='\0';
	memset(m_requestheader,0,MAXHEADERSIZE);
	memset(m_ResponseHeader,0,MAXHEADERSIZE);

	m_nCurIndex = 0;		//
	m_bResponsed = FALSE;
	m_nResponseHeaderSize = -1;
/*
	m_nBufferSize = nBufferSize;
	m_pBuffer = new char[nBufferSize];
	memset(m_pBuffer,0,nBufferSize);*/
}

CHttpSocket::~CHttpSocket()
{
	CloseSocket();
}

BOOL CHttpSocket::Socket()
{
	if(m_bConnected)return FALSE;

	struct protoent *ppe; 
	ppe=getprotobyname("tcp"); 
	
	///创建SOCKET对象
	
	m_s->m_sock=socket(PF_INET,SOCK_STREAM,ppe->p_proto);
	if(m_s->m_sock==INVALID_SOCKET)
	{
		//MessageBox(NULL,"socket()函数执行失败!","错误",MB_OK);
		return FALSE;
	}

	return TRUE;

}

BOOL CHttpSocket::Connect(const char *szHostName,int nPort)
{
	if(szHostName==NULL)
		return FALSE;

	///若已经连接,则先关闭
	if(m_bConnected)
	{
		CloseSocket();
	}

	///保存端口号
	m_port=nPort;

	string ip;
	DnsParse(szHostName, ip);
	//BSSocket::DnsParse(szHostName, ip);
	/////根据主机名获得IP地址
	//m_phostent=gethostbyname(szHostName);
	//if(m_phostent==NULL)
	//{
	//	//MessageBox(NULL,"gethostbyname()函数执行失败!","错误",MB_OK);
	//	return FALSE;
	//}
	//
	/////连接
	//struct in_addr ip_addr;
	//memcpy(&ip_addr,m_phostent->h_addr_list[0],4);///h_addr_list[0]里4个字节,每个字节8位
	//
	//struct sockaddr_in destaddr;
	//memset((void *)&destaddr,0,sizeof(destaddr)); 
	//destaddr.sin_family=AF_INET;
	//destaddr.sin_port=htons(80);
	//destaddr.sin_addr=ip_addr;

	/////保存主机的IP地址字符串
	//sprintf(m_ipaddr,"%d.%d.%d.%d",
	//	destaddr.sin_addr.S_un.S_un_b.s_b1,
	//	destaddr.sin_addr.S_un.S_un_b.s_b2,
	//	destaddr.sin_addr.S_un.S_un_b.s_b3,
	//	destaddr.sin_addr.S_un.S_un_b.s_b4);
	/*inet_addr();把带点的IP地址字符串转化为in_addr格式;
	  inet_ntoa();作用相反*/
	
	/*注意理解sturct in_addr 的结构:一个32位的数;一共同体的形式使用
	(1)每8位一个即s_b1~s_b4;
	(2)每16位一个即s_w1~s_w2;
	(3)32位s_addr
	struct   in_addr {
    union   {
			  struct{
				unsigned  char   s_b1,
								 s_b2,
								 s_b3,
								 s_b4;
					} S_un_b;
              struct{
				unsigned  short  s_w1,
                                 s_w2
			        }S_un_w;      
               unsigned long  S_addr;
			} S_un;
		};
	*/

	if(m_s->ConnectSyn(ip.c_str(),m_port) == false)
	{
		//CloseSocket();
		//m_s=NULL;
		//MessageBox(NULL,"connect()函数执行失败!","错误",MB_OK);
		return FALSE;
	}

	///设置已经连接的标志
	m_bConnected=TRUE;
	return TRUE;
}

bool CHttpSocket::DnsParse(const char* domain, string& ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
	char cip[100];
	sprintf(cip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	ip.append(cip);
	return true;
}

///根据请求的相对URL输出HTTP请求头
const char *CHttpSocket::FormatRequestHeader(char *pServer,char *pObject, long &Length,
									  char *pCookie,char *pReferer,long nFrom,
									  long nTo,int nServerType)
{
	char szPort[10];
	char szTemp[20];
	sprintf(szPort,"%d",m_port);
	memset(m_requestheader,'\0',1024);

	///第1行:方法,请求的路径,版本
	strcat(m_requestheader,"GET ");
	strcat(m_requestheader,pObject);
	strcat(m_requestheader," HTTP/1.1");
    strcat(m_requestheader,"\r\n");

	///第2行:主机
    strcat(m_requestheader,"Host:");
	strcat(m_requestheader,pServer);
    strcat(m_requestheader,"\r\n");

	///第3行:
	if(pReferer != NULL)
	{
		strcat(m_requestheader,"Referer:");
		strcat(m_requestheader,pReferer);
		strcat(m_requestheader,"\r\n");		
	}

	///第4行:接收的数据类型
    strcat(m_requestheader,"Accept:*/*");
    strcat(m_requestheader,"\r\n");

	///第5行:浏览器类型
    strcat(m_requestheader,"User-Agent:Mozilla/5.0 (Windows; U; Windows NT 5.2) Gecko/2008070208 Firefox/3.0.1");
    strcat(m_requestheader,"\r\n");

	///第6行:连接设置,保持
	strcat(m_requestheader,"Connection:Keep-Alive");
	strcat(m_requestheader,"\r\n");

	///第7行:Cookie.
	if(pCookie != NULL)
	{
		strcat(m_requestheader,"Set Cookie:0");
		strcat(m_requestheader,pCookie);
		strcat(m_requestheader,"\r\n");
	}

	///第8行:请求的数据起始字节位置(断点续传的关键)
	if(nFrom > 0 || nTo > nFrom)
	{
		strcat(m_requestheader,"Range: bytes=");
		_ltoa(nFrom,szTemp,10);
		strcat(m_requestheader,szTemp);
		strcat(m_requestheader,"-");
		if(nTo > nFrom)
		{
			_ltoa(nTo,szTemp,10);
			strcat(m_requestheader,szTemp);
		}
		strcat(m_requestheader,"\r\n");
	}
	
	///最后一行:空行
	strcat(m_requestheader,"\r\n");

	///返回结果
	Length=strlen(m_requestheader);
	return m_requestheader;
}

///发送请求头
BOOL CHttpSocket::SendRequest(const char *pRequestHeader, long Length)
{
	if(!m_bConnected)return FALSE;

	if(pRequestHeader==NULL)
		pRequestHeader=m_requestheader;
	if(Length==0)
		Length=strlen(m_requestheader);

	
	if(m_s->Send(pRequestHeader,Length,0)==SOCKET_ERROR)
	{
		//MessageBox(NULL,"send()函数执行失败!","错误",MB_OK);
		return FALSE;
	}
	int nLength;
	GetResponseHeader(nLength);
	return TRUE;
}

long CHttpSocket::Receive(char* pBuffer,long nMaxLength)
{
	if(!m_bConnected)return NULL;

	///接收数据
	long nLength;
	nLength=m_s->Recv(pBuffer,nMaxLength,0);
	
	if(nLength <= 0)
	{
		//MessageBox(NULL,"recv()函数执行失败!","错误",MB_OK);
		CloseSocket();
	}
	return nLength;
}

///关闭套接字
BOOL CHttpSocket::CloseSocket()
{
	if(m_s != NULL)
	{
		
		if(m_s->Close()==SOCKET_ERROR)
		{
			//MessageBox(NULL,"closesocket()函数执行失败!","错误",MB_OK);
			return FALSE;
		}
		delete m_s;
		m_s = NULL;
	}

	m_bConnected=FALSE;
	return TRUE;
}

int CHttpSocket::GetRequestHeader(char *pHeader, int nMaxLength) const
{
	int nLength;
	if(int(strlen(m_requestheader))>nMaxLength)
	{
		nLength=nMaxLength;
	}
	else
	{
		nLength=strlen(m_requestheader);
	}
	memcpy(pHeader,m_requestheader,nLength);
	return nLength;
}

//设置接收或者发送的最长时间
BOOL CHttpSocket::SetTimeout(int nTime, int nType)
{
	if(nType == 0)
	{
		nType = SO_RCVTIMEO;
	}
	else
	{
		nType = SO_SNDTIMEO;
	}

	int dwErr;
    dwErr=setsockopt(m_s->m_sock,SOL_SOCKET,nType,(char*)&nTime,sizeof(nTime)); 
	if(dwErr)
	{
		//MessageBox(NULL,"setsockopt()函数执行失败!","错误",MB_OK);
		return FALSE;
	}
	return TRUE;
}

//获取HTTP请求的返回头
const char* CHttpSocket::GetResponseHeader(int &nLength)
{
	if(!m_bResponsed)
	{
		char c = 0;
		int nIndex = 0;
		BOOL bEndResponse = FALSE;
		while(!bEndResponse && nIndex < MAXHEADERSIZE)
		{
			m_s->Recv(&c,1,0);
			m_ResponseHeader[nIndex++] = c;
			if(nIndex >= 4)
			{
				if(m_ResponseHeader[nIndex - 4] == '\r' && m_ResponseHeader[nIndex - 3] == '\n'
					&& m_ResponseHeader[nIndex - 2] == '\r' && m_ResponseHeader[nIndex - 1] == '\n')
				bEndResponse = TRUE;
			}
		}
		m_nResponseHeaderSize = nIndex;
		m_bResponsed = TRUE;
	}
	
	nLength = m_nResponseHeaderSize;
	return m_ResponseHeader;
}

//返回HTTP响应头中的一行.
int CHttpSocket::GetResponseLine(char *pLine, int nMaxLength)
{
	if(m_nCurIndex >= m_nResponseHeaderSize)
	{
		m_nCurIndex = 0;
		return -1;
	}

	int nIndex = 0;
	char c = 0;
	do 
	{
		c = m_ResponseHeader[m_nCurIndex++];
		pLine[nIndex++] = c;
	} while(c != '\n' && m_nCurIndex < m_nResponseHeaderSize && nIndex < nMaxLength);
	
	return nIndex;
}

int CHttpSocket::GetField(const char *szSession, char *szValue, int nMaxLength)
{
	//取得某个域值
	if(!m_bResponsed) return -1;
	
	string strRespons;
	strRespons = m_ResponseHeader;
	int nPos = -1;
	nPos = strRespons.find(szSession,0);
	if(nPos != -1)
	{
		nPos += strlen(szSession);
		nPos += 2;
		int nCr = strRespons.find("\r\n",nPos);
		string strValue = strRespons.substr(nPos,nCr - nPos);
		strcpy(szValue,strValue.c_str());
		return (nCr - nPos);
	}
	else
	{
		return -1;
	}
}

int CHttpSocket::GetServerState()
{
	//若没有取得响应头,返回失败
	if(!m_bResponsed) return -1;
	
	char szState[3];
	szState[0] = m_ResponseHeader[9];
	szState[1] = m_ResponseHeader[10];
	szState[2] = m_ResponseHeader[11];
	//CHttpFile
	
	return atoi(szState);
}

bool CHttpSocket::downFile( string strServer, string strObject, int nPort, string saveFile, int from, int to )
{
	CHttpSocket httpSocket;
	long nLength;
	const char *pRequestHeader = NULL;
	pRequestHeader = httpSocket.FormatRequestHeader((char *)strServer.c_str(),(char *)strObject.c_str(),nLength, NULL, NULL, from, to);	
	httpSocket.Connect((char *)strServer.c_str(), nPort);
	httpSocket.SendRequest();
	httpSocket.SetTimeout(10000,0);
	char szValue[100];
	httpSocket.GetField("Content-Length",szValue,30);
	int nFileSize = atoi(szValue);


	int downFrom = 0, downTo = 0, fileSize;
	httpSocket.GetField("Content-Range",szValue,100);
	if(getRange(string(szValue), downFrom, downTo, fileSize)) {
		int nCompletedSize = 0;
		int nDownloadSize = downTo - downFrom + 1;
		ensureFile(saveFile, fileSize);
		fstream outFile;
		outFile.open(saveFile.c_str(), ios::out|ios::in|ios::binary);
		outFile.seekp(downFrom);
		char pData[8192];
		int nReceSize = 0;
		long dwStartTime,dwEndTime;
		while(nCompletedSize < nDownloadSize)
		{
			dwStartTime = GetTickCount();
			nReceSize = httpSocket.Receive(pData,8192);
			if(nReceSize == 0)
			{
				printf("服务器已经关闭连接.");
				break;
			}
			if(nReceSize == -1)
			{
				printf("接收数据超时.");
				break;
			}
			dwEndTime = GetTickCount();
			outFile.write(pData, nReceSize);
			nCompletedSize += nReceSize;
			printf("write count is %d", outFile.gcount());
			printf("download size is %d, all size is %d", nCompletedSize, nFileSize);
		}
		outFile.close();
	} else {
		int nCompletedSize = 0;
		fstream outFile;
		outFile.open(saveFile.c_str(), ios::out|ios::binary);

		char pData[8192];
		int nReceSize = 0;
		long dwStartTime,dwEndTime;
		while(nCompletedSize < nFileSize)
		{
			dwStartTime = GetTickCount();
			nReceSize = httpSocket.Receive(pData,8192);
			if(nReceSize == 0)
			{
				printf("服务器已经关闭连接.");
				break;
			}
			if(nReceSize == -1)
			{
				printf("接收数据超时.");
				break;
			}
			dwEndTime = GetTickCount();
			outFile.write(pData, nReceSize);
			nCompletedSize += nReceSize;
			printf("write count is %d", outFile.gcount());
			printf("download size is %d, all size is %d", nCompletedSize, nFileSize);
		}
		outFile.close();
	}

	return true;
}

BOOL CHttpSocket::getRange( string range, int& from, int &to, int& fileLength )
{
	from = 0;
	to = 0;
	fileLength = 0;
	if(range.size() < 6 || range.find_first_of("bytes ") == string::npos) {
		return FALSE;
	}
	range = trim((char *)range.c_str());
	range = range.substr(6);
	vector<string> tmp;
	splitStr(tmp, range, "/");
	if(tmp.size() < 2) {
		return FALSE;
	}
	fileLength = atoi(tmp[1].c_str());
	splitStr(tmp, tmp[0], "-");
	if(tmp.size() < 2) {
		return FALSE;
	}
	from = atoi(tmp[0].c_str());
	to = atoi(tmp[1].c_str());
	return true;
}

bool CHttpSocket::ensureFile( string filePath, int fileSize  )
{
	fstream file( filePath.c_str(), ios::in);
	if(!file) {
		fstream outfile( filePath.c_str(), ios::out);
		outfile.close();
	} else {
		file.seekg(0, ios::end);      //设置文件指针到文件流的尾部
		ios::pos_type ps = file.tellg();  //读取文件指针的位置
		if(ps.seekpos() > fileSize && fileSize != -1) {
			file.close();
			printf("文件大小不匹配，丢弃！");
			fstream outfile( filePath.c_str(), ios::out);
			outfile.close();
		} else {
			file.close();
		}
	}
	return true;
}
