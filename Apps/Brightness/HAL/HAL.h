#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>

namespace HAL {
    
//* ap3216c data structure
typedef struct
{
    unsigned short IR;
    unsigned short ALS;
    unsigned short PS;
} Ap3216c_Info_t;
    
void HAL_Init();

// open device file
void Ap3216c_Init();
// read ap3216c's data to info
void Ap3216c_GetInfo(Ap3216c_Info_t* info);

}

#endif //__HAL_