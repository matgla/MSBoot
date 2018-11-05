ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 64K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 20K
}

/* begin of stack in ARM adresses are decreasing */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Place sections in memory */
SECTIONS 
{
    /* startup code */
    .isr_vector :
    {
        . = ALIGN(4);
        __isr_vector_start__ = .;
        KEEP(*(.isr_vector);
        ASSERT(. != __interrupt_vector_start__, ".interrupt_vector section is empty! Startup code must be provided")
        . = ALIGN(4);
    } >FLASH

    /* user code & read only data */
    .text:
    {
        . = ALIGN(4);
        _stext = .;
        *(.text*)
        *(.rodata*)
        KEEP(*(.init)) /* static constructors */
        KEEP(*(.fini)) /* static destructors */
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    /* ARM stack unwinding */
    .ARM.extab :
    {
        *(.ARM.extab*)
    } >FLASH
    .ARM.exidx : 
    {
        *(.ARM.exidx*)
    } >FLASH 

    /* Newlib C++ support */
    .preinit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } >FLASH
    .init_array :
    {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } >FLASH
    .fini_array :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
        . = ALIGN(4)
    } >FLASH

    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    ._heap :
    {
        . = ALIGN(4);
        . = . + _heap_size;
        . = ALIGN(4);
    } >RAM
    ._stack:
    {
        . = ALIGN(4);
        . = . + _stack_size;
        . = ALIGN(4);
    } >RAM 
}

__isr_vector_size__ = SIZEOF(.isr_vector);
__text_size__ = SIZEOF(.text);
__data_size__ = SIZEOF(.data);
__bss_size__ = SIZEOF(.bss);
