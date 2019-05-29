#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "orquesta.h"


static int generarId(void);

/** \brief  Adds an orquesta with the given parameters
* \param    array Orquesta* Pointer to array of
* \param    len int Array len of orquesta
* \param    indexPosition The position in the orquesta array
* \param    nombre Name to be assigned
* \param    lugar Place to be assigned
* \param    tipo type of orquesta to be assigned
* \return   return (-1) if wrong, (0) if OK.
* */
int orquesta_preCarga(Orquesta* array,int len,int indexPosition,char* nombre,
                      char* lugar,int tipo)
{
    int retorno=-1;
    if((array!=NULL)&&(len>0))
    {
        strncpy(array[indexPosition].name,nombre,sizeof(array[indexPosition].name));
        strncpy(array[indexPosition].lugar,lugar,sizeof(array[indexPosition].lugar));
        array[indexPosition].tipo=tipo;
        array[indexPosition].idOrquesta=generarId();
        array[indexPosition].isEmpty=0;
        retorno=0;
    }
    return retorno;
}

/** \brief  add values entered by the user to
*           an existing array of orquesta
*           in an empty position.
* \param    array Orquesta* Pointer to array of
* \param    len int Array len of orquesta
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int orquesta_addOrquesta(Orquesta* array,int len,char* msgE,int tries)
{
    int indexFree;
    char bufferName[30];
    char bufferLugar[30];
    int auxTipo;
    char stringTipo[30];
    int retorno=-1;
    if((array!=NULL)&&(len>0))
    {
        indexFree=orquesta_findFree(array,len);
        if((indexFree!=-1)&&(!getStringAlphanumeric(bufferName,"\nIngrese Nombre: ",msgE,tries))
            &&(!getStringAlphanumeric(bufferLugar,"\nIngrese Lugar: ",msgE,tries))
            &&(!getIntInRange(&auxTipo,"\nIngrese Tipo: Sinfonica(1)/Filarmonica(2)"
                "Camara(3) ","\nDATO NO VALIDO\n",1,3,tries)))
        {
            strncpy(array[indexFree].name,bufferName,sizeof(bufferName));
            strncpy(array[indexFree].lugar,bufferLugar,sizeof(bufferLugar));
            array[indexFree].tipo=auxTipo;
            array[indexFree].idOrquesta=generarId();
            array[indexFree].isEmpty=0;
            switch(auxTipo)
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
            printf("\nNombre: %s\nLugar: %s\nTipo: %s\nCodigo Orquesta: %d",
                   array[indexFree].name,
                   array[indexFree].lugar,
                   stringTipo,
                   array[indexFree].idOrquesta);
            retorno=0;
        }
    }
    return retorno;
}

/** \brief  Modify values in an existing
*           array of orquesta
*           in an existing position.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    generalMsgE char Shows an error message to be printed
*           when a value is not valid.
* \param    exitMenuNumber int Number that exits the menu
            and also used as max number to stablish a range
            of menu options to acces the corresponding function.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int orquesta_alter(Orquesta* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferName[30];
    char bufferLugar[30];
    int auxTipo;
    char* alterMenuText="\n1-Modificar Nombre\n2-Modificar Lugar\n"
                        "3-Modificar Tipo\n4- Atras (Menu Principal)\n";
    int retorno=-1;

    if((array!=NULL)&&(len>0))
    {
        auxID=orquesta_getID(array,len,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=orquesta_findOrquestaById(array,len,auxID);
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
                            if(!getStringAlphanumeric(bufferName,"\nIngrese NUEVO Nombre: ",generalMsgE,tries))
                            {
                                strncpy(array[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringAlphanumeric(bufferLugar,"\nIngrese NUEVO Lugar: ",generalMsgE,tries))
                            {
                                strncpy(array[posOfID].lugar,bufferLugar,sizeof(bufferLugar));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if((!getIntInRange(&auxTipo,"\nIngrese NUEVO Tipo: Sinfonica(1)/Filarmonica(2)"
                                "Camara(3) ","\nDATO NO VALIDO\n",1,3,tries)))
                            {
                                array[posOfID].tipo=auxTipo;
                            }
                        }
                    }
                }
            }
            else
            {
                printf("\n----No se encontro el ID!-----\n");
            }
        }
    }
    return retorno;
}

/** \brief  Remove an orquesta by Id (put isEmpty Flag in 1)
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_removeOrquesta(Orquesta* array, int len,char* msgE,int tries,int* removedOrqId)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(array!=NULL && len>0)
    {
        auxID=orquesta_getID(array,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=orquesta_findOrquestaById(array,len,auxID);
            if(posOfID!=-1)
            {
               array[posOfID].isEmpty=1;
               *removedOrqId=auxID;
               retorno=0;
            }
            else
            {
                printf("\n---El Codigo de orquesta no es valido---\n");
            }
        }
     }
    return retorno;
}

/** \brief  Sort the elements in the array of orquesta,
*           UP or DOWN according to its order parameter
*           by lugar.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_sortOrquestaByLugar(Orquesta* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Orquesta buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(strcmp(array[i].lugar,array[j].lugar)>0))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(array[i].lugar,array[j].lugar)<0))
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


/** \brief  Sort the elements in the array of orquesta,
*           UP or DOWN according to its order parameter
*           by Nombre.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_sortOrquestaByNombre(Orquesta* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Orquesta buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(strcmp(array[i].name,array[j].name)>0))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(array[i].name,array[j].name)<0))
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

/** \brief  Sort the elements in the array of orquesta,
*           UP or DOWN according to its order parameter
*           by tipo.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_sortOrquestaByTipo(Orquesta* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Orquesta buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(array[i].tipo>array[j].tipo))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(array[i].tipo<array[j].tipo))
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

/** \brief  Sort the elements in the array of orquesta,
*           UP or DOWN according to its order parameter
*           by tipo when lugar matches.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_sortOrquestaByTipoMismoLugar(Orquesta* arrayOrquesta,int lenOrquesta,int order)
{
    int i;
    Orquesta buffer;

    for(i=1;i<lenOrquesta;i++)
    {
        if(strcmp(arrayOrquesta[i-1].lugar,arrayOrquesta[i].lugar)==0)
        {
            if((order==1)&&(arrayOrquesta[i-1].tipo>arrayOrquesta[i].tipo))
            {
                buffer=arrayOrquesta[i-1];
                arrayOrquesta[i-1]=arrayOrquesta[i];
                arrayOrquesta[i]=buffer;
            }
            else if((order==0)&&(arrayOrquesta[i-1].tipo<arrayOrquesta[i].tipo))
            {
                buffer=arrayOrquesta[i-1];
                arrayOrquesta[i-1]=arrayOrquesta[i];
                arrayOrquesta[i]=buffer;
            }
        }
    }
    return 0;
}

/** \brief  Sort the elements in the array of employees,
*           UP or DOWN according to its order parameter
*           by tipo and place with a better method.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int orquesta_sortOrquestasByLugaryTipoEficiente(Orquesta* arrayOrquesta,
                                                    int lenOrquesta,int order)///1up 0down
{
    int i;
    int flagNoEstaOrdenado=1;
    int retorno=-1;
    Orquesta buffer;
    if(arrayOrquesta!=NULL && lenOrquesta>0 && (order==0 || order==1))
    {
        while(flagNoEstaOrdenado==1)
        {
            flagNoEstaOrdenado=0;
            for(i=1;i<lenOrquesta;i++)
            {
                if((order==1)&&(strcmp(arrayOrquesta[i-1].lugar,arrayOrquesta[i].lugar)>0))///Creciente
                {
                    buffer=arrayOrquesta[i-1];
                    arrayOrquesta[i-1]=arrayOrquesta[i];
                    arrayOrquesta[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(arrayOrquesta[i-1].lugar,arrayOrquesta[i].lugar)<0))///Decreciente
                {
                    buffer=arrayOrquesta[i-1];
                    arrayOrquesta[i-1]=arrayOrquesta[i];
                    arrayOrquesta[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
            }
        }
        if(flagNoEstaOrdenado==0)
        {
            orquesta_sortOrquestaByTipoMismoLugar(arrayOrquesta,lenOrquesta,order);
        }
    }
    return retorno;
}

/** \brief  Indicates that all positions in the array are empty
*           by setting the flag isEmpty in 0 in all positions.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \return   return 0.
**/
int orquesta_initOrquesta(Orquesta* array,int len)
{
    int i;
    if(array!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            //array[i].idOrquesta=-1;
            array[i].isEmpty=1;
        }
    }
    return 0;
}

