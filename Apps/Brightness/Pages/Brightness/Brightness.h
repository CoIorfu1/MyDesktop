#ifndef __BRIGHTNESS_H
#define __BRIGHTNESS_H

#include "BrightnessView.h"
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
    static void onEvent(lv_event_t* event);

private:
    BrightnessView View;
};

}

#endif
