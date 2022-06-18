/*
 * @file loop.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */

#include <main.h>
#include <stm32f1xx.h>
#include <timer_systick.h>

void alarma_transicion(Alarma *self, EstadoAlarma NuevoEstado)
{
    /*
     *  Debemos realizar una cola donde se vayan apilando las transiciones, es decir que no
     *  sucedan instantaneamente, sino con un retardo. Este retardo nos permite estabilizar
     *  el cambio que se producira.
     */
}

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
                    alarma_transicion(&self,TEMP_ARMADO);
                    break;
                default:
                    break;
            }
            break;
        case TEMP_ARMADO:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Se cancelo la activacion de la alarma...\n");
                        alarma_transicion(&self,DESARMADA);
                        break;
                    case FIN_TEMPORIZACION:
                        alarma_transicion(&self,ARMADA);
                        break;
                    default:
                        // No realiza ninguna actividad
                        break;
                }
            break;
        case ARMADA:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        alarma_transicion(&self,DESARMADA);
                        break;
                    case Deteccion_Z1:
                        printf("Movimiento detectado en la Zona1!");
                        // Debera enviar un mensaje para que quede registrado
                        alarma_transicion(&self,DISPARADA);
                        break;
                    default:
                        // No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        break;
                }
            break;
        case TEMP_DISPARO:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        alarma_transicion(&self,DESARMADA);
                        break;
                    default:
                        // No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        break;
                }
            break;
        case DISPARADA:
            switch (evento)
                {
                    case DESARMAR:
                        printf("Alarma desactivada...\n");
                        alarma_transicion(&self,DESARMADA);
                        break;
                    case Deteccion_Z1:
                        // Debe conservar el encendido de la sirena.
                        break;
                    default:
                        // No realiza ninguna actividad si no se encuentra en algun comando anterior.
                        break;
                }
            break;
        default:
            break;
    }
}

void control_entrada(void)
{
    /*  Debemos controlar las entradas que entran a nuestro sistema programa. 
     *  Debemos emplear la lectura del registro IDR.
     */
}

void loop(Alarma *self)
{
    /*
    Debemos detectar las entradas de comandos para poder realizar las transiciones de estado
    */
    control_entrada();
    alarma_procesaEvento(&self,DESARMAR);
    printf("Hola cabron.\n");
}