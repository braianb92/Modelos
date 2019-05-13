#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "autor.h"
#include "utn_strings.h"
#include "prestamo.h"



static int generarId(void);

int prestamo_menu(Prestamo* arrayPrestamo,Socio* arraySocio, Libro* arrayLibro,Autor* arrayAutor,
                  int lenPrestamo,int lenSocio,int lenLibro,int lenAutor,
                  char* menuText,int exitMenuNumber,int tries)
{
    int option=0;
    int flag=0;
    char* noAddMsg="\n----AUN NO HAY PRESTAMOS EN LA NOMINA----\n";
    char* addMsg="\n----Alta satisfactoria!----\n";
    char* addMsgE="\n----NO se realizo el Alta----\n";
    char* alterMsg="\n----Se modifico exitosamente!----\n";
    char* alterMsgE="\n----NO se realizo la Modificacion----\n";
    char* removeMsg="\n----Se dio de baja exitosamente!----\n";
    char* removeMsgE="\n----NO se realizo la Baja----\n";
    char* generalMsgE="DATO NO VALIDO\n";

    prestamo_initPrestamo(arrayPrestamo,lenPrestamo);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    libro_printLibro(arrayLibro,arrayAutor,lenLibro,lenAutor);
                    socio_printSocio(arraySocio,lenSocio);
                    if(!prestamo_addPrestamo(arrayPrestamo,arraySocio,arrayLibro,
                                             lenPrestamo,lenSocio,lenLibro,generalMsgE,tries))
                    {
                        flag=1;
                        printf(addMsg);
                    }
                    else
                    {
                        printf(addMsgE);
                    }
                break;
            case 2:
                if(flag)
                {

                    if(!prestamo_alter(arrayPrestamo,lenPrestamo,generalMsgE,4,tries))
                    {
                        printf(alterMsg);
                    }
                    else
                    {
                        printf(alterMsgE);
                    }
                }
                else
                {
                    printf(noAddMsg);
                }
                break;
            case 3:
                if(flag)
                {
                    if(!prestamo_removePrestamo(arrayPrestamo,lenPrestamo,generalMsgE,tries))
                    {
                        printf(removeMsg);
                    }
                    else
                    {
                        printf(removeMsgE);
                    }
                }
                else
                {
                    printf(noAddMsg);
                }
                break;
        }
    }
    return 0;
}

int prestamo_addPrestamo(Prestamo* arrayPrestamo,Socio* arraySocio,Libro* arrayLibro,
                         int lenPrestamo,int lenSocio,int lenLibro,char* msgE,int tries)
{
    int indexFree;
    int auxDia;
    int auxMes;
    int auxYear;
    int retorno=-1;
    int auxIdSocio;
    int auxIdLibro;
    int posOfIdSocio;
    int posofIdLibro;
    if((arrayPrestamo!=NULL)&&(lenPrestamo>0)&&(arraySocio!=NULL)&&(lenSocio>0)
       &&(arrayLibro!=NULL)&&(lenLibro>0))
    {
        indexFree=prestamo_findFree(arrayPrestamo,lenPrestamo);
        auxIdSocio=socio_getID(arraySocio,lenSocio,msgE,tries);
        auxIdLibro=libro_getID(arrayLibro,lenLibro,msgE,tries);
        posOfIdSocio=socio_findSocioById(arraySocio,lenSocio,auxIdSocio);
        posofIdLibro=libro_findLibroById(arrayLibro,lenLibro,auxIdLibro);
        if((indexFree!=-1)&&(auxIdSocio>=0)
           &&(posOfIdSocio!=-1)&&(auxIdLibro>=0)
           &&(posofIdLibro!=-1)
           &&(!getDate(&auxDia,&auxMes,&auxYear,msgE,tries)))
        {
            arrayPrestamo[indexFree].idSocio=auxIdSocio;
            arrayPrestamo[indexFree].idLibro=auxIdLibro;
            arrayPrestamo[indexFree].day=auxDia;
            arrayPrestamo[indexFree].month=auxMes;
            arrayPrestamo[indexFree].year=auxYear;
            arrayPrestamo[indexFree].idPrestamo=generarId();
            arrayPrestamo[indexFree].isEmpty=0;
            retorno=0;
        }
    }
    return retorno;
}

int prestamo_alter(Prestamo* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int auxDia;
    int auxMes;
    int auxYear;
    int opcion=0;
    char* alterMenuText="\n1-Modificar Fecha\n2-Modificar Codigo Libro\n"
                        "3-Modificar Codigo Socio\n4- Atras (Menu Principal)\n";
    int retorno=-1;

    if((array!=NULL)&&(len>0))
    {
        auxID=prestamo_getID(array,len,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=prestamo_findPrestamoById(array,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=exitAlterMenuNumber)
                {
                    printf(alterMenuText);
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",generalMsgE,1,
                                  exitAlterMenuNumber,tries);
                    switch(opcion)
                    {
                        case 1:
                        {
                            if(!getDate(&auxDia,&auxMes,&auxYear,generalMsgE,tries))
                            {
                                array[posOfID].day=auxDia;
                                array[posOfID].month=auxMes;
                                array[posOfID].year=auxYear;
                                retorno=0;
                            }
                            break;
                        }

                    }
                }
            }
        }
        else
        {
            printf("\n----No se encontro el CODIGO!-----\n");
        }
    }
    return retorno;
}

