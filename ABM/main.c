#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Empleado.h"
#include "utn_strings.h"
#define LEN 4
#define TRIES 3


int main()
{
    Employee Empleado[LEN];
    int posLibre;
    float promedio;
    float totalSueldos;
    int employeeOverPromedio;
    char seguir='s';
    int opcion=0;
    int flag=0;

    emp_initEmployees(Empleado,LEN);
    while(seguir=='s')
    {
        printf("\n1- Alta\n");
        printf("2- Modificacion\n");
        printf("3- Baja\n");
        printf("4- Informar\n");
        printf("5- Salir\n");

        getIntInRange(&opcion,"\n   INGRESE OPCION: ","DATO NO VALIDO\n",1,5,TRIES);
        switch(opcion)
        {
            case 1:
                posLibre=emp_findFree(Empleado,LEN);
                if(posLibre!=-1)
                {
                    printf("\n----Se encontro posicion libre!----\n");
                    if(!emp_addEmployees(Empleado,LEN,posLibre,"\nDATO NO VALIDO\n",TRIES))
                    {
                        flag=1;
                        printf("\n----Alta satisfactoria!----\n");
                    }
                    else
                    {
                        printf("\n----No se realizo el Alta----\n");
                    }
                }
                else
                {
                    printf("\n----No se encontro posicion libre!----\n");
                }
                break;
            case 2:
                if(flag)
                {
                    if(!emp_alter(Empleado,LEN,"\nDATO NO VALIDO\n",TRIES))
                    {
                        printf("\n----Se modifico exitosamente!----\n");
                    }
                }
                else
                {
                    printf("\n----AUN NO HAY EMPLEADOS EN LA NOMINA!----\n");
                }
                break;
            case 3:
                if(flag)
                {
                    if(!emp_removeEmployee(Empleado,LEN,"\nDATO NO VALIDO\n",TRIES))
                    {
                        printf("\n----Se dio de baja exitosamente!----\n");
                    }
                }
                else
                {
                    printf("\n----AUN NO HAY EMPLEADOS EN LA NOMINA!----\n");
                }
                break;
            case 4:
                emp_printEmployees(Empleado,LEN);
                emp_totalPromedio(Empleado,LEN,&totalSueldos,&promedio);
                emp_salaryOverPromedio(Empleado,LEN,promedio,&employeeOverPromedio);
                printf("\nEL TOTAL DE SALARIOS ES: %.2f\n",totalSueldos);
                printf("\nEL PROMEDIO DE SALARIOS ES: %.2f\n",promedio);
                printf("\nLOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",employeeOverPromedio);
                break;
            case 5:
                seguir = 'n';
                break;
        }
    }

    return 0;
}
