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
/* Register name faking - works in collusion with the linker.  */
register char *stack_ptr asm("sp");

caddr_t _sbrk_r(struct _reent *r, int incr) {
    extern char end asm("end"); /* Defined by the linker.  */
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = &end;

    prev_heap_end = heap_end;

    if (heap_end + incr > stack_ptr) {
/* Some of the libstdc++-v3 tests rely upon detecting
out of memory errors, so do not abort here.  */
#if 0
		extern void abort (void);

		_write (1, "_sbrk: Heap and stack collision\r\n", 32);

		abort ();
#else
        // errno = ENOMEM;
        return (caddr_t)-1;
#endif
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

int _write(int file, const char *ptr, int len) {
    int i;
    USART_SendData(USART1, 1);
    USART_SendData(USART1, len);
   // USART_SendData(USART1, len && 0x000000ff);
    for (i = 0; i < len; i++) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
        USART_SendData(USART1, (uint8_t)ptr[i]);
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {};
    return len;
}
