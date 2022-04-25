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
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Brightness::onViewLoad()
{
    Model.Init();
    View.Create(root);
}

void Brightness::onViewDidLoad()
{
}

void Brightness::onViewWillAppear()
{ 
    lv_obj_clear_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    View.AppearAnimStart();
}

void Brightness::onViewDidAppear()
{
    timer = lv_timer_create(onTimerUpdate, 300, this);
}

void Brightness::onViewWillDisappear()
{
    lv_timer_del(timer);
    lv_obj_add_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_fade_out(root, 250, 250);
}

void Brightness::onViewDidDisappear()
{
    
}

void Brightness::onViewDidUnload()
{
    Model.Deinit();
    View.Delete();
}

void Brightness::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Brightness::onEvent(lv_event_t* event)
{ 
    Brightness* instance = (Brightness*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
}

void Brightness::onTimerUpdate(lv_timer_t* timer)
{
    Brightness* instance = (Brightness*)timer->user_data;
    instance->Update();
}

void Brightness::Update()
{
    if(Model.mtx.try_lock()){
        unsigned short buf[3];
        buf[0] = Model.GetIR();
        lv_label_set_text_fmt(View.ui.ap3216cInfo.labelInfoGrp[0].lableValue, "%d ", buf[0]);

        buf[1] = Model.GetALS();
        lv_label_set_text_fmt(View.ui.ap3216cInfo.labelInfoGrp[1].lableValue, "%d ", buf[1]);

        buf[2] = Model.GetPS();
        lv_label_set_text_fmt(View.ui.ap3216cInfo.labelInfoGrp[2].lableValue, "%d ", buf[2]);
        Model.mtx.unlock();
    }
    
}
