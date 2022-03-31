#ifndef _DATA_PROC_H_
#define _DATA_PROC_H_

#include "../../Utils/DataCenter/DataCenter.h"
#include "../HAL/HAL.h"

// create all pub account and init
void DataProc_Init();
//init the pub account
void DP_Ap3216c_Init(Account* account);

namespace DataProc{
    DataCenter* Center();
}

#endif
