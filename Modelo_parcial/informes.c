#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "informes.h"
#include "utn_strings.h"
#define TIPO_INST_CUERDA 1
#define TIPO_INST_V_MAD 2
#define TIPO_INST_V_MET 3
#define TIPO_INST_PERCUSION 4
#define TIPO_ORQ_SINFO 1
#define TIPO_ORQ_FILARM 2
#define TIPO_ORQ_CAMARA 3

/** \brief  Menu to be printed with the appropriate
*           functions to call within.
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    arrayMusico Musico* Pointer to array of musico
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    lenOrquesta orquesta array lenght
* \param    lenMusico musico array lenght
* \param    lenInstrumento instrumento array lenght
* \param    exitMenuNumber int Number that exits the menu
            and also used as max number to be stablish a range
            of menu options to acces the corresponding function.
* \param    tries Number of tries in case of type mistakes.
* \return   int Return 0.
* */
int informe_menu(Orquesta* arrayOrquesta,Musico* arrayMusico,Instrumento* arrayInstrumento,
                 int lenOrquesta,int lenMusico,int lenInstrumento,int exitMenuNumber,int tries)
{
    int option=0;

    while(option!=exitMenuNumber)
    {
        printf("\n1-Orquesta con mas de 5 musicos(A)\n2-Musicos mas de 30(B)\n"
               "3-Orquestas lugar particular(C)\n4-Orquesta Completa(D)\n"
               "5-Listar Musico por Orquesta determinada(E)\n"
               "6-Orquesta con mas musicos(F)\n7-Musicos instrumentos de cuerda(G)\n"
               "8-Imprimir promedio de musicos por Orquestas(H)\n9-Atras (menu principal)\n");

        getIntInRange(&option,"\n   INGRESE OPCION: ","\nNO\n",1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                informe_orquestaConMasde5Musicos(arrayOrquesta,arrayMusico,lenOrquesta,lenMusico);
                break;
            case 2:
                informe_edadMusicoMasDe30(arrayMusico,arrayInstrumento,arrayOrquesta,
                                          lenInstrumento,lenMusico,lenOrquesta);
                break;
            case 3:
                informe_printOrquestasByLugarDeterminado(arrayOrquesta,lenOrquesta);
                break;
            case 4:
                informe_orquestaCompleta(arrayOrquesta,arrayInstrumento,arrayMusico,lenOrquesta,lenInstrumento,
                                         lenMusico);
                break;
            case 5:
                informe_printMusicosByOrquestaDeterminada(arrayMusico,arrayOrquesta,arrayInstrumento,lenMusico,lenOrquesta,
                                                          lenInstrumento,"\nERROR\n");
                break;
            case 6:
                informe_orquestaConMasMusicos(arrayOrquesta,arrayMusico,lenOrquesta,lenMusico);
                break;
            case 7:
                informe_printMusicoSoloCuerda(arrayMusico,arrayInstrumento,lenMusico,
                                              lenInstrumento);
                break;
            case 8:
                informe_promedioMusicosPorOrquesta(arrayMusico,arrayOrquesta,lenMusico,lenOrquesta);
                break;
        }
    }
    return 0;
}

