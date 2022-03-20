#include "DataProc.h"

static DataCenter center("CENTER");

DataCenter* DataProc::Center(){
    return &center;
}