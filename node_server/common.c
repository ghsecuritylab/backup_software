
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "lib_general.h"


int package_make(unsigned char *tbuf, const unsigned char can_addr, const unsigned char ctrl_bit, const unsigned char cmd)
{
	assert(tbuf);

	int ret = 0, len = 0;
	unsigned char data[128] = {0};
	unsigned short crc16; 
	unsigned short node_num = htons(0xAAAD),data_len;

	//unsigned char buf[3] = {0x0,0x0,0x0a};//׮��������
	unsigned char buf[DATA_LEN] = {0x54,0x4A,0x16,0xC9,0xF1,0x3A, 0xAA,0xAD, 0x00,0x01, 0x00,0x01};//my
	unsigned char txbuf[512] = {0};

	//ret = lib_b64_encode_hex(txbuf,buf,3);//base64����
	ret = lib_b64_encode_hex(txbuf,buf,DATA_LEN);//base64����
	//printf("--------->ret = %d\n",ret);
	
	data_len = htons(ret + 2);//���Ǿ��⸺������Ļ���Ҫ��+1
		
	data[len++] = FRAME_HEAD;//֡ͷ
	data[len++] = 0x02;//��ˮ��,0~255
	memcpy(&data[len],&node_num,2);//�ڵ�����
	len += 2;
	
	data[len++] = can_addr;//�豸��ַ
	data[len++] = ctrl_bit;//����λ
	data[len++] = cmd;//���������

	memcpy(&data[len],&data_len,2);//���ݳ���
	len += 2;

	data[len++] = 0x44;//0x61;//������D
	data[len++] = 0x50;//0x69;//������P
	
	memcpy(&data[len],&txbuf,ret);//������
	len += ret;

	//data[len++] = 0x26;//& //�����⸺�����벻��Ҫ &

	crc16 = htons((unsigned short)lib_crc16_with_byte(&data[1],len-1));//У��
	memcpy(&data[len],&crc16,2);
	len += 2;
	
	data[len++] = FRAME_TAIL;//֡β

	ret = __uplink_escape(tbuf,data,len);//ת��

	//fprintf(stderr,"packet len:%d\n",ret);
	lib_printf_v2("-----------PACKAGE-------------", data, len, 16);

	return ret;
}


int data_frame_init(data_frame_t *data)
{
	data->head = 0xf1;
	data->serial_num = 0x01;
	data->term_code = htons(0xaaad);
	data->dev_addr = 0x00;
	data->ctrl_bit = 0x02;
	data->tail = 0xf2;
	
	return 0;
}


