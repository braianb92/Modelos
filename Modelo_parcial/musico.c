#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "musico.h"

static int generarId(void);

/** \brief  Adds a musico with the given parameters
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    indexPosition The position in the musico array
* \param    nombre Name to be assigned
* \param    apellido Surname to be assigned
* \param    edad age to be assigned
* \param    idOrquesta  Existing orquesta ID to be assigned
* \param    idInstrumento Existing instrumento ID to be assigned
* \return   return (-1) if wrong, (0) if OK.
* */
int musico_preCarga(Musico* array,int len,int indexPosition,char* nombre,
                    char* apellido,int edad,int idOrquesta,int idInstrumento)
{
    int retorno=-1;
    if((array!=NULL)&&(len>0))
    {
        strncpy(array[indexPosition].name,nombre,sizeof(array[indexPosition].name));
        strncpy(array[indexPosition].surname,apellido,sizeof(array[indexPosition].surname));
        array[indexPosition].edad=edad;
        array[indexPosition].idOrquesta=idOrquesta;
        array[indexPosition].idInstrumento=idInstrumento;
        array[indexPosition].idMusico=generarId();
        array[indexPosition].isEmpty=0;
        retorno=0;
    }
    return retorno;
}

/** \brief  add values entered by the user to
*           an existing array of musico
*           in an empty position.
* \param    array Musico* Pointer to array of
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int musico_addMusico(Musico* arrayMusico,Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,
                    int lenMusico,int lenOrquesta,int lenInstrumento,char* msgE,int tries)
{
    int indexFree;
    int retorno=-1;
    char bufferName[30];
    char bufferSurname[30];
    char bufferEdad[30];
    int auxEdad;
    int auxIdOrquesta;
    int auxIdInstrumento;
    int posOfIdOrquesta;
    int posofIdInstrumento;
    if((arrayMusico!=NULL)&&(lenMusico>0)&&(arrayOrquesta!=NULL)&&(lenOrquesta>0)
       &&(arrayInstrumento!=NULL)&&(lenInstrumento>0))
    {
        indexFree=musico_findFree(arrayMusico,lenMusico);
        auxIdOrquesta=orquesta_getID(arrayOrquesta,lenOrquesta,msgE,tries);
        auxIdInstrumento=instrumento_getID(arrayInstrumento,lenInstrumento,msgE,tries);
        posOfIdOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,auxIdOrquesta);
        posofIdInstrumento=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,auxIdInstrumento);
        if((indexFree!=-1)&&(auxIdOrquesta>=0)
           &&(posOfIdOrquesta!=-1)&&(auxIdInstrumento>=0)
           &&(posofIdInstrumento!=-1)
           &&(!getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries))
           &&(!getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries))
           &&(!getStringNumeros(bufferEdad,"\nIngrese Edad: ",msgE,tries)))
        {
            auxEdad=atoi(bufferEdad);
            strncpy(arrayMusico[indexFree].name,bufferName,sizeof(bufferName));
            strncpy(arrayMusico[indexFree].surname,bufferSurname,sizeof(bufferSurname));
            arrayMusico[indexFree].edad=auxEdad;
            arrayMusico[indexFree].idOrquesta=auxIdOrquesta;
            arrayMusico[indexFree].idInstrumento=auxIdInstrumento;
            arrayMusico[indexFree].idMusico=generarId();
            arrayMusico[indexFree].isEmpty=0;
            retorno=0;
        }
    }
    return retorno;
}

/** \brief  Modify values in an existing
*           array of musico
*           in an existing position.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    generalMsgE char Shows an error message to be printed
*           when a value is not valid.
* \param    exitMenuNumber int Number that exits the menu
            and also used as max number to stablish a range
            of menu options to acces the corresponding function.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int musico_alter(Musico* arrayMusico,Orquesta* arrayOrquesta,int lenMusico,int lenOrquesta,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferEdad[30];
    int auxEdad;
    char bufferIdOrquesta[30];
    int auxIdOrquesta;
    int posIdOrquesta;
    char* alterMenuText="\n1-Modificar Edad\n2-Modificar Id Orquesta\n"
                        "3- Atras (Menu Principal)\n";
    int retorno=-1;

    if((arrayMusico!=NULL)&&(lenMusico>0)
       &&(arrayOrquesta!=NULL)&&(lenOrquesta>0))
    {
        auxID=musico_getID(arrayMusico,lenMusico,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=musico_findMusicoById(arrayMusico,lenMusico,auxID);
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
                            if(!getStringNumeros(bufferEdad,"\nIngrese NUEVA Edad: ",generalMsgE,tries))
                            {
                                auxEdad=atoi(bufferEdad);
                                arrayMusico[posOfID].edad=auxEdad;
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringNumeros(bufferIdOrquesta,"\nIngrese NUEVO ID de Orquesta: ",generalMsgE,tries))
                            {
                                auxIdOrquesta=atoi(bufferIdOrquesta);
                                posIdOrquesta=orquesta_findOrquestaById(arrayOrquesta,lenOrquesta,auxIdOrquesta);
                                if(auxIdOrquesta>=0 && posIdOrquesta!=-1)
                                {
                                    arrayMusico[posOfID].idOrquesta=auxIdOrquesta;
                                    retorno=0;
                                }
                            }
                            break;
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

/** \brief  Remove a musico by Id (put isEmpty Flag in 1)
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_removeMusico(Musico* array, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(array!=NULL && len>0)
    {
        auxID=musico_getID(array,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=musico_findMusicoById(array,len,auxID);
            if(posOfID!=-1)
            {
               array[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

/** \brief  Remove a musico by Id (put isEmpty Flag in 1)
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_removeMusicoApartirDeOrquesta(Musico* arrayMusico,int lenMusico,int removedOrquestaID)
{
    int i;
    int posIdMusico;
    int retorno=-1;
    if(arrayMusico!=NULL && lenMusico>0&&removedOrquestaID>=0)
    {
        for(i=0;i<lenMusico;i++)
        {
            posIdMusico=musico_findMusicoByIdOrquesta(arrayMusico,lenMusico,arrayMusico[i].idOrquesta==removedOrquestaID);
            if(posIdMusico!=-1)
            {
               arrayMusico[posIdMusico].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by Surname.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicoBySurname(Musico* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Musico buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(strcmp(array[i].surname,array[j].surname)>0))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(array[i].surname,array[j].surname)<0))
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


/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by Nombre.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicoByNombre(Musico* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Musico buffer;
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

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by edad.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicoByEdad(Musico* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Musico buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(array[i].edad>array[j].edad))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(array[i].edad<array[j].edad))
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

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by edad when having equal surname.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicoByEdadMismoSurname(Musico* arrayMusico,int lenMusico,int order)
{
    int i;
    Musico buffer;

    for(i=1;i<lenMusico;i++)
    {
        if(strcmp(arrayMusico[i-1].surname,arrayMusico[i].surname)==0)
        {
            if((order==1)&&(arrayMusico[i-1].edad>arrayMusico[i].edad))
            {
                buffer=arrayMusico[i-1];
                arrayMusico[i-1]=arrayMusico[i];
                arrayMusico[i]=buffer;
            }
            else if((order==0)&&(arrayMusico[i-1].edad<arrayMusico[i].edad))
            {
                buffer=arrayMusico[i-1];
                arrayMusico[i-1]=arrayMusico[i];
                arrayMusico[i]=buffer;
            }
        }
    }
    return 0;
}

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by edad when having equal surname with better method.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicosBySurnameyEdadEficiente(Musico* arrayMusico,
                                                    int lenMusico,int order)///1up 0down
{
    int i;
    int flagNoEstaOrdenado=1;
    int retorno=-1;
    Musico buffer;
    if(arrayMusico!=NULL && lenMusico>0 && (order==0 || order==1))
    {
        while(flagNoEstaOrdenado==1)
        {
            flagNoEstaOrdenado=0;
            for(i=1;i<lenMusico;i++)
            {
                if((order==1)&&(strcmp(arrayMusico[i-1].surname,arrayMusico[i].surname)>0))///Creciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(arrayMusico[i-1].surname,arrayMusico[i].surname)<0))///Decreciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
            }
        }
        if(flagNoEstaOrdenado==0)
        {
            musico_sortMusicoByEdadMismoSurname(arrayMusico,lenMusico,order);
        }
    }
    return retorno;
}

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by instrumento with better method.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicosByInstrumentoEficiente(Musico* arrayMusico,int lenMusico,int order)///1up 0down
{
    int i;
    int flagNoEstaOrdenado=1;
    int retorno=-1;
    Musico buffer;
    if(arrayMusico!=NULL && lenMusico>0 && (order==0 || order==1))
    {
        while(flagNoEstaOrdenado==1)
        {
            flagNoEstaOrdenado=0;
            for(i=1;i<lenMusico;i++)
            {
                if((order==1)&&(arrayMusico[i-1].idInstrumento>arrayMusico[i].idInstrumento))///Creciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
                else if((order==0)&&(arrayMusico[i-1].idInstrumento<arrayMusico[i].idInstrumento))///Decreciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

/** \brief  Sort the elements in the array of musico,
*           UP or DOWN according to its order parameter
*           by orquesta with better method.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int musico_sortMusicosByIdOrquestaEficiente(Musico* arrayMusico,int lenMusico,int order)///1up 0down
{
    int i;
    int flagNoEstaOrdenado=1;
    int retorno=-1;
    Musico buffer;
    if(arrayMusico!=NULL && lenMusico>0 && (order==0 || order==1))
    {
        while(flagNoEstaOrdenado==1)
        {
            flagNoEstaOrdenado=0;
            for(i=1;i<lenMusico;i++)
            {
                if((order==1)&&(arrayMusico[i-1].idOrquesta>arrayMusico[i].idOrquesta))///Creciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
                else if((order==0)&&(arrayMusico[i-1].idOrquesta<arrayMusico[i].idOrquesta))///Decreciente
                {
                    buffer=arrayMusico[i-1];
                    arrayMusico[i-1]=arrayMusico[i];
                    arrayMusico[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}
/** \brief  Indicates that all positions in the array are empty
*           by setting the flag isEmpty in 0 in all positions.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \return   return 0.
**/
int musico_initMusico(Musico* array,int len)
{
    int i;
    if(array!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            //array[i].idMusico=-1;
            array[i].isEmpty=1;
        }
    }
    return 0;
}

