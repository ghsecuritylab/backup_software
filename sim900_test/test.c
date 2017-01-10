#include <stdio.h>
#include "lib_general.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>


#define SIM900_UART		"/dev/ttyUSB3"
#define READ_SLEEP		100


int main(void)
{
		//printf("sim900 test ...\n");
	
#if 1 
		int ret = -1;
		char tbuf[128] = {0},rbuf[128] = {0};
		lib_serial_t sim900;
		
		memset(&sim900, 0, sizeof(lib_serial_t));
		//���ڳ�ʼ��
		strcpy(sim900.pathname,SIM900_UART);
		sim900.flags = O_RDWR;
		sim900.speed = 9600;
		sim900.databits = 8;
		sim900.stopbits = 1;

		ret = lib_serial_init(&sim900);
		if(ret == -1)
		{
			perror("serial init");
		}
		printf("uart init ret:%d, sfd:%d\n", ret, sim900.sfd);
#endif
		#if 0 //����
		ret = lib_serial_send(sim900.sfd, "ATE1\r", strlen("ATE1\r"));

		ret = lib_serial_readn_select(sim900.sfd, &rbuf, sizeof(rbuf), 200);

		printf("read data:%s\n", rbuf);
		#endif

		//lib_begin_runtime_printf();
	
		ret = lib_tcp_connect_setup(sim900.sfd, "112.74.97.250", "60000");

		//lib_end_runtime_printf();

		//lib_sleep(2);
	#if 0 //�ر�TCP����
		ret = lib_serial_send(sim900.sfd, "AT+CIPCLOSE=1\r", strlen("AT+CIPCLOSE=1\r"));

		ret = lib_serial_readn_select(sim900.sfd, &rbuf, sizeof(rbuf), 200);
		printf("read data:%s\n", rbuf);

		ret = lib_serial_send(sim900.sfd, "AT+CIPSHUT\r", strlen("AT+CIPSHUT\r"));

		ret = lib_serial_readn_select(sim900.sfd, &rbuf, sizeof(rbuf), 200);
		printf("read data:%s\n", rbuf);
		
	#endif

		
		
		//shutdown(sim900.sfd, SHUT_WR); //�ر�д��

		lib_close(sim900.sfd);
		
		return 0;
}

#define READ_DATA	1
int lib_tcp_connect_setup(int sfd, const char *ip, const char *port)
{
	int ret = -1, i = 0;
	unsigned char cmd[128] = {0}, data[128] = {0};

	for(i = 0; i < 2; i++)
	{
		if(i == 0)
		{
		#if 1 //��ʼ��
			//�����ƶ�̨̨���Ϊ B
			strcpy(cmd, "AT+CGCLASS=\"B\"\r"); 
			ret = lib_serial_send(sfd, cmd, strlen(cmd));
			#if READ_DATA
			ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
			printf("read data:%s\n", data);
			#endif
			memset(cmd, 0, sizeof(cmd));
			memset(data, 0, sizeof(data));

			//���� PDP �����ı��־Ϊ 1������IPЭ�飬�����Ϊ"CMNET"
			strcpy(cmd, "AT+CGDCONT=1,\"IP\",\"CMNET\"\r");
			ret = lib_serial_send(sfd, cmd, strlen(cmd));
			#if READ_DATA
			ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
			printf("read data:%s\n", data);
			#endif
			memset(cmd, 0, sizeof(cmd));
			memset(data, 0, sizeof(data));

			//���ø��� GPRS ҵ��
			strcpy(cmd, "AT+CGATT=1\r");
			ret = lib_serial_send(sfd, cmd, strlen(cmd));
			#if READ_DATA
			ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
			printf("read data:%s\n", data);
			#endif
			memset(cmd, 0, sizeof(cmd));
			memset(data, 0, sizeof(data));

			//����Ϊ GPRS ���ӣ������Ϊ��CMNET��
			strcpy(cmd, "AT+CIPCSGP=1,\"CMNET\"\r");
			ret = lib_serial_send(sfd, cmd, strlen(cmd));
			#if READ_DATA
			ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
			printf("read data:%s\n", data);
			#endif
			memset(cmd, 0, sizeof(cmd));
			memset(data, 0, sizeof(data));

			//���� TCP ���ӱ��ض˿ں�
			strcpy(cmd, "AT+CLPORT=\"TCP\",\"2000\"\r");
			ret = lib_serial_send(sfd, cmd, strlen(cmd));
			#if READ_DATA
			ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP + 300);
			printf("read data:%s\n", data);
			#endif
			memset(cmd, 0, sizeof(cmd));
			memset(data, 0, sizeof(data));
		#endif
		}

		lib_begin_runtime_printf();
		//����TCP������IP�Ͷ˿�	
		strcpy(cmd, "AT+CIPSTART=\"TCP\",");
		strcat(cmd, "\"");
		strcat(cmd, ip);
		strcat(cmd, "\"");
		strcat(cmd, ",");
		strcat(cmd, "\"");
		strcat(cmd, port);
		strcat(cmd, "\"\r");
		ret = lib_serial_send(sfd, cmd, strlen(cmd));
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP + 3000);
		printf("read data:%s\n", data);
		#endif
		memset(cmd, 0, sizeof(cmd));
		memset(data, 0, sizeof(data));
		
		//�������ݷ���ģʽ
		strcpy(cmd, "AT+CIPSEND\r");
		ret = lib_serial_send(sfd, cmd, strlen(cmd));
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP + 100);
		printf("read data:%s\n", data);
		#endif
		memset(cmd, 0, sizeof(cmd));
		memset(data, 0, sizeof(data));

		//��������
		strcpy(cmd, "hello world"); //send data
		ret = lib_serial_send(sfd, cmd, strlen(cmd));
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
		printf("read data:%s\n", data);
		#endif
		memset(cmd, 0, sizeof(cmd));
		memset(data, 0, sizeof(data));

		//�������ݷ���
		cmd[0] = 0x1A;
		ret = lib_serial_send(sfd, cmd, 1);
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP);
		printf("read data:%s\n", data);
		#endif
		memset(cmd, 0, sizeof(cmd));
		memset(data, 0, sizeof(data));

	#if 1 
		//�ر�TCP����
		strcpy(cmd, "AT+CIPCLOSE=1\r"); //send data
		ret = lib_serial_send(sfd, cmd, strlen(cmd));
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP + 100);
		printf("read data:%s\n", data);
		#endif
		memset(cmd, 0, sizeof(cmd));
		memset(data, 0, sizeof(data));

		#if 1
		//�ر��ƶ�����
		strcpy(cmd, "AT+CIPSHUT\r"); //send data
		ret = lib_serial_send(sfd, cmd, strlen(cmd));
		#if READ_DATA
		ret = lib_serial_readn_select(sfd, &data, sizeof(data), READ_SLEEP + 100);
		printf("read data:%s\n", data);
		#endif
		#endif
	#endif
		lib_end_runtime_printf();
	
		lib_sleep(2);
		printf("-------------------------------------\n");
	}

		
	return 0;
}
