/*
 * @file loop.c
 * @author Adan J.A. Lema (adanlema@hotmail.com)
 * @brief Implementación de una alarma 
 */

#include <main.h>
#include "alarma.h"
#include <stm32f1xx.h>
#include <timer_systick.h>

// Clase Indicador: Biestable
typedef struct Indicador
{
    Biestado super;
    const char *etiqueta;
}Indicador;

void Indicador_si(Indicador *self)
{
    printf("Activar [%s]\n",self->etiqueta);
}
void Indicador_no(Indicador *self)
{
    printf("Activar [%s]\n",self->etiqueta);
}
void Indicador_init(Indicador *self, const char *etiqueta)
{
    static const Biestado_VT vt ={
        .si = Indicador_si,
        .no = Indicador_no
    };
    ((Biestado *)self) ->vptr = &vt;
    self->etiqueta = etiqueta;
}

// fin Indicador




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