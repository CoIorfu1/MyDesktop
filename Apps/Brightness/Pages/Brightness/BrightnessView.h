#ifndef __BRIGHTNESS_VIEW_H
#define __BRIGHTNESS_VIEW_H

#include "../Page.h"

namespace Page
{

class BrightnessView
{
public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* lableValue;
        lv_obj_t* lableUnit;
    } SubInfo_t;

public:
    struct
    {  
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

        struct
        {
            lv_obj_t* cont;
            SubInfo_t labelInfoGrp[3];
        }ap3216cInfo;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

private:
    void TopInfo_Create(lv_obj_t* par);
    void Ap3216cInfo_Create(lv_obj_t* par);
    void SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText);
};

}

#endif 
