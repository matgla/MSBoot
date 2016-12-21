#include "memoryManagement.hpp"
#include "logger.hpp"

u8 heap[1000];

void memory_init() {
    heap[0] = 0;
}

void *ms_alloc(std::size_t size) {
    *heap = 0;

    // set size in header
    std::size_t *header = reinterpret_cast<std::size_t *>(heap);
    *header = size;

    *heap = *heap | 0x80; // set use flag

    return heap + sizeof(std::size_t);
}

bool is_used(std::size_t header) {
    return header >> sizeof(std::size_t) - 1;
}

std::size_t get_size(std::size_t header) {
    Logger::log(Level::DEBUG, "memory", "get_size header: &d", header);
    return header &= ~(1 << (sizeof(std::size_t) - 1));
}

#ifdef TEST_ENABLED
u8 *getHeap() {
    return heap;
}
#endif