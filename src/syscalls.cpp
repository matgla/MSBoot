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
      extern char end asm("end");
  static char* heap_end;
  char* prev_heap_end, *min_stack_ptr;

  if (heap_end == 0) {
    heap_end = &end;
  }

  prev_heap_end = heap_end;

  if (heap_end + incr > stack_ptr)
  {
		_write(1, "Heap and stack collision\n", 25);
//		abort();
   // errno = ENOMEM;
    return (caddr_t) - 1;
  }

  heap_end += incr;

  return (caddr_t) prev_heap_end;
}

int _write(int file, const char* ptr, int len)
{
    int i;
    hw::USART<hw::USARTS::USART1_PP1>::getUsart().send(ptr, len);

    return len;
}
