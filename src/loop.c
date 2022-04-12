/**
 * @file loop.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Implementación del lazo principal sencilla para probar el 
 *      funcionamiento básico del entorno y el hardware. Simplemente hace 
 *      parpadear el LED conectado al pin 13 del puero C del bluepill.
 */
#include <main.h>
#include <stm32f1xx.h>

typedef enum EstadoLed{ENCENDIDO,APAGADO}EstadoLed;

inline static void estadoLed(EstadoLed estado)
{
    if (estado == ENCENDIDO)
        GPIOC->BSRR |= GPIO_BSRR_BR13;
    else
        GPIOC->BSRR |= GPIO_BSRR_BS13;
}


inline static void esperaMilisegundos(uint32_t tiempo)
{
    if (tiempo == 0) tiempo = 1;
    uint32_t final = tiempo + SysTick_getTicks();
    while (SysTick_getTicks() != final);
}


inline static EstadoLed nuevoEstado(EstadoLed estadoActual)
{
    if (estadoActual == ENCENDIDO)
        return APAGADO;
    return ENCENDIDO;
}




void loop(void)
{
    static EstadoLed estado = ENCENDIDO;
    estadoLed(estado);
    esperaMilisegundos(500);
    estado = nuevoEstado(estado);
}
