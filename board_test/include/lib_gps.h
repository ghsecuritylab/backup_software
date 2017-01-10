#ifndef __LIB_GPS_H__
#define __LIB_GPS_H__

/*
 * ͷ�ļ�
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#include "lib_general.h"

/*
 * ���������붨��
 */
#define GPS_NULL			(NULL) 
#define GPS_EOK				(0)  //����
#define GPS_ERROR			(-1) //����
#define GPS_ETIMEOUT		(-2) //��ʱ
#define GPS_EFULL			(-3) //��
#define GPS_EEMPTY			(-4) //��
#define GPS_ENOMEM 			(-5) //�ڴ治��
#define GPS_EXCMEM			(-6) //�ڴ�Խ��
#define GPS_EBUSY			(-7) //æ

#define GPS_TRUE			(1)
#define GPS_FALSE			(0)

#define uchar unsigned char


// struct
struct gps_zda{

	int  msec;
	int sec;     
	int min;     
	int hour;    
	short day;     
	short mon;     
	short year; 
}__attribute__((packed));

struct gps_tm {
	
	int tm_sec;       /* �� �C ȡֵ����Ϊ[0,59] */
	int tm_min;       /* �� - ȡֵ����Ϊ[0,59] */
	int tm_hour;      /* ʱ - ȡֵ����Ϊ[0,23] */
	int tm_mday;      /* һ�����е����� - ȡֵ����Ϊ[1,31] */
	int tm_mon;       /* �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] */
	int tm_year;      /* ��ݣ���ֵ����ʵ����ݼ�ȥ1900 */
	int tm_wday;      /* ���� �C ȡֵ����Ϊ[0,6]������0���������죬1��������һ���Դ����� */
	int tm_yday;      /* ��ÿ���1��1�տ�ʼ������ �C ȡֵ����Ϊ[0,365]������0����1��1�գ�1����1��2�գ��Դ����� */
}__attribute__((packed));


struct gps_gga{

	double latitude;
	unsigned char ns_indicator;
	double longitude;
	unsigned char ew_indicator;
}__attribute__((packed));

// function
/* ************ Init ************** */
int __gps_init(lib_serial_t *serial, char *DEV_NAME, int speed);
int __gps_resease(lib_serial_t *serial);


/* ************ CRC ************** */
int gps_nmea_crc(uchar *crcbuf, int size);
void gps_ubx_crc(uchar *retbuf,uchar *crcbuf, int size);

/* ************ Off_On ************** */
int gps_gga_off(int fd);
int gps_gga_on(int fd);
int gps_gll_off(int fd);
int gps_gll_on(int fd);
int gps_gsa_off(int fd);
int gps_gsa_on(int fd);
int gps_gsv_off(int fd);
int gps_gsv_on(int fd);
int gps_rmc_off(int fd);
int gps_rmc_on(int fd);
int gps_vtg_off(int fd);
int gps_vtg_on(int fd);
int gps_zda_off(int fd);
int gps_zda_off(int fd);


/* ************ Get ************** */
int gps_set_rate(int fd,int ms_rate);
int gps_split_info(char *rxbuf, char (*line)[512], int *times);
int gps_get_gga(char *rxbuf, struct gps_gga *gga);
int gps_get_tm(char *rxbuf, struct gps_tm *tm);
int gps_get_zda(char *rxbuf, struct gps_zda *zda);
void gps_show_zda(struct gps_zda *zda);
void gps_show_gga(struct gps_gga *gga);


/* ************ date ************** */
int get_yday(int year,int mon,int day);
int monthday(int m ,int team);
int leap(int y);



#endif
