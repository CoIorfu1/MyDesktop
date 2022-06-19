#ifndef __LIVEMAP_MODEL_H
#define __LIVEMAP_MODEL_H

#include "lvgl/lvgl.h"
#include "../MapConv/MapConv.h"
#include "../TileConv/TileConv.h"
#include "../../DataProc/DataProc.h"
#include <vector>

namespace Page
{

class LiveMapModel
{
public:
    LiveMapModel();
    ~LiveMapModel() {}
    void Init();
    void Deinit();
    void GetGPS_Info(HAL::GPS_Info_t* info);
    void GetArrowTheme(char* buf, uint32_t size);

public:
    MapConv mapConv;
    TileConv tileConv;
    
private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);

};

}

#endif
