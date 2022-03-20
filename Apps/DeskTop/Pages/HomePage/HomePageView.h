#ifndef __DIALPLATE_VIEW_H
#define __DIALPLATE_VIEW_H

#include "../Page.h"

namespace Page
{

class HomePageView
{

public:

public:
    struct
    {
        struct
        {
            lv_obj_t* cont;
            lv_obj_t* mapIcon;
            lv_obj_t* musicIcon;
        } AppCont;

        struct
        {
            lv_obj_t* cont;
            lv_obj_t* brightnessIcon;
        } BottomCont;

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

        lv_obj_t * BackGround;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();
    void AppearAnimStart(bool reverse = false);

private:
    void AppCont_Create(lv_obj_t* par);
    void BottomCont_Create(lv_obj_t* par);
    void TopInfo_Create(lv_obj_t* par);
    void Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base);
};

}

#endif // !__VIEW_H
