#ifndef __BRIGHTNESS_H
#define __BRIGHTNESS_H

#include "BrightnessView.h"
#include "BrightnessModel.h"
#include "../../Modules/Modules.h"

namespace Page
{

class Brightness : public PageBase
{
public:
    Brightness();
    virtual ~Brightness();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();
private:
    void AttachEvent(lv_obj_t* obj);
    void Update();
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    BrightnessView View;
    BrightnessModel Model;
    lv_timer_t* timer;
};

}

#endif
