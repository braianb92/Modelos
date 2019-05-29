#ifndef MUSICO_H_INCLUDED
#define MUSICO_H_INCLUDED
#include "orquesta.h"
#include "instrumento.h"

typedef struct
{
    char name[30];
    char surname[30];
    int edad;
    int idOrquesta;
    int idInstrumento;
    int idMusico;
    int isEmpty; //1 free - 0 full
}Musico;

int musico_preCarga(Musico* array,int len,int indexPosition,char* nombre,
                    char* apellido,int edad,int idOrquesta,int idInstrumento);

int musico_addMusico(Musico* arrayMusico,Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,
                    int lenMusico,int lenOrquesta,int lenInstrumento,char* msgE,int tries);

int musico_alter(Musico* arrayMusico,Orquesta* arrayOrquesta,int lenMusico,int lenOrquesta,char* generalMsgE,int exitAlterMenuNumber,int tries);
int musico_removeMusico(Musico* array, int len,char* msgE,int tries);
int musico_removeMusicoApartirDeOrquesta(Musico* arrayMusico,int lenMusico,int removedOrquestaID);

int musico_sortMusicoBySurname(Musico* array, int len,int order);
int musico_sortMusicoByNombre(Musico* array, int len,int order);
int musico_sortMusicoByEdad(Musico* array, int len,int order);
int musico_sortMusicoByEdadMismoSurname(Musico* arrayMusico,int lenMusico,int order);
int musico_sortMusicosBySurnameyEdadEficiente(Musico* arrayMusico,int lenMusico,int order);
int musico_sortMusicosByInstrumentoEficiente(Musico* arrayMusico,int lenMusico,int order);
int musico_sortMusicosByIdOrquestaEficiente(Musico* arrayMusico,int lenMusico,int order);


int musico_printMusico(Musico* arrayMusico,Instrumento* arrayInstrumento,int lenMusico,int lenInstrumento);
int musico_printMusicoBasic(Musico* array,int len);

int musico_initMusico(Musico* array,int len);
int musico_findFree(Musico* array, int len);
int musico_findMusicoById(Musico* array, int len, int idE);
int musico_findMusicoByIdOrquesta(Musico* array, int len, int idE);
int musico_getID (Musico* array,int len,char* msgE,int tries);

#endif // MUSICO_H_INCLUDED
