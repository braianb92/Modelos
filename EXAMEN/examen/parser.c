#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "entregas.h"
#include "parser.h"


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int parser_EntregaFromText(FILE* pFile , LinkedList* pArrayListEntrega)
{
    char bufferId[4096];
    char bufferTipo[4096];
    char bufferCantidad[4096];
    char bufferPeso[4096];
    int cantidadDatos;
    Entrega *pEmpleado;
    int retorno=-1;

    if(pFile != NULL && pArrayListEntrega!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",  bufferId,
                                                  bufferTipo,
                                                  bufferCantidad,
                                                  bufferPeso);
        do
        {
            cantidadDatos=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",  bufferId,
                                                  bufferTipo,
                                                  bufferCantidad,
                                                  bufferPeso);
            if(cantidadDatos==4)
            {
                pEmpleado = entrega_newParametros( bufferId,
                                                    bufferTipo,
                                                    bufferCantidad,
                                                    bufferPeso);
                if(pEmpleado != NULL)
                {
                    if(!ll_add(pArrayListEntrega,pEmpleado))
                    {
                        retorno=0;
                    }
                }
            }
        }while(!feof(pFile));
    }
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int parser_EntregaFromBinary(FILE* pFile , LinkedList* pArrayListEntrega)
{
    Entrega* pe;
    int cantidad;
    int retorno=-1;

    do
    {
        pe=entrega_new();
        if(pe!=NULL&&pFile!=NULL&&pArrayListEntrega!=NULL)
        {
            cantidad=fread(pe,sizeof(Entrega),1,pFile);
            if(cantidad==1)
            {
                if(!ll_add(pArrayListEntrega,pe))
                {
                    retorno=0;
                }
            }
            else
            {
                entrega_delete(pe);
                retorno=0;
            }
        }
    }while(!feof(pFile));
    return retorno;
}
