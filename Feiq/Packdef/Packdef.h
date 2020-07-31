#ifndef _PACKDEF_H
#define _PACKDEF_H


#define DEF_PORT 1234
#define DEF_BUFFERSIZE  45

#define DEF_CONTENTSIZE   100
#define DEF_PACKSIZE  1024

#define DEF_PROTOCOL_BASE   10
//消息
#define UM_ONLINEMSG      WM_USER +1
#define UM_OFFLINEMSG     WM_USER +2
#define UM_DATAINFOMSG    WM_USER +3
//协议
#define DEF_PROTOCOL_ONLINE_RQ    DEF_PROTOCOL_BASE +1
#define DEF_PROTOCOL_ONLINE_RS    DEF_PROTOCOL_BASE +2

#define DEF_PROTOCOL_OFFLINE_RQ    DEF_PROTOCOL_BASE +3

#define DEF_PROTOCOL_DATAINFO_RQ    DEF_PROTOCOL_BASE +4
#define DEF_PROTOCOL_DATAINFO_RS   DEF_PROTOCOL_BASE  +5

typedef char PackType;
   
//协议包
struct STRU_ONLINE
{
	PackType  m_nType;
	char      m_szName[DEF_BUFFERSIZE];
//	long      m_lhostIp;
};

struct STRU_OFFLINE
{
	PackType  m_nType;
};

struct STRU_DATAINFO_RQ
{
	PackType  m_nType;
	char      m_szBuffer[DEF_CONTENTSIZE];
	int       m_nSeq;
};

struct STRU_DATAINFO_RS
{
	PackType  m_nType;
	int       m_nSeq;
};








#endif