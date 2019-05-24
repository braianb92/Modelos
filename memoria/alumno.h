#ifndef PERSONA_H
#define PERSONA_H
#define QTY_NAME 50
typedef struct
{
    int id;
    char nombre[32];
    char apellido[32];
    int edad;
} Persona;
#endif

Persona* persona_new();
Persona* persona_newParametros(char* nombre,char* apellido,char* edad);
int persona_delete(Persona* this);


int persona_setId(Persona* this, int value);
int persona_setLegajo(Persona* this, int value);
int persona_setEdad(Persona* this, char* value);
int persona_setNombre(Persona* this, char* value);
int persona_setApellido(Persona* this, char* value);

int persona_getId(Persona* this, int* value);
int persona_getLegajo(Persona* this, int* value);
int persona_getEdad(Persona* this, int* value);
int persona_getNombre(Persona* this, char* value);
int persona_getApellido(Persona* this, char* value);

int per_addPersona(Persona* arrayPersona[],int lenPersona,char* msgE,int tries);
int per_initArray(Persona* arrayPer[],int lenPer);
int per_findFree(Persona* arrayPersona[], int lenPersona);











