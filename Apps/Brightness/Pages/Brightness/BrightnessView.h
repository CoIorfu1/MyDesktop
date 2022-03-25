#ifndef __BRIGHTNESS_VIEW_H
#define __BRIGHTNESS_VIEW_H

#include "../Page.h"

namespace Page
{

class BrightnessView
{

public:

public:
    struct
    {  
        lv_style_t topInfoContStyle;
        lv_style_t styleMain;
        lv_style_t styleIndicator;
        lv_style_t styleKnob;
        lv_style_t stylePressedColor;

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

        lv_obj_t* Slider;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

private:
    void TopInfo_Create(lv_obj_t* par);
    void Slider_Creat(lv_obj_t* par);
    void Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base);
};

}

#endif // !__VIEW_H
