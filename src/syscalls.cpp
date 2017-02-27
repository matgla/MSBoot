#include "stm32f4xx_conf.h"
#include "syscall.hpp"
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "usart.hpp"


int _gettimeofday(struct timeval* tv, void* tzvp)
{
    uint64_t t = 0;                        // get uptime in nanoseconds
    tv->tv_sec = t / 1000000000;           // convert to seconds
    tv->tv_usec = (t % 1000000000) / 1000; // get remaining microseconds
    return 0;                              // return non-zero for error
}


int _close(int file)
{
    return 0;
}

int _fstat(int file, struct stat* st)
{
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    return -1;
}

int _read(int file, char* ptr, int len)
{
    return 0;
}

int _kill()
{
    return 0;
}

int _getpid()
{
    return 0;
}

void _exit(int code)
{
}
char* heap = NULL;
/* Register name faking - works in collusion with the linker.  */
register char* stack_ptr asm("sp");
caddr_t _sbrk(int incr)
{
    extern char _heap asm("_heap");   /* Defined by the linker.  */
    extern char _eheap asm("_eheap"); /* Defined by the linker.  */
    caddr_t prevHeap;
    caddr_t nextHeap;

    if (heap == NULL)
    { // first allocation
        heap = (caddr_t)&_heap;
    }

    prevHeap = heap;

    // Always return data aligned on a 8 byte boundary
    nextHeap = (caddr_t)(((unsigned int)(heap + incr) + 7) & ~7);

    // Check enough space and there is no collision with stack coming the other way
    // if stack is above start of heap
    if (nextHeap >= (caddr_t)&_eheap)
    {
        //errno = 1;
        _write(1, "no more memory", 10);
        return NULL; // error - no more memory
    }
    else
    {
        heap = nextHeap;
        return (caddr_t)prevHeap;
    }
}

int _write(int file, const char* ptr, int len)
{
    int i;
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send(len + 1);
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send(file);
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send(ptr, len);

    return len;
}
