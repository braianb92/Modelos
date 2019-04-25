#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "Empleado.h"

#define LEN_LISTA 4

int main()
{
    Empleado wachin[LEN_LISTA];
    int idEmpleado=1;
    int posLibre;
    int opcion=0;

    Empleado_inicializarArray(wachin,LEN_LISTA);
    while(opcion!=10)
    {
        getIntInRange(&opcion,"\n1)Ingresar\n2)Listar\n3)Modificar con ID\n4)Modificar con Legajo\n5)Baja\n6)Ordenar por Nombre\n"
                      "7)Ordenar por Apellido\n8)Ordenar por Legajo\n9)Ordenar por ID\n10)Salir\n\n    INGRESE OPCION: ","ERROR\n",1,10,3);
        switch(opcion)
        {
            case 1:
            {
                posLibre=Empleado_posLibre(wachin,LEN_LISTA);
                if(posLibre>=0)
                {
                    printf("\n----Se encontro lugar----\n");
                    if(Empleado_alta(wachin,LEN_LISTA,posLibre,idEmpleado,"DATO NO VALIDO\n"))
                    {
                        idEmpleado++;
                        Empleado_mostrarArray(wachin,LEN_LISTA);
                    }
                }
                else
                {
                    printf("\n----No se encontro lugar libre!----\n");
                }
                break;
            }
            case 2:
            {
                Empleado_mostrarArray(wachin,LEN_LISTA);
                break;
            }
            case 3:
            {
                if(Empleado_modifyFromID(wachin,LEN_LISTA,"DATO NO VALIDO\n"))
                {
                    printf("\n----Se modifico exitosamente----\n");
                }
                break;
            }
            case 4:
            {
                if(Empleado_modifyFromLegajo(wachin,LEN_LISTA,"DATO NO VALIDO\n"))
                {
                    printf("\n----Se modifico exitosamente----\n");
                }
                break;
            }
            case 5:
            {
                if(Empleado_bajaLogica(wachin,LEN_LISTA,"DATO NO VALIDO\n"))
                {
                    printf("\n----La BAJA se realizo con exito!----\n");
                }
                break;
            }
            case 6:
            {
                Empleado_ordenarNameAtoZ(wachin,LEN_LISTA);
                printf("----Se ordeno por NOMBRE!----\n");
                break;
            }
            case 7:
            {
                Empleado_ordenarSurnameAtoZ(wachin,LEN_LISTA);
                printf("----Se ordeno por APELLIDO!----\n");
                break;
            }
             case 8:
            {
                Empleado_orderByLegajo(wachin,LEN_LISTA);
                printf("----Se ordeno por LEGAJO!----\n");
                break;
            }
             case 9:
            {
                Empleado_orderByID(wachin,LEN_LISTA);
                printf("----Se ordeno por ID!----\n");
                break;
            }

        }
    }
    return 0;
}
