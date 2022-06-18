/*
 * @file loop.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */

#include <main.h>
#include <stm32f1xx.h>
#include <timer_systick.h>


void alarma_procesaEvento(Alarma *self, EventosAlarma evento)
{
    switch(self->estado){
        case DESARMADA:
            switch (evento)
            {
                case Deteccion_Z1:
                    printf("Se detecto movimiento en la Zona1!");
                    /*
                    Deberia registrar el horario en el que se acciono.
                    */
                    break;
                case ARMAR:
                    // Deberia provocar un cambio de estado para que comience el armado de la alarma
        
                    alarma_transicion(&self,ARMADA);
                    break;
                default:
                    /*
                    No realiza ninguna actividad si no se encuentra en algun comando anterior.
                    */
                    break;
            }
            break;
        case TEMP_ARMADO:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Se cancelo la activacion de la alarma...\n");
                        /*
                        Deberia cambiar el estado de la alarma.
                        */
                        break;
                    case FIN_TEMPORIZACION:
                        /*
                        Debe indicar el cambio de estado de la alarma a armada.
                        */
                        break;
                    default:
                        /*
                        No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        */
                        break;
                }
            break;
        case ARMADA:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        /*
                        Deberia cambiar el estado de la alarma.
                        */
                        break;
                    case Deteccion_Z1:
                        /*
                        Debe encenderse la sirena, es decir debe actuar el comando de disparo.
                        */
                        break;
                    default:
                        /*
                        No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        */
                        break;
                }
            break;
        case TEMP_DISPARO:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        /*
                        Deberia cambiar el estado de la alarma y apagar la sirena.
                        */
                        break;
                    default:
                        /*
                        No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        */
                        break;
                }
            break;
        case DISPARADA:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        /*
                        Deberia cambiar el estado de la alarma.
                        */
                        break;
                    case Deteccion_Z1:
                        /*
                        Debe conservar el encendido de la sirena.
                        */
                        break;
                    default:
                        /*
                        No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        */
                        break;
                }
            break;
        default:
            break;
    }
}

void alarma_transicion(Alarma *self, EstadoAlarma NuevoEstado)
{

}

void loop(Alarma *self)
{
    /*
    Debemos detectar las entradas de comandos para poder realizar las transiciones de estado
    */
    alarma_procesaEvento(&self,DESARMAR);
    printf("Hola cabron.\n");
}