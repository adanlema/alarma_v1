#include <ejemplo.h>
#include <unity.h>
#include <ticks_systick.h>
#include <ejemplo.h>

static void suma_dos_numeros_34(void)
{    
    TEST_ASSERT_EQUAL_INT32(34,Ejemplo_suma(10,24));
} 

static void suma_dos_numeros_16(void)
{    
    TEST_ASSERT_EQUAL_INT32(16,Ejemplo_suma(8,8));
} 

int main(void)
{
    Ticks_configura_1ms();
    Ticks_esperaMilisegundos(500);
    UNITY_BEGIN();
    RUN_TEST(suma_dos_numeros_34);
    RUN_TEST(suma_dos_numeros_16);
    UNITY_END();   
}