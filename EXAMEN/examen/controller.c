#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "entregas.h"
#include "controller.h"
#include "parser.h"
#include "baldino_validation.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEntrega)
{
    FILE* pFile;
    int retorno=-1;
    if(pArrayListEntrega!=NULL)
    {
        pFile = fopen(path,"r");
        if(pFile!=NULL)
        {
            if(!parser_EntregaFromText(pFile , pArrayListEntrega))
            {
                fclose(pFile);
                retorno=0;
            }
        }
    }
    return retorno;
}


/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_addEntrega(LinkedList* pArrayListEntrega)
{
    Entrega* newEmp;
    char bufferId[4096];
    char bufferTipo[4096];
    char bufferCantidad[4096];
    char bufferPeso[4096];
    int retorno=-1;

    if(pArrayListEntrega!=NULL)
    {
        if((!getStringNumeros(bufferId,"Ingrese ID:","DATO NO VALIDO\n",3))
           &&(!getStringLetras(bufferTipo,"Ingrese Tipo: ","DATO NO VALIDO",3))
           &&(!getStringNumeros(bufferCantidad,"Ingrese Horas Trabajadas(int): ","DATO NO VALIDO",3))
           &&(!getStringNumeros(bufferPeso,"Ingrese Peso(int): ","DATO NO VALIDO",3)))
        {
            newEmp=entrega_newParametros(bufferId,bufferTipo,bufferCantidad,bufferPeso);
            if(newEmp!=NULL)
            {
                ll_add(pArrayListEntrega,newEmp);
                retorno=0;
            }
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_editEntrega(LinkedList* pArrayListEntrega)
{
    Entrega* pEntrega;
    int retorno = -1;
    int tamLista;
    char bufferId[4096];
    int auxId;
    char bufferTipo [4096];
    char bufferCantidad [4096];
    char bufferPeso [4096];
    int i;
    int option;

    if (pArrayListEntrega != NULL)
    {
        tamLista = ll_len(pArrayListEntrega);
        if(!getStringNumeros(bufferId,"Ingrese el ID del empleado que desea modificar: ","DATO NO VALIDO\n",3))
        {
            auxId=atoi(bufferId);
            for (i=0;i<tamLista;i++)
            {
                pEntrega=ll_get(pArrayListEntrega,i);
                if(auxId == pEntrega->id)
                {
                    do
                    {
                        printf("Elija que desea modificar: \n");
                        printf("1- Tipo del empleado\n2- Horas que trabajo el empleado\n"
                               "3- Peso del empleado\n4- Salir\n");
                        getIntInRange(&option,"Ingrese Opcion: ","DATO NO VALIDO\n",1,4,3);
                        switch (option)
                        {
                            case 1:
                                if(!getStringLetras(bufferTipo,"Ingrese Nuevo Tipo: ","DATO NO VALIDO\n",3))
                                {
                                    entrega_setTipo(pEntrega,bufferTipo);
                                    retorno=0;
                                }
                                break;
                            case 2:
                                if(!getStringNumeros(bufferCantidad,"Ingrese Horas Trabajadas: ","DATO NO VALIDO\n",3))
                                {
                                    entrega_setCantidad(pEntrega,bufferCantidad);
                                    retorno=0;
                                }
                                break;
                            case 3:
                                if(!getStringNumeros(bufferPeso,"Ingrese Nuevo Peso: ","DATO NO VALIDO\n",3))
                                {
                                    entrega_setPeso(pEntrega,bufferPeso);
                                    retorno=0;
                                }
                                break;
                        }
                    }while (option != 4);
                }
            }
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_removeEntrega(LinkedList* pArrayListEntrega)
{
    Entrega* pEntrega;
    int tamLista;
    char bufferId[4096];
    int auxId;
    int i;
    int retorno = -1;

    if(pArrayListEntrega != NULL)
    {
        tamLista=ll_len(pArrayListEntrega);
        if(!getStringNumeros(bufferId,"Ingrese ID empleado a eliminar: ","DATO NO VALIDO\n",3))
        {
            auxId=atoi(bufferId);
            if(auxId>=0&&tamLista>0)
            {
                for (i = 0; i < tamLista; i++)
                {
                    pEntrega=ll_get(pArrayListEntrega,i);
                    if (pEntrega->id == auxId)
                    {
                        ll_remove(pArrayListEntrega, i);
                        entrega_delete(pEntrega);
                        retorno=0;
                        break;
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_ListEntrega(LinkedList* pArrayListEntrega)
{
    Entrega* pE;
    int auxId;
    int auxPeso;
    int auxHoras;
    char auxTipo[4096];
    int size;
    int i;

    if(pArrayListEntrega!=NULL)
    {
        size=ll_len(pArrayListEntrega);
        for(i=0;i<size;i++)
        {
            pE=ll_get(pArrayListEntrega,i);
            entrega_getId(pE,&auxId);
            entrega_getTipo(pE,auxTipo);
            entrega_getPeso(pE,&auxPeso);
            entrega_getCantidad(pE,&auxHoras);
            if(pE!=NULL)
            {
                printf("%d,%s,%d,%d\n",auxId,
                                        auxTipo,
                                        auxPeso,
                                        auxHoras);
            }
        }
    }
   return 1;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_sortEntrega(LinkedList* pArrayListEntrega)
{
    int retorno=-1;
    if(pArrayListEntrega!=NULL)
    {
        ll_sort(pArrayListEntrega,entrega_sortByTipo,1);
        retorno=0;
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEntrega LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEntrega)
{
    Entrega* pE;
    int auxId;
    int auxPeso;
    int auxHoras;
    char auxTipo[4096];
    int size;
    int i;

    FILE* fp=fopen(path,"w");
    if(fp!=NULL && pArrayListEntrega!=NULL)
    {
        fprintf(fp,"id,tipo,cantidad,peso\n");
        size=ll_len(pArrayListEntrega);
        for(i=0;i<size;i++)
        {
            pE=ll_get(pArrayListEntrega,i);
            entrega_getId(pE,&auxId);
            entrega_getTipo(pE,auxTipo);
            entrega_getPeso(pE,&auxPeso);
            entrega_getCantidad(pE,&auxHoras);
            if(pE!=NULL)
            {
                fprintf(fp,"%d,%s,%d,%d\n",auxId,
                                        auxTipo,
                                        auxHoras,
                                        auxPeso);
            }
        }
        fclose(fp);
        return 0;
    }
    return 1;
}

