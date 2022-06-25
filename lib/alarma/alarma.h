#ifndef ALARMA_H
#define ALARMA_H
#include <stdbool.h>
#include "biestado.h"

typedef struct Alarma Alarma;

typedef enum{
    Deteccion_Z1, FIN_TEMPORIZACION, ARMAR, DESARMAR
} EventosAlarma;

typedef void (*EstadoAlarma)(Alarma *self, EventosAlarma evento);
/* 
Esta ultima inicilizacion significa que estamos creando tipo de dato EstadoAlarma, el cual es un puntero que apunta
a una funcion, cuya funcion debe cumplir con el argumento colocado. Es decir que guarda la direccion de memoria de
de estas funciones en un tipo de dato EstadoAlarma.
Si llamamos una funcion, por ej adc(void). Si nosotros colocamos directamente su nombre adc; esto nos arroja su direccion
de memoria, es decir que es analogo a &adc; mientras que si colocamos adc() llamamos a la funcion.
Se logro que cada estado de la alarma sea una funcion.
*/



void Alarma_estadoDesarmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento);
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento);
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento);



struct Alarma 
{                             
    EstadoAlarma estado;
    Biestado * indicarActividadZ1;
    Biestado * indicarArmado;
    Biestado * indicarAlarma;
    Biestado * indicarTemporizacion;
}; 


void Alarma_iniciar(Alarma *self, 
                    EstadoAlarma estadoInicial,
                    Biestado * indicarActividadZ1,
                    Biestado * indicarArmado,
                    Biestado * indicarAlarma,
                    Biestado * indicarTemporizacion);

void Alarma_transicion(Alarma *self, EstadoAlarma NuevoEstado);
void Alarma_estadoDesarmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento);
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento);
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento);
void Alarma_procesaEvento(Alarma *self, EventosAlarma evento);




#endif