#ifndef __LIB_RENT_RECORD_H__
#define __LIB_RENT_RECORD_H__


/*@*/
#ifdef __cplusplus
extern "C" {
#endif
/*@*/


struct rent_info_fmt		//���ü�¼��ʽ
{ 
	unsigned char bike_NO[32];		//���г����
	unsigned char rent_name[64];	//�⳵������
	unsigned char rent_time[32];	//�⳵ʱ��
	unsigned char return_name[64];	//����������
	unsigned char return_time[32];	//����ʱ��
	unsigned char used_time[16];	//����ʱ��
	unsigned char fee[16];			//�۷�
}__attribute__((packed));
typedef struct rent_info_fmt rent_info_fmt_t;



int ParseRentBikeRecord(char* buff,int len);




/*@*/
#ifdef __cplusplus
}
#endif

#endif/*#ifndef __LIB_RENT_RECORD_H__*/

