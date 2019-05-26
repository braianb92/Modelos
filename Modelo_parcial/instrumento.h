#ifndef INSTRUMENTO_H_INCLUDED
#define INSTRUMENTO_H_INCLUDED

typedef struct
{
    char name[30];
    int tipo;//cuerdas(1);viento-madera(2);viento-metal(3);percusion(4)
    int idInstrumento;
    int isEmpty; //1 free - 0 full
}Instrumento;


int instrumento_preCarga(Instrumento* array,int len,int indexPosition,char* nombre,int tipo);

int instrumento_addInstrumento(Instrumento* array,int len,char* msgE,int tries);
int instrumento_alter(Instrumento* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int instrumento_removeInstrumento(Instrumento* array, int len,char* msgE,int tries);

int Instrumento_sortInstrumentoByNombre(Instrumento* array, int len,int order);
int Instrumento_sortInstrumentoByTipo(Instrumento* array, int len,int order);
int instrumento_sortInstrumentosByNombreEficiente(Instrumento* arrayInstrumento,
                                                        int lenInstrumento,int order);

int instrumento_printInstrumento(Instrumento* array,int len);

int instrumento_initInstrumento(Instrumento* array,int len);
int instrumento_findFree(Instrumento* array, int len);
int instrumento_findInstrumentoById(Instrumento* array, int len, int idE);
int instrumento_findInstrumentoByTipo(Instrumento* array, int len, int idE);
int instrumento_getID (Instrumento* array,int len,char* msgE,int tries);

#endif // INSTRUMENTO_H_INCLUDED
