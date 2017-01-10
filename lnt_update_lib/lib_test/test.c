#include <stdio.h>
#include "lib_reader_update.h"
#include <pthread.h>


//Ҫ�����Ķ������̼��ļ�
#if 1
#define	FIRMWARE "/mnt/mount/lnt_update_lib/firmware/LNT_ZM_V1.1_20160219.lfd"
#else 
#define	FIRMWARE "/mnt/mount/lnt_update_lib/firmware/LNT_ZM_V1.1_20151127.lfd"
#endif


void *run(void *arg)
{	
	int ret = -1;	
	int fd = *(int *)arg;

	//printf("haha--------------\n");
	while(1)
	{	
		#if 0
		ret = lib_get_update_status();
		printf("lib_get_update_status, ret:%d\n", ret);
		if(ret == READER_UPDATE_ING)
		{
			printf("reader updating......\n");
			return (void *)(-1);
		}
		lib_sleep(1);
		#endif
		
		ret = lnt_reader_update(fd, FIRMWARE);	
		if(ret >= 1)
			break;
	}

	pthread_exit((void *)0);
	return (void *)ret;
}

int main(int argc,char *argv[])
{	
	int ret = -1, fd = -1;	
	char *version;	
	time_t begin_times, end_times;
	unsigned int consume_time = 0;//������ʱ

	time(&begin_times);

	version = lib_update_version();	
	fprintf(stderr,"\nsoftware version:%s\n",version);		

#if 1
	fd = lnt_init();//����ͨģ���ʼ��(�ϵ� ���ڳ�ʼ�� ��ȡ����汾)
	if(fd < 0){
		fprintf(stderr,"lnt_init failed!\n");
		return fd;
	}
#endif
#if 1
	pthread_t tid;
	ret = pthread_create(&tid, NULL, run, &fd);
	printf("pthread_create ret:%d\n",ret);
	lib_sleep(40);
#else
	ret = lnt_reader_update(fd, FIRMWARE);		
#if 1
	if(ret == LIB_UPDATE_OK){		
		fprintf(stderr,"\t��ϲ��,�̼������ɹ���!\n");	
	}else{		
		fprintf(stderr,"\t��Ǹ,�̼�����ʧ����!\n");	
	}	
#endif
#endif
	time(&end_times);
	consume_time = end_times - begin_times;
	printf("Update takes %d seconds.\n",consume_time);//������ʱ

#if 0
	ret = lib_get_update_status();
	printf("----------ret:%d\n", ret);
#endif

	return ret;
}


