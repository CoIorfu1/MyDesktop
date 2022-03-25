#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include "HomePageView.h"
#include "../../Modules/Modules.h"

namespace Page
{

class HomePage : public PageBase
{
public:
    HomePage();
    virtual ~HomePage();

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
    void onAppClicked(lv_obj_t* btn);

private:
    HomePageView View;
    static void onTimer(lv_timer_t* timer);
};

}

#endif
