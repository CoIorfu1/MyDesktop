#include "Brightness.h"
#include <stdio.h>

using namespace Page;

Brightness::Brightness()
{
}

Brightness::~Brightness()
{
}

void Brightness::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP);
}

void Brightness::onViewLoad()
{
    View.Create(root);
    printf("view creat\n");
    /* AttachEvent(View.ui.Slider);
    printf("attch event\n"); */
    /* lv_timer_t* timer = lv_timer_create(onTimer, 2000, this);
    lv_timer_set_repeat_count(timer, 1); */
}

/* void Brightness::onTimer(lv_timer_t* timer)
{
    Brightness* instance = (Brightness*)timer->user_data;

    instance->Manager->Pop();
} */

void Brightness::onViewDidLoad()
{

}

void Brightness::onViewWillAppear()
{ 
    
}

void Brightness::onViewDidAppear()
{
    //lv_obj_cleaBrightnessPager_flag(View.ui.AppCont.cont, LV_OBJ_FLAG_HIDDEN);
}

void Brightness::onViewWillDisappear()
{
    
    lv_obj_fade_out(root, 250, 250);
    //View.AppearAnimStart(true);
}

void Brightness::onViewDidDisappear()
{
}

void Brightness::onViewDidUnload()
{
    View.Delete();
}

/* void Brightness::AttachEvent(lv_obj_t* obj)
{
    printf("test\n");
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
} */


