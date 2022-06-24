/*
 * @file loop.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */

#include <main.h>
#include <stm32f1xx.h>
#include <timer_systick.h>

void Alarma_iniciar(Alarma *self, 
                    EstadoAlarma estadoInicial,
                    Indicar indicarActividadZ1,
                    Indicar indicarArmado,
                    Indicar indicarAlarma,
                    Indicar indicarTemporizacion)
{
    printf("Iniciliazando alarma...\n");
    self->estado = estadoInicial;
    self->indicarActividadZ1 = indicarActividadZ1;
    self->indicarArmado = indicarArmado;
    self->indicarAlarma = indicarAlarma;
    self->indicarTemporizacion = indicarTemporizacion;
}


void Alarma_transicion(Alarma *self, EstadoAlarma NuevoEstado)
{
    self->estado = NuevoEstado;
}


void Alarma_estadoDesarmada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
            {
                case Deteccion_Z1:
                    self->indicarActividadZ1(true);
                    break;
                case ARMAR:
                    self->indicarTemporizacion(true);
                    Alarma_transicion(self,Alarma_estadoTempArmado);
                    break;
                default:
                    printf("Ignorado...");
                    break;
            }
}
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        self->indicarActividadZ1(true);
                        break;
                    case DESARMAR:
                        self->indicarArmado(false);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        self->indicarArmado(true);
                        Alarma_transicion(self,Alarma_estadoArmada);
                        break;
                    default:
                        printf("Ignorado...\n");
                        break;
                }
}
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        self->indicarActividadZ1(true);
                        Alarma_transicion(self,Alarma_estadoTempDisparo);
                        break;
                    case DESARMAR:
                        self->indicarArmado(false);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        self->indicarAlarma(true);
                        Alarma_transicion(self,Alarma_estadoDisparada);
                        break;
                    default:
                        printf("Ignorado...\n");
                        break;
                }
}
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        self->indicarActividadZ1(true);
                        break;
                    case DESARMAR:
                        self->indicarArmado(false);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        self->indicarAlarma(true);
                        Alarma_transicion(self,Alarma_estadoDisparada);
                        break;
                    default:
                        printf("Ignorado...\n");
                        break;
                }
}
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento)
{
switch (evento)
                {
                    case Deteccion_Z1:
                        self->indicarAlarma(true);
                        break;
                    case DESARMAR:
                        self->indicarArmado(false);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        self->indicarAlarma(false);
                        Alarma_transicion(self,Alarma_estadoArmada);
                        break;
                    default:
                        printf("Ignorado...\n");
                        break;
                }
}

void Alarma_procesaEvento(Alarma *self, EventosAlarma evento)
{
    self->estado(self,evento);
    /*
    Como self->estado es un puntero a una funcion, entonces si lo llamo puedo llamar directamente a la funcion
    que apunta el estado. Otra manera analoga de hacer esto es:
    (*self->estado)(self,evento);
    Esto lo podemos hacer ya que estado es un puntero que llama a una funcion. Ademas esto es rapido, porque si nos fijamos
    directamente hace un llamado a un evento, no controla todos los eventos, sino solo el que apunta la funcion.
    */
}

static void ind_actividadZ1(bool indicacion)
{
    if(indicacion)    printf("Z1!\n");
}
static void ind_armado(bool indicacion)
{
    if (indicacion)   printf("Armada\n");
    else              printf("Desarmando...\n");
}
static void ind_alarma(bool indicacion)
{
    if (indicacion)   printf("Disparada!!\n");
    else              printf("Deja de sonar...\n");
}
static void ind_temporizacion(bool indicacion)
{
    if(indicacion)    printf("Temporizar\n");
}


void loop(Alarma *self)
{
    Alarma_iniciar (self,Alarma_estadoDesarmada,
                        ind_actividadZ1,
                        ind_armado,
                        ind_alarma,
                        ind_temporizacion);
                        
    Alarma_procesaEvento(self,Deteccion_Z1);
    Alarma_procesaEvento(self,ARMAR);
    Alarma_procesaEvento(self,Deteccion_Z1);
    Alarma_procesaEvento(self,FIN_TEMPORIZACION);
    Alarma_procesaEvento(self,Deteccion_Z1);
    Alarma_procesaEvento(self,FIN_TEMPORIZACION);
    Alarma_procesaEvento(self,FIN_TEMPORIZACION);
    Alarma_procesaEvento(self,Deteccion_Z1);
    Alarma_procesaEvento(self,DESARMAR);
}