#ifndef __LNT_H__
#define __LNT_H__

#include <arpa/inet.h>

#define LNT_NULL				(NULL) 
#define LNT_EOK					(0)  //����
#define LNT_ERROR				(-1) //����
#define LNT_ETIMEOUT			(-2) //��ʱ
#define LNT_EFULL				(-3) //��
#define LNT_EEMPTY				(-4) //��
#define LNT_ENOMEM 				(-5) //�ڴ治��
#define LNT_EXCMEM				(-6) //�ڴ�Խ��
#define LNT_EBUSY				(-7) //æ
#define LNT_NOT_SUPPORT			(-8) //��֧�ָ�ָ��

#define LNT_TRUE				(1)
#define LNT_FALSE				(0)

#define LNT_CHAR_MAX			0xff
#define LNT_SHORT_MAX			0xffff
#define LNT_INT_MAX				0xffffffff

#define LNT_NTOHS(n)				ntohs(n)	
#define LNT_HTONS(n)				htons(n)
#define LNT_NTOHL(n)				ntohl(n)
#define LNT_HTONL(n)				htonl(n)



/* ��־���� */
//#define LNT_LOG_RUN

#ifdef LNT_LOG_RUN
#include <syslog.h>
#define SYS_LOG_EMERG(fmt, args...) 		syslog(LOG_EMERG, fmt, ##args)
#define SYS_LOG_ALERT(fmt, args...) 			syslog(LOG_ALERT, fmt, ##args)
#define SYS_LOG_CRIT(fmt, args...) 			syslog(LOG_CRIT, fmt, ##args)
#define SYS_LOG_ERR(fmt, args...) 			syslog(LOG_ERR, fmt, ##args)
#define SYS_LOG_WARNING(fmt, args...) 		syslog(LOG_WARNING, fmt, ##args) 
#define SYS_LOG_NOTICE(fmt, args...)  		syslog(LOG_NOTICE, fmt, ##args)
#define SYS_LOG_INFO(fmt, args...) 			syslog(LOG_INFO, fmt, ##args)
#define SYS_LOG_DEBUG(fmt, args...) 		syslog(LOG_DEBUG, fmt, ##args)
#else
#define SYS_LOG_EMERG(fmt, args...) 		fprintf(stderr, fmt, ##args)
#define SYS_LOG_ALERT(fmt, args...) 			fprintf(stderr, fmt, ##args)
#define SYS_LOG_CRIT(fmt, args...) 			fprintf(stderr, fmt, ##args)
#define SYS_LOG_ERR(fmt, args...) 			fprintf(stderr, fmt, ##args)
#define SYS_LOG_WARNING(fmt, args...) 		fprintf(stderr, fmt, ##args)
#define SYS_LOG_NOTICE(fmt, args...) 		fprintf(stderr, fmt, ##args)
#define SYS_LOG_INFO(fmt, args...) 			fprintf(stderr, fmt, ##args)
#define SYS_LOG_DEBUG(fmt, args...) 		fprintf(stderr, fmt, ##args)
#endif


/*
* ����ͨģ�������
*/
#define LNT_MOC_ERROR_NORMAL					0x00  //��������
#define LNT_MOC_ERROR_SAM_EMPTY				0x60 //û�а�װSAM��
#define LNT_MOC_ERROR_INIT						0x61 //SAM����ʼ�������δ��ʼ��
#define LNT_MOC_ERROR_PIN						0x62 //SAM������PIN����
#define LNT_MOC_ERROR_READ						0x65 //SAM��������
#define LNT_MOC_ERROR_WRITE					0x66 //SAM��д����
#define LNT_MOC_ERROR_CARD_NOTAG				0x80  //û�п�
#define LNT_MOC_ERROR_CARD_AUTH				0x83  //��֤��Ƭ����
#define LNT_MOC_ERROR_CARD_OP_FAIL			0x89  //��Ƭ����ʧ��
#define LNT_MOC_ERROR_CARD_UNKOWN			0x90  //������ͨ��
#define LNT_MOC_ERROR_CARD_OUTOFDATE			0x91  //��Ƭ������Ч��
#define LNT_MOC_ERROR_CARD_NAMELIST			0x94   //������
#define LNT_MOC_ERROR_CARD_OWEPTY			0x95   //Ǯ����
#define LNT_MOC_ERROR_CARD_OVERLIMIT			0x96   //Ǯ����������
#define LNT_MOC_ERROR_CARD_PURSE_UNUSED		0x97   //Ǯ��δ����
#define LNT_MOC_ERROR_TS_PENDING				0xB0   //���ײ�����;�ж�
#define LNT_MOC_ERROR_LASTTIME_TRADE_FAIL		0xD4   //�ϴν���δ�ɹ�
#define LNT_MOC_ERROR_INVALID_PARAM			0xE3	   //��������


