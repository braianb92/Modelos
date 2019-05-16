#include <stdio.h>
#include <stdlib.h>
#include "alumno.h"
#include "utn_strings.h"


Alumno* alumno_new()
{
    return (Alumno*) malloc(sizeof(Alumno));
}

Alumno* alumno_newParametros(int id,int legajo,int status,char* nombre)
{
    return NULL;
}

int alumno_delete(Alumno* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}

int alumno_setId(Alumno* this, int value)
{
    int retorno = -1;
    if(this != NULL && value >= 0)
    {
        this->id = value;
        retorno = 0;
    }
    return retorno;
}

int alumno_setLegajo(Alumno* this, int value)
{
    int retorno = -1;
    if(this != NULL && isNumber(value))
    {
        this->legajo = value;
        retorno = 0;
    }
    return retorno;
}

int alumno_setStatus(Alumno* this, int value)
{
    int retorno = -1;
    if(this != NULL && isNumber(value))
    {
        this->status = value;
        retorno = 0;
    }
    return retorno;
}

int alumno_setNombre(Alumno* this, char* value)
{
    int retorno = -1;
    if(this != NULL && isLetter(value))
    {
        strncpy(this->nombre,value,sizeof(value));
        retorno = 0;
    }
    return retorno;
}

int alumno_getId(Alumno* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value >=0)
    {
        *value = this->id;
        retorno = 0;
    }
    return retorno;
}

int alumno_getLegajo(Alumno* this, int* value)
{
    int retorno = -1;
    if(this != NULL && isNumber(value))
    {
        *value = this->legajo;
        retorno = 0;
    }
    return retorno;
}

int alumno_getStatus(Alumno* this, int* value)
{
    int retorno = -1;
    if(this != NULL && isNumber(value))
    {
        *value = this->status;
        retorno = 0;
    }
    return retorno;
}

int alumno_getNombre(Alumno* this, char* value)
{
    int retorno = -1;
    if(this != NULL && isLetter(value))
    {
        strncpy(value,this->nombre,sizeof(this->nombre));
        retorno = 0;
    }
    return retorno;
}












