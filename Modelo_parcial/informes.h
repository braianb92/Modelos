#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED
#include "orquesta.h"
#include "instrumento.h"
#include "musico.h"

int informe_cantidadOrquestas(Orquesta* arrayOrquesta,int lenOrquesta,int* pCantidadOrquestas);
int informe_cantidadMusicos(Musico* arrayMusico,int lenMusico,int* pCantidadMusicos);
int informe_cantidadInstrumentos(Instrumento* arrayInstrumento,int lenInstrumento,int* pCantidadInst);

int informe_tipoInstrumentoMasUsado(Instrumento* arrayInstrumento,int lenInstrumento,int* pTipoInstMasUsado);
int informe_InstrumentoMasUsadoPorMusicos(Instrumento* arrayInstrumento,Musico* arrayMusico,int lenInstrumento,int lenMusico);
int informe_InstrumentosMenosUsadosPorMusicos(Instrumento* arrayInstrumento,Musico* arrayMusico,int lenInstrumento,int lenMusico);

int informe_printMusicoByInstrumentoDeterminado(Musico* arrayMusico,Instrumento* arrayInstrumento,
                                                int lenMusico,int lenInstrumento,char* msgE);

int informe_printMusicosByOrquestaDeterminada(Musico* arrayMusico,Orquesta* arrayOrquesta,
                                                int lenMusico,int lenOrquesta,char* msgE);

int informe_promedioDeEdadMusicos(Musico* arrayMusico,int lenMusico);
int informe_musicoOverPromedio(Musico* arrayMusico,int lenMusico,float promedioResult,int* valor);

int informe_tipoOrquestaMasFrecuente(Orquesta* arrayOrquesta,int lenOrquesta);
int informe_orquestaConMasMusicos(Orquesta* arrayOrquesta,Musico* arrayMusico,int lenOrquesta,int lenMusico);

#endif // INFORMES_H_INCLUDED