#define LNT_MOC_ERROR_LILIN_NOT_CPU_CARD		0xFE	   //��CPU��

/*
 * �豸��Ӧ״̬��
 */
#define LNT_SW_ERROR_NORMAL					0x9000 //�ɹ�ִ��,�޴���
#define LNT_SW_ERROR_LENGTH					0x6700 //���Ȳ���
#define LNT_SW_ERROR_INS						0x6D00 //INS����
#define LNT_SW_ERROR_CLA						0x6E00 //CLA����
#define LNT_SW_ERROR_DATA						0x6F00 //������Ч
#define LNT_SW_ERROR_AUTH						0x6300 //��֤ʧ��


/******************************************************************
*						����ͨ�������̼�����
********************************************************************/

/*
* ����״̬����
*/
struct update_stat_set{
	unsigned char mode;//ģʽ
	unsigned short total_packets;//�����ݰ���,��"ģʽ"Ϊ0x02���޴���
}__attribute__((packed));
typedef struct update_stat_set update_stat_set_t;

/*
* Ԥ������Ӧ
*/
struct pre_update_ack{
	unsigned int next_position;
}__attribute__((packed));
typedef struct pre_update_ack pre_update_ack_t;

/*
* ������Ӧ
*/
struct update_ack{
	unsigned char retcode[5];
}__attribute__((packed));
typedef struct update_ack update_ack_t;







/******************************************************************
*						����ͨ������ָ��
********************************************************************/
/*
* ����ͨ������ָ��--���ݹ������г�
*/
#define LNT_GETVERSION				0x60 	//��ȡ����汾
#define LNT_CORE_INIT				0xD2		//����ģ���ʼ��
#define LNT_QRY_TICKET_INFO			0xD3        //��ѯ����Ϣ
#define LNT_QRY_RENT_INFO			0xD9         //��ѯ�⻹��Ϣ
#define LNT_SET_RENT_INFO			0xDA		//�����⻹��Ϣ
#define LNT_CONSUME					0xD4         //����
#define LNT_SET_BL_FLAG				0xD5         //����������
#define LNT_GET_HIS_RECORD			0xD6         //�����ʷ���׼�¼
#define LNT_SET_PARAM				0xD7         //��������
#define LNT_GET_TRANS				0xD8         //��ȡ���׼�¼

#define LNT_DEPOSIT_INIT			0xE3         //Ѻ���ʼ��
#define LNT_DEPOSIT_PROCESS			0xE4        //Ѻ����


/*
 * ����ͨ����ģ���ֵЭ��
 */
#define LNT_R_CMD					0xFF//0x40
#define LNT_R_CLA					0xBB
#define LNT_R_INIT_INS				0x10
#define LNT_R_AC_LOGIN_1_INS		0xC8




/*
 * Ѻ���־
 */
struct deposit_sign
{
	unsigned char rfu1:2;
	unsigned char type:2;
	unsigned char foshan:1;
	unsigned char guangzhou:1;
	unsigned char rfu2:2;
}__attribute__((packed));
typedef struct deposit_sign deposit_sign_t;


