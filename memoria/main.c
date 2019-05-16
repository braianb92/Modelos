#include <stdio.h>
#include <stdlib.h>
#include "alumno.h"
#define QTY_ALUMNO 1000

int main()
{
    Alumno* arrayAlumnos[QTY_ALUMNO];
    Alumno* pAux;
    pAux = alumno_new();
    if(pAux != NULL)
    {
        alumno_setId(pAux,44);
        arrayAlumnos[0] = pAux;
    }


    pAux = alumno_new();
    if(pAux != NULL)
    {
        alumno_setId(pAux,14);
        arrayAlumnos[1] = pAux;
    }

    pAux = alumno_newParametros(11,11100,0,"Juan");
    if(pAux != NULL)
    {
        arrayAlumnos[2] = pAux;
    }
    return 0;
}
