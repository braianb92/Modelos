#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utn_strings.h"
#include "libro.h"
#include "autor.h"
#include "socio.h"
#include "prestamo.h"
#include "informe.h"

#define LEN_AUTOR 10
#define LEN_LIBRO 10
#define LEN_SOCIO 10
#define LEN_PRESTAMO 10
#define REINTENTOS 3
int main()
{
    Autor autores[LEN_AUTOR];
    Libro libros[LEN_LIBRO];
    Socio socios[LEN_SOCIO];
    Prestamo prestamos[LEN_PRESTAMO];
    int option=0;
    int flagAltaAutor=0;
    int flagAltaLibro=0;
    int flagAltaSocio=0;
    int flagAltaPrest=0;
    int contAutor=0;
    int contLibro=0;
    int contSocio=0;
    int contPrest=0;

    autor_initAutor(autores,LEN_AUTOR);
    libro_initLibro(libros,LEN_LIBRO);
    socio_initSocio(socios,LEN_SOCIO);
    prestamo_initPrestamo(prestamos,LEN_PRESTAMO);

    while(option!=120)
    {
        printf("\n1)ALTA AUTOR\n2)MODIFICAR AUTOR\n3)BAJA AUTOR\n-----------\n4)ALTA LIBRO\n5)MODIFICAR LIBRO\n6)BAJA LIBRO\n----------\n"
               "7)ALTA SOCIO\n8)MODIFICAR SOCIO\n9)BAJA SOCIO\n----------\n10)ALTA PRESTAMO\n11)MODIFICAR PRESTAMO\n12)BAJA PRESTAMO\n----------\n"
               "13)LISTAR AUTORES\n14)LISTAR LIBROS\n15)LISTAR SOCIOS\n16)LISTAR PRESTAMOS POR SOCIO DETERMINADO(D)\n"
               "17)INFORMAR TOTAL PRESTAMOS Y PROMEDIO DIARIO(A)\n18)LISTAR SOCIO POR LIBRO DETERMINADO(C)\n"
               "19)LISTAR SOCIO CON MAYOR CANTIDAD DE PRESTAMOS(F)\n----------\n120)Salir\n");


        getIntInRange(&option,"\n   Ingrese Opcion: ","\nDATO NO VALIDO\n",
                    1,20,REINTENTOS);
        system("cls");
        switch(option)
        {
            case 1:
                system("cls");
                if(!autor_addAutor(autores,LEN_AUTOR,"\nNO\n",REINTENTOS))
                {
                    flagAltaAutor=1;
                    contAutor++;
                }
                break;
            case 2:
                system("cls");
                if(flagAltaAutor)
                {
                    autor_printAutor(autores,LEN_AUTOR);
                    autor_alter(autores,LEN_AUTOR,"\nNO\n",5,REINTENTOS);
                }
                else
                {
                    printf("\n--No hay autores en la nomina!--\n");
                }
                break;
            case 3:
                system("cls");
                if(flagAltaAutor)
                {
                    if(!autor_removeAutor(autores,LEN_AUTOR,"\nNO\n",REINTENTOS))
                    {
                        contAutor--;
                        if(contAutor==0)
                        {
                            flagAltaAutor=0;
                        }
                    }
                }
                else
                {
                    printf("\n--No hay autores en la nomina!--\n");
                }
                break;
            case 4:
                system("cls");
                if(flagAltaAutor)
                {
                    autor_printAutor(autores,LEN_AUTOR);
                    if(!libro_addLibro(libros,autores,LEN_LIBRO,LEN_AUTOR,"\nNO\n",REINTENTOS))
                    {
                        flagAltaLibro=1;
                        contLibro++;
                    }
                }
                else
                {
                    printf("\n--No hay autores en la nomina!--\n");
                }
                break;
            case 5:
                system("cls");
                if(flagAltaLibro)
                {
                    libro_printLibro(libros,autores,LEN_LIBRO,LEN_AUTOR);
                    libro_alter(libros,LEN_LIBRO,"\nNO\n",5,REINTENTOS);
                }
                else
                {
                    printf("\n--No hay Libros en la nomina!--\n");
                }
                break;
            case 6:
                system("cls");
                if(flagAltaLibro)
                {
                    if(!libro_removeLibro(libros,LEN_LIBRO,"\nNO\n",REINTENTOS))
                    {
                        contLibro--;
                        if(contLibro==0)
                        {
                            flagAltaLibro=0;
                        }
                    }
                }
                else
                {
                    printf("\n--No hay Libros en la nomina!--\n");
                }
                break;
            case 7:
                system("cls");
                if(!socio_addSocio(socios,LEN_SOCIO,"\nNO\n",REINTENTOS))
                {
                    flagAltaSocio=1;
                    contSocio++;
                }
                break;
            case 8:
                system("cls");
                if(flagAltaSocio)
                {
                    socio_printSocio(socios,LEN_SOCIO);
                    socio_alter(socios,LEN_SOCIO,"\nNO\n",5,REINTENTOS);
                }
                else
                {
                    printf("\n--No hay Socios en la nomina!--\n");
                }
                break;
            case 9:
                system("cls");
                if(flagAltaSocio)
                {
                    if(!socio_removeSocio(socios,LEN_SOCIO,"\nNO\n",REINTENTOS))
                    {
                        contSocio--;
                        if(contSocio==0)
                        {
                            flagAltaSocio=0;
                        }
                    }
                }
                else
                {
                    printf("\n--No hay Socios en la nomina!--\n");
                }
                break;
            case 10:
                system("cls");
                if(flagAltaLibro&&flagAltaSocio)
                {
                    libro_printLibro(libros,autores,LEN_LIBRO,LEN_AUTOR);
                    if(!prestamo_addPrestamo(prestamos,socios,libros,LEN_PRESTAMO,LEN_SOCIO,LEN_LIBRO,"\nNO\n",REINTENTOS))
                    {
                        flagAltaPrest=1;
                        contPrest++;
                    }
                }
                else
                {
                    printf("\n--No hay Libros/Socios en la nomina!--\n");
                }
                break;
            case 11:
                system("cls");
                if(flagAltaPrest)
                {
                    prestamo_printPrestamo(prestamos,LEN_PRESTAMO);
                    prestamo_alter(prestamos,LEN_PRESTAMO,"\nNO\n",5,REINTENTOS);
                }
                else
                {
                    printf("\n--No hay Prestamos en la nomina!--\n");
                }
                break;
            case 12:
                system("cls");
                if(flagAltaPrest)
                {
                    if(!prestamo_removePrestamo(prestamos,LEN_PRESTAMO,"\nNO\n",REINTENTOS))
                    {
                        contPrest--;
                        if(contPrest==0)
                        {
                            flagAltaPrest=0;
                        }
                    }
                }
                else
                {
                    printf("\n--No hay Prestamos en la nomina!--\n");
                }
                break;
            case 13:
                if(flagAltaAutor)
                {
                    autor_sortAutor(autores,LEN_AUTOR,1);
                    autor_printAutor(autores,LEN_AUTOR);
                }
                break;
            case 14:
                if(flagAltaLibro)
                {
                    libro_sortLibro(libros,LEN_LIBRO,1);
                    libro_printLibro(libros,autores,LEN_LIBRO,LEN_AUTOR);
                }
                break;
            case 15:
                if(flagAltaSocio)
                {
                    socio_printSocio(socios,LEN_SOCIO);
                }
                break;
            case 16:
                if(flagAltaPrest&&flagAltaSocio)
                {
                    informe_printPrestamoBySocioDeterminado(prestamos,autores,socios,libros,
                                                         LEN_PRESTAMO,LEN_AUTOR,LEN_SOCIO,LEN_LIBRO,"\nNO\n");
                }
                break;
            case 17:
                if(flagAltaPrest&&flagAltaSocio)
                {
                    prestamo_informarTotalyPromedioDiario(prestamos,LEN_PRESTAMO);
                }
                break;
            case 18:
                if(flagAltaPrest&&flagAltaSocio)
                {
                    informe_printSocioByLibroDeterminado(prestamos,socios,libros,
                                                         LEN_PRESTAMO,LEN_SOCIO,LEN_LIBRO,"\nNO\n");
                }
                break;
            case 19:
                if(flagAltaPrest&&flagAltaSocio)
                {
                    informe_socioConMasPrestamos(socios,prestamos,LEN_SOCIO,LEN_PRESTAMO);
                }
                break;
        }
    }

    return 0;
}
