#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "socio.h"



static int generarId(void);

int socio_menu(Socio* arraySocio,int lenSocio, char* menuText,
             int exitMenuNumber,int tries)
{
    int option=0;
    int flag=0;
    char* noAddMsg="\n----AUN NO HAY SOCIOS EN LA NOMINA----\n";
    char* addMsg="\n----Alta satisfactoria!----\n";
    char* addMsgE="\n----NO se realizo el Alta----\n";
    char* alterMsg="\n----Se modifico exitosamente!----\n";
    char* alterMsgE="\n----NO se realizo la Modificacion----\n";
    char* removeMsg="\n----Se dio de baja exitosamente!----\n";
    char* removeMsgE="\n----NO se realizo la Baja----\n";
    char* generalMsgE="DATO NO VALIDO\n";

    socio_initSocio(arraySocio,lenSocio);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    if(!socio_addSocio(arraySocio,lenSocio,generalMsgE,tries))
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
                    socio_printSocio(arraySocio,lenSocio);
                    if(!socio_alter(arraySocio,lenSocio,generalMsgE,6,tries))
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
                    if(!socio_removeSocio(arraySocio,lenSocio,generalMsgE,tries))
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
                    socio_sortSocio(arraySocio,lenSocio,1);///order UP
                    socio_printSocio(arraySocio,lenSocio);
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

int socio_addSocio(Socio* arraySocio,int lenSocio,char* msgE,int tries)
{
    int indexFree;
    char bufferName[TAM_SOCIO_STRING];
    char bufferSurname[TAM_SOCIO_STRING];
    char bufferGender[10];
    char bufferTelephone[TAM_SOCIO_STRING];
    char bufferMail[31];
    int auxDia;
    int auxMes;
    int auxYear;
    int retorno=-1;
    if((arraySocio!=NULL)&&(lenSocio>0))
    {
        indexFree=socio_findFree(arraySocio,lenSocio);
        if((indexFree!=-1)&&(!getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries))
           &&(!getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries)))
        {
            if((!getGender(bufferGender,"\nIngrese genero F/M: ",msgE,tries))
               &&(!getTelephone(bufferTelephone,"\nIngrese Telefono: ",msgE,tries))
               &&(!getMail(bufferMail,"\nIngrese Mail: ",msgE,tries))
               &&(!getDate(&auxDia,&auxMes,&auxYear,msgE,tries)))
            {
                strncpy(arraySocio[indexFree].name,bufferName,sizeof(bufferName));
                strncpy(arraySocio[indexFree].surname,bufferSurname,sizeof(bufferSurname));
                strncpy(arraySocio[indexFree].sexo,bufferGender,sizeof(bufferGender));
                strncpy(arraySocio[indexFree].telefono,bufferTelephone,sizeof(bufferTelephone));
                strncpy(arraySocio[indexFree].email,bufferMail,sizeof(bufferMail));
                arraySocio[indexFree].dia=auxDia;
                arraySocio[indexFree].mes=auxMes;
                arraySocio[indexFree].year=auxYear;
                arraySocio[indexFree].idSocio=generarId();
                arraySocio[indexFree].isEmpty=0;
                retorno=0;
            }
        }
    }
    return retorno;
}

