#ifndef __LIB_READER_UPDATE_H__
#define __LIB_READER_UPDATE_H__


/*@*/
#ifdef __cplusplus
extern "C" {
#endif
/*@*/


#define LIB_UPDATE_OK			1	//�����ɹ�
#define LIB_UPDATE_ERR   		2	//����ʧ��

enum UPDATE_STATUS {
	READER_UPDATE_ING = 1,	//��������
	READER_UPDATE_SUCCESS,	//�����ɹ�
	READER_UPDATE_FAILED,	//����ʧ��
};


/*��ȡ����汾��*/
char *lib_update_version(void);
/*�����ӿ�*/
int lnt_reader_update(int fd, char *firmware_path);

/*��ȡ����������״̬*/
enum UPDATE_STATUS lib_get_update_status(void);


/*@*/
#ifdef __cplusplus
}
#endif
#endif