/** \brief  Searchs through the array for an orquesta position.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \return   return (-1) if no position found,
*           (Empty position) if empty position.
**/
int orquesta_findFree(Orquesta* array, int len)
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

/** \brief  Searchs through the array for a
*           specific value(ID).
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    idE Value to be found and matched in the array.
* \return   return (-1) if not found,
*           (position) if position matched.
**/
int orquesta_findOrquestaById(Orquesta* array, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((array[i].isEmpty==0)&&(array[i].idOrquesta==idE))
        {
            ret=i;
        }
    }
    return ret;
}

/** \brief  Asks the user to enter an ID.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if error, (ID) if OK
**/
int orquesta_getID (Orquesta* array,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(array!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de Orquesta: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief  Shows the existing orquestas.
* \param    array Orquesta* Pointer to array of orquesta
* \param    len int Array len of orquesta
* \param    msgE char Shows an error message to be printed
* \return   return 0.
**/
int orquesta_printOrquesta(Orquesta* array,int len)
{
    int i;
    char stringTipo[30];
    int flag=1;
    for(i=0;i<len;i++)
    {
        if(array[i].isEmpty==0)
        {
            switch(array[i].tipo)
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
            printf("\nCodigo Orquesta: %d\nNombre: %s\nLugar: %s\nTipo: %s\n-------\n",
                   array[i].idOrquesta,
                   array[i].name,
                   array[i].lugar,
                   stringTipo);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

/** \brief  Generates a unique ID.
* \param    receives void
* \return   return void.
**/
static int generarId(void)
{
    static int idOrq=1;
    return idOrq++;
}
