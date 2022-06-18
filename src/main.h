#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>
#include <timer_systick.h>


typedef enum {
    DESARMADA,
    TEMP_ARMADO,
    ARMADA,
    TEMP_DISPARO,
    DISPARADA
} EstadoAlarma;

typedef enum{
    Deteccion_Z1,
    FIN_TEMPORIZACION,
    ARMAR,
    DESARMAR
} EventosAlarma; 

typedef struct Alarma {                             
    EstadoAlarma estado;
} Alarma; 


void iniciar_alarma(Alarma *self, EstadoAlarma estadoInicial);
void setup(Alarma *self);
void loop(Alarma *self);
void control_alarma();



#endif
