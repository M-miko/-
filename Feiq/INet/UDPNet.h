#ifndef _UDPNET_H
#define _UDPNET_H

#include "INet.h"
class UDPNet :public INet
{
public:
	UDPNet();
	~UDPNet();
public:
	bool InitNetWork();
	void UnInitNetWork();
	bool SendData(long lSendIp, char *szbuf,int nlen);
public:
	static  unsigned  __stdcall ThreadProc( void * );
private:
	SOCKET  m_sock;
	SOCKET  m_sockFile;
	HANDLE  m_hThread;
	bool    m_bFlagQuit;
	fd_set  m_fdsets;
};

#endif