/*
 * Ʊ����Ϣ����˵��
 */
struct ticket_info
{
	unsigned int blance;         	//���
	unsigned char pid[8];			//������(��M1��ǰ��4��0)
	unsigned char lid[8];           //�߼�����
	unsigned short ttype;			//��Ƭ����
	unsigned char ctim[4];			//��ֵʱ��(YYYYMMDD)
	unsigned char pursetype;		//Ǯ������(0x01:M1Ǯ��, 0x02:CPUǮ��)
	unsigned char areaid;			//�������
	unsigned char areacardtype[2];	//���򿨴���
	unsigned char areacarddate[4];	//����������Ч��
	unsigned char dflag;			//���ݷ�ɽѺ���־
	unsigned char dflagother[4];	//���������Ѻ���־
	unsigned short pcode;			//��Ӫ�̱���
	unsigned char pmflag;			//��Ӫ�̻�Ա��־
}__attribute__((packed));
typedef struct ticket_info ticket_info_t;

/*
 * ���׼�¼
 */
struct trade_record
{
	unsigned char rectype; 			//��¼����
	unsigned char areaid;			//��Ƭ�������
	unsigned char ctype[2];			//������
	unsigned char areacardtype[2];	//��������
	unsigned int opid:24;			//����Ա����,3�ֽ�
	unsigned char curtransdevid[6];	//���ν����豸���
	unsigned int offlinetranssn; 		////�ѻ�������ˮ
	unsigned char curtransdtime[7];	//���ν�������ʱ��
	unsigned char lid[8];               		//�߼�����
	unsigned char pid[8];			//������(��M1��ǰ��4��0)
	unsigned int amount;			//���׽��
	unsigned int priceofticket;		//Ʊ��
	unsigned int blance;         		//���׺������
	unsigned char ttype;	      		//��������
	unsigned char addittype;		//���ӽ�������
	unsigned short rechargettimes;	//��ֵ���״���
	unsigned short consumettimes;      //���ѽ��״���
	unsigned char lasttdevid[6];		//�ϴν����豸���
	unsigned char lasttdtime[7];		//�ϴν�������ʱ��
	unsigned int authcode;			//������֤��
	unsigned char rfu[13];			//����
}__attribute__((packed));
typedef struct trade_record trade_record_t;

/*
 * ��������¼
 */
struct blacklist_record
{
	unsigned char pid[8];			//������
	unsigned char lid[8];			//�߼�����
}__attribute__((packed));
typedef struct blacklist_record blacklist_record_t;

/*
 * M1��ʷ��¼
 */
struct m1_history_record
{
	unsigned short spid;          //�����̴���
	unsigned char ttype;	      //��������
	unsigned int amount:24;     //���׽��(��λ��ǰ)
	unsigned char samid[4]; 	      //SAM����
	unsigned char dtime[6];        //����ʱ��(YYMMDDHHMMSS)
}__attribute__((packed));
typedef struct m1_history_record m1_history_record_t; 

/*
 * CPU��ʷ��¼
 */
struct cpu_history_record
{
	unsigned short spid;          //�������(��λ��ǰ)
	unsigned int ovd:24; 	    //͸֧�޶�(��λ��ǰ
	unsigned int amount;    		//���׽��(��λ��ǰ)
	unsigned char ttype;	      //��������
	unsigned char tid[6];	      //�ն˻����
	unsigned char date[4]; 	      //��������(XXMMDD)
	unsigned char time[3];        //����ʱ��(HHMMSS)
}__attribute__((packed));
typedef struct cpu_history_record cpu_history_record_t; 

/*
 * �⻹����Ϣ
 */
