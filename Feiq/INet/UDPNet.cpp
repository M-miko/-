#include "stdafx.h"
#include "UDPNet.h"
#include "821Feiq.h"

UDPNet::UDPNet()
{
	m_sock = NULL;
	m_hThread = NULL;
	m_bFlagQuit = true;
	FD_ZERO(&m_fdsets);
}

UDPNet::~UDPNet()
{}


bool UDPNet::InitNetWork()
{
	//1.选择种类  炸臭豆腐 烤冷面 板面 -- 加载库 --
	WSADATA wsaData;
    int err;
	WORD wVersionRequested;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */

        return false;
    }

/* Confirm that the WinSock DLL supports 2.2.*/
/* Note that if the DLL supports versions greater    */
/* than 2.2 in addition to 2.2, it will still return */
/* 2.2 in wVersion since that is the version we      */
/* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
      
        UnInitNetWork();
        return false;
    }
  
	//2.雇人  -- 创建套接字-- 
	m_sock = socket(AF_INET,SOCK_DGRAM ,IPPROTO_UDP );
	if(m_sock == INVALID_SOCKET )
	{
		UnInitNetWork();
        return false;
	}
	m_sockFile = socket(AF_INET,SOCK_DGRAM ,IPPROTO_UDP );
	if(m_sockFile == INVALID_SOCKET )
	{
		UnInitNetWork();
        return false;
	}
	FD_SET(m_sock,&m_fdsets);
	FD_SET(m_sockFile,&m_fdsets);
	//将socket 属性改为非阻塞
	// u_long argp = 1;
	//ioctlsocket(m_sock,FIONBIO,&argp);
	//ioctlsocket(m_sockFile,FIONBIO,&argp);
	//socket广播
	BOOL bval = TRUE;
	setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(const char*)&bval,sizeof(bval));
	//3.找地  -- 绑定 --
	sockaddr_in  addrserver;//127.0.0.1 本机环网
	addrserver.sin_addr.S_un.S_addr = INADDR_ANY;//192.168.1.1  192.168.5.20
	addrserver.sin_family = AF_INET;
	addrserver.sin_port = htons(DEF_PORT);
	if(SOCKET_ERROR == bind(m_sock,(const sockaddr *)&addrserver,sizeof(addrserver)))
	{
		UnInitNetWork();
        return false;
	}
	addrserver.sin_port = htons(1235);
	if(SOCKET_ERROR == bind(m_sockFile,(const sockaddr *)&addrserver,sizeof(addrserver)))
	{
		UnInitNetWork();
        return false;
	}

	//recvfrom -- 创建线程
	m_hThread = (HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
	return true;
}

unsigned  __stdcall UDPNet::ThreadProc( void *lpvoid )
{
	UDPNet *pthis = (UDPNet*)lpvoid;
	char szbuf[DEF_PACKSIZE] = {0};
	sockaddr_in addrClient;
	int nSize =sizeof(sockaddr_in);
	int nRelReadNum;
	fd_set fdsettemp;
	timeval tv;
	tv.tv_sec =0;
	tv.tv_usec = 100;
	while(pthis->m_bFlagQuit)
	{
		//将集合交给select 管理
		fdsettemp = pthis->m_fdsets;
		select(0,&fdsettemp,0,0,&tv);

		if(FD_ISSET(pthis->m_sock,&fdsettemp))
		{
			nRelReadNum = recvfrom(pthis->m_sock,szbuf,DEF_PACKSIZE,0,(sockaddr*)&addrClient,&nSize);
 			if(nRelReadNum >0)
			{
				//处理--内存池
				theApp.m_pMediator->DealData(szbuf,addrClient.sin_addr.s_addr);
			}
		}
		if(FD_ISSET(pthis->m_sockFile,&fdsettemp))
		{
			nRelReadNum = recvfrom(pthis->m_sockFile,szbuf,DEF_PACKSIZE,0,(sockaddr*)&addrClient,&nSize);
			if(nRelReadNum >0)
			{
				//处理--内存池
				theApp.m_pMediator->DealData(szbuf,addrClient.sin_addr.s_addr);
			}
		}
		
	
	}
	return 0;
}
void UDPNet::UnInitNetWork()
{
	m_bFlagQuit = false;
	if(m_hThread)
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThread,100))
			TerminateThread(m_hThread,-1);

		CloseHandle(m_hThread);
		m_hThread =NULL;
	}
	if(m_sock)
	{
		closesocket(m_sock);
		m_sock = NULL;
	}
	 WSACleanup();
}
bool UDPNet::SendData(long lSendIp, char *szbuf,int nlen)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = lSendIp;
	addr.sin_port = htons(DEF_PORT);

	if(sendto(m_sock,szbuf,nlen,0,(const sockaddr*)&addr,sizeof(addr))<=0)
		return false;
	return true;
}