//INFORME A
/** \brief  Print orquestas that have five or more musicians
*           with all the proper information.
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    arrayMusico Musico* Pointer to array of musico
* \param    lenOrquesta orquesta array lenght
* \param    lenMusico musico array lenght
* \return   returns 0
*
*/
int informe_orquestaConMasde5Musicos (Orquesta* arrayOrquesta,Musico* arrayMusico,
                                   int lenOrquesta,int lenMusico)
{
    int i;
    int posIdOrquesta;
    char stringTipo[30];
    int orquestaAnterior=0;
    int contadorOrquesta=0;

    musico_sortMusicosByIdOrquestaEficiente(arrayMusico,lenMusico,1);
    for(i=0;i<lenMusico;i++)
    {
        if(arrayMusico[i].isEmpty==0)
        {
            posIdOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,arrayMusico[i].idOrquesta);
            if(orquestaAnterior==posIdOrquesta)
            {
                contadorOrquesta++;
            }
            else
            {
                contadorOrquesta--;
            }
            orquestaAnterior=posIdOrquesta;
            if(contadorOrquesta>=5)
            {
                switch(arrayOrquesta[posIdOrquesta].tipo)
                {
                    case 1:
                        strncpy(stringTipo,"Sinfonica",sizeof(stringTipo));
                        break;
                    case 2:
                        strncpy(stringTipo,"Filarmonica",sizeof(stringTipo));
                        break;
                    case 3:
                        strncpy(stringTipo,"Camara",sizeof(stringTipo));
                        break;
                }
                printf("\nID orquesta: %d\nNombre: %s\n"
                       "Tipo: %s\nLugar: %s",
                       arrayOrquesta[posIdOrquesta].idOrquesta,
                       arrayOrquesta[posIdOrquesta].name,
                       stringTipo,
                       arrayOrquesta[posIdOrquesta].lugar);
            }
        }
    }
    printf("\nNo se encontraron Orquestas\n");
    return 0;
}

//INFORME B
/** \brief  Print all the muscicians in the array
*           that are over 30 years old.
* \param    arrayMusico Musico* Pointer to array of musico
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \param    lenOrquesta orquesta array lenght
* \return   int Return 0.
* */
int informe_edadMusicoMasDe30(Musico* arrayMusico,Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,
                              int lenInstrumento,int lenMusico,int lenOrquesta)
{
    int i;
    int posIdInstrumento;
    int posIdOrquesta;
    if(arrayMusico!=NULL && lenMusico>=0)
    {
        musico_sortMusicoByEdad(arrayMusico,lenMusico,1);
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0&&arrayMusico[i].edad>30)
            {
                posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                posIdOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,arrayMusico[i].idOrquesta);
                printf("\nID Musico: %d\nNombre: %s\n"
                       "Apellido: %s\nEdad: %d\n"
                       "Nombre Orquesta: %s\n"
                       "Nombre Instrumento: %s\n",
                       arrayMusico[i].idMusico,
                       arrayMusico[i].name,
                       arrayMusico[i].surname,
                       arrayMusico[i].edad,
                       arrayOrquesta[posIdOrquesta].name,
                       arrayInstrumento[posIdInstrumento].name);
            }

        }
    }
    return 0;
}
//INFORME C
/** \brief  Asks the user to type an orquesta place
*           and prints all the matching orquestas
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenOrquesta orquesta array lenght
* \return   int Return 0 if OK; return -1 if wrong
* */
int informe_printOrquestasByLugarDeterminado(Orquesta* arrayOrquesta,int lenOrquesta)
{
    int i;
    char bufferLugar[32];
    char stringTipo[30];
    int flag=1;
    int retorno=-1;

    if(!getStringAlphanumeric(bufferLugar,"\nIngrese lugar: ","\nERROR.\n",3))
    {
        for(i=0;i<lenOrquesta;i++)
        {
            if(strcmp(bufferLugar,arrayOrquesta[i].lugar)==0)
            {
                switch(arrayOrquesta[i].tipo)
                    {
                       case 1:
                        strncpy(stringTipo,"Sinfonica",sizeof(stringTipo));
                        break;
                    case 2:
                        strncpy(stringTipo,"Filarmonica",sizeof(stringTipo));
                        break;
                    case 3:
                        strncpy(stringTipo,"Camara",sizeof(stringTipo));
                        break;
                    }
                    printf("\nID de Orquesta: %d\nNombre: %s\nTipo: %s\nLugar: %s"
                           "\n-------\n",
                           arrayOrquesta[i].idOrquesta,
                           arrayOrquesta[i].name,
                           stringTipo,
                           arrayOrquesta[i].lugar);
                           flag=0;
                           retorno=0;
            }
        }
        if(flag)
        {
            printf("\nNo se encontro el lugar\n");
            retorno=0;
        }
    }
    return retorno;
}

