function(board_to_mcu board mcu)
    if (${board} STREQUAL "Stm32_Black_Pill")
        set(${mcu} "STM32F103C8T6" PARENT_SCOPE)
    else ()
        message(FATAL_ERROR "Unsupported board: ${board}")
    endif ()
endfunction()