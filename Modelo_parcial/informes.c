#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "informes.h"

/** \brief  Shows the total amount of salary between employees,
*           the average salary and the number of employees
*           over the average.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
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

/** \brief  Calculates the number of employees over
*           the average salary.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    promedioResult The average salary
* \param    valor Pointer that keeps the
*           number of employees that are
*           over the average salary.
* \return   return (-1) if wrong, (0) if OK.
**/
int informe_cantidadMusicos(Musico* arrayMusico,int lenMusico,int* pCantidadMusicos)
{
    int i;
    int contadorMusicos=0;
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

/** \brief  Calculates the number of employees over
*           the average salary.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    promedioResult The average salary
* \param    valor Pointer that keeps the
*           number of employees that are
*           over the average salary.
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

int informe_tipoInstrumentoMasUsado(Instrumento* arrayInstrumento,int lenInstrumento,int* pTipoInstMasUsado)
{
    int i;
    int max=0;
    int contadorOcurrencia=0;
    int instrumentoMayorOcurrencia;
    int retorno=-1;
    if(arrayInstrumento!=NULL && lenInstrumento>=0 && pTipoInstMasUsado!=NULL)
    {
        Instrumento_sortInstrumentoByTipo(arrayInstrumento,lenInstrumento,1);
        for(i=1;i<lenInstrumento;i++)
        {
            if(arrayInstrumento[i-1].tipo==arrayInstrumento[i].tipo)
            {
                contadorOcurrencia++;
                if(contadorOcurrencia>max)
                {
                    max=contadorOcurrencia;
                    instrumentoMayorOcurrencia=arrayInstrumento[i].tipo;
                }
            }
            else
            {
                contadorOcurrencia=0;
            }
        }
        if(instrumentoMayorOcurrencia>=1 || instrumentoMayorOcurrencia<=4)
        {
            *pTipoInstMasUsado=instrumentoMayorOcurrencia;
            retorno=0;
        }
    }
    return retorno;
}

int informe_InstrumentosMenosUsadosPorMusicos(Instrumento* arrayInstrumento,Musico* arrayMusico,
                                              int lenInstrumento,int lenMusico)
{
    int i;
    int min=lenInstrumento+1;
    int contadorOcurrencia=0;
    int IdInstrumentoMenorOcurrencia;
    int posIdInstrumento;
    char stringTipo[30];
    int retorno=-1;
    if(arrayInstrumento!=NULL && lenInstrumento>0
       && arrayMusico!=NULL && lenMusico>0)
    {
        Instrumento_sortInstrumentoByTipo(arrayInstrumento,lenInstrumento,1);
        musico_sortMusicosByInstrumentoEficiente(arrayMusico,lenMusico,1);
        for(i=1;i<lenMusico;i++)
        {
            if(arrayMusico[i-1].idInstrumento!=arrayMusico[i].idInstrumento)
            {
                contadorOcurrencia--;
            }
            else
            {
                contadorOcurrencia++;
            }
            if(contadorOcurrencia<=min)
            {
                min=contadorOcurrencia;
                IdInstrumentoMenorOcurrencia=arrayMusico[i-1].idInstrumento;
                posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,
                                                         IdInstrumentoMenorOcurrencia);
                if(posIdInstrumento!=-1)
                {
                    switch(arrayInstrumento[posIdInstrumento].tipo)
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
                    printf("\n----\nInstrumentos menos Usados Por Musicos\n----\n"
                           "Nombre: %s\nId Instrumento: %d\nTipo: %s\n",
                           arrayInstrumento[posIdInstrumento].name,
                           arrayInstrumento[posIdInstrumento].idInstrumento,
                           stringTipo);
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

int informe_InstrumentoMasUsadoPorMusicos(Instrumento* arrayInstrumento,Musico* arrayMusico,
                                              int lenInstrumento,int lenMusico)
{
    int i;
    int max=0;
    int contadorOcurrencia=0;
    int IdInstrumentoMayorOcurrencia;
    int posIdInstrumento;
    char stringTipo[30];
    int retorno=-1;
    if(arrayInstrumento!=NULL && lenInstrumento>0
       && arrayMusico!=NULL && lenMusico>0)
    {
        Instrumento_sortInstrumentoByTipo(arrayInstrumento,lenInstrumento,1);
        musico_sortMusicosByInstrumentoEficiente(arrayMusico,lenMusico,1);
        for(i=1;i<lenMusico;i++)
        {
            if(arrayMusico[i-1].idInstrumento==arrayMusico[i].idInstrumento)
            {
                contadorOcurrencia++;
                if(contadorOcurrencia>max)
                {
                    max=contadorOcurrencia;
                    IdInstrumentoMayorOcurrencia=arrayMusico[i].idInstrumento;
                }
            }
            else
            {
                contadorOcurrencia=0;
            }
        }
        posIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,
                                                         IdInstrumentoMayorOcurrencia);
        if(posIdInstrumento!=-1)
        {
            switch(arrayInstrumento[posIdInstrumento].tipo)
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
            printf("\nInstrumento mas Usado Por Musicos: %s\n"
                   "Id Instrumento: %d\nTipo: %s\n",
                   arrayInstrumento[posIdInstrumento].name,
                   arrayInstrumento[posIdInstrumento].idInstrumento,
                   stringTipo);
            retorno=0;
        }
    }
    return retorno;
}

int informe_promedioDeEdadMusicos(Musico* arrayMusico,int lenMusico)
{
    int i;
    int edadesSumadas;
    float promedioResult;
    int musicoOverPromedio;
    int cantidadMusicos=0;
    int sum=0;
    int ret=-1;
    if(arrayMusico!=NULL && lenMusico>0)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                sum+=arrayMusico[i].edad;
                cantidadMusicos++;
            }
        }
        edadesSumadas=sum;
        promedioResult=edadesSumadas/cantidadMusicos;
        informe_musicoOverPromedio(arrayMusico,lenMusico,promedioResult,&musicoOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nLa edad promedio es: %.2f\n"
                    "Cantidad demusicos que superan la edad promedio: %d\n",
                    promedioResult,musicoOverPromedio);
        }
    }
    return ret;
}

int informe_musicoOverPromedio(Musico* arrayMusico,int lenMusico,float promedioResult,int* valor)
{
    int i;
    int contadorMusico=0;
    int ret=-1;
    if(arrayMusico!=NULL && lenMusico>0 && valor!=NULL)
    {
        for(i=0;i<lenMusico;i++)
        {
            if(arrayMusico[i].isEmpty==0)
            {
                if(arrayMusico[i].edad>promedioResult)
                {
                    contadorMusico++;
                }
            }

        }
        *valor=contadorMusico;
        ret=0;
    }
    return ret;
}

int informe_printMusicoByInstrumentoDeterminado(Musico* arrayMusico,Instrumento* arrayInstrumento,
                                                int lenMusico,int lenInstrumento,char* msgE)
{
    int i;
    int auxIdInstrumento;
    int posInstrumento;
    int posMusico;
    char stringTipo[30];
    int flag=1;

    auxIdInstrumento=instrumento_getID(arrayInstrumento,lenInstrumento,msgE,3);
    posInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,auxIdInstrumento);
    if((auxIdInstrumento>=0)&&(posInstrumento!=-1))
    {
        for(i=0;i<lenMusico;i++)
        {
            if((arrayMusico[i].isEmpty==0)&&(arrayMusico[i].idInstrumento==auxIdInstrumento))
            {
                posInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
                posMusico=musico_findMusicoById(arrayMusico,lenMusico,arrayMusico[i].idMusico);
                if((posInstrumento>=0)&&(posMusico>=0))
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
                    printf("\nMusico: %s %s\nInstrumento: %s\nTipo: %s\nCodigo Musico: %d\n"
                           "Codigo Instrumento: %d\n-------\n",
                           arrayMusico[posMusico].name,
                           arrayMusico[posMusico].surname,
                           arrayInstrumento[posInstrumento].name,
                           stringTipo,
                           arrayMusico[posMusico].idMusico,
                           arrayInstrumento[posInstrumento].idInstrumento);
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

int informe_printMusicosByOrquestaDeterminada(Musico* arrayMusico,Orquesta* arrayOrquesta,
                                                int lenMusico,int lenOrquesta,char* msgE)
{
    int i;
    int auxIdOrquesta;
    int posOrquesta;
    int posMusico;
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
                if((posOrquesta>=0)&&(posMusico>=0))
                {
                    switch(arrayOrquesta[posOrquesta].tipo)
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
                    printf("\nMusico: %s %s\nOrquesta: %s\nTipo: %s\nCodigo Musico: %d\n"
                           "Codigo Orquesta: %d\n-------\n",
                           arrayMusico[posMusico].name,
                           arrayMusico[posMusico].surname,
                           arrayOrquesta[posOrquesta].name,
                           stringTipo,
                           arrayMusico[posMusico].idMusico,
                           arrayOrquesta[posOrquesta].idOrquesta);
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

int informe_tipoOrquestaMasFrecuente(Orquesta* arrayOrquesta,int lenOrquesta)
{
    int i;
    int max=0;
    int contadorOcurrencia=0;
    int tipoOrquestaMayorOcurrencia;
    char stringTipo[30];
    int retorno=-1;
    if(arrayOrquesta!=NULL && lenOrquesta>=0)
    {
        orquesta_sortOrquestaByTipo(arrayOrquesta,lenOrquesta,1);
        for(i=1;i<lenOrquesta;i++)
        {
            if(arrayOrquesta[i-1].tipo==arrayOrquesta[i].tipo)
            {
                contadorOcurrencia++;
                if(contadorOcurrencia>max)
                {
                    max=contadorOcurrencia;
                    tipoOrquestaMayorOcurrencia=arrayOrquesta[i].tipo;
                }
            }
            else
            {
                contadorOcurrencia=0;
            }
        }
        if(tipoOrquestaMayorOcurrencia>=1 || tipoOrquestaMayorOcurrencia<=3)
        {
            switch(tipoOrquestaMayorOcurrencia)
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
            printf("\nTipo de Orquesta mas frecuente: %s\n-------\n",stringTipo);
            retorno=0;
        }
    }
    return retorno;
}

int informe_orquestaConMasMusicos (Orquesta* arrayOrquesta,Musico* arrayMusico,
                                   int lenOrquesta,int lenMusico)
{
    int i;
    int max=0;
    int contadorMusico=0;
    int IdorquestaConMasMusicos;
    int posIdOrquesta;
    char stringTipo[30];
    int retorno=-1;

    if(arrayOrquesta!=NULL&&arrayMusico!=NULL
       &&lenOrquesta>0&&lenMusico>0)
    {
        musico_sortMusicosByIdOrquestaEficiente(arrayMusico,lenMusico,1);
        for(i=1;i<lenMusico;i++)
        {
            if(arrayMusico[i-1].idOrquesta==arrayMusico[i].idOrquesta)
            {
                contadorMusico++;
                if(contadorMusico>max)
                {
                    max=contadorMusico;
                    IdorquestaConMasMusicos=arrayMusico[i].idOrquesta;
                }
            }
            else
            {
                contadorMusico=0;
            }
        }
        posIdOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,IdorquestaConMasMusicos);
        if(posIdOrquesta!=-1)
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
            printf("\nOrquesta con mas Musicos: %s\n"
                   "Tipo: %s\nCodigo Orquesta: %d\n",
                   arrayOrquesta[posIdOrquesta].name,
                   stringTipo,
                   arrayOrquesta[posIdOrquesta].idOrquesta);
            retorno=0;
        }
    }
    return retorno;
}