//INFORME D
/** \brief  Prints all the orquestas that have 5 or more
*           musicians assigned a type 1 instrument (cuerda),
*           3 muscicians assigned a type 2 or 3 instrument (viento),
*           and 2 muscicians assigned a type 4 instrument (percusion).
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayMusico Musico* Pointer to array of musico
* \param    lenOrquesta orquesta array lenght
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \return   int Return 0 if OK; return -1 if wrong
* */
int informe_orquestaCompleta(Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,Musico* arrayMusico,
                             int lenOrquesta,int lenInstrumento,int lenMusico)
{
    int i;
    int cantidadInstCuerda;
    int cantidadInstViento;
    int cantidadInstPercusion;
    int flag=1;
    int retorno=-1;

    if(arrayOrquesta!=NULL&&arrayInstrumento!=NULL
       &&lenOrquesta>0&&lenInstrumento>0)
    {

        for(i=0;i<lenOrquesta;i++)
        {
            informe_cantInstCuerdaEnOrquestaEspecifica(arrayInstrumento,arrayOrquesta,arrayMusico,
                                                       lenInstrumento,lenMusico,i,&cantidadInstCuerda);
            informe_cantInstVientosEnOrquestaEspecifica(arrayInstrumento,arrayOrquesta,arrayMusico,
                                                       lenInstrumento,lenMusico,i,&cantidadInstViento);
            informe_cantInsPercusionEnOrquestaEspecifica(arrayInstrumento,arrayOrquesta,arrayMusico,
                                                       lenInstrumento,lenMusico,i,&cantidadInstPercusion);
            if((cantidadInstCuerda>=5)&&(cantidadInstViento==3)&&(cantidadInstPercusion==2))
            {
                printf("\n--Orquestas Completas:\n"
                       "Nombre Orquesta: %s\nLugar: %s\n"
                       "ID de Orquesta: %d\n",
                       arrayOrquesta[i].name,
                       arrayOrquesta[i].lugar,
                       arrayOrquesta[i].idOrquesta);
                       flag=0;
                       retorno=0;
            }
        }
        if(flag)
            {
                printf("\nNo hay orquestas completas\n");
                retorno=0;
            }
    }
    return retorno;
}

//INFORME E
/** \brief  Asks the user to enter an existing orquesta ID
*           and then prints all the muscicians assigned to it.
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayMusico Musico* Pointer to array of musico
* \param    lenOrquesta orquesta array lenght
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \param    msgE message error if something wrong
* \return   int Return 0 if OK; return -1 if wrong
* */
int informe_printMusicosByOrquestaDeterminada(Musico* arrayMusico,Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,
                                              int lenMusico,int lenOrquesta,int lenInstrumento,char* msgE)
{
    int i;
    int auxIdOrquesta;
    int posOrquesta;
    int posMusico;
    int posInstrumento;
    char stringTipo[30];
    int flag=1;

    auxIdOrquesta=orquesta_getID(arrayOrquesta,lenOrquesta,msgE,3);
    posOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,auxIdOrquesta);
    if((auxIdOrquesta>=0)&&(posOrquesta!=-1))
    {
        for(i=0;i<lenMusico;i++)
        {
            if((arrayMusico[i].isEmpty==0)&&(arrayMusico[i].idOrquesta==auxIdOrquesta))
            {
                posOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,arrayMusico[i].idOrquesta);
                posMusico=musico_findMusicoById(arrayMusico,lenMusico,arrayMusico[i].idMusico);
                posInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                if((posOrquesta>=0)&&(posMusico>=0)&&(posMusico>=0))
                {
                    switch(arrayInstrumento[posInstrumento].tipo)
                    {
                       case 1:
                           strncpy(stringTipo,"Cuerda",sizeof(stringTipo));
                           break;
                        case 2:
                            strncpy(stringTipo,"Viento-Madera",sizeof(stringTipo));
                            break;
                        case 3:
                            strncpy(stringTipo,"Viento-Metal",sizeof(stringTipo));
                            break;
                        case 4:
                            strncpy(stringTipo,"Percusion",sizeof(stringTipo));
                            break;
                    }
                    printf("\nMusico: %s %s\nEdad: %d\nTipo: %s\nNombre Instrumento: %s"
                           "\n-------\n",
                           arrayMusico[posMusico].name,
                           arrayMusico[posMusico].surname,
                           arrayMusico[posMusico].edad,
                           stringTipo,
                           arrayInstrumento[posInstrumento].name);
                           flag=0;
                }
            }
        }
        if(flag)
        {
            printf("\n----El listado se encuentra vacio----\n");
        }
    }
    return 0;
}

