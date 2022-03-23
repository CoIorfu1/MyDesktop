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
    lv_obj_clear_flag(View.ui.BackGround, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(View.ui.BottomCont.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(View.ui.BottomCont.cont);
    lv_obj_move_foreground(View.ui.TopInfo.cont);
    lv_obj_move_foreground(View.ui.AppCont.cont);
    lv_obj_move_background(View.ui.BackGround);
    printf("view will appear\n");
    View.AppearAnimStart();
}

void HomePage::onViewDidAppear()
{
    lv_obj_clear_flag(View.ui.AppCont.cont, LV_OBJ_FLAG_HIDDEN);
}

void HomePage::onViewWillDisappear()
{
    lv_obj_add_flag(View.ui.BottomCont.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(View.ui.AppCont.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(View.ui.BackGround, LV_OBJ_FLAG_HIDDEN);
    lv_obj_fade_out(root, 250, 250);
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
    if (btn == View.ui.BottomCont.brightnessIcon)
    {
        dbus_method_call("net.my.lvgl.Brightness", "/net/my/lvgl/Brightness", "net.my.lvgl.Brightness", "states", 0, 0);

    }
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
