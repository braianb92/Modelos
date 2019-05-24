#include <stdio.h>
#include <stdlib.h>
#include "alumno.h"
#define QTY_ARRAYPER 100

int main()
{
    Persona* arrayPersona[QTY_ARRAYPER];
    per_initArray(arrayPersona,QTY_ARRAYPER);
    per_addPersona(arrayPersona,QTY_ARRAYPER,"aaa",3);


    return 0;
}
