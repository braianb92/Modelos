#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "Pantalla.h"
#include "Publicidad.h"
#define REINTENTOS 3
#define LEN_LISTA 5

int main()
{
    Pantalla screen[LEN_LISTA];
    Publicidad publi[LEN_LISTA];
    int flag=0;
    int posLibre;
    int opcion=0;

    pan_initPantalla(screen,LEN_LISTA);
    pub_initPublicidad(publi,LEN_LISTA);
    while(opcion!=10)
    {
        getIntInRange(&opcion,"\n1)Alta de pantalla\n2)Modificar datos de pantalla\n3)Baja de pantalla\n"
                      "4)Contratar Publicidad\n5)Modificar condiciones de publicidad\n8)Listar Contrataciones\n9)Listar Pantallas\n10)Salir\n"
                          "INGRESE OPCION: ","ERROR\n",1,10,3);
        switch(opcion)
        {
            case 1:
            {
                posLibre=pan_findFree(screen,LEN_LISTA);
                if(posLibre>=0)
                {
                    printf("\n----Se encontro lugar----\n");
                    if(!pan_addPan(screen,LEN_LISTA,posLibre,"DATO NO VALIDO\n",REINTENTOS))
                    {
                        flag=1;
                        printf("\n----Se dio de ALTA exitosamente!----\n");
                    }
                    else
                    {
                        printf("\n----No se realizo el ALTA!----\n");
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
                if(flag)
                {
                    if(pan_alter(screen,LEN_LISTA,"DATO NO VALIDO\n",REINTENTOS))
                    {
                        printf("\n----Se modifico exitosamente----\n");
                    }
                }
                else
                {
                    printf("\n----No hay ALTAS en la NOMINA!----\n");
                }
                break;
            }
            case 3:
            {
                if(flag)
                {
                    if(pan_removePantalla(screen,LEN_LISTA,"DATO NO VALIDO\n",REINTENTOS))
                    {
                        printf("\n----La BAJA se realizo con exito!----\n");
                    }
                }
                else
                {
                    printf("\n----No hay ALTAS en la NOMINA!----\n");
                }
                break;
            }
            case 4:
            {
                if(flag)
                {
                    pan_printPantalla(screen,LEN_LISTA);
                    if(!pub_addPub(publi,screen,LEN_LISTA,"\nDATO NO VALIDO\n",REINTENTOS))
                    {
                        printf("\n----La CONTRATACION se realizo con exito!----\n");
                    }
                    else
                    {
                        printf("\n----No pudo CONTRATARSE la pantalla!----\n");
                    }
                }
                else
                {
                    printf("\n----No hay PANTALLAS en la NOMINA!----\n");
                }
                break;
            }
            case 5:
                {
                    if(flag)
                    {
                        pub_alterContratacion(publi,screen,LEN_LISTA,"\nDATO NO VALIDO\n",REINTENTOS);
                    }
                    else
                    {
                        printf("\n----No hay PANTALLAS en la NOMINA!----\n");
                    }
                    break;
                }
            case 8:
            {
                pub_printContrataciones(publi,screen,LEN_LISTA,LEN_LISTA);
                break;
            }
            case 9:
            {
                pan_printPantalla(screen,LEN_LISTA);
                break;
            }
        }
    }
    return 0;
}
