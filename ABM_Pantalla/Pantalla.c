#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "utn_strings.h"
static int generarId(void);


int Pan_inicializarArray(Pantalla* pPantalla,int len)
{
    int i;
    for(i=0; i<len;i++)
    {
        pPantalla[i].isEmpty=1;
    }
    return 0;
}

int Pan_mostrarArray(Pantalla* pPantalla,int len)
{
    int i;
    int flag=1;
    for(i=0;i<len;i++)
    {
        if(pPantalla[i].isEmpty==0)
        {
            flag=0;
            printf("\nID: %d\nNombre: %s\nDireccion: %s\nPrecio: %.2f\nTipo 1(LCD-PASEO COMERCIAL) / 2 (LED-VIA PUBLICA): %d\n-------",
                   pPantalla[i].idPantalla,pPantalla[i].nombre,pPantalla[i].direccion,pPantalla[i].precio,pPantalla[i].tipo);
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

int Pan_alta(Pantalla* pPantalla,int len,int pIndex,char* msgE,int reintentos)
{
    char bufferName[50];
    char bufferAdress[250];
    char bufferPrecio[50];
    char bufferTipo[50];
    float auxPrecio;
    int auxTipo;
    int retorno=-1;

    if((pPantalla!=NULL)&&(len>0))
    {
        if(((getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,reintentos)==0)&&
            (getStringAlphanumeric(bufferAdress,"\nIngrese Direccion: ",msgE,reintentos)==0)))
        {
            printf("Segundo");
            if((getStringNumerosFloat(bufferPrecio,"\nIngrese Precio: ",msgE,reintentos)==0)
                &&(getStringNumeros(bufferTipo,"\nIngrese Tipo 1-LCD Paseo Comp. / 2-"
                "Via Publ.: ",msgE,reintentos)==0))
            {
                printf("tercer");
                auxTipo=atoi(bufferTipo);
                auxPrecio=atof(bufferPrecio);
                printf("%d",auxTipo);
                if(auxTipo==1 || auxTipo==2)
                {
                    strncpy(pPantalla[pIndex].nombre,bufferName,sizeof(bufferName));
                    strncpy(pPantalla[pIndex].direccion,bufferAdress,sizeof(bufferAdress));
                    pPantalla[pIndex].precio=auxPrecio;
                    pPantalla[pIndex].tipo=auxTipo;
                    pPantalla[pIndex].isEmpty=0;
                    pPantalla[pIndex].idPantalla=generarId();
                }
            }
        }

    }
    return retorno;
}

int Pan_modifyFromID(Pantalla* pPantalla, int len,char* msgE,int reintentos)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferName[50];
    char bufferAdress[250];
    char bufferPrecio[20];
    char bufferTipo[20];
    float auxPrecio;
    int auxTipo;
    int retorno=0;

    if((pPantalla!=NULL)&&(len>0))
    {
        if(getInt(&auxID,"\nIngrese ID: ",msgE)==0)
        {
            if((posOfID=Pan_findID(pPantalla,len,auxID))&&(posOfID!=-1))
            {
                while(opcion!=5)
                {
                    getIntInRange(&opcion,"\n1)Modificar Nombre\n2)Modificar Direccion\n"
                                "3)Modificar Precio\n4)Modificar Tipo\n5)Salir",msgE,1,5,reintentos);
                    switch(opcion)
                    {
                        case 1:
                        {
                            if(getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",msgE,reintentos)==0)
                            {
                                strncpy(pPantalla[posOfID].nombre,bufferName,sizeof(bufferName));
                            }
                            break;
                        }
                        case 2:
                        {
                            if(getStringAlphanumeric(bufferAdress,"\nIngrese NUEVA Direccion: ",msgE,reintentos)==0)
                            {
                                strncpy(pPantalla[posOfID].direccion,bufferAdress,sizeof(bufferAdress));
                            }
                            break;
                        }
                        case 3:
                        {
                            if(getStringNumerosFloat(bufferPrecio,"\nIngrese NUEVO Precio: ",msgE,reintentos)==0)
                            {
                                auxPrecio=atof(bufferPrecio);
                                pPantalla[posOfID].precio=auxPrecio;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(getStringNumeros(bufferTipo,"\nIngrese Tipo 1-LCD Paseo Comp. / 2-"
                                "Via Publ.: ",msgE,reintentos)==0)
                            {
                                auxTipo=atoi(bufferTipo);
                                pPantalla[posOfID].tipo=auxTipo;
                            }
                            break;
                        }

                    }

                }

            }
        }
    }

    return retorno;
}

int Pan_bajaLogica(Pantalla* pPantalla, int len,char* msgE,int reintentos)
{
    char bufferID[20];
    int auxID;
    int posOfID;
    int retorno=0;

    do
    {
        if(getStringNumeros(bufferID,"\nIngrese ID: ",msgE,reintentos))
        {
            break;
        }
        auxID=atoi(bufferID);
        posOfID=Pan_findID(pPantalla,len,auxID);
        if(posOfID==-1)
        {
            printf("\n----El ID no existe!----\n");
            break;
        }
        pPantalla[posOfID].isEmpty=1;
        retorno=1;
    }while(retorno==0);
    return retorno;
}

int Pan_orderByPrice(Pantalla* pPantalla, int len)
{
    int i;
    int j;
    Pantalla buffer;
    for(i=0;i<len-1;i++)
    {
        if(pPantalla[i].isEmpty==1)
        {
            continue;
        }
        for(j=i+1;j<len;j++)
        {
            if(pPantalla[j].isEmpty==1)
            {
                continue;
            }
            if(pPantalla[i].precio>pPantalla[j].precio)
            {
                buffer=pPantalla[i];
                pPantalla[i]=pPantalla[j];
                pPantalla[j]=buffer;
            }
        }
    }
    return 0;
}

int Pan_orderByID(Pantalla* pPantalla, int len)
{
    int i;
    int j;
    Pantalla buffer;
    for(i=0;i<len-1;i++)
    {
        if(pPantalla[i].isEmpty==1)
        {
            continue;
        }
        for(j=i+1;j<len;j++)
        {
            if(pPantalla[j].isEmpty==1)
            {
                continue;
            }
            if(pPantalla[i].idPantalla>pPantalla[j].idPantalla)
            {
                buffer=pPantalla[i];
                pPantalla[i]=pPantalla[j];
                pPantalla[j]=buffer;
            }
        }
    }
    return 0;
}

int Pan_findID(Pantalla* pPantalla, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pPantalla[i].idPantalla==idE)
        {
            ret=i;
        }
    }
    return ret;
}

int Pan_posLibre(Pantalla* pPantalla, int len)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pPantalla[i].isEmpty==1)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

static int generarId(void)
{
    static int idPant=0;
    return idPant++;
}