//INFORME F
/** \brief  Prints orquesta with more muscicians.
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    arrayMusico Musico* Pointer to array of musico
* \param    lenOrquesta orquesta array lenght
* \param    lenMusico musico array lenght
* \return   int Return 0 if OK; return -1 if wrong
* */
int informe_orquestaConMasMusicos(Orquesta* arrayOrquesta,Musico* arrayMusico,int lenOrquesta,int lenMusico)
{
    int i;
    int cantidadMusicos;
    char stringTipo[30];
    int max=0;
    int retorno=-1;

    if(arrayOrquesta!=NULL&&arrayMusico!=NULL
       &&lenOrquesta>0&&lenMusico>0)
   {
       for(i=0;i<lenOrquesta;i++)
       {
           if(arrayOrquesta[i].isEmpty==0)
           {
               informe_cantMusicosEnOrquestaEspecifica(arrayOrquesta,arrayMusico,lenMusico,i,&cantidadMusicos);
               if(cantidadMusicos>=max)
               {
                    max=cantidadMusicos;
                    switch(arrayOrquesta[i].tipo)
                    {
                        case 1:
                            strncpy(stringTipo,"Sinfonica",sizeof(stringTipo));
                            break;
                        case 2:
                            strncpy(stringTipo,"Filarmonica",sizeof(stringTipo));
                            break;
                        case 3:
                            strncpy(stringTipo,"Camara",sizeof(stringTipo));
                            break;
                    }
                    printf("\nID orquesta: %d\nNombre: %s\n"
                           "Tipo: %s\nLugar: %s\nCantidad de Musicos: %d\n",
                           arrayOrquesta[i].idOrquesta,
                           arrayOrquesta[i].name,
                           stringTipo,
                           arrayOrquesta[i].lugar,
                           cantidadMusicos);
                    retorno=0;
               }

           }
       }
   }
    return retorno;
}

