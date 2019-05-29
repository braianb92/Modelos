#include <stdio.h>
#include <stdlib.h>
#include "persona.h"
#define QTY_ARRAYPER 100

int main()
{
    Persona* arrayPersona[QTY_ARRAYPER];
    persona_initArray(arrayPersona,QTY_ARRAYPER);
    persona_addPersona(arrayPersona,QTY_ARRAYPER,"\nDATO NO VALIDO\n",3);


    return 0;
}
