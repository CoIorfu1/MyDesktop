#ifndef _APP_MANAGER_H_
#define _APP_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../Modules.h"

int is_app_foreground();
void wait_for_app_foreground();
void change_app_state(int state);

#ifdef __cplusplus
}
#endif

#endif