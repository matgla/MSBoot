#pragma once 

#include "types.h"

// enum Messages
// {
//     Connection
// };

struct Message 
{
    u8 fd;
    u8 size;
    u8 payload[255];
};