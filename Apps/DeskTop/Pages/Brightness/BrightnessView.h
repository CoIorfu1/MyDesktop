#ifndef __DIALPLATE_VIEW_H_
#define __DIALPLATE_VIEW_H_

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
        struct
        {
            lv_obj_t* cont;
            SubInfo_t labelInfoGrp[3];
        }ap3216cInfo;

    } ui;

    void Create(lv_obj_t* root);
    void Delete();

private:
    void Ap3216cInfo_Create(lv_obj_t* par);
    void SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText);
};

}

#endif // !__VIEW_H
