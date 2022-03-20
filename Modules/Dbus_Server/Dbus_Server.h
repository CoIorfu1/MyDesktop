#ifndef _DBUS_SERVER_H_
#define _DBUS_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../Modules.h"

void dbus_server_init(const char *path, const char *iface);
void dbus_method_call(const char *destination, const char *path, const char *iface, const char *method, const int state, const int pid);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 