int prestamo_removePrestamo(Prestamo* array, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(array!=NULL && len>0)
    {
        auxID=prestamo_getID(array,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=prestamo_findPrestamoById(array,len,auxID);
            if(posOfID!=-1)
            {
               array[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

int prestamo_sortPrestamo(Prestamo* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Prestamo buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(array[i].day>array[j].day))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(array[i].day<array[j].day))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

int prestamo_informarTotalyPromedioDiario(Prestamo* array,int len)
{
    int i;
    int totalGeneral;
    float promedioDiario;
    int diasDiferentes=0;
    int contadorTotal=0;
    int ret=-1;

    prestamo_sortPrestamo(array,len,1);
    if(array!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==0)
            {
                contadorTotal++;
                if(array[i].day!=array[i-1].day)
                {
                    diasDiferentes++;
                }
            }
        }
        totalGeneral=contadorTotal;
        promedioDiario=totalGeneral/diasDiferentes;
        ret=0;
        if(ret==0)
        {
            printf("\nEl total de prestamos es: %d\nEl promedio diario de prestamos es: %.2f\nDias diferentes: %d",
                    totalGeneral,promedioDiario,diasDiferentes);
        }
    }
    return ret;
}

int prestamo_initPrestamo(Prestamo* array,int len)
{
    int i;
    if(array!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            //array[i].idPrestamo=-1;
            array[i].isEmpty=1;
        }
    }
    return 0;
}

int prestamo_findFree(Prestamo* array, int len)
{
    int i;
    int ret=-1;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==1)
            {
                ret=i;
                printf("\n----Se encontro lugar libre----\n");
                break;
            }
        }
        if(ret==-1)
        {
            printf("\n----NO hay lugar libre!!----\n");
        }
    }
    return ret;
}

int prestamo_findPrestamoById(Prestamo* array, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((array[i].isEmpty==0)&&(array[i].idPrestamo==idE))
        {
            ret=i;
        }
    }
    return ret;
}

int prestamo_getID (Prestamo* array,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(array!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de prestamo: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

int prestamo_printPrestamoBySocioDeterminado(Prestamo* arrayPrestamo,Autor* arrayAutor,Socio* arraySocio,
                             Libro* arrayLibro,int lenPrestamo,int lenAutor,int lenSocio,
                             int lenLibro,char* msgE)
{
    int i;
    int posAutor;
    int posLibro;
    int auxIdSocio;
    int posSocio;
    int flag=1;

    auxIdSocio=socio_getID(arraySocio,lenSocio,msgE,3);
    posSocio=socio_findSocioById(arraySocio,lenSocio,auxIdSocio);
    if((auxIdSocio>=0)&&(posSocio!=-1))
    {
        for(i=0;i<lenPrestamo;i++)
        {
            if((arrayPrestamo[i].isEmpty==0)&&(arrayPrestamo[i].idSocio==auxIdSocio))
            {
                posLibro=libro_findLibroById(arrayLibro,lenLibro,arrayPrestamo[i].idLibro);
                posAutor=autor_findAutorById(arrayAutor,lenAutor,arrayLibro[posLibro].idAutor);
                if((posLibro>=0)&&(posAutor>=0))
                {
                    printf("\nFecha de Prestamo: %d/%d/%d\nAutor: %s %s\nLibro: %s\n"
                           "Codigo Prestamo: %d\nCodigo Autor: %d\nCodigo Libro: %d\n"
                           "Codigo Socio: %d\n-------\n",
                            arrayPrestamo[i].day,
                            arrayPrestamo[i].month,
                            arrayPrestamo[i].year,
                            arrayAutor[posAutor].name,
                            arrayAutor[posAutor].surname,
                            arrayLibro[posLibro].titulo,
                            arrayPrestamo[i].idPrestamo,
                            arrayAutor[posAutor].idAutor,
                            arrayPrestamo[i].idLibro,
                            arrayPrestamo[i].idSocio);
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

int prestamo_printPrestamo(Prestamo* arrayPrestamo,int lenPrestamo)
{
    int i;
    int flag=1;
    for(i=0;i<lenPrestamo;i++)
    {
        if(arrayPrestamo[i].isEmpty==0)
        {
            printf("\nID Prestamo: %d\nFecha: %d/%d/%d\nCodigo Socio: %d\n"
                   "Codigo Libro: %d\n--------\n",
                   arrayPrestamo[i].idPrestamo,
                   arrayPrestamo[i].day,
                   arrayPrestamo[i].month,
                   arrayPrestamo[i].year,
                   arrayPrestamo[i].idSocio,
                   arrayPrestamo[i].idLibro);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

static int generarId(void)
{
    static int idEmp=0;
    return idEmp++;
}
