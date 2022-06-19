#ifndef __LIVEMAP_PRESENTER_H
#define __LIVEMAP_PRESENTER_H

#include "LiveMapView.h"
#include "LiveMapModel.h"
#include "../../Modules/Modules.h"

namespace Page
{

class LiveMap : public PageBase
{
public:
    typedef struct
    {
        int32_t x0;
        int32_t y0;
        int32_t x1;
        int32_t y1;
    } Area_t;

    LiveMap();
    virtual ~LiveMap();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    LiveMapView View;
    LiveMapModel Model;

    struct
    {
        uint32_t lastMapUpdateTime;
        uint32_t lastContShowTime;
        lv_timer_t* timer;
        TileConv::Point_t lastTileContOriPoint;
    } priv;

    static uint16_t mapLevelCurrent;

private:
    void Update();
    void UpdateDelay(uint32_t ms);
    void CheckPosition();

    /* MapTileCont */
    bool GetIsMapTileContChanged();
    void onMapTileContRefresh(const Area_t* area, int32_t x, int32_t y);
    void MapTileContUpdate(int32_t mapX, int32_t mapY, float course);
    void MapTileContReload();
    
    void AttachEvent(lv_obj_t* obj);
    static void onEvent(lv_event_t* event);
};

}

#endif
