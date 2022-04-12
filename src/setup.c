/**
 * @file setup.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Configuración básica: 
 *      - Pin 13 del puerto C (led del bluepill) como salida 2MHz PushPull
 *      - Interrupción SysTick cada 1ms
 */
#include <main.h>
#include <stm32f1xx.h>

inline static void conectaRelojPuertoC(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

inline static void configuraPin13PuertoC_SalidaPushPull_2MHz_inicial_1(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BS13;
    GPIOC->CRH = (GPIOC->CRH & ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13))|(GPIO_CRH_MODE13_1);
}

inline static void configuraSysTick_1ms(void)
{
    SystemCoreClockUpdate();
    const uint32_t ciclosPorMilisegundo = SystemCoreClock/1000;
    const uint32_t falla = SysTick_Config(ciclosPorMilisegundo);
    while(falla)asm volatile("nop");
}

void setup(void)
{
    conectaRelojPuertoC();
    configuraPin13PuertoC_SalidaPushPull_2MHz_inicial_1();
    configuraSysTick_1ms();
}