struct rent_info
{
	unsigned char app_locker;       //Ӧ��������־
	unsigned short provider;		//����Ӫ�˴���
	unsigned char version_no:4;		//�汾���--��4λ
	unsigned char rent_flag:4;		//�⻹����־--��4λ
	unsigned char member_level:4;	//��Ա����--��4λ
	unsigned char member_type:4;	//��Ա����--��4λ
	unsigned char ticket_type;		//Ʊ�ֱ��
	unsigned short accum;			//����/����/����
	unsigned short cur_accum;		//�������Ѵ���/����/����
	unsigned short cur_deal_sn;		//���ν�����ˮ
	unsigned char start_time[3];		//����ʱ��   			YYMMDD
	unsigned char  cur_deal_date[5];	//���ν�������ʱ��   YYMMDDHHMM
	unsigned char site_no[6]; 		//վ����
	unsigned char lock_no[4];		//��׮���
	unsigned char bike_no[4];		//���г����
	unsigned short accu_time_of_day; //�����ۼ�ʱ��
}__attribute__((packed));
typedef struct rent_info rent_info_t;

 

/*
* ��ȡ����汾
*/
struct lnt_getversion_ack
{
	unsigned char version[32]; 		//ASCII
}__attribute__((packed));
typedef struct lnt_getversion_ack lnt_getversion_ack_t;

/*
 * ����ģ���ʼ��
 */
struct lnt_core_init_req
{
	unsigned char spno[2];//�����̴���
}__attribute__((packed));
typedef struct lnt_core_init_req lnt_core_init_req_t;

struct lnt_core_init_ack
{
	unsigned char psam[4];//PSAM����
}__attribute__((packed));
typedef struct lnt_core_init_ack lnt_core_init_ack_t;

/*
 * ��ѯƱ����Ϣ
 */
 struct lnt_qry_ticket_info_ack
{
	unsigned char length;
	struct ticket_info ticket;
}__attribute__((packed));
typedef  struct lnt_qry_ticket_info_ack lnt_qry_ticket_info_ack_t;

/*
 * ��ѯ�⻹����Ϣ
 */
struct lnt_rent_info_req
{
	unsigned char id;//����Ӧ�����ͱ�ʶ��
}__attribute__((packed));
typedef struct lnt_rent_info_req lnt_rent_info_req_t;

struct lnt_rent_info_ack
{
	unsigned char length;
	struct rent_info rent;
}__attribute__((packed));
typedef struct lnt_rent_info_ack lnt_rent_info_ack_t;

struct lnt_rent_info
{
	unsigned char id;
	unsigned char length;
	struct rent_info rent;
}__attribute__((packed));
typedef struct lnt_rent_info lnt_rent_info_t;


/*
 * ����
 */
#define LNT_ATY_RENT		0x11		//�⳵
#define LNT_ATY_RETURN		0x17		//����
struct lnt_consume_req
{
	unsigned int amount;		//���׽��(��λ��ǰ)
	unsigned int fee;			//Ӧ�ս��(��λ��ǰ)
	unsigned char time[6];		//YYMMDDHHMMSS
	unsigned char phyiscalid[8];	//������
	unsigned char aty;			//���ӽ�������
}__attribute__((packed));
typedef struct lnt_consume_req lnt_consume_req_t;

/*
 * ��������
 */
struct lnt_parameter_set_req
{
	unsigned char conpa;//���ѳ�ʼ����
	unsigned char cvad;//��������Ч������
}__attribute__((packed));
typedef struct lnt_parameter_set_req lnt_parameter_set_req_t;

/*
 * ����������
 */
struct lnt_blacklist_record_ack
{
	struct blacklist_record blacklist;
}__attribute__((packed));
typedef struct lnt_blacklist_record_ack lnt_blacklist_record_ack_t;

/*
 * �����ʷ���׼�¼
 */
struct lnt_history_record_ack
{
	unsigned char ticket_type;
	union{
		struct m1_history_record m1_his;
		struct cpu_history_record cpu_his;
	}s_un;
}__attribute__((packed));
typedef struct lnt_history_record_ack lnt_history_record_ack_t;


/*
 * ��ȡ��������
 */
struct lnt_trade_record_ack
{
	struct trade_record record;
}__attribute__((packed));
typedef struct lnt_trade_record_ack lnt_trade_record_ack_t;



