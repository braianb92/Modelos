#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "autor.h"
#include "utn_strings.h"
#include "libro.h"



static int generarId(void);

int libro_menu(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor, char* menuText,
             int exitMenuNumber,int tries)
{
    int option=0;
    int flag=0;
    char* noAddMsg="\n----AUN NO HAY AUTORES EN LA NOMINA----\n";
    char* addMsg="\n----Alta satisfactoria!----\n";
    char* addMsgE="\n----NO se realizo el Alta----\n";
    char* alterMsg="\n----Se modifico exitosamente!----\n";
    char* alterMsgE="\n----NO se realizo la Modificacion----\n";
    char* removeMsg="\n----Se dio de baja exitosamente!----\n";
    char* removeMsgE="\n----NO se realizo la Baja----\n";
    char* generalMsgE="DATO NO VALIDO\n";

    libro_initLibro(arrayLibro,lenLibro);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    autor_printAutor(arrayAutor,lenAutor);
                    if(!libro_addLibro(arrayLibro,arrayAutor,lenLibro,lenAutor,generalMsgE,tries))
                    {
                        flag=1;
                        printf(addMsg);
                    }
                    else
                    {
                        printf(addMsgE);
                    }
                break;
            case 2:
                if(flag)
                {
                    libro_printLibro(arrayLibro,arrayAutor,lenLibro,lenAutor);
                    if(!libro_alter(arrayLibro,lenLibro,generalMsgE,5,tries))
                    {
                        printf(alterMsg);
                    }
                    else
                    {
                        printf(alterMsgE);
                    }
                }
                else
                {
                    printf(noAddMsg);
                }
                break;
            case 3:
                if(flag)
                {
                    if(!libro_removeLibro(arrayLibro,lenLibro,generalMsgE,tries))
                    {
                        printf(removeMsg);
                    }
                    else
                    {
                        printf(removeMsgE);
                    }
                }
                else
                {
                    printf(noAddMsg);
                }
                break;
            case 4:
                if(flag)
                {
                    libro_sortLibro(arrayLibro,lenLibro,1);///order UP
                    libro_printLibro(arrayLibro,arrayAutor,lenLibro,lenAutor);
                }
                else
                {
                    printf(noAddMsg);
                }
                break;
        }
    }

    return 0;
}

int libro_addLibro(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor,char* msgE,int tries)
{
    int indexFree;
    char bufferTitulo[50];
    int retorno=-1;
    int auxIdAutor;
    int posOfIdAutor;
    if((arrayLibro!=NULL)&&(lenLibro>0)&&(arrayAutor!=NULL)&&(lenAutor>0))
    {
        indexFree=libro_findFree(arrayLibro,lenLibro);
        auxIdAutor=autor_getID(arrayAutor,lenAutor,msgE,tries);
        posOfIdAutor=autor_findAutorById(arrayAutor,lenAutor,auxIdAutor);
        if((indexFree!=-1)&&(auxIdAutor>=0)&&
            (posOfIdAutor!=-1)&&(getStringLetras(bufferTitulo,"\nIngrese Titulo: ",msgE,tries)==0))
        {
            strncpy(arrayLibro[indexFree].titulo,bufferTitulo,sizeof(bufferTitulo));
            arrayLibro[indexFree].idLibro=generarId();
            arrayLibro[indexFree].idAutor=auxIdAutor;
            arrayLibro[indexFree].isEmpty=0;
            retorno=0;
        }
    }
    return retorno;
}

int libro_alter(Libro* array, int len,char* generalMsgE,int exitAlterMenuNumber,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferTitulo[50];
    char* alterMenuText="\n1-Modificar Titulo\n2-Modificar Apellido\n"
                        "3- Atras (Menu Principal)\n";
    int retorno=-1;

    if((array!=NULL)&&(len>0))
    {
        auxID=libro_getID(array,len,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=libro_findLibroById(array,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=exitAlterMenuNumber)
                {
                    printf(alterMenuText);
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",generalMsgE,1,
                                  exitAlterMenuNumber,tries);
                    switch(opcion)
                    {
                        case 1:
                        {
                            if(!getStringLetras(bufferTitulo,"\nIngrese NUEVO Titulo: ",generalMsgE,tries))
                            {
                                strncpy(array[posOfID].titulo,bufferTitulo,sizeof(bufferTitulo));
                                retorno=0;
                            }
                            break;
                        }

                    }
                }
            }
        }
        else
        {
            printf("\n----No se encontro el ID!-----\n");
        }
    }
    return retorno;
}

