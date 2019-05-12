#include <stdio.h>
#include <stdlib.h>

int calcCanPresEnDia(Prestamo* lista,int len,int diaAContar)
{
    int i;
    int cont=0;
{

    Prestamo prestamos[500];


}nDia(lista,len,diaActual);
    if(canPresEnDia<prom)
        cont++;

    for(i=1; i<len;i++)
    {
        if(lista[i].dia!=lista[i-1].dia)
        {
    for(i=0; i<len; i++)
    {
        if(lista[i].isEmpty==0)
        {
int main()
            diaActual = lista[i].dia;

            canPresEnDia = calcCanPresEnDia(lista,len,diaActual);
            if(canPresEnDia<prom)
                cont++;
        }
    }

}


            if(lista[i].dia==diaAContar)
                cont++;
        }
    }
    return cont;
}

int inf_c(Socio* socios,int lenSoc, Prestamo* prestamos,int lenPrestamos,int idLibro)
{
    int i;
    int idSocio;
    for(i=0; i<lenSoc;i++)
    {
        idSocio = socios[i].id;

        // filtro
        if(socioTienePrestamoDeLibro(prestamos,lenPrestamos,idLibro,idSocio))
        {
            // PRINT
            printf("nombre: %s",socios[i].nombre);
        }
    }
}


int socioTienePrestamoDeLibro(Prestamo* prestamos,int len,int idLibro,int idSocio)
{
    int i;
    int tiene=0;
    for(i=0; i<len;i++)
    {
        if(prestamos[i].isEmpty==0)
        {
            if( prestamos[i].idSocio == idSocio &&
                prestamos[i].idLibro == idLibro)
            {
                tiene=1;
                break;
            }
        }
    }
    return tiene;
}
    // devulve el total

    int i;
    int cont=0;
    for(i=0; i<len;i++)
    {
        if(lista[i].isEmpty==0)
            cont++;
    }
    return cont;