/*
 * *******************  ����ͨ����ģ���ֵЭ�� *************************
 */
/*
 * R_INIT(������ʼ��)
 */
struct lnt_r_init_ack
{
	unsigned char pki[4];   	 //PKI������
	unsigned char fw_ver[8];  //�������̼��汾
	unsigned short sw;    	 //״̬��
}__attribute__((packed));
typedef struct lnt_r_init_ack lnt_r_init_ack_t;

/*
 * R_AC_LOGIN_1(ǩ������1)
 */
struct lnt_r_ac_login_1_ack
{
	unsigned char login1_data[8+128+2];//+2
}__attribute__((packed));
typedef struct lnt_r_ac_login_1_ack lnt_r_ac_login_1_ack_t;

/*
 * R_AC_LOGIN_2(ǩ������2)
 */
struct lnt_r_ac_login_2_req
{
	unsigned char login2_data[8+128+5];//+5
}__attribute__((packed));
typedef struct lnt_r_ac_login_2_req lnt_r_ac_login_2_req_t;

struct lnt_r_ac_login_2_ack
{
	unsigned char rfu[46];
	unsigned char login1_data[8+128+2];//+2
}__attribute__((packed));
typedef struct lnt_r_ac_login_2_ack lnt_r_ac_login_2_ack_t;

/*
 * R_PUB_QRY_HIS(��ѯ��������Ϣ)
 */ 
struct card_status_16bytes 
{
	unsigned short spid;          //�����̴���
	unsigned char ttype;	      //��������			//0x17:��ͨ����,0x14:��ֵ,0x13:��������
	unsigned int amount:24;     //���׽��(��λ��ǰ)
	unsigned char samid[4]; 	      //SAM����
	unsigned char dtime[6];        //����ʱ��(YYMMDDHHMMSS)
}__attribute__((packed));

struct card_status_18bytes 
{
	unsigned int amount;    		//���׽��(��λ��ǰ)
	unsigned char ttype_ident;  //�������ͱ�ʶ
	unsigned char tid[6];	      //�ն˻����
	unsigned char rfu[2];	      //����
	unsigned char date[4]; 	      //��������(XXMMDD)
	unsigned char ttype;	      //��������     //0x17:��ͨ����,0x14:��ֵ,0x13:��������
}__attribute__((packed));

struct lnt_r_pub_qry_his_ack
{
	unsigned char sak;
	unsigned char card_status;
	union{
		struct card_status_16bytes b16;
		struct card_status_18bytes b18;
	}s_un;
}__attribute__((packed));
typedef struct lnt_r_pub_qry_his_ack lnt_r_pub_qry_his_ack_t;

/*
 * R_PUB_QRY_PHYSICS_INFO(��ѯ��������Ϣ)
 */
struct lnt_r_pub_qry_physics_info_NoEncry_ack  //������
{
	unsigned char data[51];
	unsigned short sw;
}__attribute__((packed));
typedef struct lnt_r_pub_qry_physics_info_NoEncry_ack lnt_r_pub_qry_physics_info_NoEncry_ack_t;

struct lnt_r_pub_qry_physics_info_Encry_ack  //����
{
	unsigned char data[80];
	unsigned short sw;
}__attribute__((packed));
typedef struct lnt_r_pub_qry_physics_info_Encry_ack lnt_r_pub_qry_physics_info_Encry_ack_t;

/*
 * R_PUB_SET_READCRADINFO(���ö�����+����Ϣ)
 */
 struct lnt_r_pub_set_readcardinfo_req
{
	unsigned char data[8+72+5];
}__attribute__((packed));
typedef  struct lnt_r_pub_set_readcardinfo_req lnt_r_pub_set_readcardinfo_req_t;

 struct lnt_r_pub_set_readcardinfo_ack
{
	unsigned char data[72];   //�������͵�Ʊ�����ز�ͬ
	unsigned short sw;
}__attribute__((packed));
typedef  struct lnt_r_pub_set_readcardinfo_ack lnt_r_pub_set_readcardinfo_ack_t;

