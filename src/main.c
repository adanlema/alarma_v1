/**
 * @file main.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */
#include <main.h>

int main(void)
{
    EstadoAlarma AL;
    setup(&AL);
    for(;;)loop(&AL);
    return 0;
}
