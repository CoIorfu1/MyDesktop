/*********************
 *      INCLUDES
 *********************/
#include "App_Manager.h"

#if LV_USE_APP_MANAGER
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

static atomic_int lv_state = ATOMIC_VAR_INIT(1);
static pthread_mutex_t lv_mutex = PTHREAD_MUTEX_INITIALIZER;

static void sleep_lvgl_thread();
static void wakeup_lvgl_thread();

static void sleep_lvgl_thread(){
    pthread_mutex_lock(&lv_mutex);
    atomic_fetch_sub(&lv_state, 1);
}

static void wakeup_lvgl_thread(){
    atomic_fetch_add(&lv_state, 1);
    pthread_mutex_unlock(&lv_mutex);
}

void wait_for_app_foreground(){
    pthread_mutex_lock(&lv_mutex);
    pthread_mutex_unlock(&lv_mutex);
}

void change_app_state(int state){
    if(state == 0){
        sleep_lvgl_thread();
    }
        
    else if(state == 1){
        wakeup_lvgl_thread();
    }
}

int is_app_foreground(){
    return atomic_load(&lv_state);
}

#endif
