#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "utn_strings.h"

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

int Pan_alta(Pantalla* pPantalla,int len,int pIndex,int idE,char* msgE)
{
    char bufferName[50];
    char bufferAdress[250];
    float auxPrecio;
    int auxTipo;
    int retorno=0;
    while(retorno==0)
    {
        if(getStringLetras(bufferName,"\nIngrese Nombre: ",msgE))
        {
            break;
        }
        if(getStringAlphanumeric(bufferAdress,"\nIngrese Direccion: ",msgE,3))
        {
            break;
        }
        if(getFloat(&auxPrecio,"\nIngrese Precio: ",msgE))
        {
            break;
        }
        if(getInt(&auxTipo,"\nIngrese tipo de pantalla 1(LCD-PASEO COMER.) / 2(LED-VIA PUB.): ",msgE))
        {
            break;
        }
        if(auxTipo!=1 && auxTipo!=2)
        {
            printf(msgE);
            break;
        }
        strncpy(pPantalla[pIndex].nombre,bufferName,sizeof(bufferName));
        strncpy(pPantalla[pIndex].direccion,bufferAdress,sizeof(bufferAdress));
        pPantalla[pIndex].precio=auxPrecio;
        pPantalla[pIndex].tipo=auxTipo;
        pPantalla[pIndex].isEmpty=0;
        pPantalla[pIndex].idPantalla=idE;
        retorno=1;
    }
    return retorno;
}

int Pan_modifyFromID(Pantalla* pPantalla, int len,char* msgE)
{
    char bufferID[20];
    char bufferName[50];
    char bufferAdress[250];
    float auxPrecio;
    int auxID;
    int posOfID;
    int auxTipo;
    int retorno=0;

    do
    {
        if(getStringNumeros(bufferID,"\nIngrese ID: ",msgE))
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
        if(getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",msgE))
        {
            break;
        }
        if(getStringLetras(bufferAdress,"\nIngrese NUEVA Direccion: ",msgE))
        {
            break;
        }
           if(getFloat(&auxPrecio,"\nIngrese NUEVO Precio: ",msgE))
        {
            break;
        }
        if(getIntInRange(&auxTipo,"\nIngrese NUEVO tipo de pantalla 1(LCD-PASEO COMER.) / 2(LED-VIA PUB.): ",msgE,1,2,3))
        {
            break;
        }
        strncpy(pPantalla[posOfID].nombre,bufferName,sizeof(bufferName));
        strncpy(pPantalla[posOfID].direccion,bufferAdress,sizeof(bufferAdress));
        pPantalla[posOfID].precio=auxPrecio;
        pPantalla[posOfID].tipo=auxTipo;
        retorno=1;
    }while(retorno==0);
    return retorno;
}

int Pan_bajaLogica(Pantalla* pPantalla, int len,char* msgE)
{
    char bufferID[20];
    int auxID;
    int posOfID;
    int retorno=0;

    do
    {
        if(getStringNumeros(bufferID,"\nIngrese ID: ",msgE))
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
