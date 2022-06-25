#ifndef MAIN_H
#define MAIN_H
#include <stdint.h>
#include <stdbool.h>
#include "alarma.h"
#include <timer_systick.h>
#include "biestado.h"

void setup(void);
void loop(Alarma *self);

#endif
