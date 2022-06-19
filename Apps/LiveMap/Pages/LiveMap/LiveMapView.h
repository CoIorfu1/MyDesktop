#ifndef __LIVEMAP_VIEW_H
#define __LIVEMAP_VIEW_H

#include "../Page.h"
#include <vector>

namespace Page
{

class LiveMapView
{
public:
    struct
    {
        lv_obj_t* labelInfo;

        lv_style_t styleCont;
        lv_style_t styleLabel;
        lv_style_t styleLine;

        struct
        {
            lv_obj_t* cont;
            lv_obj_t* imgArrow;
            lv_obj_t** imgTiles;
            uint32_t tileNum;            
        } map;

        struct
        {
            lv_obj_t* cont;
            lv_obj_t* labelInfo;
            lv_obj_t* slider;
        } zoom;
    } ui;

    void Create(lv_obj_t* root, uint32_t tileNum);
    void Delete();
    void SetImgArrowStatus(lv_coord_t x, lv_coord_t y, float angle)
    {
        lv_obj_t* img = ui.map.imgArrow;
        lv_obj_set_pos(img, x, y);
        lv_img_set_angle(img, int16_t(angle * 10));
    }
    void SetMapTile(uint32_t tileSize, uint32_t widthCnt);
    void SetMapTileSrc(uint32_t index, const char* src);
    //void SetArrowPath(const char* path);

private:
    void Style_Create();
    void Map_Create(lv_obj_t* par, uint32_t tileNum);
    void ZoomCtrl_Create(lv_obj_t* par);
};

}

#endif // !__VIEW_H
