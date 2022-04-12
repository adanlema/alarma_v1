/**
 * @file systick_isr.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Implementación simple de ISR de SysTick generando un contador de milisegundos.
 */
#include <main.h>

static volatile uint32_t ticks;

uint32_t SysTick_getTicks(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks ++;
}