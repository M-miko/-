#ifndef _UDPMEDIATOR_H
#define _UDPMEDIATOR_H

#include "IMediator.h"

class UDPMediator;
typedef void (UDPMediator:: *PFUN)(char *,long)  ;
struct ProtocolMap
{
	PackType m_nType;  //Э��
	PFUN     m_pfun;   //����ָ��

};

class UDPMediator :public IMediator
{
public:
	UDPMediator();
	virtual ~UDPMediator();
public:
	bool Open();
	void Close();
	bool SendData(long lSendIp, char *szbuf,int nlen);
	void DealData(char *szbuf,long lRecvIp);
public:
    void OnLineRq(char *szbuf,long lRecvIp);
	void OnLineRs(char *szbuf,long lRecvIp);
	void OffLineRq(char *szbuf,long lRecvIp);
	void DataInfo(char *szbuf,long lRecvIp);

};

#endif
