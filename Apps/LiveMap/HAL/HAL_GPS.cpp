#include "./HAL.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>

static int fd;
static int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;
	
	if ( tcgetattr(fd, &oldtio) != 0) { 
		perror("SetupSerial 1");
		return -1;
	}
	
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag |= CLOCAL | CREAD; 
	newtio.c_cflag &= ~CSIZE; 

	newtio.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
	newtio.c_oflag  &= ~OPOST;   /*Output*/

	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
	break;
	case 8:
		newtio.c_cflag |= CS8;
	break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
	break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
	break;
	case 'N': 
		newtio.c_cflag &= ~PARENB;
	break;
	}

	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
	break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
	break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
	break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	break;
	}
	
	if( nStop == 1 )
		newtio.c_cflag &= ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |= CSTOPB;
	
	newtio.c_cc[VMIN]  = 1;  /* 读数据时的最小字节数: 没读到这些数据我就不返回! */
	newtio.c_cc[VTIME] = 0; /* 等待第1个数据的时间: 
	                         * 比如VMIN设为10表示至少读到10个数据才返回,
	                         * 可以设置VTIME超时时间(单位是10秒)
	                         * 假设VTIME=1，表示: 
	                         *    10秒内一个数据都没有的话就返回
	                         *    如果10秒内至少读到了1个字节，那就继续等待，完全读到VMIN个数据再返回
	                         */
	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	printf("com set done!\n");
	return 0;
}

static int read_gps_raw_data(int fd, char *buf)
{
	int i = 0;
	int ret;
	char c;
	int start = 0;
	
	while (1)
	{
		ret = read(fd, &c, 1);
		if(ret == 1){
			if(c == '$')
				start = 1;
			if(start){
				buf[i++] = c;
			}
			if(c == '\n' || c == '\r')
				return 0;
		}
		else{
			return -1;
		}
	}
}

void HAL::GPS_Init(){
    fd = open("/dev/ttymxc5", O_RDWR);
    if(fd < 0){
        printf("open gps fail\n");
    }
    if(fcntl(fd, F_SETFL, 0)<0) /* 设置串口为阻塞状态*/{
			printf("fcntl failed!\n");
			return;
	}
    int ret = 0;
    ret = set_opt(fd, 9600, 8, 'N', 1);
	if(ret){
		printf("set port err!\n");
		return;
	}
}

bool HAL::GPS_GetInfo(GPS_Info_t* info){
	char buf[200];
	int ret = 0;
    memset(info, 0, sizeof(GPS_Info_t));
    ret = read_gps_raw_data(fd, buf);
	nmeaINFO meaInfo;                  // nmea协议解析结果结构体
    nmeaPARSER parser;              // nmea协议解析载体
 
    nmea_zero_INFO(&meaInfo);          // 填入默认的解析结果
    nmea_parser_init(&parser);      // 为解析载体分配内存空间
    // 调用函数完成GPS信息解析，最终结果保留于info数组中
    if( (nmea_parse(&parser, buf, (int)strlen(buf), &meaInfo)) > 0 ){
        printf("parse gps ok\n");
    }
	info->isVaild = meaInfo.sig;
    info->longitude = meaInfo.lon;
    info->latitude = meaInfo.lat;
	info->course = meaInfo.direction;

    info->clock.year = meaInfo.utc.year;
    info->clock.month = meaInfo.utc.mon;
    info->clock.day = meaInfo.utc.day;
    info->clock.hour = meaInfo.utc.hour;
    info->clock.minute = meaInfo.utc.min;
    info->clock.second = meaInfo.utc.sec;
    info->satellites = meaInfo.satinfo.inuse;
    nmea_parser_destroy(&parser);   // 释放解析载体的内存空间
    return info->isVaild;
}


