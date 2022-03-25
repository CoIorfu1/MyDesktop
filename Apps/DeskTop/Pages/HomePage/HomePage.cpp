#include "HomePage.h"
#include <stdio.h>

using namespace Page;

HomePage::HomePage()
{
}

HomePage::~HomePage()
{
}

void HomePage::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void HomePage::onViewLoad()
{
    View.Create(root);
    printf("view creat\n");
    AttachEvent(View.ui.BottomCont.brightnessIcon);
    printf("attch event\n");
}

void HomePage::onViewDidLoad()
{

}

void HomePage::onViewWillAppear()
{
    View.AppearAnimStart();
}

void HomePage::onViewDidAppear()
{
    //lv_obj_clear_flag(View.ui.AppCont.cont, LV_OBJ_FLAG_HIDDEN);
}

void HomePage::onViewWillDisappear()
{
    //View.AppearAnimStart(true);
}

void HomePage::onViewDidDisappear()
{
}

void HomePage::onViewDidUnload()
{
    View.Delete();
}

void HomePage::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void HomePage::onAppClicked(lv_obj_t* btn)
{
    printf("Clicked\n");
    bool isRepeat = false;
    if (btn == View.ui.BottomCont.brightnessIcon)
    {
        Manager->Push("Pages/Brightness");
        //dbus_method_call("net.my.lvgl.Brightness", "/net/my/lvgl/Brightness", "net.my.lvgl.Brightness", "states", 0, 0);
        lv_timer_t* timer = lv_timer_create(onTimer, 500, NULL);
        lv_timer_set_repeat_count(timer, 1);
    }
}

void HomePage::onTimer(lv_timer_t* timer)
{
    dbus_method_call("net.my.lvgl.Brightness", "/net/my/lvgl/Brightness", "net.my.lvgl.Brightness", "states", 0, 0);
    
}

void HomePage::onEvent(lv_event_t* event)
{
    
    HomePage* instance = (HomePage*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED)
    {
        instance->onAppClicked(obj);
    }
}
