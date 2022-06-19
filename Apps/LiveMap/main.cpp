#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <dbus/dbus.h>
#include <pthread.h>
#include <stdio.h>
#include "../Utils/lvgl/lvgl.h"
#include "../Utils/lv_drivers/display/fbdev.h"
#include "../Utils/lv_drivers/indev/evdev.h"
#include "../Utils/lv_lib_png/lv_png.h"
#include "../../Modules/Modules.h"
#include "./App.h"
#include "./DataProc/DataProc.h"

#define DISP_BUF_SIZE (1024 * 600)

int main(void){
    const char* path = "/net/my/lvgl/LiveMap";
    const char* interface =  "net.my.lvgl.LiveMap";
    pthread_t app_exit_thread;

    HAL::HAL_Init();
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 1024;
    disp_drv.ver_res    = 600;
    lv_disp_drv_register(&disp_drv);

	/* Linux input device init */
    evdev_init();
	
    /* Initialize and register a display input driver */
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/

    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;   //lv_gesture_dir_t lv_indev_get_gesture_dir(const lv_indev_t * indev)
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv); 

    // 支持png
    lv_png_init();

    // Set Image Cache size
    lv_img_cache_set_size(32);

    // 建立APP DBUS服务器
    dbus_server_init(path, interface);
    dbus_method_call("net.my.lvgl.Main", "/net/my/lvgl/Main", "net.my.lvgl.Main", "states", 0, 0);

    App_Init();
    pthread_create(&app_exit_thread, NULL, home_button_init, NULL);

    while(1) {
        lv_task_handler();
        //lv_tick_inc(5*1000);
        usleep(5000);
    }
    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}