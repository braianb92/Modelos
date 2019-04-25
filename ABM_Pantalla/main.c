#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "Pantalla.h"

#define LEN_LISTA 5

int main()
{
    Pantalla visores[LEN_LISTA];
    int idPantallas=1;
    int posLibre;
    int opcion=0;

    Pan_inicializarArray(visores,LEN_LISTA);
    while(opcion!=7)
    {
        getIntInRange(&opcion,"\n1)Ingresar\n2)Listar\n3)Modificar con ID\n4)Baja\n5)Ordenar por Precio\n6)Ordenar por ID\n7)Salir\n\n    INGRESE OPCION: ","ERROR\n",1,7,3);
        switch(opcion)
        {
            case 1:
            {
                posLibre=Pan_posLibre(visores,LEN_LISTA);
                if(posLibre>=0)
                {
                    printf("\n----Se encontro lugar----\n");
                    if(Pan_alta(visores,LEN_LISTA,posLibre,idPantallas,"DATO NO VALIDO\n"))
                    {
                        idPantallas++;
                        Pan_mostrarArray(visores,LEN_LISTA);
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
                Pan_mostrarArray(visores,LEN_LISTA);
                break;
            }
            case 3:
            {
                if(Pan_modifyFromID(visores,LEN_LISTA,"DATO NO VALIDO\n"))
                {
                    printf("\n----Se modifico exitosamente----\n");
                }
                break;
            }
            case 4:
            {
                if(Pan_bajaLogica(visores,LEN_LISTA,"DATO NO VALIDO\n"))
                {
                    printf("\n----La BAJA se realizo con exito!----\n");
                }
                break;
            }
            case 5:
            {
                Pan_orderByPrice(visores,LEN_LISTA);
                printf("----Se ordeno por PRECIO!----\n");
                break;
            }
            case 6:
            {
                Pan_orderByID(visores,LEN_LISTA);
                printf("----Se ordeno por ID!----\n");
                break;
            }
        }
    }
    return 0;
}
