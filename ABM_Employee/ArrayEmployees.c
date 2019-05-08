#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "ArrayEmployees.h"

static int generarId(void);

int emp_menu(Employee* pEmployee,int len, char* menuText,
             int exitMenuNumber,int tries)
{
    int option=0;
    int flag=0;
    char* noAddMsg="\n----AUN NO HAY EMPLEADOS EN LA NOMINA----\n";
    char* addMsg="\n----Alta satisfactoria!----\n";
    char* addMsgE="\n----NO se realizo el Alta----\n";
    char* alterMsg="\n----Se modifico exitosamente!----\n";
    char* alterMsgE="\n----NO se realizo la Modificacion----\n";
    char* removeMsg="\n----Se dio de baja exitosamente!----\n";
    char* removeMsgE="\n----NO se realizo la Baja----\n";
    char* generalMsgE="DATO NO VALIDO\n";

    emp_initEmployees(pEmployee,len);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    if(!emp_addEmployees(pEmployee,len,generalMsgE,tries))
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
                    if(!emp_alter(pEmployee,len,generalMsgE,5,tries))
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
                    if(!emp_removeEmployee(pEmployee,len,generalMsgE,tries))
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
                    emp_sortEmployees(pEmployee,len,1);///order UP
                    emp_printEmployees(pEmployee,len);
                    emp_informarTotalSalariosPromedio(pEmployee,len);
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

int emp_addEmployees(Employee* pEmployee,int len,char* msgE,int tries)
{
    int indexFree;
    char bufferName[50];
    char bufferSurname[50];
    char bufferSalary[50];
    char bufferSector[20];
    float auxSalary;
    int auxSector;
    int retorno=-1;
    if((pEmployee!=NULL)&&(len>0))
    {
        indexFree=emp_findFree(pEmployee,len);
        if((indexFree!=-1)&&(getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries)==0)&&
            (getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries)==0))
        {
            if((getStringNumerosFloat(bufferSalary,"\nIngrese Salario: ",msgE,tries)==0)
                &&(getStringNumeros(bufferSector,"\nIngrese Sector: ",msgE,tries)==0))
            {
                auxSalary=atof(bufferSalary);
                auxSector=atoi(bufferSector);
                strncpy(pEmployee[indexFree].name,bufferName,sizeof(bufferName));
                strncpy(pEmployee[indexFree].surname,bufferSurname,sizeof(bufferSurname));
                pEmployee[indexFree].salary=auxSalary;
                pEmployee[indexFree].sector=auxSector;
                pEmployee[indexFree].idEmployee=generarId();
                pEmployee[indexFree].isEmpty=0;
                retorno=0;
            }
        }
    }
    return retorno;
}

int emp_alter(Employee* pEmployee, int len,char* generalMsgE,int exitAlterMenuNumber,int tries)
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
    char* alterMenuText="\n1-Modificar Nombre\n2-Modificar Apellido\n"
                        "3-Modificar Salario\n4-Modificar Sector\n"
                        "5- Atras (Menu Principal)\n";
    int retorno=-1;

    if((pEmployee!=NULL)&&(len>0))
    {
        auxID=emp_getID(pEmployee,len,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=emp_findEmployeeById(pEmployee,len,auxID);
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
                            if(!getStringLetras(bufferName,"\nIngrese NUEVO Nombre: ",generalMsgE,tries))
                            {
                                strncpy(pEmployee[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferSurname,"\nIngrese NUEVO Apellido: ",generalMsgE,tries))
                            {
                                strncpy(pEmployee[posOfID].surname,bufferSurname,sizeof(bufferSurname));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(!getStringNumerosFloat(bufferSalario,"\nIngrese NUEVO Salario: ",generalMsgE,tries))
                            {
                                auxPrecio=atof(bufferSalario);
                                pEmployee[posOfID].salary=auxPrecio;
                                retorno=0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(!getStringNumeros(bufferSector,"\nIngrese NUEVO Sector: ",generalMsgE,tries))
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

int emp_sortEmployees(Employee* pEmpleado, int len,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Employee buffer;
    if(pEmpleado!=NULL && len>0)
    {
        for(i=0;i<len-1;i++)
        {

            for(j=i+1;j<len;j++)
            {

                if((order==1)&&(strcmp(pEmpleado[i].surname,pEmpleado[j].surname)>0))
                {
                    buffer=pEmpleado[i];
                    pEmpleado[i]=pEmpleado[j];
                    pEmpleado[j]=buffer;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(pEmpleado[i].surname,pEmpleado[j].surname)<0))
                {
                    buffer=pEmpleado[i];
                    pEmpleado[i]=pEmpleado[j];
                    pEmpleado[j]=buffer;
                    retorno=0;
                }
            }
        }
    }
    return retorno;
}

int emp_informarTotalSalariosPromedio(Employee* pEmployee,int len)
{
    int i;
    float totalResult;
    float promedioResult;
    int employeeOverPromedio;
    int contadorPromedio=0;
    float sum=0;
    int ret=-1;
    if(pEmployee!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployee[i].isEmpty==0)
            {
                sum+=pEmployee[i].salary;
                contadorPromedio++;
            }
        }
        totalResult=sum;
        promedioResult=totalResult/contadorPromedio;
        emp_salaryOverPromedio(pEmployee,len,promedioResult,&employeeOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nEL TOTAL DE SALARIOS ES: %.2f\nEL PROMEDIO DE SALARIOS ES: %.2f\n"
                    "LOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",
                    totalResult,promedioResult,employeeOverPromedio);
        }
    }
    return ret;
}

int emp_salaryOverPromedio(Employee* pEmployee,int len,float promedioResult,int* valor)
{
    int i;
    int contadorEmployee=0;
    int ret=-1;
    if(pEmployee!=NULL && len>0 && valor!=NULL)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployee[i].isEmpty==0)
            {
                if(pEmployee[i].salary>promedioResult)
                {
                    contadorEmployee++;
                }
            }

        }
        *valor=contadorEmployee;
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
            //pEmployee[i].idEmployee=-1;
            pEmployee[i].isEmpty=1;
        }
    }
    return 0;
}

int emp_findFree(Employee* pEmployee, int len)
{
    int i;
    int ret=-1;
    if(pEmployee!=NULL && len>0)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployee[i].isEmpty==1)
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

int emp_findEmployeeById(Employee* pEmployee, int len, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<len;i++)
    {
        if((pEmployee[i].isEmpty==0)&&(pEmployee[i].idEmployee==idE))
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
