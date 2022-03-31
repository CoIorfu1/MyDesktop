#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    
    int fd;
    unsigned short bufdata[3];
    unsigned char buf[6];
    unsigned short ir, als, ps;
    int len;
    
    fd = open("/dev/ap3216c", O_RDWR);
    if(fd < 0){
        printf("open fail\n");
    }
    while(1){
        len = read(fd, bufdata, sizeof(buf));
        //len = read(fd, buf, 6);
        if(len < 0) printf("read fail\n");

        ir = bufdata[0]; /* ir 传感器数据*/
        als = bufdata[1]; /* als 传感器数据 */
        ps = bufdata[2]; /* ps 传感器数据*/
        printf("ir = %d, als = %d, ps = %d\r\n", ir, als, ps);
        usleep(300000);
    }  
    close(fd);
    return 0;
}