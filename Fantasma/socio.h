#ifndef SOCIO_H_INCLUDED
#define SOCIO_H_INCLUDED
#define TAM_SOCIO_STRING 51
#include "socio.h"
#include "libro.h"


typedef struct
{
    char name[30];
    char surname[30];
    char sexo[10];
    char telefono[31];
    char email[31];
    int dia;
    int mes;
    int year;
    int idSocio;
    int isEmpty; //1 free - 0 full
}Socio;

int socio_menu(Socio* arraySocio,int lenSocio, char* menuText,
                int exitMenuNumber,int tries);

int socio_addSocio(Socio* arraySocio,int len,char* msgE,int tries);
int socio_alter(Socio* arraySocio, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int socio_removeSocio(Socio* arraySocio, int len,char* msgE,int tries);
int socio_sortSocio(Socio* arraySocio, int len,int order);

int socio_printSocio(Socio* arraySocio,int len);

int socio_informarTotalSalariosPromedio(Socio* arraySocio,int len);
int socio_salaryOverPromedio(Socio* arraySocio,int len,float promedioResult,int* valor);

int socio_initSocio(Socio* arraySocio,int len);
int socio_findFree(Socio* arraySocio, int len);
int socio_findSocioById(Socio* arraySocio, int len, int idE);
int socio_getID (Socio* arraySocio,int len,char* msgE,int tries);

#endif // SOCIO_H_INCLUDED