int libro_removeLibro(Libro* array, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(array!=NULL && len>0)
    {
        auxID=libro_getID(array,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=libro_findLibroById(array,len,auxID);
            if(posOfID!=-1)
            {
               array[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

int libro_sortLibro(Libro* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Libro buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(strcmp(array[i].titulo,array[j].titulo)>0))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(array[i].titulo,array[j].titulo)<0))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

int libro_sortLibroById(Libro* array, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Libro buffer;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(array[i].idLibro>array[j].idLibro))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(array[i].idLibro<array[j].idLibro))
                {
                    buffer=array[i];
                    array[i]=array[j];
                    array[j]=buffer;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}
/*int libro_informarTotalSalariosPromedio(Libro* array,int len)
{
    int i;
    float totalResult;
    float promedioResult;
    int libroloyeeOverPromedio;
    int contadorPromedio=0;
    float sum=0;
    int ret=-1;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==0)
            {
                sum+=array[i].salary;
                contadorPromedio++;
            }
        }
        totalResult=sum;
        promedioResult=totalResult/contadorPromedio;
        libro_salaryOverPromedio(array,len,promedioResult,&libroloyeeOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nEL TOTAL DE SALARIOS ES: %.2f\nEL PROMEDIO DE SALARIOS ES: %.2f\n"
                    "LOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",
                    totalResult,promedioResult,libroloyeeOverPromedio);
        }
    }
    return ret;
}*/

/*int libro_salaryOverPromedio(Libro* array,int len,float promedioResult,int* valor)
{
    int i;
    int contadorLibro=0;
    int ret=-1;
    if(array!=NULL && len>0 && valor!=NULL)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==0)
            {
                if(array[i].salary>promedioResult)
                {
                    contadorLibro++;
                }
            }

        }
        *valor=contadorLibro;
        ret=0;
    }
    return ret;
}*/

int libro_initLibro(Libro* array,int len)
{
    int i;
    if(array!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            //array[i].idLibro=-1;
            array[i].isEmpty=1;
        }
    }
    return 0;
}

int libro_findFree(Libro* array, int len)
{
    int i;
    int ret=-1;
    if(array!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(array[i].isEmpty==1)
            {
                ret=i;
                printf("\n----Se encontro lugar libre----\n");
                break;
            }
        }
        if(ret==-1)
        {
            printf("\n----NO hay lugar libre!!----\n");
        }
    }
    return ret;
}

int libro_findLibroById(Libro* array, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((array[i].isEmpty==0)&&(array[i].idLibro==idE))
        {
            ret=i;
        }
    }
    return ret;
}

int libro_getID (Libro* array,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(array!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese Codigo de libro: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

int libro_printLibro(Libro* arrayLibro,Autor* arrayAutor,int lenLibro,int lenAutor)
{
    int i;
    int posAutor;
    int flag=1;
    for(i=0;i<lenLibro;i++)
    {
        if(arrayLibro[i].isEmpty==0)
        {
            posAutor=autor_findAutorById(arrayAutor,lenAutor,arrayLibro[i].idAutor);
            if(posAutor>=0)
            {
                printf("\nTitulo: %s\nAutor: %s %s\nCodigo Libro: %d\nCodigo Autor: %d\n-------",
                arrayLibro[i].titulo,
                arrayAutor[posAutor].name,
                arrayAutor[posAutor].surname,
                arrayLibro[i].idLibro,
                arrayAutor[posAutor].idAutor);
                flag=0;
            }
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

static int generarId(void)
{
    static int idEmp=0;
    return idEmp++;
}
