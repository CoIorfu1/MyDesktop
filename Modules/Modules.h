#ifndef _MODULES_H_
#define _MODULES_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "../Apps/Utils/lvgl/lvgl.h"
#endif

#include "../Apps/modules_conf.h"
#include "./App_Manager/App_Manager.h"
#include "./Dbus_Server/Dbus_Server.h"
#include "./Home_Button/Home_Button.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#error "lv_100ask_modules: Wrong lvgl version"
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 