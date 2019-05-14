#ifndef PRESTAMO_H_INCLUDED
#define PRESTAMO_H_INCLUDED
#include "socio.h"
#include "autor.h"
#include "libro.h"


typedef struct
{
    int day;
    int month;
    int year;
    int idSocio;
    int idLibro;
    int idPrestamo;
    int isEmpty; //1 free - 0 full
}Prestamo;

int prestamo_menu(Prestamo* arrayPrestamo,Socio* arraySocio, Libro* arrayLibro,Autor* arrayAutor,
                  int lenPrestamo,int lenSocio,int lenLibro,int lenAutor,
                  char* menuText,int exitMenuNumber,int tries);

int prestamo_addPrestamo(Prestamo* arrayPrestamo,Socio* arraySocio,Libro* arrayLibro,
                         int lenPrestamo,int lenSocio,int lenLibro,char* msgE,int tries);

int prestamo_alter(Prestamo* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int prestamo_removePrestamo(Prestamo* array, int len,char* msgE,int tries);
int prestamo_sortPrestamo(Prestamo* array, int len,int order);

int prestamo_printPrestamo(Prestamo* arrayPrestamo,int lenPrestamo);
int prestamo_informarTotalyPromedioDiario(Prestamo* array,int len);

int prestamo_initPrestamo(Prestamo* array,int len);
int prestamo_findFree(Prestamo* array, int len);
int prestamo_findPrestamoById(Prestamo* array, int len, int idE);
int prestamo_getID (Prestamo* array,int len,char* msgE,int tries);

#endif // PRESTAMO_H_INCLUDED