/** \brief  Searchs through the array for a musico position.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \return   return (-1) if no position found,
*           (Empty position) if empty position.
**/
int musico_findFree(Musico* array, int len)
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
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    idE Value to be found and matched in the array.
* \return   return (-1) if not found,
*           (position) if position matched.
**/
int musico_findMusicoById(Musico* array, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((array[i].isEmpty==0)&&(array[i].idMusico==idE))
        {
            ret=i;
        }
    }
    return ret;
}

/** \brief  Searchs through the array for a
*           specific value(ID orquesta).
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    idE Value to be found and matched in the array.
* \return   return (-1) if not found,
*           (position) if position matched.
**/
int musico_findMusicoByIdOrquesta(Musico* array, int len, int idE)
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
* \param    array Musico* Pointer to array of Musico
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if error, (ID) if OK
**/
int musico_getID (Musico* array,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(array!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de Musico: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief  Shows the values of occupied positions.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return 0.
**/
int musico_printMusico(Musico* arrayMusico,Instrumento* arrayInstrumento,int lenMusico,int lenInstrumento)
{
    int i;
    int posInst;
    char stringTipo[30];
    int flag=1;
    for(i=0;i<lenMusico;i++)
    {
        if(arrayMusico[i].isEmpty==0)
        {
            posInst=instrumento_findInstrumentoById(arrayInstrumento,lenInstrumento,arrayMusico[i].idInstrumento);
            if(posInst!=-1)
            {
                switch(arrayInstrumento[posInst].tipo)
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
                printf("\nID Musico: %d\nNombre: %s\nApellido: %s\n"
                "Edad: %d\nNombre Instrumento: %s\nTipo: %s\n-------\n",
                       arrayMusico[i].idMusico,
                       arrayMusico[i].name,
                       arrayMusico[i].surname,
                       arrayMusico[i].edad,
                       arrayInstrumento[posInst].name,
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

/** \brief  Shows the values of occupied positions.
* \param    array Musico* Pointer to array of musico
* \param    len int Array len of musico
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return 0.
**/
int musico_printMusicoBasic(Musico* array,int len)
{
    int i;
    int flag=1;
    for(i=0;i<len;i++)
    {
        if(array[i].isEmpty==0)
        {
            printf("\nID Musico: %d\nNombre: %s\nApellido: %s\n",
                   array[i].idMusico,
                   array[i].name,
                   array[i].surname);
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
    static int idMus=1;
    return idMus++;
}
