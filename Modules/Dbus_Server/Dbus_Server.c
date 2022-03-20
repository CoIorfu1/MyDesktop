/*********************
 *      INCLUDES
 *********************/
#include "Dbus_Server.h"

#if LV_USE_DBUS_SERVER
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <dbus/dbus.h>


static char *my_object_path;
static char *my_iface;

static void check_and_abort(DBusError *error);
static DBusHandlerResult handle_message(DBusConnection *connection, DBusMessage *message, void *user_data);
static void respond_to_introspect(DBusConnection *connection, DBusMessage *request);
static void respond_to_states(DBusConnection *connection, DBusMessage *request);
static void *dbus_dispatch_thread_func(void *pvoid);

static void check_and_abort(DBusError *error) {
    if (dbus_error_is_set(error)) {
        puts(error->message);
        abort();
    }
}

static void *dbus_dispatch_thread_func(void *pvoid){
    DBusConnection * connection = (DBusConnection *)pvoid;
    while(1)
    {
        //* 从DBus队列读取消息，阻塞直到消息可用，然后将消息分派给感兴趣的对象，等待时间为1000ms
        dbus_connection_read_write_dispatch(connection, 1000);
    }
}

static DBusHandlerResult handle_message(DBusConnection *connection, DBusMessage *message, void *user_data){
    const char *interface_name = dbus_message_get_interface(message);
    const char *member_name = dbus_message_get_member(message);
    printf("interface:%s\n", interface_name);
    printf("member_name:%s\n", member_name);
    
    if (0==strcmp("org.freedesktop.DBus.Introspectable", interface_name) &&
        0==strcmp("Introspect", member_name)) {
        respond_to_introspect(connection, message);
        return DBUS_HANDLER_RESULT_HANDLED;
    } 
    else if (0==strcmp(my_iface, interface_name) &&
           0==strcmp("states", member_name)) {         
        respond_to_states(connection, message);
        return DBUS_HANDLER_RESULT_HANDLED;
    }  
    else {
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }
};

static void respond_to_introspect(DBusConnection *connection, DBusMessage *request){
    DBusMessage *reply;
    char introspection_data[1024];
    sprintf(introspection_data, \
        " <!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" "
        "\"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">"
        " <!-- dbus-sharp 0.8.1 -->"
        " <node>"
        "   <interface name=\"org.freedesktop.DBus.Introspectable\">"
        "     <method name=\"Introspect\">"
        "       <arg name=\"data\" direction=\"out\" type=\"s\" />"
        "     </method>"
        "   </interface>"
        "   <interface name=\"%s\">"
        "     <method name=\"states\">"
        "       <arg name=\"states\" direction=\"in\" type=\"i\" />"
        "       <arg name=\"pid\" direction=\"in\" type=\"i\" />"
        "     </method>"
        "     <property name=\"Status\" type=\"u\" access=\"readwrite\"/>"
        "   </interface>"
        " </node>"
        , my_iface);
    
    reply = dbus_message_new_method_return(request);
    dbus_message_append_args(reply,
                 DBUS_TYPE_STRING, &introspection_data,
                 DBUS_TYPE_INVALID);
    dbus_connection_send(connection, reply, NULL);
    dbus_message_unref(reply);
}

static void respond_to_states(DBusConnection *connection, DBusMessage *request){
    DBusMessage *reply;
    DBusError error;
    int states = 1;
    int pid = 0;

    dbus_error_init(&error);

    // 获取参数数值
    dbus_message_get_args(request, &error,
                  DBUS_TYPE_INT32, &states,
                  DBUS_TYPE_INT32, &pid,
                  DBUS_TYPE_INVALID);
    if (dbus_error_is_set(&error)) {
        reply = dbus_message_new_error(request, "wrong_arguments", "Illegal arguments");
        dbus_connection_send(connection, reply, NULL);
        dbus_message_unref(reply);
        return;
    }

    //* 根据state值到app_manager判断前后台
    change_app_state(states);

    //* 
    if (0 == strcmp(my_iface, "net.my.lvgl.Main")){
        // kill 目标进程
        if (pid != 0 ){
            kill(pid, SIGKILL);    
        }
    }
}

//* 建立DBus服务器端
void dbus_server_init(const char *path, const char *iface){
    DBusConnection *myconnection;
    DBusError error;
    DBusObjectPathVTable vtable;
    int ret;
    pthread_t tid;
 
    my_object_path = path;       
    my_iface = iface;    

    printf("object_path: %s, object_interface: %s\n", my_object_path, my_iface);

    dbus_error_init(&error);
    myconnection = dbus_bus_get(DBUS_BUS_SESSION, &error);  //* 连接到DBus总线
    check_and_abort(&error);
 
    //* 给连接分配一个公共名
    dbus_bus_request_name(myconnection, my_iface, 0, &error);
    check_and_abort(&error);
 
    vtable.message_function = handle_message;
    vtable.unregister_function = NULL;
     
    //* 注册服务端path、消息处理函数
    dbus_connection_try_register_object_path(myconnection,
                         my_object_path,
                         &vtable,
                         NULL,
                         &error);
    check_and_abort(&error);

    ret = pthread_create(&tid, NULL, dbus_dispatch_thread_func, myconnection);
}

void dbus_method_call(const char *destination, const char *path, const char *iface, const char *method, const int state, const int pid){
    DBusConnection *connection;
    DBusError error;
    DBusMessage *message;
    printf("dbus method call\n");
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);

    if ( dbus_error_is_set(&error) )
    {
        printf("Error getting dbus connection: %s\n",error.message);
        dbus_error_free(&error);
        dbus_connection_unref(connection);
        return 0;
    }

    message = dbus_message_new_method_call(destination, path, iface, method);
    if(message == NULL) {
        printf("[error] Message NULL!!!");
        return;
    }
    printf("iface=%s\n",iface);
    /* Append the argument to the message */
    dbus_message_append_args(message, DBUS_TYPE_INT32, &state, DBUS_TYPE_INT32, &pid, DBUS_TYPE_INVALID);

    dbus_message_set_no_reply(message, TRUE);  // We don't want to receive a reply
    if( !dbus_connection_send(connection, message, NULL)){
        printf("Out of Memory/n");
        exit(1);
    }

    dbus_message_unref(message);
    dbus_connection_unref(connection);
    printf("message send\n");
}

#endif
