
#ifndef ALUMNO_H
#define ALUMNO_H
#define QTY_NAME 50
typedef struct
{
    int id;
    char nombre[QTY_NAME];
    int legajo;
    int status;
}Alumno;
#endif

Alumno* alumno_new();
Alumno* alumno_newParametros(int id,int legajo,int status,char* nombre);
int alumno_delete(Alumno* this);

int alumno_setId(Alumno* this, int value);
int alumno_setLegajo(Alumno* this, int value);
int alumno_setStatus(Alumno* this, int value);
int alumno_setNombre(Alumno* this, char* value);

int alumno_getId(Alumno* this, int* value);
int alumno_getLegajo(Alumno* this, int* value);
int alumno_getStatus(Alumno* this, int* value);
int alumno_getNombre(Alumno* this, char* value);











