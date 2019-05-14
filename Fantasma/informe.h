#ifndef INFORME_H_INCLUDED
#define INFORME_H_INCLUDED
#include "utn_strings.h"
#include "libro.h"
#include "autor.h"
#include "socio.h"
#include "prestamo.h"

int informe_printPrestamoBySocioDeterminado(Prestamo* arrayPrestamo,Autor* arrayAutor,Socio* arraySocio,
                                             Libro* arrayLibro,int lenPrestamo,int lenAutor,int lenSocio,
                                             int lenLibro,char* msgE);

int informe_printSocioByLibroDeterminado(Prestamo* arrayPrestamo,Socio* arraySocio,
                                         Libro* arrayLibro,int lenPrestamo,int lenSocio,
                                         int lenLibro,char* msgE);




#endif // INFORME_H_INCLUDED
