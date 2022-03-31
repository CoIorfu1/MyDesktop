#include "./HAL.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int fd;

void HAL::Ap3216c_Init(){
    fd = open("/dev/ap3216c", O_RDWR);
    if(fd < 0){
        printf("open ap3216c fail\n");
    }
}

void HAL::Ap3216c_GetInfo(Ap3216c_Info_t* info){
    memset(info, 0, sizeof(Ap3216c_Info_t));
    unsigned short bufdata[3];
    int ret = 0;
    ret = read(fd, bufdata, sizeof(bufdata));
    if(ret < 0) printf("read fail\n");
    info -> IR = bufdata[0];
    info -> ALS = bufdata[1];
    info -> PS = bufdata[2];
}
