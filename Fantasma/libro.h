#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED
#include "autor.h"

typedef struct
{
    char titulo[31];
    int idAutor;
    int idLibro;
    int isEmpty; //1 free - 0 full
}Libro;

int libro_menu(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor, char* menuText,
             int exitMenuNumber,int tries);

int libro_addLibro(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor,char* msgE,int tries);
int libro_alter(Libro* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int libro_removeLibro(Libro* array, int len,char* msgE,int tries);
int libro_sortLibro(Libro* array, int len,int order);
int libro_sortLibroById(Libro* array, int len,int order);

int libro_printLibro(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor);
int libro_informarTotalSalariosPromedio(Libro* array,int len);
int libro_salaryOverPromedio(Libro* array,int len,float promedioResult,int* valor);

int libro_initLibro(Libro* array,int len);
int libro_findFree(Libro* array, int len);
int libro_findLibroById(Libro* array, int len, int idE);
int libro_getID (Libro* array,int len,char* msgE,int tries);

#endif // LIBRO_H_INCLUDED
