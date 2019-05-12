#ifndef AUTOR_H_INCLUDED
#define AUTOR_H_INCLUDED

typedef struct
{
    char name[30];
    char surname[30];
    int idAutor;
    int isEmpty; //1 free - 0 full
}Autor;

int autor_menu(Autor* array,int len, char* menuText,
             int exitMenuNumber,int tries);

int autor_addAutor(Autor* array,int len,char* msgE,int tries);
int autor_alter(Autor* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int autor_removeAutor(Autor* array, int len,char* msgE,int tries);
int autor_sortAutor(Autor* array, int len,int order);

int autor_printAutor(Autor* array,int len);
int autor_informarTotalSalariosPromedio(Autor* array,int len);
int autor_salaryOverPromedio(Autor* array,int len,float promedioResult,int* valor);

int autor_initAutor(Autor* array,int len);
int autor_findFree(Autor* array, int len);
int autor_findAutorById(Autor* array, int len, int idE);
int autor_getID (Autor* array,int len,char* msgE,int tries);

#endif // AUTOR_H_INCLUDED

