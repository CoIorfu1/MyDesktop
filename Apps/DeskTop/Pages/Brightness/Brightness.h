#ifndef __DIALPLATE_PRESENTER_H_
#define __DIALPLATE_PRESENTER_H_

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
    //void AttachEvent(lv_obj_t* obj);

private:
    BrightnessView View;
    //static void onTimer(lv_timer_t* timer);

};

}

#endif
