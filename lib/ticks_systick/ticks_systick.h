#ifndef TICKS_SYSTICK_H
#define TICKS_SYSTICK_H
#include <stdint.h>

typedef enum Ticks_Result {TICKS_OK,TICKS_ERROR} Ticks_Result;

uint32_t Ticks_getTicks(void);

Ticks_Result Ticks_configura_1ms(void);
void Ticks_esperaMilisegundos(uint32_t tiempo);

#endif