///////////////////////////////////////////////////////
/*
 * R_CPU_LOAD_INIT(CPUǮ��Ȧ���ʼ��)
 */
struct lnt_r_cpu_load_init_req
{
	unsigned char data[93];///
}__attribute__((packed));
typedef  struct lnt_r_cpu_load_init_req lnt_r_cpu_load_init_req_t;

struct lnt_r_cpu_load_init_ack
{
	unsigned char data[104];
	unsigned short sw;
}__attribute__((packed));
typedef  struct lnt_r_cpu_load_init_ack lnt_r_cpu_load_init_ack_t;


/*
 * R_CPU_LOAD(CPU Ǯ��Ȧ��)
 */
struct lnt_r_cpu_load_req
{
	unsigned char data[61];///
}__attribute__((packed));
typedef  struct lnt_r_cpu_load_req lnt_r_cpu_load_req_t;

struct lnt_r_cpu_load_ack
{
	unsigned char data[80];
	unsigned short sw;
}__attribute__((packed));
typedef  struct lnt_r_cpu_load_ack lnt_r_cpu_load_ack_t;

/*
 * R_M1_LOAD(M1 ��ֵ)
 */
struct lnt_r_m1_load_req
{
	unsigned char data[128];///
}__attribute__((packed));
typedef  struct lnt_r_m1_load_req lnt_r_m1_load_req_t;

struct lnt_r_m1_load_ack
{
	unsigned char data[32];
	unsigned short sw;
}__attribute__((packed));
typedef  struct lnt_r_m1_load_ack lnt_r_m1_load_ack_t;

/*
 * R_M1_CPU_QRY(M1_CPU Ǯ����ѯ)
 */
struct lnt_r_m1_cpu_qry_req
{
	unsigned char data[128];///
}__attribute__((packed));
typedef  struct lnt_r_m1_cpu_qry_req lnt_r_m1_cpu_qry_req_t;

struct lnt_r_m1_cpu_qry_ack
{
	unsigned char data[128];///
}__attribute__((packed));
typedef  struct lnt_r_m1_cpu_qry_ack lnt_r_m1_cpu_qry_ack_t;

//////////////////////////////////////////////////////

/*
 * R_DEPOSIT_INIT(Ѻ���ʼ��)
 */
struct lnt_r_deposit_init_req
{
	unsigned char area;          //�������
	unsigned char dtype;         //Ѻ������
	unsigned char mark;  	  //����������־
	unsigned short code;       //��Ӫ�̱��� 
	unsigned char member;	   //��Ա
}__attribute__((packed));
typedef struct lnt_r_deposit_init_req lnt_r_deposit_init_req_t;

struct lnt_r_deposit_init_ack
{
	unsigned char data[176];
}__attribute__((packed));
typedef struct lnt_r_deposit_init_ack lnt_r_deposit_init_ack_t;

/*
 * R_DEPOSIT_PROCESS(Ѻ����)
 */
struct lnt_r_deposit_process_req
{
	unsigned char data[152];
}__attribute__((packed));
typedef struct lnt_r_deposit_process_req lnt_r_deposit_process_req_t;

struct lnt_r_deposit_process_ack
{
	unsigned char tmark;          		//�������ݱ�־
	unsigned char comp_tdata[87];    //���Ͻ�������
	unsigned short sw1sw2;        	//��Ƭ������
}__attribute__((packed));
typedef struct lnt_r_deposit_process_ack lnt_r_deposit_process_ack_t;



/******************************************************************
*						����ͨ����ָ��
********************************************************************/
/*
 * ǩ������ָ��
 */
