/********************************************************
* PING
* : GCC-4.2.4 
* YSQ-NJUST,yushengqiangyu@163.com
* 
*******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ping.h"
//#include "../include/ping.h"
 
#define E_FAILD_FD -1
#define ICMP_DATA_LEN 32 /* ÿ��ping���Ĵ�С(bytes) */
#define ICMP_ECHO_MAX 4 /* ECHO-REQUEST �ܹ�ping�İ��� */
#define ICMP_REQUEST_TIMEOUT 15 /* ÿ��ping���ĳ�ʱ */
 
/* ICMP  */
static unsigned char aucSendBuf[1024 * 1024] = {0};
static unsigned char aucRecvBuf[1024 * 1024] = {0};
   
/*  */
typedef struct tagIcmpStatic
{
unsigned int uiSendPktNum;
unsigned int uiRcvPktNum;
float fMinTime;
float fMaxTime;
float fArgTime;
}ICMP_STATIC_S;
   
/*  */
ICMP_STATIC_S g_stPktStatic; /* ICMP */
struct timeval stSendTime = {0}; /* ECHO-REQUEST */
struct timeval stRcvTime ={0}; /* ECHO-REPLY */
 
/*  */
enum CHECK_RESULT showStatic(const ICMP_STATIC_S *pstStInfo)
{
	unsigned int uiSend, uiRecv;
	 
	uiSend = pstStInfo->uiSendPktNum;
	uiRecv = pstStInfo->uiRcvPktNum;
	printf("\n*********************PING Statistics***************************");
	printf("\n\tPackets:Send = %u,Recveived = %u,Lost = %u", uiSend, uiRecv, uiSend - uiRecv);
	printf("\n\tTime:Minimum = %.1fms,Maximum = %.1fms,Average=%.2fms\n", pstStInfo->fMinTime, pstStInfo->fMaxTime, pstStInfo->fArgTime);

	if(uiSend > uiRecv)//�ж���
	{
		if(uiRecv == 0) //ȫ������
		{
			return CHECK_RESULT_PACKET_ERROR;
		}
		return CHECK_RESULT_PACKET_LOSS;
	}
	else if(uiSend == uiRecv) //û�ж���
	{
		return CHECK_RESULT_PACKET_OK;
	}
	
	return CHECK_RESULT_PACKET_OK;
}
 
/* */
unsigned int timeSub(const struct timeval *pstOut, const struct timeval *pstIn)
{
unsigned int uiSec = 0;
int iUsec = 0;
 
uiSec = pstOut->tv_sec - pstIn->tv_sec;
iUsec = pstOut->tv_usec - pstIn->tv_usec;
if (0 > iUsec)
{
iUsec += 1000000;
uiSec--;
}
return uiSec * 1000 + (unsigned int)(iUsec / 1000);
}
 
/* */
unsigned short calcIcmpChkSum(const void *pPacket, int iPktLen)
{
    unsigned short usChkSum = 0;
    unsigned short *pusOffset = NULL;
 
    pusOffset = (unsigned short *)pPacket;
    while(1 < iPktLen)
    {
        usChkSum += *pusOffset++;
        iPktLen -= sizeof(unsigned short);
    }
    if (1 == iPktLen)
    {
        usChkSum += *((char *)pusOffset);
    }
    usChkSum = (usChkSum >> 16) + (usChkSum & 0xffff);
    usChkSum += (usChkSum >>16);
 
    return ~usChkSum;
}
 
/* ICMP*/
int newIcmpEcho(const int iPacketNum, const int iDataLen)
{
struct icmp *pstIcmp = NULL;
 
memset(aucSendBuf, 0, sizeof(aucSendBuf));
pstIcmp = (struct icmp *)aucSendBuf;
pstIcmp->icmp_type = ICMP_ECHO;
pstIcmp->icmp_code = 0;
pstIcmp->icmp_seq = htons((unsigned short)iPacketNum);
pstIcmp->icmp_id = htons((unsigned short)getpid());
pstIcmp->icmp_cksum = 0;
pstIcmp->icmp_cksum = calcIcmpChkSum(pstIcmp, iDataLen + 8);
return iDataLen + 8;
}
 
/* ECHOREPLY*/
int parseIcmp(const struct sockaddr_in *pstFromAddr, char *pRecvBuf, const int iLen)
{
int iIpHeadLen = 0;
int iIcmpLen = 0;
struct ip *pstIp = NULL;
struct icmp *pstIcmpReply = NULL;
 
pstIp = (struct ip *)pRecvBuf;
iIpHeadLen = pstIp->ip_hl << 2;
pstIcmpReply = (struct icmp *)(pRecvBuf + iIpHeadLen);
/*  */
iIcmpLen = iLen - iIpHeadLen;
if (8 > iIcmpLen)
{
printf("[Error]Bad ICMP Echo-reply\n");
return -1;
}
/*  */
if ((pstIcmpReply->icmp_type != ICMP_ECHOREPLY) ||
 (pstIcmpReply->icmp_id != htons((unsigned short)getpid())))
{
return -1;
}
sleep(1);
printf("%d bytes reply from %s: icmp_seq=%u Time=%dms TTL=%d\n", iIcmpLen, inet_ntoa(pstFromAddr->sin_addr), ntohs(pstIcmpReply->icmp_seq), timeSub(&stRcvTime, &stSendTime), pstIp->ip_ttl);
 
return 1;
}
 
