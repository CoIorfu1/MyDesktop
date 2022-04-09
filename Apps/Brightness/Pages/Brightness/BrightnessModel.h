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
    HAL::Ap3216c_Info_t ap3216cInfo;
    std::mutex mtx;

public:
    void Init();
    void Deinit();

    unsigned short GetIR()
    {
        return ap3216cInfo.IR;
    }

    unsigned short GetALS()
    {     
        return ap3216cInfo.ALS;
    }

    unsigned short GetPS()
    {
        return ap3216cInfo.PS;
    }

private:
    Account* account;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);
};

}

#endif