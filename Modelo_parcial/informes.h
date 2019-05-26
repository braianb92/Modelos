#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED
#include "orquesta.h"
#include "instrumento.h"
#include "musico.h"

int informe_menu(Orquesta* arrayOrquesta,Musico* arrayMusico,Instrumento* arrayInstrumento,
                 int lenOrquesta,int lenMusico,int lenInstrumento,int exitMenuNumber,int tries);

//INFORME A
int informe_orquestaConMasde5Musicos (Orquesta* arrayOrquesta,Musico* arrayMusico,int lenOrquesta,int lenMusico);
//INFORME B
int informe_edadMusicoMasDe30(Musico* arrayMusico,Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,
                              int lenInstrumento,int lenMusico,int lenOrquesta);
//INFORME C
int informe_printOrquestasByLugarDeterminado(Orquesta* arrayOrquesta,int lenOrquesta);
//INFORME D
int informe_orquestaCompleta(Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,Musico* arrayMusico,
                             int lenOrquesta,int lenInstrumento,int lenMusico);
//INFORME E
int informe_printMusicosByOrquestaDeterminada(Musico* arrayMusico,Orquesta* arrayOrquesta,Instrumento* arrayInstrumento,
                                              int lenMusico,int lenOrquesta,int lenInstrumento,char* msgE);
//INFORME F
int informe_orquestaConMasMusicos(Orquesta* arrayOrquesta,Musico* arrayMusico,int lenOrquesta,int lenMusico);
//INFORME G
int informe_printMusicoSoloCuerda(Musico* arrayMusico,Instrumento* arrayInstrumento,
                                  int lenMusico,int lenInstrumento);
//INFORME H
int informe_promedioMusicosPorOrquesta(Musico* arrayMusico,Orquesta* arrayOrquesta,int lenMusico,int lenOrquesta);

//SOLO LLAMADAS POR OTRAS FUNCIONES DENTRO DE IFORMES.C (USO INTERNO)
int informe_cantidadOrquestas(Orquesta* arrayOrquesta,int lenOrquesta,int* pCantidadOrquestas);
int informe_cantidadMusicos(Musico* arrayMusico,int lenMusico,int* pCantidadMusicos);
int informe_cantidadInstrumentos(Instrumento* arrayInstrumento,int lenInstrumento,int* pCantidadInst);
int informe_cantInstCuerdaEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstCuerda);

int informe_cantInstVientosEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstVientos);

int informe_cantInsPercusionEnOrquestaEspecifica(Instrumento* arrayInstrumento,Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenInstrumento,int lenMusico,int indexOrquesta,int* pCantidadInstPercusion);

int informe_cantMusicosEnOrquestaEspecifica (Orquesta* arrayOrquesta,Musico* arrayMusico,
                                                int lenMusico,int indexOrquesta,int* pCantMusicosEnUnaOrquesta);
//FIN USO INTERNO
#endif // INFORMES_H_INCLUDED
