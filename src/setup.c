/**
 * @file main.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Configuración básica: 
 *      - Inicilizar la alarma
 *      - Configurar los puertos
 *      - Interrupción SysTick cada 1ms
 */
#include <main.h>
#include <timer_systick.h>
#include <stm32f1xx.h>

void setup(void)
{
    TimerSysTick_init();
}
