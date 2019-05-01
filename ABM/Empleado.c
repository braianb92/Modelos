#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "Empleado.h"

static int generarId(void);

int emp_addEmployees(Employee* pEmployee,int len,int pIndex,char* msgE,int tries)
{
    char bufferName[50];
    char bufferSurname[50];
    char bufferSalary[50];
    char bufferSector[20];
    float auxSalary;
    int auxSector;
    int retorno=-1;
    if((pEmployee!=NULL)&&(len>0))
    {
        if(((getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries)==0)&&
            (getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries)==0)))
        {
            if((getStringNumerosFloat(bufferSalary,"\nIngrese Salario: ",msgE,tries)==0)
                &&(getStringNumeros(bufferSector,"\nIngrese Sector: ",msgE,tries)==0))
            {
                auxSalary=atof(bufferSalary);
                auxSector=atoi(bufferSector);
                strncpy(pEmployee[pIndex].name,bufferName,sizeof(bufferName));
                strncpy(pEmployee[pIndex].surname,bufferSurname,sizeof(bufferSurname));
                pEmployee[pIndex].salary=auxSalary;
                pEmployee[pIndex].sector=auxSector;
                pEmployee[pIndex].idEmployee=generarId();
                pEmployee[pIndex].isEmpty=0;
            }
        }
    }
    return retorno;
}

int emp_alter(Employee* pEmployee, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int opcion=0;
    char bufferName[50];
    char bufferSurname[50];
    char bufferSalario[20];
    char bufferSector[20];
    float auxPrecio;
    int auxSector;
    int retorno=-1;

    if((pEmployee!=NULL)&&(len>0))
    {
        auxID=emp_getID(pEmployee,len,msgE,tries);
        if(auxID>=0)
        {
            posOfID=emp_findEmployeeById(pEmployee,len,auxID);
            if(posOfID!=-1)
            {
                while(opcion!=5)
                {
                    printf("\n1- Modificar Nombre\n");
                    printf("2- Modificar Apellido\n");
                    printf("3- Modificar Salario\n");
                    printf("4- Modificar Sector\n");
                    printf("5- Atras (Menu Principal)\n");
                    getIntInRange(&opcion,"\n   INGRESE OPCION (Menu Modificacion): ",msgE,1,5,tries);
                    switch(opcion)
                    {
                        case 1:
                        {
                            if(!getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",msgE,tries))
                            {
                                strncpy(pEmployee[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferSurname,"\nIngrese NUEVO Apellido: ",msgE,tries))
                            {
                                strncpy(pEmployee[posOfID].surname,bufferSurname,sizeof(bufferSurname));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(!getStringNumerosFloat(bufferSalario,"\nIngrese NUEVO Salario: ",msgE,tries))
                            {
                                auxPrecio=atof(bufferSalario);
                                pEmployee[posOfID].salary=auxPrecio;
                                retorno=0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(!getStringNumeros(bufferSector,"\nIngrese NUEVO Sector: ",msgE,tries))
                            {
                                auxSector=atoi(bufferSector);
                                pEmployee[posOfID].sector=auxSector;
                                retorno=0;
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("\n----No se encontro el ID!-----\n");
            }
        }
    }
    return retorno;
}

int emp_removeEmployee(Employee* pEmployee, int len,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(pEmployee!=NULL && len>0)
    {
        auxID=emp_getID(pEmployee,len,msgE,tries);
         if(auxID>=0)
        {
            posOfID=emp_findEmployeeById(pEmployee,len,auxID);
            if(posOfID!=-1)
            {
               pEmployee[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

/*int emp_sortEmployees(Employee* pEmpleado, int len, int order) //1UP 0DOWN
{
    int i;
    int j;

    Employee buffer;
    if(pEmpleado!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {
            if(pEmpleado[i].isEmpty==1)
            {
                continue;
            }
            for(j=i+1;j<len;j++)
            {
                if(pEmpleado[j].isEmpty==1)
                {
                    continue;
                }
                if(strcmp(pEmpleado[i].surname,pEmpleado[j].surname)>0)
                {
                    buffer=pEmpleado[i];
                    pEmpleado[i]=pEmpleado[j];
                    pEmpleado[j]=buffer;
                }
            }
        }
    }
    return 0;
}*/

int emp_totalPromedio(Employee* pEmployee, int len,float* totalResult,float* promedioResult)
{
    int i;
    int ret=-1;
    float sum=0;
    if(pEmployee!=NULL && len>0 && promedioResult!=NULL)
    {
        for(i=0;i<len;i++)
        {
            sum+=pEmployee[i].salary;
        }
        *totalResult=sum;
        *promedioResult=sum/len;
        ret=0;
    }
    return ret;
}

int emp_salaryOverPromedio(Employee* pEmployee,int len,float promedioResult,int* employeeOverPromedio)
{
    int i;
    int contadorEmployee=0;
    int ret=-1;
    if(pEmployee!=NULL && len>0 && employeeOverPromedio!=NULL)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployee[i].salary>promedioResult)
            {
                contadorEmployee++;
            }
        }
        *employeeOverPromedio=contadorEmployee;
        ret=0;
    }
    return ret;
}

int emp_initEmployees(Employee* pEmployee,int len)
{
    int i;
    if(pEmployee!=NULL && len>0)
    {
        for(i=0; i<len;i++)
        {
            pEmployee[i].idEmployee=-1;
            pEmployee[i].isEmpty=1;
        }
    }
    return 0;
}

int emp_findFree(Employee* pEmployee, int len)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pEmployee[i].isEmpty==1)
        {
            ret=i;
            break;
        }
    }
    return ret;
}

int emp_findEmployeeById(Employee* pEmployee, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if(pEmployee[i].idEmployee==idE)
        {
            ret=i;
        }
    }
    return ret;
}

int emp_getID (Employee* pEmpleado,int len,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(pEmpleado!=NULL && len>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

int emp_printEmployees(Employee* pEmployee,int len)
{
    int i;
    int flag=1;
    for(i=0;i<len;i++)
    {
        if(pEmployee[i].isEmpty==0)
        {
            printf("\nID: %d\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\n-------",
                   pEmployee[i].idEmployee,pEmployee[i].name,pEmployee[i].surname,pEmployee[i].salary,pEmployee[i].sector);
            flag=0;
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
