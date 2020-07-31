#ifndef _INET_H
#define _INET_H

#include "Packdef.h"
#include <Winsock2.h>
#include <process.h>
#include <list>
#pragma comment(lib,"Ws2_32.lib")
class INet
{
public:
	INet()
	{}
	virtual ~INet()
	{}
public:
	virtual bool InitNetWork() =0;
	virtual void UnInitNetWork() =0;
	virtual bool SendData(long lSendIp, char *szbuf,int nlen) = 0;
public:
	static  void GetValidIp()
	{
		char szName[100] = {0};
		hostent *remoteHost = NULL;
		int i = 0;
		struct in_addr addr;
	      //1.获取本机名
		   if(!gethostname(szName,100))
		   {
				//2.获取iplist
			   remoteHost = gethostbyname(szName);
			    while (remoteHost->h_addr_list[i] != 0) 
				{
					addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
					m_lstip.push_back( addr.s_addr);
				}

		   }
		

	
	}

public:
	static std::list<long> m_lstip;
};

#endif
