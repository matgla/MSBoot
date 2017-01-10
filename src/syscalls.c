#include "stm32f4xx_conf.h"

#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>


int _gettimeofday(struct timeval *tv, void *tzvp) {
    uint64_t t = 0;                        // get uptime in nanoseconds
    tv->tv_sec = t / 1000000000;           // convert to seconds
    tv->tv_usec = (t % 1000000000) / 1000; // get remaining microseconds
    return 0;                              // return non-zero for error
}

int __errno;

int _close(int file) {
    return 0;
}

int _fstat(int file, struct stat *st) {
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _open(const char *name, int flags, int mode) {
    return -1;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _kill() {
    return 0;
}

int _getpid() {
    return 0;
}

void _exit(int code) {

}
char *heap = NULL;
/* Register name faking - works in collusion with the linker.  */
register char *stack_ptr asm("sp");
caddr_t _sbrk(int incr)
    {
    extern char _heap asm("_heap"); /* Defined by the linker.  */
    extern char _eheap asm("_eheap"); /* Defined by the linker.  */
    caddr_t prevHeap;
    caddr_t nextHeap;

    if (heap == NULL)
    { // first allocation
        heap = (caddr_t) & _heap;
    }

    prevHeap = heap;

    // Always return data aligned on a 8 byte boundary
    nextHeap = (caddr_t) (((unsigned int) (heap + incr) + 7) & ~7);

    // Check enough space and there is no collision with stack coming the other way
    // if stack is above start of heap
    if (nextHeap >= (caddr_t) & _eheap)
    {
    //errno = 1;
    _write(1, "no more memory", 10);
    return NULL; // error - no more memory
    }
    else
    {
    heap = nextHeap;
    return (caddr_t) prevHeap;
    }
    }

int _write(int file, const char *ptr, int len) {
    int i;
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
    USART_SendData(USART1, 1);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
    USART_SendData(USART1, len);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
   // USART_SendData(USART1, len && 0x000000ff);
    for (i = 0; i < len; i++) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
        USART_SendData(USART1, (uint8_t)ptr[i]);
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
    return len;
}
