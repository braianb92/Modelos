#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "entregas.h"
#include "parser.h"
#include "baldino_validation.h"
#include "informe.h"

int generarArchivoInformes(char* fileName,LinkedList* arrayList)
{
    int auxMax;
    int promBulto;
    int promPeso;
    int size;

    FILE* fp=fopen(fileName,"w+");
    if(fp!=NULL && arrayList!=NULL)
    {

        fprintf(fp,"cant_ent,cant_x_tipo,cant_max_entregado,prom,peso_prom\n");
        size=ll_len(arrayList);
        cantidadMaxima(arrayList,&auxMax);
        promedioBultosxEntrega(arrayList,&promBulto);
        pesoPromxEntrega(arrayList,&promPeso);
        //FALTA POR TIPO
        fprintf(fp,"%d,%d,%d,%d",   size,
                                    auxMax,
                                    promBulto,
                                    promPeso);
        fclose(fp);
        return 0;
    }
    return 1;
}

int cantidadMaxima(LinkedList* arrayList,int* CantMaxEntregas)
{
    Entrega* pEntrega;
    int i;
    int cantidad;
    int auxMax=0;
    int retorno=-1;

    if(arrayList!=NULL)
    {
        for(i=0;i<ll_len(arrayList);i++)
        {
            pEntrega=ll_get(arrayList,i);
            entrega_getCantidad(pEntrega,&cantidad);
            if(pEntrega!=NULL&&cantidad>auxMax)
            {
                auxMax=cantidad;
            }
        }
        *CantMaxEntregas=auxMax;
        retorno=0;
    }

    return retorno;
}


int promedioBultosxEntrega(LinkedList* arrayList,int* promBultos)
{
    Entrega* pEntrega;
    int i;
    int cantidad;
    int cantTotal=0;
    int size;
    int retorno=-1;

    if(arrayList!=NULL)
    {
        size=ll_len(arrayList);
        for(i=0;i<size;i++)
        {
            pEntrega=ll_get(arrayList,i);
            entrega_getCantidad(pEntrega,&cantidad);
            if(pEntrega!=NULL&&cantidad>=0)
            {
                cantTotal+=cantidad;
            }
        }
        *promBultos=cantTotal/size;
        retorno=0;
    }

    return retorno;
}

int pesoPromxEntrega(LinkedList* arrayList,int* pesoProm)
{
    Entrega* pEntrega;
    int i;
    int peso;
    int cantTotal=0;
    int size;
    int retorno=-1;

    if(arrayList!=NULL)
    {
        size=ll_len(arrayList);
        for(i=0;i<size;i++)
        {
            pEntrega=ll_get(arrayList,i);
            entrega_getPeso(pEntrega,&peso);
            if(pEntrega!=NULL&&peso>=0)
            {
                cantTotal+=peso;
            }
        }
        *pesoProm=cantTotal/size;
        retorno=0;
    }

    return retorno;
}

int porTipo(LinkedList* arrayList,int* cantidad)
{
    int retorno=-1;

    if(arrayList!=NULL&&cantidad!=NULL)
    {

    }

    return retorno;

}