#define LNT_REGISTER_STAGE1				0xDD01
#define LNT_REGISTER_STAGE2				0xDD02
#define LNT_REGISTER_STAGE3				0xDD03
#define LNT_REGISTER_STAGE4				0xDD04
#define LNT_REGISTER_STAGE5				0xDD05
#define LNT_REGISTER_STAGE6				0xDD06
#define LNT_REGISTER_STAGE7				0xDD07
#define LNT_REGISTER_STAGE8				0xDD08

//������ָ��
#define LNT_ON_OFF_CARD				    0xDD73

/*
 * ��ֵ����ָ��
 */
#define LNT_RECHARGE_STAGE1				0xDD11
#define LNT_RECHARGE_STAGE2				0xDD12
#define LNT_RECHARGE_STAGE3				0xDD13
#define LNT_RECHARGE_STAGE4				0xDD14
#define LNT_RECHARGE_STAGE5				0xDD15
#define LNT_RECHARGE_STAGE6				0xDD16
#define LNT_RECHARGE_STAGE7				0xDD17
#define LNT_RECHARGE_STAGE8				0xDD18
#define LNT_RECHARGE_STAGE9				0xDD19
#define LNT_RECHARGE_STAGE10			0xDD20
#define LNT_RECHARGE_STAGE11			0xDD21
#define LNT_RECHARGE_STAGE12			0xDD22




struct lnt_packet_head
{
	unsigned short head;
	unsigned char version;
	unsigned short length;
}__attribute__((packed));
typedef struct lnt_packet_head lnt_packet_head_t;


/*
 * ǩ���׶�1
 */
 struct lnt_packet_register_stage1_CTS
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];	  //PKI����
	unsigned char ilen;           //��Ϣ����
	unsigned char INFO[0];      //��Ϣ
	unsigned int crc32;         //У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage1_CTS lnt_packet_register_stage1_CTS_t;

/*
 * ǩ���׶�2
 */
 struct lnt_packet_register_stage2_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[5];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage2_STC lnt_packet_register_stage2_STC_t;

/*
 * ǩ���׶�3: R-INIT����
 */
 struct lnt_packet_register_stage3_CTS    
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];	  //PKI����
	unsigned char ilen;           //��Ϣ����
	unsigned char R_INIT[14];      //��Ϣ(R-INIT���ر���)
	unsigned int crc32;         //У����	
}__attribute__((packed));
typedef  struct lnt_packet_register_stage3_CTS lnt_packet_register_stage3_CTS_t;

/*
 * ǩ���׶�4
 */
 struct lnt_packet_register_stage4_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[5];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage4_STC lnt_packet_register_stage4_STC_t;


/*
 * ǩ���׶�5
 */
 struct lnt_packet_register_stage5
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[8+128+2];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage5 lnt_packet_register_stage5_t;

/*
 * ǩ���׶�6
 */
 struct lnt_packet_register_stage6
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char R_AC_LOGIN2[46+8+128+2];  	//��Ϣ(R_AC_Login2����)
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage6 lnt_packet_register_stage6_t;

/*
 * ǩ���׶�7
 */
 struct lnt_packet_register_stage7
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[46+8+128+2];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage7 lnt_packet_register_stage7_t;
  

/*
 * ǩ���׶�8
 */
 struct lnt_packet_register_stage8
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[0];   //��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_register_stage8 lnt_packet_register_stage8_t;

unsigned int lnt_crc32(unsigned char *buffer, unsigned int size);



/*
 * �����������׶�1
 */
struct lnt_open_close_card_stage1
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[176];    //��Ϣ
	unsigned int crc32;  	    //У����
}__attribute__((packed));
typedef  struct lnt_open_close_card_stage1 lnt_open_close_card_stage1_t;


/*
 * �����������׶�2
 */
 struct lnt_open_close_card_stage2
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;      //����ָʾ��
	unsigned char retcode;      //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char R_AC_LOGIN2[152];  
	unsigned int crc32;  	    //У����
}__attribute__((packed));
typedef  struct lnt_open_close_card_stage2 lnt_open_close_card_stage2_t;


/***************************��ֵ********************************/
/*
 * ��ֵ�׶�1
 */