int socio_alter(Socio* arraySocio, int lenSocio,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferName[TAM_SOCIO_STRING];
    char bufferSurname[TAM_SOCIO_STRING];
    char bufferGender[10];
    char bufferTelephone[TAM_SOCIO_STRING];
    char bufferMail[31];
    char* alterMenuText="\n1-Modificar Nombre\n2-Modificar Apellido\n"
                        "3-Modificar Sexo\n4-Modificar Telefono\n"
                        "5-Modificar Mail\n6- Atras (Menu Principal)\n";
    int retorno=-1;

    if((arraySocio!=NULL)&&(lenSocio>0))
    {
        auxID=socio_getID(arraySocio,lenSocio,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=socio_findSocioById(arraySocio,lenSocio,auxID);
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
                                strncpy(arraySocio[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferSurname,"\nIngrese NUEVO Apellido: ",generalMsgE,tries))
                            {
                                strncpy(arraySocio[posOfID].surname,bufferSurname,sizeof(bufferSurname));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                             if(!getGender(bufferGender,"\nIngrese NUEVO genero F/M: ",generalMsgE,tries))
                             {
                                 strncpy(arraySocio[posOfID].sexo,bufferGender,sizeof(bufferGender));
                             }
                             break;
                        }
                        case 4:
                        {
                             if(!getTelephone(bufferTelephone,"\nIngrese NUEVO Telefono: ",generalMsgE,tries))
                             {
                                 strncpy(arraySocio[posOfID].telefono,bufferTelephone,sizeof(bufferTelephone));
                             }
                             break;
                        }
                        case 5:
                        {
                             if(!getMail(bufferMail,"\nIngrese NUEVO Mail: ",generalMsgE,tries))
                             {
                                 strncpy(arraySocio[posOfID].email,bufferMail,sizeof(bufferMail));
                             }
                             break;
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
    return retorno;
}

int socio_removeSocio(Socio* arraySocio, int lenSocio,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(arraySocio!=NULL && lenSocio>0)
    {
        auxID=socio_getID(arraySocio,lenSocio,msgE,tries);
         if(auxID>=0)
        {
            posOfID=socio_findSocioById(arraySocio,lenSocio,auxID);
            if(posOfID!=-1)
            {
               arraySocio[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

int socio_sortSocio(Socio* arraySocio, int lenSocio,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Socio buffer;
    if(arraySocio!=NULL && lenSocio>0)
    {
        for(i=0;i<lenSocio-1;i++)
        {

            for(j=i+1;j<lenSocio;j++)
            {

                if((order==1)&&(strcmp(arraySocio[i].surname,arraySocio[j].surname)>0))
                {
                    buffer=arraySocio[i];
                    arraySocio[i]=arraySocio[j];
                    arraySocio[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(arraySocio[i].surname,arraySocio[j].surname)<0))
                {
                    buffer=arraySocio[i];
                    arraySocio[i]=arraySocio[j];
                    arraySocio[j]=buffer;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

/*int socio_informarTotalSalariosPromedio(Socio* arraySocio,int lenSocio)
{
    int i;
    float totalResult;
    float promedioResult;
    int socioloyeeOverPromedio;
    int contadorPromedio=0;
    float sum=0;
    int ret=-1;
    if(arraySocio!=NULL && lenSocio>0)
    {
        for(i=0;i<lenSocio;i++)
        {
            if(arraySocio[i].isEmpty==0)
            {
                sum+=arraySocio[i].salary;
                contadorPromedio++;
            }
        }
        totalResult=sum;
        promedioResult=totalResult/contadorPromedio;
        socio_salaryOverPromedio(arraySocio,lenSocio,promedioResult,&socioloyeeOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nEL TOTAL DE SALARIOS ES: %.2f\nEL PROMEDIO DE SALARIOS ES: %.2f\n"
                    "LOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",
                    totalResult,promedioResult,socioloyeeOverPromedio);
        }
    }
    return ret;
}*/

/*int socio_salaryOverPromedio(Socio* arraySocio,int lenSocio,float promedioResult,int* valor)
{
    int i;
    int contadorSocio=0;
    int ret=-1;
    if(arraySocio!=NULL && lenSocio>0 && valor!=NULL)
    {
        for(i=0;i<lenSocio;i++)
        {
            if(arraySocio[i].isEmpty==0)
            {
                if(arraySocio[i].salary>promedioResult)
                {
                    contadorSocio++;
                }
            }

        }
        *valor=contadorSocio;
        ret=0;
    }
    return ret;
}*/

int socio_initSocio(Socio* arraySocio,int lenSocio)
{
    int i;
    if(arraySocio!=NULL && lenSocio>0)
    {
        for(i=0; i<lenSocio;i++)
        {
            //arraySocio[i].idSocio=-1;
            arraySocio[i].isEmpty=1;
        }
    }
    return 0;
}

int socio_findFree(Socio* arraySocio, int lenSocio)
{
    int i;
    int ret=-1;
    if(arraySocio!=NULL && lenSocio>0)
    {
        for(i=0;i<lenSocio;i++)
        {
            if(arraySocio[i].isEmpty==1)
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

int socio_findSocioById(Socio* arraySocio, int lenSocio, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<lenSocio;i++)
    {
        if((arraySocio[i].isEmpty==0)&&(arraySocio[i].idSocio==idE))
        {
            ret=i;
        }
    }
    return ret;
}

int socio_getID (Socio* arraySocio,int lenSocio,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(arraySocio!=NULL && lenSocio>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de Socio: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

int socio_printSocio(Socio* arraySocio,int lenSocio)
{
    int i;
    int flag=1;
    for(i=0;i<lenSocio;i++)
    {
        if(arraySocio[i].isEmpty==0)
        {
            printf("\nCodigo Socio: %d\nNombre: %s\nApellido: %s\n"
                   "Sexo: %s\nEmail: %s\nTelefono: %s\n"
                   "Fecha: %d/%d/%d\n-----------\n",
                   arraySocio[i].idSocio,
                   arraySocio[i].name,
                   arraySocio[i].surname,
                   arraySocio[i].sexo,
                   arraySocio[i].email,
                   arraySocio[i].telefono,
                   arraySocio[i].dia,
                   arraySocio[i].mes,
                   arraySocio[i].year);
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

