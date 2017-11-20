// HttpSocket.h: interface for the CHttpSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _NET_HTTPSOCKET_H_
#define _NET_HTTPSOCKET_H_
#include "BSSocket.h"

void  splitStr(vector<string> &gRet, string cStr ,const char* cSplit );
char* strrevX(char * str); 
char* rtrim(char* str); 
char* ltrim(char* str); 
char* trim(char* str);

class  CHttpSocket  
{
public:
	int				GetServerState();						//���ط�����״̬�� -1��ʾ���ɹ�
	int				GetField(const char* szSession,char *szValue,int nMaxLength);	//����ĳ����ֵ,-1��ʾ���ɹ�
	int				GetResponseLine(char *pLine,int nMaxLength);				//��ȡ����ͷ��һ��
	const char*		GetResponseHeader(int &Length);								//��ȡ�����ķ���ͷ
	const char *	FormatRequestHeader(char *pServer,char *pObject,long &Length,
						char* pCookie=NULL,char *pReferer=NULL,
						long nFrom=0,long nTo=0,
						int nServerType=0);									//��ʽ������ͷ
	int				GetRequestHeader(char *pHeader,int nMaxLength) const;
	BOOL			SendRequest(const char* pRequestHeader = NULL,long Length = 0);
    
	
	CHttpSocket();
	virtual ~CHttpSocket();

	BOOL			SetTimeout(int nTime,int nType=0);
	long			Receive(char* pBuffer,long nMaxLength);
	BOOL			Connect(const char* szHostName,int nPort=80);
	BOOL			Socket();
	BOOL			CloseSocket();
	// Domain parse
	bool DnsParse(const char* domain, string& ip);
	static bool ensureFile(string filePath, int fileSize = -1);
	static bool downFile(string strServer, string strObject, int nPort, string saveFile, int from = 0, int to = 0);
	static BOOL getRange(string range, int& from, int &to, int& fileLength);

protected:	
	char m_requestheader[1024];		//����ͷ
	char m_ResponseHeader[1024];	//��Ӧͷ
	int m_port;						//�˿�
	char m_ipaddr[256];				//IP��ַ
	BOOL m_bConnected;
	BSSocket* m_s;
	hostent *m_phostent;

	int m_nCurIndex;				//GetResponsLine()�������α��¼
	BOOL m_bResponsed;				//�Ƿ��Ѿ�ȡ���˷���ͷ
	int m_nResponseHeaderSize;		//��Ӧͷ�Ĵ�С
/*
	int m_nBufferSize;
	char *m_pBuffer;*/

};

#endif 
