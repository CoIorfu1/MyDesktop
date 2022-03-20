#include "Home_Button.h"

#if LV_USE_HOME_BUTTON

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h>

//存放输入事件信息
static struct input_event keys_input_event;

void* home_button_init(){
    int err;
    int fd = open("/dev/input/event2",O_RDONLY);
    if(fd<0){
        printf("open fail\n");
    }
    printf("open ok\n");
    while (1)
    {
        err = read(fd,&keys_input_event,sizeof(keys_input_event));
        if(err <0){
            printf("read fail\n");
        }
        if(err>0){
            if((keys_input_event.type == EV_KEY) && (keys_input_event.code == KEY_4)){
                if(keys_input_event.value == 0){
                    printf("key 1 up\n");
                    dbus_method_call("net.my.lvgl.Main", "/net/my/lvgl/Main", "net.my.lvgl.Main", "states", 1, getpid());
                }
            } 
        }
    }
}

#endif