//INFORME G
/** \brief  Prints orquesta with more muscicians.
* \param    arrayMusico Musico* Pointer to array of musico
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    lenMusico musico array lenght
* \param    lenInstrumento instrumento array lenght
* \return   int Return 0 if OK; return -1 if wrong
* */
int informe_printMusicoSoloCuerda(Musico* arrayMusico,Instrumento* arrayInstrumento,
                                  int lenMusico,int lenInstrumento)
{
    int i;
    int posInstrumentoCuerda;
    int auxTipo;
    char stringTipo[30];
    int flag=1;
    Instrumento_sortInstrumentoByTipo(arrayInstrumento,lenInstrumento,1);
    for(i=0;i<lenMusico;i++)
    {

        if(arrayMusico[i].isEmpty==0)
        {
            posInstrumentoCuerda=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
            auxTipo=instrumento_findInstrumentoByTipo(arrayInstrumento,lenInstrumento,arrayInstrumento[posInstrumentoCuerda].tipo);
            if(posInstrumentoCuerda!=-1&&auxTipo==1)
            {
                switch(auxTipo)
                {
                   case 1:
                       strncpy(stringTipo,"Cuerda",sizeof(stringTipo));
                       break;
                    case 2:
                        strncpy(stringTipo,"Viento-Madera",sizeof(stringTipo));
                        break;
                    case 3:
                        strncpy(stringTipo,"Viento-Metal",sizeof(stringTipo));
                        break;
                    case 4:
                        strncpy(stringTipo,"Percusion",sizeof(stringTipo));
                        break;
                }
                printf("\nNombre: %s\nApellido: %s\n"
                "Edad: %d\nNombre Instrumento: %s\n"
                "Tipo Instrumento: %s\n-------\n",
                       arrayMusico[i].name,
                       arrayMusico[i].surname,
                       arrayMusico[i].edad,
                       arrayInstrumento[posInstrumentoCuerda].name,
                       stringTipo);
                flag=0;
            }

        }

    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

//INFORME H
/** \brief  Prints the average of muscicians per orquestas
* \param    arrayMusico Musico* Pointer to array of musico
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenMusico musico array lenght
* \param    lenOrquesta orquesta array lenght
* \return   returns 0
**/
int informe_promedioMusicosPorOrquesta(Musico* arrayMusico,Orquesta* arrayOrquesta,
                                       int lenMusico,int lenOrquesta)
{
    int cantidadMusicos;
    int cantidadOrquesta;
    float promedio;

    informe_cantidadMusicos(arrayMusico,lenMusico,&cantidadMusicos);
    informe_cantidadOrquestas(arrayOrquesta,lenOrquesta,&cantidadOrquesta);
    if(cantidadOrquesta!=0)
    {
        promedio=(float)cantidadMusicos/(float)cantidadOrquesta;
        printf("\nEL promedio de Musicos por orquesta es: %.1f\n",
               promedio);
    }
    else
    {
        printf("\nNo hay Orquestas\n");
    }
    return 0;
}

//FUNCIONES LLAMADAS POR OTRAS EN INFORMES.C (USO INTERNO)
/** \brief  Calculates the total existing orquestas
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenOrquesta orquesta array lenght
* \param    pCantidadOrquestas Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantidadOrquestas(Orquesta* arrayOrquesta,int lenOrquesta,int* pCantidadOrquestas)
{
    int i;
    int contadorOrquestas=0;
    int ret=-1;
    if(arrayOrquesta!=NULL && lenOrquesta>0 && pCantidadOrquestas!=NULL)
    {
        for(i=0;i<lenOrquesta;i++)
        {
            if(arrayOrquesta[i].isEmpty==0)
            {
                contadorOrquestas++;
                ret=0;
            }
        }
        *pCantidadOrquestas=contadorOrquestas;
    }
    return ret;
}

/** \brief  Calculates the total existing muscicians
* \param    arrayMusico Musico* Pointer to array of musico
* \param    lenMusico musico array lenght
* \param    pCantidadMusicos Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantidadMusicos(Musico* arrayMusico,int lenMusico,int* pCantidadMusicos)
{
    int i;
    float contadorMusicos=0;
    int ret=-1;
    if(arrayMusico!=NULL && lenMusico>0 && pCantidadMusicos!=NULL)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                contadorMusicos++;
                ret=0;
            }
        }
        *pCantidadMusicos=contadorMusicos;
    }
    return ret;
}

/** \brief  Calculates the total existing instruments
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    lenIntrumento instrumento array lenght
* \param    pCantidadInst Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantidadInstrumentos(Instrumento* arrayInstrumento,int lenInstrumento,int* pCantidadInst)
{
    int i;
    int contadorInstrumentos=0;
    int ret=-1;
    if(arrayInstrumento!=NULL && lenInstrumento>0 && pCantidadInst!=NULL)
    {
        for(i=0;i<lenInstrumento;i++)
        {
            if(arrayInstrumento[i].isEmpty==0)
            {
                contadorInstrumentos++;
                ret=0;
            }
        }
        *pCantidadInst=contadorInstrumentos;
    }
    return ret;
}

/** \brief  Calculates the existing amount of
*           instrumentos of type 1(cuerda) in a
*           specific orquesta.
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \param    indexOrquesta value that represents the orquesta position
* \param    pCantidadInstCuerda Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantInstCuerdaEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstCuerda)
{
    int i;
    int posIdInstrumento;
    int contadorInstrumentosCuerda=0;
    int ret=-1;
    if(arrayInstrumento!=NULL&&pCantidadInstCuerda!=NULL&&arrayMusico!=NULL&&lenMusico>0&&indexOrquesta>=0)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                if(arrayMusico[i].idOrquesta==arrayOrquesta[indexOrquesta].idOrquesta)
                {
                    posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                    if(arrayInstrumento[posIdInstrumento].tipo==TIPO_INST_CUERDA)
                    {
                        contadorInstrumentosCuerda++;
                    }
                }
            }
        }
        *pCantidadInstCuerda=contadorInstrumentosCuerda;
        ret=0;
    }
    return ret;
}

/** \brief  Calculates the existing amount of
*           instrumentos of type 2 and 3(vientp) in a
*           specific orquesta.
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \param    indexOrquesta value that represents the orquesta position
* \param    pCantidadInstVientos Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantInstVientosEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstVientos)
{
    int i;
    int posIdInstrumento;
    int contadorInstrumentosVientos=0;
    int ret=-1;
    if(arrayInstrumento!=NULL&&pCantidadInstVientos!=NULL&&arrayMusico!=NULL&&lenMusico>0&&indexOrquesta>=0)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                if(arrayMusico[i].idOrquesta==arrayOrquesta[indexOrquesta].idOrquesta)
                {
                    posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                    if(arrayInstrumento[posIdInstrumento].tipo==TIPO_INST_V_MAD
                       ||arrayInstrumento[posIdInstrumento].tipo==TIPO_INST_V_MET)
                    {
                        contadorInstrumentosVientos++;
                    }
                }
            }
        }
        *pCantidadInstVientos=contadorInstrumentosVientos;
        ret=0;
    }
    return ret;
}

/** \brief  Calculates the existing amount of
*           instrumentos of type 4(percusion) in a
*           specific orquesta.
* \param    arrayInstrumento Instrumento* Pointer to array of instrumento
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenInstrumento instrumento array lenght
* \param    lenMusico musico array lenght
* \param    indexOrquesta value that represents the orquesta position
* \param    pCantidadInstPercusion Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantInsPercusionEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstPercusion)
{
    int i;
    int posIdInstrumento;
    int contadorInstrumentosPercusion=0;
    int ret=-1;
    if(arrayInstrumento!=NULL&&pCantidadInstPercusion!=NULL&&arrayMusico!=NULL&&lenMusico>0&&indexOrquesta>=0)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                if(arrayMusico[i].idOrquesta==arrayOrquesta[indexOrquesta].idOrquesta)
                {
                    posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                    if(arrayInstrumento[posIdInstrumento].tipo==TIPO_INST_PERCUSION)
                    {
                        contadorInstrumentosPercusion++;
                    }
                }
            }
        }
        *pCantidadInstPercusion=contadorInstrumentosPercusion;
        ret=0;
    }
    return ret;
}

/** \brief  Calculates the existing amount of
*           muscicians in a specific orquesta.
* \param    arrayOrquesta Orquesta* Pointer to array of orquesta
* \param    lenMusico musico array lenght
* \param    indexOrquesta value that represents the orquesta position
* \param    pCantMusicosEnUnaOrquesta Pointer that returns the
*           calculated value
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantMusicosEnOrquestaEspecifica (Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenMusico,int indexOrquesta,int* pCantMusicosEnUnaOrquesta)
{
    int i;
    int max=0;
    int contadorMusico=0;
    int retorno=-1;

    if(arrayOrquesta!=NULL&&arrayMusico!=NULL
       &&lenMusico>0&&pCantMusicosEnUnaOrquesta!=NULL)
    {
        musico_sortMusicosByIdOrquestaEficiente(arrayMusico,lenMusico,1);
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0
               &&(arrayMusico[i].idOrquesta==arrayOrquesta[indexOrquesta].idOrquesta))
            {
                contadorMusico++;
                if(contadorMusico>max)
                {
                    max=contadorMusico;
                    *pCantMusicosEnUnaOrquesta=contadorMusico;
                    retorno=0;
                }
            }
            else
            {
                contadorMusico=0;
            }
        }
    }
    return retorno;
}
//FIN FUNCIONES USO INTERNO
