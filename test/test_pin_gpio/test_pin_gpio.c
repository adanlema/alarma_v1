#include <unity.h>
#include <timer_systick.h>
#include <pin_gpio.h>
#include <stm32f1xx.h>
#include <stdbool.h>

static GPIO_TypeDef miPuerto;
enum {MI_PIN = 13}                                          // Declara una constante como un simbolo, 
// Analogo es poner #define MI_PIN 13, es decir ponerlo como una macro


void setUp(void)                                            // Se definen porque las llaman de unity, sino fallan.
{
    miPuerto = (GPIO_TypeDef) {.CRH=0x44444444, .CRL=0x44444444}

}                                          
void tearDown(void){}                                       // Analogo a lo anterior, aunque no hagan nada hay que definirla.


// Si la funcion es global cuando hacemos los test no nos indicara que no estamos usando esta prueba, pero si nosotros colocamos "static" adelante provoca que el compilador no largue un warning ya que nos indica que no estamos utilizkando esa funcion
static void pin_debePermitirLeerEstado_0(void)
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN);
    const bool estado = Pin_lee(&miPin);                     // Si esta definida dentro de una funcion es una variable loca, no preserva su valor cuando sale de la funcion
    TEST_ASSERT_FALSE(estado);                               // Chequea que sea falso

}

static void pin_debePermitirLeerEstado_1(void)
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN);
    miPuerto.IDR = 1<<MI_PIN;
    
    const bool estado = Pin_lee(&miPin);                     // Si esta definida dentro de una funcion es una variable loca, no preserva su valor cuando sale de la funcion
    TEST_ASSERT_TRUE(estado);                               

}


static void pin_debeColocarUnCeroenSalida(void)
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN);                    // Inicializamos el Pin
    Pin_escribe(&miPin,0);
    const uint32_t reset = miPuerpo.BRR | (miPuerto.BSRR >> 16);
    const uint32_t set   = miPuerto.BSRR & ((1UL << 16) - 1UL);
    enum(RESET_ESPERADO = (1UL << MI_PIN), SET_ESPERADO = 0);
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,reset);
    TEST_ASSERT_EQUAL_HEX32(SET_ESPERADO, set);                                   
}

static void pin_debeColocarUnUnoenSalida(void)
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN);                    // Inicializamos el Pin
    Pin_escribe(&miPin,0);
    const uint32_t reset = miPuerpo.BRR | (miPuerto.BSRR >> 16);
    const uint32_t set   = miPuerto.BSRR & ((1UL << 16) - 1UL);
    enum(RESET_ESPERADO =0 ,SET_ESPERADO= (1UL << MI_PIN));
    
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,reset);                           
    TEST_ASSERT_EQUAL_HEX32(SET_ESPERADO  ,set);
}




int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();                                      // Llamamos a la macro UNITY_BEGIN
    
    RUN_TEST(pin_debePermitirLeerEstado_0);  
    RUN_TEST(pin_debePermitirLeerEstado_1);
    RUN_TEST(pin_debeColocarUnCeroenSalida);
    RUN_TEST(pin_debeColocarUnUnoenSalida);
    
    UNITY_END();   
}