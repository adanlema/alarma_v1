#include "alarma.h"

void Alarma_iniciar(Alarma *self, 
                    EstadoAlarma estadoInicial,
                    Biestado * indicarActividadZ1,
                    Biestado * indicarArmado,
                    Biestado * indicarAlarma,
                    Biestado * indicarTemporizacion)
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
                    Biestado_si(self->indicarActividadZ1);
                    break;
                case ARMAR:
                    Biestado_si(self->indicarTemporizacion);
                    Alarma_transicion(self,Alarma_estadoTempArmado);
                    break;
                default:
                    break;
            }
}
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        Biestado_si(self->indicarActividadZ1);
                        break;
                    case DESARMAR:
                        Biestado_no(self->indicarArmado);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        self->indicarArmado(true);
                        Alarma_transicion(self,Alarma_estadoArmada);
                        break;
                    default:
                        break;
                }
}
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        Biestado_si(self->indicarActividadZ1);
                        Alarma_transicion(self,Alarma_estadoTempDisparo);
                        break;
                    case DESARMAR:
                        Biestado_no(self->indicarArmado);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        Biestado_si(self->indicarAlarma);
                        Alarma_transicion(self,Alarma_estadoDisparada);
                        break;
                    default:
                        break;
                }
}
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento)
{
    switch (evento)
                {
                    case Deteccion_Z1:
                        Biestado_si(self->indicarActividadZ1);
                        break;
                    case DESARMAR:
                        Biestado_no(self->indicarArmado);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        Biestado_si(self->indicarAlarma);
                        Alarma_transicion(self,Alarma_estadoDisparada);
                        break;
                    default:
                        break;
                }
}
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento)
{
switch (evento)
                {
                    case Deteccion_Z1:
                        Biestado_si(self->indicarAlarma);
                        break;
                    case DESARMAR:
                        Biestado_no(self->indicarArmado);
                        Alarma_transicion(self,Alarma_estadoDesarmada);
                        break;
                    case FIN_TEMPORIZACION:
                        Biestado_no(self->indicarAlarma);
                        Alarma_transicion(self,Alarma_estadoArmada);
                        break;
                    default:
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