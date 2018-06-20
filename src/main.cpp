#include <stm32f10x.h>
#include <stm32f10x_iwdg.h>

int main()
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    while (true)
    {
    }

    return 0;
}
