#ifndef __HAL_H
#define __HAL_H

#include "../nmealib/include/nmea.h"
#include <stdint.h>
#include <atomic>

namespace HAL {

    /* Clock */
typedef struct
{
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t year;
    uint16_t millisecond;
} Clock_Info_t;

typedef struct
{
    bool isVaild;
    int16_t satellites;
    double longitude;
    double latitude;
    double course;
    Clock_Info_t clock;
} GPS_Info_t;
    
void HAL_Init();

// open device file
void GPS_Init();
// read GPS's data to info
bool GPS_GetInfo(GPS_Info_t* info);

}

#endif //__HAL_