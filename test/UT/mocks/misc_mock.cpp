#include "misc_mock.hpp"

MOCK_VOID_FUNCTION(NVIC_Init, (a),
    (NVIC_InitTypeDef * a), NVIC_InitTypeDef*);