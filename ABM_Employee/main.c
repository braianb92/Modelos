#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployees.h"
#include "utn_strings.h"
#define LEN 1000
#define TRIES 3


int main()
{
    Employee Empleado[LEN];
    emp_menu(Empleado,LEN,"\n1)Alta\n2)Modificacion\n3)Baja\n"
             "4)Informar\n5)Salir\n",5,TRIES);
    return 0;
}
