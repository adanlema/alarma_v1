#include <ticks_systick.h>
#include <stm32f1xx.h>

Ticks_Result Ticks_configura_1ms(void)
{
    SystemCoreClockUpdate();
    const uint32_t ciclosPorMilisegundo = SystemCoreClock/1000;
    const uint32_t falla = SysTick_Config(ciclosPorMilisegundo);
    if (falla)
        return TICKS_ERROR;
    return TICKS_OK; 
}

void Ticks_esperaMilisegundos(uint32_t tiempo)
{
    if (tiempo == 0) tiempo = 1;
    uint32_t final = tiempo + Ticks_getTicks();
    while (Ticks_getTicks() != final);
}
