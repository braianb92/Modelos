#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entregas.h"
#include "baldino_validation.h"


Entrega* entrega_new()
{
    return (Entrega*) malloc(sizeof(Entrega));
}

Entrega* entrega_newParametros(char* idStr,char* tipoStr,char* cantidadStr,char* peso)
{

    Entrega* emp=entrega_new();
    if(emp!=NULL)
    {
        entrega_setId(emp,idStr);
        entrega_setTipo(emp,tipoStr);
        entrega_setCantidad(emp,cantidadStr);
        entrega_setPeso(emp,peso);
    }
    return emp;
}

int entrega_delete(Entrega* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}

int entrega_setId(Entrega* this, char* value)
{
    int auxID;
    int retorno = -1;

    if(this != NULL && value!=NULL && isNumber(value))
    {
        auxID=atoi(value);
        if(auxID>=0)
        {
            this->id = auxID;
            retorno = 0;
        }
    }
    return retorno;
}


int entrega_setPeso(Entrega* this,char* value)
{
    int auxPeso;
    int retorno = -1;
    if(this != NULL && value!=NULL && isNumber(value))
    {
        auxPeso=atoi(value);
        if(auxPeso>=0)
        {
            this->peso = auxPeso;
            retorno = 0;
        }
    }
    return retorno;
}

int entrega_setTipo(Entrega* this, char* value)
{
    int retorno = -1;
    if(this != NULL && value!=NULL && isLetter(value))
    {
        if(strlen(value)>0)
        {
            strncpy(this->tipo,value,sizeof(this->tipo));
            retorno = 0;
        }
    }
    return retorno;
}


int entrega_setCantidad(Entrega* this,char* value)
{
    int auxHoras;
    int retorno = -1;
    if(this != NULL && value!=NULL && isNumber(value))
    {
        auxHoras=atoi(value);
        if(auxHoras>=0)
        {
            this->cantidad = auxHoras;
            retorno = 0;
        }
    }
    return retorno;
}


int entrega_getTipo(Entrega* this, char* value)
{
    int retorno = -1;
    if(this != NULL && value!=NULL)
    {
        strncpy(value,this->tipo,sizeof(this->tipo));
        retorno = 0;
    }
    return retorno;
}

int entrega_getPeso(Entrega* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value!=NULL)
    {
        *value=this->peso;
        retorno = 0;
    }
    return retorno;
}

int entrega_getCantidad(Entrega* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value!=NULL)
    {
        *value=this->cantidad;
        retorno = 0;
    }
    return retorno;
}

int entrega_getId(Entrega* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value!=NULL)
    {
        *value=this->id;
        retorno = 0;
    }
    return retorno;
}


int entrega_sortByTipo(void* entregaA,void* entregaB)
{
    int mayor=1;
    int menor=-1;
    int igual=0;
    Entrega* pEntregaA;
    Entrega* pEntregaB;

    pEntregaA=(Entrega*)entregaA;
    pEntregaB=(Entrega*)entregaB;
    if(strcmp(pEntregaA->tipo,pEntregaB->tipo)>0)
    {
        return mayor;
    }
    if(strcmp(pEntregaA->tipo,pEntregaB->tipo)<0)
    {
        return menor;
    }
return igual;

}

//CALCULOS
