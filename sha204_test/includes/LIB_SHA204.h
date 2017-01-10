#ifndef __LIB_SHA204_H__
#define __LIB_SHA204_H__


/*@*/
#ifdef __cplusplus
extern "C" {
#endif
/*@*/


#define LIB_WAKE_UP_SUCCESS 0

#define LIB_EV_OK			1	//��֤ͨ��
#define LIB_EV_ERR   		2	//��֤ʧ��


/*��ȡ����汾��*/
char *LIB_EV_Version(void);
/*��֤�ӿ�*/
int LIB_Encry_Verify(void);
/*��ȡ�ڵ���豸��Ϣ*/
int read_device_info(unsigned char *device_info);


/*@*/
#ifdef __cplusplus
}
#endif
#endif

