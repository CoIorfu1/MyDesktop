#include "DataProc.h"
#include "../HAL/HAL.h"

static DataCenter center("CENTER");

DataCenter* DataProc::Center(){
    return &center;
}

void DataProc_Init(){
    Account* actGPS = new Account("GPS", &center, sizeof(HAL::GPS_Info_t));
    DP_GPS_Init(actGPS);
}