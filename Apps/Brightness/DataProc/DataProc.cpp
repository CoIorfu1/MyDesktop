#include "DataProc.h"
#include "../HAL/HAL.h"

static DataCenter center("CENTER");

DataCenter* DataProc::Center(){
    return &center;
}

void DataProc_Init(){
    Account* actAp3216c = new Account("Ap3216c", &center, sizeof(HAL::Ap3216c_Info_t));
    DP_Ap3216c_Init(actAp3216c);
}