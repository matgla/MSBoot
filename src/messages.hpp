#pragma once

#include "types.h"

struct Message
{
    u8 fd;
    u8 size;
    u8 payload[255];
};