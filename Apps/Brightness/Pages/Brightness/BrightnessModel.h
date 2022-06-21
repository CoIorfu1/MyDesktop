#ifndef __BRIGHTNESS_MODEL_H
#define __BRIGHTNESS_MODEL_H

#include <atomic>
#include <mutex>
#include <limits.h>
#include "../../DataProc/DataProc.h"

namespace Page
{

class BrightnessModel
{
public:
    void Init();
    void Deinit();
    void GetAp3216c_Info(HAL::Ap3216c_Info_t* info);

private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);
};

}

#endif