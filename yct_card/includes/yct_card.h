
#ifndef __YCT_CARD_H_
#define __YCT_CARD_H_

int GetVersion(char* szVer);//��ȡ����汾
int Module_Init(char pSPno[2], char pSamID[4]);//����ģ���ʼ��
int QuerTicketInfo(char* pData);//��ѯƱ����Ϣ
int QuerRentInfo(char bID,char* pData,char* pLen);//��ѯ�⻹����Ϣ
int SetRentInfo(char bID,char* pData,char* pLen);//�����⻹����Ϣ
int Consume(long lAmount, long lFee, char pTime[6], char bPHysicalID[8], char bAddtionalType);//����
int SetBlackFlag(char pData[16]);//���ú�����
int GetHisRecord(char* pType, char* pData);//������׼�¼
int GetTrans(char bTrans[90]);//��ȡ��������
unsigned char CheckSum(unsigned char *data,const unsigned char len);//У����

#endif // __yct_card_H__
