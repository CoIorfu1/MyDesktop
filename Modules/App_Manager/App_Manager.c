/*********************
 *      INCLUDES
 *********************/
#include "App_Manager.h"

#if LV_USE_APP_MANAGER
#include <stdio.h>
#include <pthread.h>

static int lv_state = 1;
static pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lv_mutex = PTHREAD_MUTEX_INITIALIZER;

static void sleep_lvgl_thread();
static void wakeup_lvgl_thread();

static void sleep_lvgl_thread(){
    pthread_mutex_lock(&lv_mutex);
    lv_state = 0;
}

static void wakeup_lvgl_thread(){
    lv_state = 1;
    pthread_mutex_unlock(&lv_mutex);
}

void wait_for_app_foreground(){
    pthread_mutex_lock(&lv_mutex);
    pthread_mutex_unlock(&lv_mutex);
}

void change_app_state(int state){
    pthread_mutex_lock(&state_mutex);
    if(state == 0){
        sleep_lvgl_thread();
    }
        
    else if(state == 1){
        wakeup_lvgl_thread();
    }
    pthread_mutex_unlock(&state_mutex); 
}

int is_app_foreground(){
    pthread_mutex_lock(&state_mutex);
    int tmp = lv_state;
    pthread_mutex_unlock(&state_mutex);
    return tmp;
}

#endif
