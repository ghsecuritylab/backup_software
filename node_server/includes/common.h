
#ifndef __COMMON_H__
#define __COMMON_H__


#define 	FRAME_HEAD	0xf1
#define 	FRAME_TAIL	0xf2
#define 	DATA_LEN	(12)
#define 	DAT_LEN	(23)


typedef	 unsigned char uchar;
typedef  unsigned int uint;
typedef  unsigned short ushort;

struct dev_register_req{
	uchar mac_addr[6];
	uchar encry_key[16];
}__attribute((packed));
typedef struct dev_register_req dev_register_req_t;

struct dev_register_ack{
	uchar status;
	uchar server_time[7];
}__attribute((packed));
typedef struct dev_register_ack dev_register_ack_t;


//ͨ������֡�����ֶ���
#define	DEV_REGISTER		0xA1 //�豸ǩ��
#define	DEV_CTRL			0xA2 //�豸����
#define	FILE_SEND			0xA3 //���ļ�����
#define	LOAD_BALANCE_REQ 	0xA4 //���ؾ�������
#define	PASS_SEND			0xA5 //����͸�� 

struct load_balance_req{
	uchar mac_addr[6];	//mac��ַ
	ushort dev_code;	//�豸���
	ushort operator_code;//��Ӫ�̱���
	ushort dev_type;	//�豸����
}__attribute__((packed));
typedef struct load_balance_req load_balance_req_t;


struct load_balance_ack{
	uchar status;	//ִ��״̬
	uchar com_ip[8];//ͨѶ��ip
	ushort com_port;//ͨѶ���˿�
	uchar encry_key[16];//������Կ
}__attribute((packed));
typedef struct load_balance_ack load_balance_ack_t;

//
struct data_frame{
	uchar head;//֡ͷ
	uchar serial_num;//��ˮ��
	ushort term_code;//�ն˱��
	uchar dev_addr;//�豸��ַ
	uchar ctrl_bit;//����λ
	uchar cmd;//���������
	ushort data_len;//���ݳ���
	ushort guid_word;//������
	uchar data[128];
	ushort crc16;//У��
	uchar tail;//֡β
}__attribute((packed));
typedef struct data_frame data_frame_t;


//���ļ�ͷ
struct file_header{
	ushort fnum;//�ļ����
	ushort packet_sum;//�ָ�����
	ushort packet_num;//�ָ����
	uchar  ftype;//�ļ����
	uchar  feature[9];//��������
}__attribute((packed));
typedef struct file_header file_header_t;





int package_make(unsigned char *tbuf, const unsigned char can_addr, const unsigned char ctrl_bit, const unsigned char cmd);	
//int make_package(unsigned char *tbuf, const unsigned char can_addr, const unsigned char ctrl_bit, const unsigned char cmd);



#endif /*__COMMON_H__*/