struct recharge_info{
	unsigned char apply_type;//Ӧ������
	unsigned char recharge_amount[4];//��ֵ���
	unsigned char order_num[10];//������
}__attribute__((packed));
typedef struct recharge_info recharge_info_t;

struct lnt_packet_recharge_stage1_CTS
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];	  //PKI����
	unsigned char ilen;           //��Ϣ����
	struct recharge_info INFO;      //��Ϣ
	unsigned int crc32;         //У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage1_CTS lnt_packet_recharge_stage1_CTS_t;

/*
 * ��ֵ�׶�2
 */
struct lnt_packet_recharge_stage2_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[29];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage2_STC lnt_packet_recharge_stage2_STC_t;

/*
 * ��ֵ�׶�3 
 */
struct lnt_packet_recharge_stage3_CTS    
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];	  //PKI����
	unsigned char ilen;           //��Ϣ����
	//unsigned char INFO[80];      //51����80 //
	union info{
		unsigned char Encry_INFO[80+2];//����
		unsigned char NoEncry_INFO[51+2];//������
	}INFO;
	unsigned int crc32;         //У����	
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage3_CTS  lnt_packet_recharge_stage3_CTS_t;

/*
 * ��ֵ�׶�4
 */
 struct lnt_packet_recharge_stage4_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[8+72+5];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage4_STC lnt_packet_recharge_stage4_STC_t;


/*
 * ��ֵ�׶�5
 */
 struct lnt_packet_recharge_stage5_CTS 
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[72+2];  	//��Ϣ ///
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage5_CTS  lnt_packet_recharge_stage5_CTS_t;

/*
 * ��ֵ�׶�6
 */
 struct lnt_packet_recharge_stage6_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[93];  	/// 
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage6_STC lnt_packet_recharge_stage6_STC_t;

/*
 * ��ֵ�׶�7
 */
 struct lnt_packet_recharge_stage7_CTS 
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[104+2];   
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage7_CTS  lnt_packet_recharge_stage7_CTS_t;
  

/*
 * ��ֵ�׶�8
 */
 struct lnt_packet_recharge_stage8_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[61];   //��Ϣ///
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage8_STC lnt_packet_recharge_stage8_STC_t;


/*
 * ��ֵ�׶�9
 */
 struct lnt_packet_recharge_stage9_CTS
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[80+2];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage9_CTS lnt_packet_recharge_stage9_CTS_t;
  

/*
 * ��ֵ�׶�10
 */
 struct lnt_packet_recharge_stage10_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[128];   //��Ϣ///
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage10_STC lnt_packet_recharge_stage10_STC_t;

/*
 * ��ֵ�׶�11
 */
 struct lnt_packet_recharge_stage11_CTS
{
	unsigned char userid[16];   //�û�ID
	unsigned char appstep;	    //Ӧ�ò���
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	unsigned char INFO[0];  	//��Ϣ
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage11_CTS lnt_packet_recharge_stage11_CTS_t;
  

/*
 * ��ֵ�׶�12
 */
struct recharge_msg{
	unsigned char recharge_record_id[10];//��ֵ��¼ID
	unsigned char pki_num[4];//PKI ����
	unsigned char logic_num[8];//�߼�����
	unsigned char recharge_amount[4];//��ֵ���
	unsigned char balance[4];//���׺����
	
}__attribute__((packed));


struct lnt_packet_recharge_stage12_STC
{
	unsigned char userid[16];   //�û�ID
	unsigned char indcode;    //����ָʾ��
	unsigned char retcode;   //������Ϣ��
	unsigned char pki[4];    	//PKI����
	unsigned char ilen;     	//��Ϣ����
	//unsigned char INFO[30];   //��Ϣ///
	struct recharge_msg INFO;
	unsigned int crc32;  	//У����
}__attribute__((packed));
typedef  struct lnt_packet_recharge_stage12_STC lnt_packet_recharge_stage12_STC_t;

#endif


