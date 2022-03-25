#ifndef __DIALPLATE_VIEW_H_
#define __DIALPLATE_VIEW_H_

#include "../Page.h"

namespace Page
{

class BrightnessView
{

public:

public:
    struct
    {  
        lv_style_t styleMain;
        lv_style_t styleIndicator;
        lv_style_t styleKnob;
        lv_style_t stylePressedColor;
        lv_obj_t* Slider;

        lv_obj_t* labelWait;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();

private:
    void Slider_Creat(lv_obj_t* par);
    void Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base);
};

}

#endif // !__VIEW_H
