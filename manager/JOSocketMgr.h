//
//  JOSocketMgr.h
//
//  Created by mac on 12-7-6.
//  Copyright (c) 2012??? __MyCompanyName__. All rights reserved.
//

#ifndef __JOSOCKETMGR_H__
#define __JOSOCKETMGR_H__

#include <unordered_map>
#include "utils/JOMacro.h"
#include "utils/JOSingleton.h"
#include "core/socket/JOSocket.h"


NS_JOFW_BEGIN
class JODataCoder;

#pragma mark -
#pragma mark JOSocketMgr
class JO_DLL JOSocketMgr : public JOSocketDelegate, public JOSingleton<JOSocketMgr> {

public:
	JOSocketMgr();
	virtual ~JOSocketMgr();

	void initMainSocketId(int id);

public:
	void connect(const char* ip, unsigned int port, bool beAsyn, int socketId = -1);
	bool disconnect(int socketId = -1);
	void sendMessage(JODataCoder* dataCoder, int socketId = -1);

	void setBigEndian(bool bigEndian);
	inline bool getBigEndian(){ return m_bBigEndian; };
	JO_SYNTHESIZE(bool, m_bDebug, Debug);
private:
	void _disconnectAll();
private:
	JOSocket* _getSocket(int id);
	JOSocket* _findSocket(int id);

private:
	short m_mainSocketId;
	bool m_bBigEndian;

	typedef unordered_map<short, JOSocket*> SOCKET_MAP;
	SOCKET_MAP socket_map;

#pragma mark JOSocketDelegate
public:
	virtual void onSocketWillConnect(JOSocket* socket);
	virtual void onSocketConnected(JOSocket* socket, const char* ip, unsigned int port);
	virtual void onSocketConnectFail(JOSocket* socket);
	virtual void onSocketDidDisconnected(JOSocket* socket);

	virtual void onSocketDidReadData(JOSocket* socket, JODataCoder* dataCoder);
	virtual JODataCoder* onSocketDidReadPartialData(JOSocket* socket, unsigned char* pData, unsigned int size, unsigned int* len);
	virtual void onSocketDidWriteData(JOSocket* socket);

	virtual void onSocketWithError(JOSocket* socket, JOSocketError error);
};

NS_JOFW_END
#endif //!__JOSOCKETMGR_H__
