
#include "lib_general.h"
#include "yct_card.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define	DEVNAME	"/dev/ttyO1"

lib_serial_t uart1;

int main(int argc,char *argv[])
{
	int ret = -1;
	char *pData,*szVer,*RentData,*pLen;
	char tbuf[128] = {0},rbuf[128] = {0};
	char pSPno[2] = {0}, pSamID[4] = {0};
	//lib_serial_t uart1;
  	memset(&uart1, 0, sizeof(lib_serial_t));
  	//���ڳ�ʼ��
  	strcpy(uart1.pathname,DEVNAME);
  	uart1.flags = O_RDWR;
  	uart1.speed = 115200;
  	uart1.databits = 8;
  	uart1.stopbits = 1;
		 
 	ret = lib_serial_init(&uart1);
	printf("uart init ret:%d,sfd:%d\n",ret, uart1.sfd);
	///////////////////////////////////////////
	ret = Module_Init(pSPno,pSamID);//����ģ���ʼ��
	GetVersion(szVer);//��ȡ����汾
	QuerTicketInfo(pData);//��ѯƱ����Ϣ
	//QuerRentInfo(0x38,RentData,pLen);//��ѯ�⻹����Ϣ
	
	return 0;
}

/////////////////////////////////////////////////
int GetVersion(char* szVer)//��ȡ����汾
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x02;//len
	tbuf[2] = 0x60;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 3);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_printf("------send------\n", tbuf, ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(szVer,&rbuf[4],24);
	//lib_printf("------recv------\n", rbuf, ret);
	lib_vprintf("software version:%s\n",szVer);
	
	return 0;
}
//����ģ���ʼ��
//����pSPno �� �����̴��� ���pSamID��PSAM ����
int Module_Init(char pSPno[2], char pSamID[4])
{
	int ret = -1;
	char tbuf[6] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x04;//len
	tbuf[2] = 0xD2;//cmd
	memcpy(&tbuf[3],pSPno,2);//data 0
	tbuf[5] = CheckSum(&tbuf[0], 7);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_printf("------send------\n", tbuf, 6);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(pSamID,&rbuf[4],4);
	//lib_printf("------recv------\n", rbuf, ret);
	
	return 0;
}

//��ѯƱ����Ϣ
int QuerTicketInfo(char* pData)
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x02;//len
	tbuf[2] = 0xD3;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 3);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_printf("------send------\n", tbuf, 4);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(&pData,&rbuf[4],1);
	lib_printf("------recv------\n", rbuf, ret);

	return 0;
}
//��ѯ�⻹����Ϣ
int QuerRentInfo(char bID,char* pData,char* pLen)
{
	int ret = -1;
	char tbuf[5] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x03;//len
	tbuf[2] = 0xD9;//cmd
	memcpy(&tbuf[3],&bID,1);//data 
	tbuf[4] = CheckSum(&tbuf[0], 4);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_printf("------send------\n", tbuf, ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(&pData,&rbuf[4],1);
	lib_printf("------recv------\n", rbuf, ret);
	
	return 0;
}
//�����⻹����Ϣ
//���룺 bID �� ����Ӧ�����ͱ�ʶ�������г�һ��Ӧ�ã� 0x38������ֵ��ԱӦ�ã� 0x68����
//pData �� �����õ��⻹����Ϣ
int SetRentInfo(char bID,char* pData,char* pLen)
{
	int ret = -1;
	char tbuf[3] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x04;//len
	tbuf[2] = 0xDA;//cmd
	memcpy(&tbuf[3],&bID,1);
	memcpy(&tbuf[4],pData,1);
	tbuf[5] = CheckSum(&tbuf[0], 5);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	pLen = (char *)ret;
	lib_printf("------recv------\n", rbuf, ret);
	
	return 0;
}
//����
int Consume(long lAmount, long lFee, char pTime[6], char bPHysicalID[8], char bAddtionalType)
{
	int ret = -1;
	char tbuf[27] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x19;//len 25
	tbuf[2] = 0xD4;//cmd
	memcpy(&tbuf[3],&lAmount,4);
	memcpy(&tbuf[7],&lFee,4);
	memcpy(&tbuf[11],pTime,6);
	memcpy(&tbuf[17],bPHysicalID,8);
	memcpy(&tbuf[25],&bAddtionalType,1);
	tbuf[26] = CheckSum(&tbuf[0], 26);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	lib_printf("------recv------\n", rbuf, ret);
	
	return 0;
}
//���ú�����
int SetBlackFlag(char pData[16])
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x02;//len
	tbuf[2] = 0xD5;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 3);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	lib_printf("------recv------\n", rbuf, ret);
	
	return 0;
}
//��ѯ�����ʷ���׼�¼
int GetHisRecord(char* pType, char* pData)
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x02;//len
	tbuf[2] = 0xD6;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 3);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(pType, &rbuf[4], 1);
	memcpy(pData,&rbuf[5],ret -6);
	lib_printf("------recv------\n", rbuf, ret);

	return 0;
}
//��ȡ��������
int GetTrans(char bTrans[90])
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[128] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x02;//len
	tbuf[2] = 0xD8;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 3);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	memcpy(bTrans,&rbuf[4],90);
	lib_printf("------recv------\n", rbuf, ret);

	return 0;
}
//��������
int Set_parameter(char arg[3])
{
	int ret = -1;
	char tbuf[4] = {0},rbuf[5] = {0};
	
	tbuf[0] = 0xBA;//header
	tbuf[1] = 0x05;//len
	tbuf[2] = 0xD7;//cmd
	tbuf[3] = CheckSum(&tbuf[0], 6);//checksum

	ret = lib_serial_send(uart1.sfd, &tbuf, sizeof(tbuf));
	lib_vprintf("send %d bytes\n",ret);
	lib_msleep(300);

	ret = lib_serial_recv(uart1.sfd, &rbuf, sizeof(rbuf));
	lib_printf("------recv------\n", rbuf, ret);

	return 0;
}
//У����
unsigned char CheckSum(unsigned char *data,const unsigned char len)
{
	int i;
	unsigned char check;
	for(i = 0; i < len; i++)
	{
		check ^= data[i];
	}

	return check;
}
















