#pragma once
#include "types.h"

#include <cstddef>

void memory_init();
void *ms_alloc(std::size_t size);
bool is_used(std::size_t header);
std::size_t get_size(std::size_t header);

#ifdef TEST_ENABLED
u8 *getHeap();
#endif