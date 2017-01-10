#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include "i2c_common.h"
#include "lib_general.h"
#include "sha204_command.h"

#if 0
#define CHIP			"/dev/i2c-3"    //i2c总线
#define CHIP_ADDR		0x64    		//i2c设备地址

#define LIB_EV_OK			1
#define LIB_EV_ERR   		2

#define EV_VER       "Encry Verify Version 1.0.1"
#endif




#if 0
int main(int argc,char *argv[])
{
	int ret = -1;
	unsigned char *version;

	version = LIB_EV_Version();
	printf("Software Version: %s\n",version);
	
	ret = LIB_Encry_Verify();
	if(ret == LIB_EV_OK){
		printf("MAC Success!\n");
	}else{
		printf("MAC Failed!\n");
		return -1;
	}

	return 0;

#if 0
	int fd = -1, ret = -1;
    unsigned char random[RANDOM_NUM_SIZE] = {0};
	unsigned char mac_response[MAC_RSP_SIZE] = {0};
    
	//expected MAC response in mode 0x20
	const unsigned char mac_response_expected[MAC_RSP_SIZE] =
	{
		MAC_RSP_SIZE,                                   // count
		0x3b, 0x0c, 0x14, 0x7c, 0x63, 0x07, 0x4a, 0x02, 
		0xca, 0x5b, 0x65, 0xa6, 0xae, 0x8b, 0x8a, 0xbe, 
		0x4c, 0xb5, 0xac, 0xaa, 0x1e, 0x4c, 0x87, 0x0d, 
		0x68, 0xea, 0x9c, 0x19, 0x71, 0x41, 0x82, 0x65,
		0x45,0x9b                           			// CRC
	};

	//data for challenge in MAC mode 0x20 command
	const unsigned char challenge[MAC_CHALLENGE_SIZE] = {
		0x2d, 0xce, 0x04, 0x63, 0x36, 0x5c, 0x17, 0xad,
		0x02, 0xe8, 0x62, 0xc6, 0x20, 0x75, 0xc7, 0x2f, 
		0x5f, 0x4a, 0x98, 0x8f, 0x40, 0xe1, 0xe9, 0xda, 
		0x9f, 0x3d, 0x4b, 0x4d, 0x5e, 0x06, 0x10, 0x4f
	};

	
    //sha204初始化
    fd = i2c_dev_init(CHIP, CHIP_ADDR);
	if(fd < 0)
    {
        printf("\nsha204 init failed!\n");
        goto err1;
    }   
	printf("\nsha204 init success!\n");

	while(1)
	{
    //唤醒sha204
    ret = sha204_wakeup(fd);
    if(ret < 0)
    {
        printf("\nwakeup failed!\n");
        goto err1;
    }
	printf("\nwakeup success!\n");

#if 0
    //产生随机数
	ret = sha204_random(fd,&random,1);
    if(ret < 0)
    {
        printf("\nRandom failed!\n");
        goto err1;
    } 
    lib_printf_v2("\nRandom Num:",&random,RANDOM_NUM_SIZE,16);
#endif
   
#if 1
	//MAC 消息认证
	ret = sha204_mac(fd,&mac_response,0x20,0,&challenge);
	//ret = sha204_mac(fd,&mac_response,0x20,0,&random);
	if(ret < 0)
    {
        printf("\nMAC error!\n");
        goto err1;
    } 
	lib_printf_v2("\nSHA-256 digest:",&mac_response[1],MAC_RSP_DIGEST_SIZE,16);
	printf("\n");

	if(memcmp(&mac_response_expected,&mac_response,MAC_RSP_SIZE) == 0)
	{
		printf("MAC Success!\n\n");
	}else{
		printf("MAC failed! Now exit the System ...\n\n");
		goto err1;
	}
	printf("Welcome to the System ...\n\n");
#endif

#if 0 //test
	unsigned char rx_buf[MAX_BUF_SIZE] = {0};

    ret = sha204_read(fd,&rx_buf,7,SHA204_ZONE_CONFIG,0x15);//read data
    //ret = sha204_read(fd,&rx_buf,7,SHA204_ZONE_DATA,0x01);//read data
	lib_printf_v2("read data:",&rx_buf[1],ret - 3,16);
	//ret = sha204_write();//write data
	//ret = sha204_update_extra(fd);//UpdateExtra
	//ret = sha204_read();//read data
	//ret = sha204_gendig(&digest);
#endif 

#if 0//进入休眠模式,此函数无效,可通过延时进入休眠(>2s).
	ret = sha204_sleep(fd);
	if(ret < 0){
		printf("\nsleep failed!\n");
		goto err1;
	}
	printf("\nsleep success!\n");
#endif

	printf("Go into Sleep Mode ...\n\n");
	lib_sleep(2);//通过延时进入休眠(>2s)

 }
	
err1:
	close(fd);
err0:
	return 0;
#endif
}
#endif


