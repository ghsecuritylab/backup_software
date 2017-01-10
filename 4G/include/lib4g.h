#ifndef __LIB_4G_H__
#define __LIB_4G_H__

/*@*/
#ifdef __cplusplus
extern "C" {
#endif
/*@*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>


struct lib_4g_gga
{
	double latitude;  				//γ�ȣ���ʽΪ ddmm.mmmmm���ȷָ�ʽ��
	unsigned char ns_indicator;  		//γ�Ȱ���N �� S����γ����γ��
	double longitude; 				//���ȣ���ʽΪ dddmm.mmmmm���ȷָ�ʽ��
	unsigned char ew_indicator; 		//���Ȱ���E �� W��������������
	int status; 					// GPS ״̬��0=δ��λ��1=��λ 
	int satellite; 					//����ʹ�õ����ڶ�λ������������00~12�� 
};
typedef struct lib_4g_gga lib_4g_gga_t;


struct gps_attr
{
	unsigned char gga:1;
	unsigned char tm:1;
	unsigned char rfu:6;
}__attribute__((packed));
typedef struct gps_attr gps_attr_t;

enum ENUM_4G_CONNECT_STATUS
{
	ECM_4G_UNCONNECT = 0,  // δ��λ
	ECM_4G_CONNECT,	    // �ǲ�ֶ�λ
	ECM_4G_SERIAL_ERROR,			// ��ֶ�λ
};

enum CARD_TYPE
{
	CARD_CMCC = 1,  // �й��ƶ�
	CARD_CUCC,	    // �й���ͨ
	CARD_CTCC,		// �й�����
};

enum CARD_STATUS
{
	CARD_STATUS_READY = 1,  // ׼������
	CARD_STATUS_SIM_PIN,	    // �ȴ����ܣ����Ǽ�����
	CARD_STATUS_NO_INSERTED,		// û��
	CARD_STATUS_NO_INSERTED_AND_ERROR,		// û����Numerical Extended error result code is enabled.
};


typedef enum __bool { false = 0, true = 1, } bool;

int lib_4g_get_csq(int fd);
int lib_4g_ecm_disconnect(int fd);
int lib_4g_ecm_connect(int fd);
int lib_4g_ecm_connect_status(int fd);



int lib_4g_ate0(int fd);
int lib_4g_decode(int fd, char* key);			// ����4G��������ĳЩ����ʧ��
int lib_4g_restart(int fd);
int lib_4g_setECMforWindows_and_restart(int fd);
int lib_4g_setECMforLinux_and_restart(int fd);
int lib_4g_get_basic_info(int fd);
int lib_4g_CUCC_CTCC_dialing(int fd);
int lib_4g_CMCC_dialing(int fd);
int lib_4g_getGPS_init(int fd);
int lib_4g_get_gps_info(int fd, char *buf, int msec);
int lib_4g_analytic_zgpsr(char *rxbuf, struct tm *my_4g_tm, lib_4g_gga_t *my_4g_gga, gps_attr_t *attr);
int lib_4g_check_cpin(int fd);
int lib_4g_check_cops(int fd);
int lib_4g_zsnt(int fd);









int get_yday(int year,int mon,int day);
int leap(int y);
int monthday(int m, int team);
void gps_show_tm(struct tm *tm);
void gps_show_gga(struct lib_4g_gga *gga);
void printf_warning(char *buf);






/*@*/
#ifdef __cplusplus
}
#endif
#endif


