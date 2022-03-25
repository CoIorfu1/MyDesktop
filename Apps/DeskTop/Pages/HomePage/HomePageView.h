#ifndef _HOMEPAGE_VIEW_H_
#define _HOMEPAGE_VIEW_H_

#include "../Page.h"

namespace Page
{

class HomePageView
{

public:

public:
    struct
    {
        lv_style_t bottomContStyle;
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* brightnessIcon;
        } BottomCont;

        lv_style_t appContStyle;
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* mapIcon;
            lv_obj_t* musicIcon;
        } AppCont;

        lv_style_t topInfoContStyle;
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* infoCont;
            lv_obj_t* blank;
            lv_obj_t* battery;
            lv_obj_t* wifi;
            lv_obj_t* timeInfo;
            lv_timer_t * timer;
        }TopInfo;
        
        lv_obj_t* BackGround;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

private:
    
    void TopInfo_Create(lv_obj_t* par);
    void AppCont_Create(lv_obj_t* par);   
    void Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base);
    void BottomCont_Create(lv_obj_t* par);
    static void lv_timer_update_time(lv_timer_t * timer);
};

}

#endif // !__VIEW_H
