#include <stdio.h>
#include <assert.h>
#include "lib_general.h"
#include "escape.h"
#include <time.h> 
#include "common.h"

//���ؾ������������
#if 1
	#define SER_IP   	"120.24.97.95"
	#define SER_PORT 	20000 
#else
	#define SER_IP   	"180.76.140.185"
	#define SER_PORT 	20001
#endif

//ͨѶ������
#define COM_IP   	"121.8.152.2"
#define COM_PORT 	10020

int make_package(unsigned char *tbuf, const unsigned char can_addr, const unsigned char ctrl_bit, const unsigned char cmd);

load_balance_ack_t ack;

int main(int argc,char *argv[])
{
	int ret = -1,sfd = -1;
	unsigned char rxbuf[512] = {0},txbuf[512] = {0},buf[512] = {0};
	
	printf("######### compile time:%s,%s #########\n",__DATE__,__TIME__);
	
#if 1
	//�������ͨѶ��
	sfd = lib_udp_client_nonb_new();
	printf("new udp,sfd = %d\n",sfd);
	if(sfd <= 0){
		fprintf(stderr,"new udp failed!\n");
		goto exit;
	}

	//����
	ret = package_make(txbuf,0x00,0x02,0xA4);//��ͨ������֡
	printf("package_make,ret = %d\n",ret);
	lib_printf_v2("txbuf",(unsigned char *)txbuf,ret,16);
	
	ret = lib_udp_sendto_select(sfd,SER_IP,SER_PORT,txbuf,ret,500);
	printf("send,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"send failed!\n");
		goto err1;
	}

	//����
	ret = lib_udp_recvfrom_select(sfd,SER_IP,SER_PORT,rxbuf,128,500);
	printf("recv,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"recv failed!\n");
		goto err1;
	}
	lib_printf_v2("-------------recv-------------",(unsigned char *)&rxbuf,ret,16);

	ret = __downlink_escape(&buf,(unsigned char *)&rxbuf,ret);
	lib_printf_v2("-------------__downlink_escape-------------",(unsigned char *)&buf,ret,16);

	ret = lib_b64_decode_hex(&rxbuf,&buf[11],36);
	lib_printf_v2("-------------b64_decode-------------",(unsigned char *)&rxbuf,ret,16);

	lib_printf_v2("-------------encry_key-------------",(unsigned char *)&rxbuf[11],16,16);
	memcpy(&ack.encry_key,&rxbuf[11],16);
 #if 1
	//ʮ���ƴ�ӡ
	printf("\n");
	int i;
	for(i = 5; i < 9; i++){
		printf("%d.",rxbuf[i]);
	}
	unsigned short port,port1;
	memcpy(&port,&rxbuf[9],2);
	port1 = htons(port);
	printf(":%d\n",port1);
	
 #endif
err1:
	lib_udp_close(sfd);
#endif

#if 1
	//�ڵ��������ͨ��
	sfd = lib_tcp_client_nonb_new(COM_IP,COM_PORT,1);
	printf("tcp_client_new,sfd = %d\n",sfd);
	if(sfd <= 0){
		fprintf(stderr,"new tcp failed!\n");
		goto exit;
	}
 #if 0	
	//�ڵ��ǩ��
	unsigned char key[16] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,0x32,0x33,0x34,0x35,0x36};
	memcpy(&ack.encry_key,&key,16);

	ret = make_package(txbuf,0x00,0x02,0xA1);//��ͨ������֡
	lib_printf_v2("--------------txbuf-------------",(unsigned char *)txbuf,ret,16);
	
	ret = lib_tcp_writen(sfd,txbuf,ret);
	printf("send,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"send failed!\n");
		goto err;
	}

	ret = lib_tcp_readn_select(sfd,rxbuf,512,5000);
	printf("recv,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"recv failed!\n");
		goto err;
	}
	lib_printf_v2("-------------recv-------------",(unsigned char *)&rxbuf,ret,16);

	ret = __downlink_escape(&buf,(unsigned char *)&rxbuf,ret);
	lib_printf_v2("-------------__downlink_escape-------------",(unsigned char *)&buf,ret,16);

	ret = lib_b64_decode_hex(&rxbuf,&buf[11],12);
	lib_printf_v2("-------------b64_decode-------------",(unsigned char *)&rxbuf,ret,16);

 #endif
 #if 0
	//��������
	memset(&txbuf,0,512);
	memset(&rxbuf,0,512);

	ret = package_make(&txbuf,0x00,0x02,0xa1);
	lib_printf_v2("--------------txbuf-------------",(unsigned char *)txbuf,ret,16);
	
	ret = lib_tcp_writen(sfd,txbuf,ret);
	printf("send,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"send failed!\n");
		goto err;
	}

	ret = lib_tcp_readn_select(sfd,rxbuf,512,5000);
	printf("recv,ret = %d\n",ret);
	if(ret <= 0){
		fprintf(stderr,"recv failed!\n");
		goto err;
	}
	lib_printf_v2("-------------recv-------------",(unsigned char *)&rxbuf,ret,16);

	ret = __downlink_escape(&buf,(unsigned char *)&rxbuf,ret);
	lib_printf_v2("-------------__downlink_escape-------------",(unsigned char *)&buf,ret,16);

	ret = lib_b64_decode_hex(&rxbuf,&buf[11],12);
	//printf("b64_decode,ret = %d\n",ret);
	lib_printf_v2("-------------b64_decode-------------",(unsigned char *)&rxbuf,ret,16);
 #endif
err:
	ret = lib_tcp_disconnect(sfd);
#endif
exit:
	return 0;
}


int make_package(unsigned char *tbuf, const unsigned char can_addr, const unsigned char ctrl_bit, const unsigned char cmd)
{
	assert(tbuf);

	int ret = 0, len = 0;
	unsigned short crc16, node_num = htons(0xAAAD),data_len;
	unsigned char data[512] = {0}, buf[512] = {0}, txbuf[512] = {0};

	dev_register_req_t req;

	lib_get_macaddr("eth1",&req.mac_addr);
	lib_printf_v2("-----------mac_addr-------------", (unsigned char *)&req.mac_addr, 6, 16);

	memcpy(&req.encry_key,&ack.encry_key,16);
	memcpy(&buf,&req,sizeof(req));
	
	lib_printf_v2("-----------data-------------", (unsigned char *)&buf, sizeof(req), 16);

	ret = lib_b64_encode_hex(txbuf,buf,sizeof(req));//base64����
	
	data_len = htons(ret + 2 + 1);
		
	data[len++] = FRAME_HEAD;//֡ͷ
	data[len++] = 0x02;//��ˮ��,0~255
	memcpy(&data[len],&node_num,2);//�ڵ�����
	len += 2;
	
	data[len++] = can_addr;//�豸��ַ
	data[len++] = ctrl_bit;//����λ
	data[len++] = cmd;//���������

	memcpy(&data[len],&data_len,2);//���ݳ���
	len += 2;

	data[len++] = 0x41;//������A
	data[len++] = 0x4e;//������N
	
	memcpy(&data[len],&txbuf,ret);//������
	len += ret;

	data[len++] = 0x26;//"&",����base64����!
	
	crc16 = htons((unsigned short)lib_crc16_with_byte(&data[1],len-1));//У��
	memcpy(&data[len],&crc16,2);
	len += 2;
	
	data[len++] = FRAME_TAIL;//֡β

	ret = __uplink_escape(tbuf,data,len);//ת��

	fprintf(stderr,"packet len:%d\n",ret);
	lib_printf_v2("-----------PACKAGE-------------", (unsigned char *)data, len, 16);

	return ret;
}






