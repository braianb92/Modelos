#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "informe.h"


int informe_printPrestamoBySocioDeterminado(Prestamo* arrayPrestamo,Autor* arrayAutor,Socio* arraySocio,
                             Libro* arrayLibro,int lenPrestamo,int lenAutor,int lenSocio,
                             int lenLibro,char* msgE)
{
    int i;
    int posAutor;
    int posLibro;
    int auxIdSocio;
    int posSocio;
    int flag=1;

    auxIdSocio=socio_getID(arraySocio,lenSocio,msgE,3);
    posSocio=socio_findSocioById(arraySocio,lenSocio,auxIdSocio);
    if((auxIdSocio>=0)&&(posSocio!=-1))
    {
        for(i=0;i<lenPrestamo;i++)
        {
            if((arrayPrestamo[i].isEmpty==0)&&(arrayPrestamo[i].idSocio==auxIdSocio))
            {
                posLibro=libro_findLibroById(arrayLibro,lenLibro,arrayPrestamo[i].idLibro);
                posAutor=autor_findAutorById(arrayAutor,lenAutor,arrayLibro[posLibro].idAutor);
                if((posLibro>=0)&&(posAutor>=0))
                {
                    printf("\nFecha de Prestamo: %d/%d/%d\nAutor: %s %s\nLibro: %s\n"
                           "Codigo Prestamo: %d\nCodigo Autor: %d\nCodigo Libro: %d\n"
                           "Codigo Socio: %d\n-------\n",
                            arrayPrestamo[i].day,
                            arrayPrestamo[i].month,
                            arrayPrestamo[i].year,
                            arrayAutor[posAutor].name,
                            arrayAutor[posAutor].surname,
                            arrayLibro[posLibro].titulo,
                            arrayPrestamo[i].idPrestamo,
                            arrayAutor[posAutor].idAutor,
                            arrayPrestamo[i].idLibro,
                            arrayPrestamo[i].idSocio);
                            flag=0;
                }
            }
        }
        if(flag)
        {
            printf("\n----El listado se encuentra vacio----\n");
        }
    }
    return 0;
}

int informe_printSocioByLibroDeterminado(Prestamo* arrayPrestamo,Socio* arraySocio,
                             Libro* arrayLibro,int lenPrestamo,int lenSocio,
                             int lenLibro,char* msgE)
{
    int i;
    int auxIdLibro;
    int posLibro;
    int posSocio;
    int flag=1;

    auxIdLibro=libro_getID(arrayLibro,lenLibro,msgE,3);
    posLibro=libro_findLibroById(arrayLibro,lenLibro,auxIdLibro);
    if((auxIdLibro>=0)&&(posLibro!=-1))
    {
        for(i=0;i<lenPrestamo;i++)
        {
            if((arrayPrestamo[i].isEmpty==0)&&(arrayPrestamo[i].idLibro==auxIdLibro))
            {
                posLibro=libro_findLibroById(arrayLibro,lenLibro,arrayPrestamo[i].idLibro);
                posSocio=socio_findSocioById(arraySocio,lenSocio,arrayPrestamo[i].idSocio);
                if((posLibro>=0)&&(posSocio>=0))
                {
                    printf("\nSocio: %s %s\nLibro: %s\nCodigo Socio: %d\nCodigo Prestamo: %d\n"
                           "Codigo Libro: %d\n-------\n",
                           arraySocio[posSocio].name,
                           arraySocio[posSocio].surname,
                           arrayLibro[posLibro].titulo,
                           arrayPrestamo[i].idSocio,
                           arrayPrestamo[i].idPrestamo,
                           arrayLibro[posLibro].idLibro);
                            flag=0;
                }
            }
        }
        if(flag)
        {
            printf("\n----El listado se encuentra vacio----\n");
        }
    }
    return 0;
}

int informe_socioConMasPrestamos (Socio* arraySocio, Prestamo* arrayPrestamo,int lenSocio,int lenPrestamo)
{
    int i;
    int max=0;
    int contadorOcurrencias=0;
    int idSocioMayorOcurrencia;
    int posSocio;

    if((arraySocio!=NULL)&&(arrayPrestamo!=NULL)
       &&((lenSocio>0)&&(lenPrestamo>0)))
    {
        socio_sortSocioEficienteById(arraySocio,lenSocio,1);
        for(i=1;i<lenPrestamo;i++)
        {
            if(arrayPrestamo[i-1].idSocio==arrayPrestamo[i].idSocio)
            {
                contadorOcurrencias++;
                if(contadorOcurrencias>max)
                {
                    max=contadorOcurrencias;
                    idSocioMayorOcurrencia=arrayPrestamo[i].idSocio;
                }
            }
            else
            {
                contadorOcurrencias=0;
            }
        }
        posSocio=socio_findSocioById(arraySocio,lenSocio,idSocioMayorOcurrencia);
        if(posSocio!=-1)
        {
            printf("\n--------\nSocio con mas Prestamos: %s %s\nCodigo Socio: %d\n"
                    "Cantidad de Prestamos: %d\n--------\n",
                    arraySocio[posSocio].name,
                    arraySocio[posSocio].surname,
                    arraySocio[posSocio].idSocio,
                    max+1);
        }
        else
        {
            printf("\n----No se encontro socio!----\n");
        }
    }
    return 0;
}
