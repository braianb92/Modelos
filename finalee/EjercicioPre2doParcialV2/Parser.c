#include "LinkedList.h"

int parser_parseEmpleados(char* fileName, LinkedList* listaEmpleados)
{
    char bufferId[4096];
    char bufferNombre[4096];
    char bufferHorasTrabajadas[4096];
    int cantidadDatos;
    Employee *pEmpleado;
    int retorno=-1;

    if(pFile != NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^\n]\n",  bufferId,
                                                  bufferNombre,
                                                  bufferHorasTrabajadas);
        do
        {
            cantidadDatos=fscanf(pFile,"%[^,],%[^,],%[^\n]\n",  bufferId,
                                                  bufferNombre,
                                                  bufferHorasTrabajadas);
            if(cantidadDatos==3)
            {
                pEmpleado = employee_newParametros( bufferId,
                                                    bufferNombre,
                                                    bufferHorasTrabajadas);
                if(pEmpleado != NULL)
                {
                    if(!ll_add(pArrayListEmployee,pEmpleado))
                    {
                        retorno=1;
                    }
                }
            }
        }while(!feof(pFile));
    }
    return retorno;
}

