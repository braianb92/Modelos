#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "orquesta.h"
#include "instrumento.h"
#include "musico.h"
#include "informes.h"

#define REINTENTOS 3
#define LEN_ORQUESTA 50
#define LEN_INSTRUMENTO 20
#define LEN_MUSICO 1000
int main()
{
    Orquesta orquestas[LEN_ORQUESTA];
    Instrumento instrumentos[LEN_INSTRUMENTO];
    Musico musicos[LEN_MUSICO];
    int removedOrquestaID;
    int option=0;
    //MODIFICAR PARA LA PRE-CARGA.
    int flagAltaOrquesta=1;
    int contadorOrquesta=4;
    int flagAltaInstrumento=1;
    int contadorInstrumento=5;
    int flagAltaMusico=1;
    int contadorMusico=6;
    //INICIALIZACION.
    orquesta_initOrquesta(orquestas,LEN_ORQUESTA);
    instrumento_initInstrumento(instrumentos,LEN_INSTRUMENTO);
    musico_initMusico(musicos,LEN_MUSICO);
    //PRE-CARGAS.
    orquesta_preCarga(orquestas,LEN_ORQUESTA,1,"Orquesta1","Lugar1",1);
    orquesta_preCarga(orquestas,LEN_ORQUESTA,2,"Orquesta2","Lugar1",2);
    orquesta_preCarga(orquestas,LEN_ORQUESTA,3,"Orquesta3","Lugar2",3);
    orquesta_preCarga(orquestas,LEN_ORQUESTA,4,"Orquesta4","Lugar3",3);
    instrumento_preCarga(instrumentos,LEN_INSTRUMENTO,1,"Inst1",1);
    instrumento_preCarga(instrumentos,LEN_INSTRUMENTO,2,"Inst2",2);
    instrumento_preCarga(instrumentos,LEN_INSTRUMENTO,3,"Inst3",2);
    instrumento_preCarga(instrumentos,LEN_INSTRUMENTO,4,"Inst4",3);
    instrumento_preCarga(instrumentos,LEN_INSTRUMENTO,5,"Inst4",4);
    musico_preCarga(musicos,LEN_MUSICO,1,"Mus1","Amus1",30,1,2);
    musico_preCarga(musicos,LEN_MUSICO,2,"Mus2","Amus2",20,2,5);
    musico_preCarga(musicos,LEN_MUSICO,3,"Mus3","Amus3",25,4,2);
    musico_preCarga(musicos,LEN_MUSICO,4,"Mus4","Amus4",27,4,1);
    musico_preCarga(musicos,LEN_MUSICO,5,"Mus5","Amus5",22,1,3);
    musico_preCarga(musicos,LEN_MUSICO,6,"Mus6","Amus6",35,3,4);
    while(option!=14)
    {
        printf("\n1)Alta Orquesta\n2)Baja Orquesta\n3)Modificar Orquesta\n"
                "4)Imprimir Orquesta\n\n5)Alta Musico\n6)Baja Musico\n"
                "7)Modificacion Musico\n8)Imprimir Musico\n\n9)Alta Instrumento\n"
                "10)Baja Instrumento\n11)Modificar Instrumento\n12)Imprimir Instrumento\n"
                "\n13-INFORMES\n14)SALIR\n");
        getIntInRange(&option,"\n   Ingrese Opcion: ","\nDATO NO VALIDO\n",
                    1,14,REINTENTOS);
        switch(option)
        {
            case 1:
                if(!orquesta_addOrquesta(orquestas,LEN_ORQUESTA,"\nDATO NO VALIDO\n",REINTENTOS))
                {
                    printf("\n--Se dio de alta correctamente--\n");
                    flagAltaOrquesta=1;
                    contadorOrquesta++;
                }
                else
                {
                    printf("\n--No se dio de alta!\n");
                }
                break;
            case 2:
                if(flagAltaOrquesta)
                {
                    orquesta_printOrquesta(orquestas,LEN_ORQUESTA);
                    if(!orquesta_removeOrquesta(orquestas,LEN_ORQUESTA,
                        "\nDATO NO VALIDO\n",REINTENTOS,&removedOrquestaID))
                    {
                        if(!musico_removeMusicoApartirDeOrquesta(musicos,LEN_MUSICO,removedOrquestaID))
                        {
                            contadorMusico--;
                            if(contadorMusico==0)
                            {
                                flagAltaMusico=0;
                            }
                        }
                        printf("\n--Se dio de baja la orquesta junto a sus musicos--\n");
                        contadorOrquesta--;
                        if(contadorOrquesta==0)
                        {
                            flagAltaOrquesta=0;
                        }
                    }
                }
                else
                {
                    printf("\nNO HAY ORQUESTAS EN LA NOMINA\n");
                }
                break;
            case 3:
                if(flagAltaOrquesta)
                {
                    if(!orquesta_alter(orquestas,LEN_ORQUESTA,
                        "\nDATO NO VALIDO\n",4,REINTENTOS))
                    {
                        printf("\n--Se modifico correctamente--\n");
                    }
                }
                else
                {
                    printf("\nNO HAY ORQUESTAS EN LA NOMINA\n");
                }
                break;
            case 4:
                if(flagAltaOrquesta)
                {
                    orquesta_printOrquesta(orquestas,LEN_ORQUESTA);
                }
                else
                {
                    printf("\nNO HAY ORQUESTAS EN LA NOMINA\n");
                }
                break;
            case 5:
                if(flagAltaOrquesta&&flagAltaInstrumento)
                {
                    orquesta_printOrquesta(orquestas,LEN_ORQUESTA);
                    instrumento_printInstrumento(instrumentos,LEN_INSTRUMENTO);
                    if(!musico_addMusico(musicos,orquestas,instrumentos,LEN_MUSICO,LEN_ORQUESTA,
                        LEN_INSTRUMENTO,"\nDATO NO VALIDO\n",REINTENTOS))
                {
                    printf("\n--Se dio de alta correctamente--\n");
                    flagAltaMusico=1;
                    contadorMusico++;
                }
                }
                else
                {
                    printf("\n--NO HAY ORQUESTAS/INSTRUMENTOS EN LA NOMINA!--\n");
                }
                break;
            case 6:
                if(flagAltaMusico)
                {
                    musico_printMusicoBasic(musicos,LEN_MUSICO);
                    if(!musico_removeMusico(musicos,LEN_MUSICO,"\nDATO NO VALIDO\n",REINTENTOS))
                    {
                       printf("\n--Se dio de baja correctamente--\n");
                       contadorMusico--;
                       if(contadorMusico==0)
                       {
                            flagAltaMusico=0;
                       }
                    }
                }
                else
                {
                    printf("\nNO HAY MUSICOS EN LA NOMINA\n");
                }
                break;
            case 7:
                if(flagAltaMusico)
                {
                    musico_printMusicoBasic(musicos,LEN_MUSICO);
                    if(!musico_alter(musicos,orquestas,LEN_MUSICO,LEN_ORQUESTA,
                        "\nDATO NO VALIDO\n",3,REINTENTOS))
                    {
                        printf("\n--Se modifico correctamente--\n");
                    }
                }
                else
                {
                    printf("\nNO HAY MUSICOS EN LA NOMINA\n");
                }
                break;
            case 8:
                if(flagAltaMusico)
                {
                    musico_printMusico(musicos,instrumentos,LEN_MUSICO,LEN_INSTRUMENTO);
                }
                else
                {
                    printf("\nNO HAY MUSICOS EN LA NOMINA\n");
                }
                break;
            case 9:
                if(!instrumento_addInstrumento(instrumentos,LEN_INSTRUMENTO,"\nDATO NO VALIDO\n",
                    REINTENTOS))
                {
                    printf("\n--Se dio de alta correctamente--\n");
                    flagAltaInstrumento=1;
                    contadorInstrumento++;
                }
                break;
            case 10:
                if(flagAltaInstrumento)
                {
                    instrumento_printInstrumento(instrumentos,LEN_INSTRUMENTO);
                    if(!instrumento_removeInstrumento(instrumentos,LEN_INSTRUMENTO,
                    "\nDATO NO VALIDO\n",REINTENTOS))
                    {
                       printf("\n--Se dio de baja correctamente--\n");
                       contadorInstrumento--;
                       if(contadorInstrumento==0)
                       {
                            flagAltaInstrumento=0;
                       }
                    }
                }
                else
                {
                    printf("\nNO HAY INSTRUMENTOS EN LA NOMINA\n");
                }
                break;
            case 11:
                if(flagAltaInstrumento)
                {
                    instrumento_printInstrumento(instrumentos,LEN_INSTRUMENTO);
                    if(!instrumento_alter(instrumentos,LEN_INSTRUMENTO,"\nDATO NO VALIDO\n",3,
                    REINTENTOS))
                    {
                        printf("\n--Se modifico correctamente--\n");
                    }
                }
                else
                {
                    printf("\nNO HAY INSTRUMENTOS EN LA NOMINA\n");
                }
                break;
            case 12:
                if(flagAltaInstrumento)
                {
                    instrumento_printInstrumento(instrumentos,LEN_INSTRUMENTO);
                }
                else
                {
                    printf("\nNO HAY INSTRUMENTOS EN LA NOMINA\n");
                }
                break;
            case 13:
                informe_menu(orquestas,musicos,instrumentos,LEN_ORQUESTA,LEN_MUSICO,LEN_INSTRUMENTO,
                             9,REINTENTOS);
                break;
        }
    }
    return 0;
}
