#include <pin_gpio.h>


void Pin_init(Pin *self, GPIO_TypeDef *puerto, int pin)
{
    self->puerto = puerto;
    self->pin = pin; 
}


bool Pin_lee(Pin *self)
{
    return (bool) (self->puerto->IDR & (1 << self->pin));
}

void Pin_escribe(Pin *self, bool valor)
{
    if(valor)
        self->puerto->BSRR = (1 << self->pin);
    else
        self->puerto->BRR  = (1 << self->pin);
}

void Pin_Modo(Pin *self, int modo)
{
    uint32_t MASK = 0xF;
    if (self->pin > 8){
        uint32_t R_CRH = (self->puerto->CRH & !(MASK << (self->pin - 8UL)));
        self->puerto->CRH = R_CRH;
        }
    else {
        uint32_t R_CRL = (self->puerto->CRL & !(MASK << self->pin));
        self->puerto->CRL = R_CRL;
    }
}




