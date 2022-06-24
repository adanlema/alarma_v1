/**
 * @file main.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */
#include <main.h>

int main(void)
{
    Alarma AL;
    setup(&AL);
    loop(&AL);
    return 0;
}
