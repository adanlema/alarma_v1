/**
 * @file main.c
 * @author Fernando A. Miranda Bonomi (fmirandabonomi@herrera.unt.edu.ar)
 * @brief Esqueleto de aplicación con una función de configuración y un lazo infinito.
 */
#include <main.h>


void iniciar_alarma(Alarma *self, EstadoAlarma estadoInicial)
{
    printf("Iniciliazando alarma...\n");
    self->estado = estadoInicial;
}


int main(void)
{
    EstadoAlarma AL;

    setup();
    iniciar_alarma(&AL,DESARMADA);
    for(;;)loop(&AL);
    return 0;
}