/* Echo */
void recvIcmp(const int fd)
{
	int iRet = 0;
	int iRecvLen = 0;
	unsigned int uiInterval = 0;
	socklen_t fromLen = sizeof(struct sockaddr_in);
	struct sockaddr_in stFromAddr = {0};
	 
	/* 文 */
	memset(aucRecvBuf, 0, 1024 * 1024);
	iRecvLen = recvfrom(fd, (void *)aucRecvBuf, sizeof(aucRecvBuf), 0, (struct sockaddr *)&stFromAddr,&fromLen); 
	gettimeofday(&stRcvTime, NULL);
	if (0 > iRecvLen)
	{
		if (EAGAIN == errno)
		{
			/* */
			printf("Request time out.\n");
			g_stPktStatic.fMaxTime = ~0;
		}
		else
		{
			/*  */
			perror("[Error]ICMP Receive");
		}
		return;
	}
	/*   */
	g_stPktStatic.uiRcvPktNum++;
	uiInterval = timeSub(&stRcvTime, &stSendTime);
	g_stPktStatic.fArgTime = (g_stPktStatic.fArgTime * (g_stPktStatic.uiSendPktNum - 1) + uiInterval)/g_stPktStatic.uiSendPktNum;
	if (uiInterval < g_stPktStatic.fMinTime)
	{
		g_stPktStatic.fMinTime = uiInterval;
	}
	if (uiInterval > g_stPktStatic.fMaxTime)
	{
		g_stPktStatic.fMaxTime = uiInterval;
	}
	/* ICMP */
	iRet = parseIcmp(&stFromAddr, (char *)aucRecvBuf, iRecvLen);
	if (0 > iRet)
	{
		return;
	}
}
 
/* ICMP */
void sendIcmp(const int fd, const struct sockaddr_in *pstDestAddr)
{
	unsigned char ucEchoNum = 0;
	int iPktLen = 0;
	int iRet = 0;

	//printf("----------ICMP_ECHO_MAX:%d, ICMP_DATA_LEN:%d\n", ICMP_ECHO_MAX, ICMP_DATA_LEN); 

	while(ICMP_ECHO_MAX > ucEchoNum)
	{
		iPktLen = newIcmpEcho(ucEchoNum, ICMP_DATA_LEN);
		//printf("------------iPktLen:%d\n", iPktLen);
		/*  */
		g_stPktStatic.uiSendPktNum++;
		gettimeofday(&stSendTime, NULL);
		
		/* ICMPECHO */
		iRet = sendto(fd, aucSendBuf, iPktLen, 0, (struct sockaddr *)pstDestAddr, sizeof(struct sockaddr_in));
		if(0 > iRet)
		{
			perror("Send ICMP Error");
			continue;
		}
		
		/* �ӶԷ�IP�������� */
		recvIcmp(fd);
		ucEchoNum++;
	}
}


 
/**/
enum CHECK_RESULT lib_get_network_status(const char *ip_addr)
{
		int ret = -1;
		int iRet = 0;
		int iRcvBufSize = 1024 * 1024;
		int fd = E_FAILD_FD;
		in_addr_t stHostAddr;
		 
		struct timeval stRcvTimeOut = {0};
		struct hostent *pHost = NULL;
		struct sockaddr_in stDestAddr = {0};
		struct protoent *pProtoIcmp = NULL;
		g_stPktStatic.uiSendPktNum = 0;
		g_stPktStatic.uiRcvPktNum =0;
		g_stPktStatic.fMinTime = 1000000.0;
		g_stPktStatic.fMaxTime = -1.0;
		g_stPktStatic.fArgTime = 0.0;

		/* ICMP */
		pProtoIcmp = getprotobyname("icmp");
		if (NULL == pProtoIcmp)
		{
			perror("[Error]Get ICMP Protoent Structrue\n");
			return CHECK_RESULT_FAILED;
		}
		
		/* ICMPSOCKET */
		fd = socket(PF_INET, SOCK_RAW, pProtoIcmp->p_proto);
		if (0 > fd)
		{
			perror("[Error]Init Socket");
			return CHECK_RESULT_FAILED;
		}
		
		/* ROOT  */
		iRet = setuid(getuid());
		if (0 > iRet)
		{
			perror("[Error]Setuid");
			close(fd);
			return CHECK_RESULT_FAILED;
		}
		
		/* ����SOCKETѡ�� */
		stRcvTimeOut.tv_sec = ICMP_REQUEST_TIMEOUT;
		setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &iRcvBufSize, sizeof(iRcvBufSize));
		setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &stRcvTimeOut, sizeof(struct timeval));
		 
		/* ����IP��ַ */
		stHostAddr = inet_addr(ip_addr);
		if (INADDR_NONE == stHostAddr)
		{
			/* IP */
			pHost = gethostbyname(ip_addr);
			if (NULL == pHost)
			{
				perror("[Error]Host Name Error");
				close(fd);
				return CHECK_RESULT_FAILED;
			}
			memcpy((char *)&stDestAddr.sin_addr, (char *)(pHost->h_addr), pHost->h_length);
		}
		else
		{
			memcpy((char *)&stDestAddr.sin_addr, (char *)&stHostAddr, sizeof(stHostAddr));
		}
		
		printf("\nPING %s(%s): %d bytes in ICMP packets\n", ip_addr, inet_ntoa(stDestAddr.sin_addr), ICMP_DATA_LEN);

		/*ICMP*/ //ping����
		sendIcmp(fd, &stDestAddr);

		/* ��ʾpingͳ�ƽ�� */
		ret = showStatic(&g_stPktStatic);

		
		/* FD */
		close(fd);
		return ret;
}

