#include "stdafx.h"
#include "UDPMediator.h"
#include "UDPNet.h"
#include "821Feiq.h"

std::list<long> INet::m_lstip;
UDPMediator::UDPMediator()
{
	m_pNet = new UDPNet;
}
UDPMediator::~UDPMediator()
{
	delete m_pNet;
	m_pNet = NULL;
}

ProtocolMap m_aryProtocolMapEntries[] = 
{
	{DEF_PROTOCOL_ONLINE_RQ,&UDPMediator::OnLineRq},
	{DEF_PROTOCOL_ONLINE_RS,&UDPMediator::OnLineRs},
	{DEF_PROTOCOL_OFFLINE_RQ,&UDPMediator::OffLineRq},
	{DEF_PROTOCOL_DATAINFO_RQ,&UDPMediator::DataInfo},
	{0,0}

};

bool UDPMediator::Open()
{
	if(!m_pNet->InitNetWork())
		return false;

	INet::GetValidIp();
	
	STRU_ONLINE so;
	gethostname(so.m_szName,sizeof(so.m_szName));
	so.m_nType = DEF_PROTOCOL_ONLINE_RQ;

	m_pNet->SendData(INADDR_BROADCAST,(char*)&so,sizeof(so));
	return true;
}
void UDPMediator::Close()
{
	STRU_OFFLINE so;
	so.m_nType = DEF_PROTOCOL_OFFLINE_RQ;
	m_pNet->SendData(INADDR_BROADCAST,(char*)&so,sizeof(so));

	m_pNet->UnInitNetWork();

}
bool UDPMediator::SendData(long lSendIp, char *szbuf,int nlen)
{
	if(!m_pNet->SendData(lSendIp,szbuf,nlen))
		return false;

	return true;
}
void UDPMediator::OnLineRq(char *szbuf,long lRecvIp)
{
	STRU_ONLINE *pso = (STRU_ONLINE*)szbuf;
			//加入好友列表
	theApp.m_pMainWnd->SendMessage(UM_ONLINEMSG,(WPARAM)pso->m_szName,lRecvIp);
    //判断是不是自己
	//遍历list  
	auto ite = INet::m_lstip.begin();
	while(ite != INet::m_lstip.end())
	{
		if(*ite == lRecvIp)
			return;
		ite++;
	}
	//回复 
	STRU_ONLINE so;
	so.m_nType = DEF_PROTOCOL_ONLINE_RS;
	gethostname(so.m_szName,sizeof(so.m_szName));

	m_pNet->SendData(lRecvIp,(char*)&so,sizeof(so));
}
void UDPMediator::OnLineRs(char *szbuf,long lRecvIp)
{
	STRU_ONLINE *pso = (STRU_ONLINE*)szbuf;
			//加入好友列表
	theApp.m_pMainWnd->SendMessage(UM_ONLINEMSG,(WPARAM)pso->m_szName,lRecvIp);
}
void UDPMediator::OffLineRq(char *szbuf,long lRecvIp)
{
	theApp.m_pMainWnd->PostMessage(UM_OFFLINEMSG,0,lRecvIp);
}
void UDPMediator::DataInfo(char *szbuf,long lRecvIp)
{
	//显示对应窗口上-- 把信息交给窗口
	STRU_DATAINFO_RQ *psdr = (STRU_DATAINFO_RQ*)szbuf;
	theApp.m_pMainWnd->SendMessage(UM_DATAINFOMSG,(WPARAM)psdr->m_szBuffer,lRecvIp);
}

void UDPMediator::DealData(char *szbuf,long lRecvIp)
{
	PackType *pType = (PackType*)szbuf;
	//遍历结构体数组
	int i =0;
	while(1)
	{
		if(m_aryProtocolMapEntries[i].m_nType == *pType)
		{
			 //diaoyong
			(this->*m_aryProtocolMapEntries[i].m_pfun)(szbuf,lRecvIp);
			 return;
		}
		else if(m_aryProtocolMapEntries[i].m_nType ==0 &&
			m_aryProtocolMapEntries[i].m_pfun ==0)
			break;

		i++;
	}

}