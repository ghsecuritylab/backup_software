#include <stdio.h>
#include "lib_rent_record.h"
#include <stdlib.h>
#include <string.h>


int ParseRentBikeRecord(char* buff,int len)
{
	if(buff == NULL || len <= 0)
	{	
		return -1;
	}
	
	int begin = 11;//�ӵ�12���ֽڿ�ʼΪ���ü�¼����
	int end = 0;	
	int cnt = 0;
	int size = 0;
	int i = 0;
	int m_CurrRecordNum = 0;
	
	rent_info_fmt_t *m_RentRecordInfo = NULL;
	m_RentRecordInfo = calloc(buff[8],sizeof(rent_info_fmt_t));//���ݼ�¼����������ռ�

	for(i = 11; i < len + 11; i++)//�ӵ�12���ֽڿ�ʼΪ���ü�¼����
	//for(i = 0; i < len; i++)//�ӵ�12���ֽڿ�ʼΪ���ü�¼����
	{
		//0x09:�ֶμ�ķָ���(tab��), 0x10:��¼��ķָ���(���м�)
		if((buff[i] == 0x09) || (buff[i] == 0x0a))
		{
			end = i;
			size = end - begin;//һ���ֶεĳ���
			switch(cnt)//�������ֶο����ṹ���Ӧ�ĳ�Ա��ȥ
			{
				case 0://���г����
					if(size >= 32)
					{
						size = 32;
					}
					if(m_CurrRecordNum == 0)
						memcpy(m_RentRecordInfo[m_CurrRecordNum].bike_NO,\
					   		&buff[begin],size);
					else
						memcpy(m_RentRecordInfo[m_CurrRecordNum].bike_NO,\
					   		&buff[begin+1],size);
					
					m_RentRecordInfo[m_CurrRecordNum].bike_NO[size] = '\0';
					break;
				case 1://�⳵������
					if(size >= 64)
					{
						size = 64;
					}
					memcpy(m_RentRecordInfo[m_CurrRecordNum].rent_name,\
						   &buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].rent_name[size] = '\0';
					break;
				case 2://�⳵��ʱ��
					if(size >= 32)
					{
						size = 32;
					}
					memcpy(m_RentRecordInfo[m_CurrRecordNum].rent_time,\
						   &buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].rent_time[size] = '\0';
					break;
				case 3://����������
					if(size >= 64)
					{
						size = 64;
					}
					memcpy(m_RentRecordInfo[m_CurrRecordNum].return_name,\
				   			&buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].return_name[size] = '\0';					
					break;
				case 4://����ʱ��
					if(size >= 32)
					{
						size = 32;
					}
					memcpy(m_RentRecordInfo[m_CurrRecordNum].return_time,\
		   					&buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].return_time[size] = '\0';
					break;
				case 5://����ʱ��
					if(size >= 16)
					{
						size = 16;
					}
					memcpy(&m_RentRecordInfo[m_CurrRecordNum].used_time,\
				   			&buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].used_time[size] = '\0';
					break;
				case 6://�۷�
					if(size >= 16)
					{
						size = 16;
					}
					memcpy(m_RentRecordInfo[m_CurrRecordNum].fee,\
				   			&buff[begin+1],size);
					m_RentRecordInfo[m_CurrRecordNum].fee[size] = '\0';
					break;
				default:
					cnt = 0;
					break;
			}
			begin = end;
			cnt++;//ͬһ����¼��ĵڼ����ֶ�
		}	
		if(buff[i] == 0x0a)
		{	
			//��ӡ��ʾÿһ�����ü�¼
			printf("---------RecordNum:[%d]---------\n",m_CurrRecordNum);
			printf("bike_NO:%s\n",m_RentRecordInfo[m_CurrRecordNum].bike_NO);
			printf("rent_name:%s\n",m_RentRecordInfo[m_CurrRecordNum].rent_name);
			printf("rent_time:%s\n",m_RentRecordInfo[m_CurrRecordNum].rent_time);
			printf("return_name:%s\n",m_RentRecordInfo[m_CurrRecordNum].return_name);
			printf("return_time:%s\n",m_RentRecordInfo[m_CurrRecordNum].return_time);
			printf("used_time:%s\n",m_RentRecordInfo[m_CurrRecordNum].used_time);
			printf("fee:%s\n",m_RentRecordInfo[m_CurrRecordNum].fee);

			m_CurrRecordNum++;//�ڼ�����¼
			cnt = 0;
		}
	}

	if(m_RentRecordInfo != NULL)
	{
		free(m_RentRecordInfo);
		m_RentRecordInfo = NULL;
	}
	
	return 0;
}


