#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "autor.h"

static int generarId(void);

int autor_menu(Autor* array,int len, char* menuText,
             int exitMenuNumber,int tries)
{
    int option=0;
    int flag=0;
    char* noAddMsg="\n----AUN NO HAY AUTORES EN LA NOMINA----\n";
    char* addMsg="\n----Alta satisfactoria!----\n";
    char* addMsgE="\n----NO se realizo el Alta----\n";
    char* alterMsg="\n----Se modifico exitosamente!----\n";
    char* alterMsgE="\n----NO se realizo la Modificacion----\n";
    char* removeMsg="\n----Se dio de baja exitosamente!----\n";
    char* removeMsgE="\n----NO se realizo la Baja----\n";
    char* generalMsgE="DATO NO VALIDO\n";

    autor_initAutor(array,len);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    if(!autor_addAutor(array,len,generalMsgE,tries))
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
                    autor_printAutor(array,len);
                    if(!autor_alter(array,len,generalMsgE,5,tries))
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
                    if(!autor_removeAutor(array,len,generalMsgE,tries))
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
            case 4:
                if(flag)
                {
                    autor_sortAutor(array,len,1);///order UP
                    autor_printAutor(array,len);
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

int autor_addAutor(Autor* array,int len,char* msgE,int tries)
{
    int indexFree;
    char bufferName[50];
    char bufferSurname[50];
    int retorno=-1;
    if((array!=NULL)&&(len>0))
    {
        indexFree=autor_findFree(array,len);
        if((indexFree!=-1)&&(getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries)==0)&&
            (getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries)==0))
        {
            strncpy(array[indexFree].name,bufferName,sizeof(bufferName));
            strncpy(array[indexFree].surname,bufferSurname,sizeof(bufferSurname));
            array[indexFree].idAutor=generarId();
            array[indexFree].isEmpty=0;
            retorno=0;
        }
    }
    return retorno;
}

int autor_alter(Autor* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferName[50];
    char bufferSurname[50];
    char* alterMenuText="\n1-Modificar Nombre\n2-Modificar Apellido\n"
                        "3- Atras (Menu Principal)\n";
    int retorno=-1;

    if((array!=NULL)&&(len>0))
    {
        auxID=autor_getID(array,len,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=autor_findAutorById(array,len,auxID);
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
                            if(!getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",generalMsgE,tries))
                            {
                                strncpy(array[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferSurname,"\nIngrese NUEVO Apellido: ",generalMsgE,tries))
                            {
                                strncpy(array[posOfID].surname,bufferSurname,sizeof(bufferSurname));
                                retorno=0;
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

int autor_removeAutor(Autor* array, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(array!=NULL && len>0)
    {
        auxID=autor_getID(array,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=autor_findAutorById(array,len,auxID);
            if(posOfID!=-1)
            {
               array[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

int autor_sortAutor(Autor* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Autor buffer;
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

/*int autor_informarTotalSalariosPromedio(Autor* array,int len)
{
    int i;
    float totalResult;
    float promedioResult;
    int autorloyeeOverPromedio;
    int contadorPromedio=0;
    float sum=0;
    int ret=-1;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==0)
            {
                sum+=array[i].salary;
                contadorPromedio++;
            }
        }
        totalResult=sum;
        promedioResult=totalResult/contadorPromedio;
        autor_salaryOverPromedio(array,len,promedioResult,&autorloyeeOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nEL TOTAL DE SALARIOS ES: %.2f\nEL PROMEDIO DE SALARIOS ES: %.2f\n"
                    "LOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",
                    totalResult,promedioResult,autorloyeeOverPromedio);
        }
    }
    return ret;
}*/

/*int autor_salaryOverPromedio(Autor* array,int len,float promedioResult,int* valor)
{
    int i;
    int contadorAutor=0;
    int ret=-1;
    if(array!=NULL && len>0 && valor!=NULL)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==0)
            {
                if(array[i].salary>promedioResult)
                {
                    contadorAutor++;
                }
            }

        }
        *valor=contadorAutor;
        ret=0;
    }
    return ret;
}*/

int autor_initAutor(Autor* array,int len)
{
    int i;
    if(array!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            //array[i].idAutor=-1;
            array[i].isEmpty=1;
        }
    }
    return 0;
}

int autor_findFree(Autor* array, int len)
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

int autor_findAutorById(Autor* array, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((array[i].isEmpty==0)&&(array[i].idAutor==idE))
        {
            ret=i;
        }
    }
    return ret;
}

int autor_getID (Autor* array,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(array!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de Autor: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

int autor_printAutor(Autor* array,int len)
{
    int i;
    int flag=1;
    for(i=0;i<len;i++)
    {
        if(array[i].isEmpty==0)
        {
            printf("\nID: %d\nNombre: %s\nApellido: %s\n-------",
                   array[i].idAutor,array[i].name,array[i].surname);
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
