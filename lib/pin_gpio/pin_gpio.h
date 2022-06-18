#ifndef PIN_GPIO_H
#define PIN_GPIO_H
#include <stm32f1xx.h>
#include <stdbool.h>


// Debemos inicializar el pin que debemos probar
typedef struct Pin {                                    // La etiqueta la usamos para colocar un nombre en la estructura, sino se coloca su nombre la trata como anonima
    //int foo;                                          // Creamos una variable ya que no debe esta vacio, foo se usa normalmente es que no hace nada
    GPIO_TypeDef *puerto;
    int pin;
} Pin; 
// Si colocamos este tipo de etiquena nos permite declarar directamente las variables del tipo Pin

void Pin_init(Pin *self, GPIO_TypeDef *puerto, int pin);
bool Pin_lee(Pin *self);
void Pin_escribe(Pin *self, bool valor);
void Pin_Modo(Pin *self, int modo);


#endif