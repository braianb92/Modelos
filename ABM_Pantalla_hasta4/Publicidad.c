#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pantalla.h"
#include "Publicidad.h"
#include "utn_strings.h"
static int generarId(void);

int pub_initPublicidad(Publicidad* pPublicidad,int len)
{
    int i;
    if(pPublicidad!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            pPublicidad[i].idPublicidad=-1;
            pPublicidad[i].isEmpty=1;
        }
    }
    return 0;
}

int pub_addPub(Publicidad* pPublicidad,Pantalla* pPantalla,int len,char* msgE,int tries)
{
    int auxIDPantalla;
    int posOfId;
    int indexFree;
    char bufferCuit[20];
    char bufferArchivo[250];
    char bufferDias[20];
    int auxDias;
    int retorno=-1;
    if((pPublicidad!=NULL)&&(len>0))
    {
        auxIDPantalla=pub_getID(pPublicidad,len,msgE,tries);

        indexFree = pub_findFree(pPublicidad,len);

        posOfId=pan_findPanById(pPantalla,len,auxIDPantalla);


        if((auxIDPantalla>=0)&&(posOfId!=-1))
        {
            if((!getCuit(bufferCuit,"\nIngrese CUIT: ",msgE,tries))&&
               (!getStringAlphanumeric(bufferArchivo,"\nIngrese nombre de Archivo: ",msgE,tries)))
               {
                   if(!getStringNumeros(bufferDias,"\nIngrese Dias a contratar: ",msgE,tries))
                   {
                       auxDias=atoi(bufferDias);
                       strncpy(pPublicidad[indexFree].cuit,bufferCuit,sizeof(bufferCuit));
                       strncpy(pPublicidad[indexFree].archivo,bufferArchivo,sizeof(bufferArchivo));
                       pPublicidad[indexFree].dias=auxDias;
                       pPublicidad[indexFree].idPantalla = auxIDPantalla;
                       pPublicidad[indexFree].idPublicidad=generarId();
                       pPublicidad[indexFree].isEmpty=0;
                       retorno=0;
                   }
               }
        }
        else
        {
            printf("\n----EL ID de pantalla no es valido!----\n");
        }
    }

    return retorno;
}

int pub_alterContratacion(Publicidad* pPublicidad, int len,char* msgE,int tries)
{
    char bufferCuit[50];
    int posOfCuit;
    int opcion=0;
    char bufferName[50];
    char bufferAdress[250];
    char bufferPrecio[20];
    char bufferTipo[20];
    float auxPrecio;
    int auxTipo;
    int retorno=-1;

    if((pPublicidad!=NULL)&&(len>0))
    {
        getCuit(bufferCuit,"\nIngrese CUIT: ",msgE,tries);
        posOfCuit=pub_findCuit(pPublicidad,len,bufferCuit);
        if((bufferCuit!=-1)&&(posOfCuit>=0))
        {
            pub_printPantallasByCuit(pPublicidad,pPantalla,len,len,bufferCuit);
                while(opcion!=5)
                {

                    printf("4- Modificar Dias\n");
                    printf("5- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,5,tries);
                    switch(opcion)
                    {
                        case 1:
                        {
                            if(!getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",msgE,tries))
                            {
                                strncpy(pPantalla[posOfID].nombre,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferAdress,"\nIngrese NUEVA Direccion: ",msgE,tries))
                            {
                                strncpy(pPantalla[posOfID].direccion,bufferAdress,sizeof(bufferAdress));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(!getStringNumerosFloat(bufferPrecio,"\nIngrese NUEVO Precio: ",msgE,tries))
                            {
                                auxPrecio=atof(bufferPrecio);
                                pPantalla[posOfID].precio=auxPrecio;
                                retorno=0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(!getStringNumeros(bufferTipo,"\nIngrese NUEVO Tipo: ",msgE,tries))
                            {
                                auxTipo=atoi(bufferTipo);
                                pPantalla[posOfID].tipo=auxTipo;
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

int pub_removePublicidad(Publicidad* pPublicidad, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(pPublicidad!=NULL && len>0)
    {
        auxID=pub_getID(pPublicidad,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=pub_findPubById(pPublicidad,len,auxID);
            if(posOfID!=-1)
            {
               pPublicidad[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

int pub_printPantallasByCuit(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub,char* valor)
{
    int i;
    int posPan;
    int flag=1;
    for(i=0;i<lenPub;i++)
    {
        if((pPublicidad[i].isEmpty==0)&&(strncmp(pPublicidad[i].cuit,valor,sizeof(valor)==0))
        {
            posPan=pan_findPanById(pPantalla,lenPan,pPublicidad[i].idPantalla);
            if(posPan>=0)
            {
                printf("\nCUIT: %s\nID Pantalla: %d\nNombre: %s\nDireccion: %s\n"
                        "Precio: %.2f\nTipo: %d",
                        pPublicidad[i].cuit,
                        pPantalla[posPan].idPantalla,
                        pPantalla[posPan].nombre,
                        pPantalla[posPan].direccion,
                        pPantalla[posPan].precio,
                        pPantalla[posPan].tipo);
            }
        }
    }
    return 0;
}

int pub_printContDiasMenorA(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub,int valor)
{
    int i;
    int posPan;
    float total;
    for(i=0;i<lenPub;i++)
    {
        if(pPantalla[i].isEmpty==0)
        {
            if(pPublicidad[i].isEmpty==0)
            {
                if(pPublicidad[i].dias<=valor)
                {
                    posPan=pan_findPanById(pPantalla,lenPan,pPublicidad[i].idPantalla);

                    if(posPan>=0)
                    {
                        total=pPantalla[posPan].precio * pPublicidad[i].dias;
                        ///nombre dias total
                        printf("%d %s %.2f %d %.2f",pPantalla[posPan].nombre,
                                pPantalla[posPan].precio,
                                pPublicidad[i].dias,
                                total);
                    }
                }
            }
        }
    }
    return 0;
}

int pub_printContrataciones(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub)
{
    int i;
    int posPant;
    int flag=1;
    for(i=0;i<lenPub;i++)
    {
        if(pPublicidad[i].isEmpty==0)
        {
            posPant=pan_findPanById(pPantalla,lenPan,pPublicidad[i].idPantalla);
            if(posPant>=0)
            {
                printf("\nID Pub: %d\nNombre Pantalla: %s\nArchivo: %s\nDias: %d\nCUIT: %s\n-------",
                        pPublicidad[i].idPantalla,
                        pPantalla[posPant].nombre,
                        pPublicidad[i].archivo,
                        pPublicidad[i].dias,
                        pPublicidad[i].cuit);
                flag=0;
            }

        }
    }
    if(flag)
    {
        printf("\n----No hay Contrataciones!----\n");
    }
    return 0;
}

int pub_findCuit(Publicidad* pPublicidad, int len,char* cuit)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pPublicidad[i].cuit==cuit)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int pub_findPubById(Publicidad* pPublicidad, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pPublicidad[i].idPublicidad==idE)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int pub_findFree(Publicidad* pPublicidad, int len)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pPublicidad[i].isEmpty==1)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int pub_getID (Publicidad* pPublicidad,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(pPublicidad!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID de pantalla a contratar: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

static int generarId(void)
{
    static int idPubli=0;
    return idPubli++;
}

