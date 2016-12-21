#include "memoryManagement.hpp"
#include "types.h"
#include "gtest/gtest.h"

#include <cstddef>

class memoryFixture : public ::testing::Test {

  protected:
    virtual void SetUp() {
        memory_init();
    };
    u8 *heap = getHeap();
};

TEST_F(memoryFixture, shouldReturnFirstAddressAfterHeaderForEmptyHeap) {
    int *testPtr = (int *)ms_alloc(sizeof(int) * 4);
    EXPECT_EQ(&heap[sizeof(std::size_t)], (u8 *)testPtr);
}

TEST_F(memoryFixture, shouldSetUseFlagAndSizeOnFirstBytes) {
    std::size_t allocationSize = sizeof(int) * 4;
    int *testPtr = (int *)ms_alloc(allocationSize);

    std::size_t *header = reinterpret_cast<std::size_t *>(heap);

    EXPECT_EQ(allocationSize, get_size(*header));
    EXPECT_EQ(1, is_used(*header));
}