#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn_strings.h"
#include "ArrayEmployees.h"

///ESTE PROGRAMA FUE COMPILADO EN WINDOWS. AUTOR BRAIAN BALDINO.
static int generarId(void);

/** \brief  Menu to be printed with the appropriate
*           functions to call within.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of employee
* \param    menuText char Text to be shown as the main menu
* \param    exitMenuNumber int Number that exits the menu
            and also used as max number to be stablish a range
            of menu options to acces the corresponding function.
* \return   int Return 0.
* */
int employee_menu(Employee* arrayEmployee,int lenEmployee, char* menuText,
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

    employee_initEmployees(arrayEmployee,lenEmployee);
    while(option!=exitMenuNumber)
    {
        printf(menuText);

        getIntInRange(&option,"\n   INGRESE OPCION: ",generalMsgE,1,exitMenuNumber,tries);
        switch(option)
        {
            case 1:
                    if(!employee_addEmployees(arrayEmployee,lenEmployee,generalMsgE,tries))
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
                    if(!employee_alter(arrayEmployee,lenEmployee,generalMsgE,5,tries))
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
                    if(!employee_removeEmployee(arrayEmployee,lenEmployee,generalMsgE,tries))
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
                    employee_sortEmployees(arrayEmployee,lenEmployee,1);///order UP
                    employee_printEmployees(arrayEmployee,lenEmployee);
                    employee_informarTotalSalariosPromedio(arrayEmployee,lenEmployee);
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

/** \brief  add values entered by the user to
*           an existing array of employees
*           in an employeety position.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int employee_addEmployees(Employee* arrayEmployee,int lenEmployee,char* msgE,int tries)
{
    int indexFree;
    char bufferName[51];
    char bufferSurname[51];
    char bufferSalary[50];
    char bufferSector[20];
    float auxSalary;
    int auxSector;
    int retorno=-1;
    if((arrayEmployee!=NULL)&&(lenEmployee>0))
    {
        indexFree=employee_findFree(arrayEmployee,lenEmployee);
        if((indexFree!=-1)&&(getStringLetras(bufferName,"\nIngrese Nombre: ",msgE,tries)==0)&&
            (getStringLetras(bufferSurname,"\nIngrese Apellido: ",msgE,tries)==0))
        {
            if((getStringNumerosFloat(bufferSalary,"\nIngrese Salario: ",msgE,tries)==0)
                &&(getStringNumeros(bufferSector,"\nIngrese Sector: ",msgE,tries)==0))
            {
                auxSalary=atof(bufferSalary);
                auxSector=atoi(bufferSector);
                strncpy(arrayEmployee[indexFree].name,bufferName,sizeof(bufferName));
                strncpy(arrayEmployee[indexFree].surname,bufferSurname,sizeof(bufferSurname));
                arrayEmployee[indexFree].salary=auxSalary;
                arrayEmployee[indexFree].sector=auxSector;
                arrayEmployee[indexFree].idEmployee=generarId();
                arrayEmployee[indexFree].isEmpty=0;
                retorno=0;
            }
        }
    }
    return retorno;
}

/** \brief  Modify values in an existing
*           array of employees
*           in an existing position.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    generalMsgE char Shows an error message to be printed
*           when a value is not valid.
* \param    exitMenuNumber int Number that exits the menu
            and also used as max number to stablish a range
            of menu options to acces the corresponding function.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
* */
int employee_alter(Employee* arrayEmployee, int lenEmployee,char* generalMsgE,int exitAlterMenuNumber,int tries)
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

    if((arrayEmployee!=NULL)&&(lenEmployee>0))
    {
        auxID=employee_getID(arrayEmployee,lenEmployee,generalMsgE,tries);
        if(auxID>=0)
        {
            posOfID=employee_findEmployeeById(arrayEmployee,lenEmployee,auxID);
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
                                strncpy(arrayEmployee[posOfID].name,bufferName,sizeof(bufferName));
                                retorno=0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(!getStringLetras(bufferSurname,"\nIngrese NUEVO Apellido: ",generalMsgE,tries))
                            {
                                strncpy(arrayEmployee[posOfID].surname,bufferSurname,sizeof(bufferSurname));
                                retorno=0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(!getStringNumerosFloat(bufferSalario,"\nIngrese NUEVO Salario: ",generalMsgE,tries))
                            {
                                auxPrecio=atof(bufferSalario);
                                arrayEmployee[posOfID].salary=auxPrecio;
                                retorno=0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(!getStringNumeros(bufferSector,"\nIngrese NUEVO Sector: ",generalMsgE,tries))
                            {
                                auxSector=atoi(bufferSector);
                                arrayEmployee[posOfID].sector=auxSector;
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


/** \brief  Remove an Employee by Id (put isEmpty Flag in 1)
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    msgE char Shows an error message to be printed
*           when a value is not valid.
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if wrong, (0) if OK.
**/
int employee_removeEmployee(Employee* arrayEmployee, int lenEmployee,char* msgE,int tries)
{
    int auxID;
    int posOfID;
    int retorno=-1;
    if(arrayEmployee!=NULL && lenEmployee>0)
    {
        auxID=employee_getID(arrayEmployee,lenEmployee,msgE,tries);
         if(auxID>=0)
        {
            posOfID=employee_findEmployeeById(arrayEmployee,lenEmployee,auxID);
            if(posOfID!=-1)
            {
               arrayEmployee[posOfID].isEmpty=1;
               retorno=0;
            }
        }
     }
    return retorno;
}

/*int employee_sortEmployeesSimple(Employee* arrayEmployee, int lenEmployee,int order)///1up 0down
{
    int i;
    int j;
    int retorno=-1;
    Employee buffer;
    if(arrayEmployee!=NULL && lenEmployee>0 && (order==0 || order==1))
    {
        for(i=0;i<lenEmployee-1;i++)
        {

            for(j=i+1;j<lenEmployee;j++)
            {

                if((order==1)&&(strcmp(arrayEmployee[i].surname,arrayEmployee[j].surname)>0))
                {
                    buffer=arrayEmployee[i];
                    arrayEmployee[i]=arrayEmployee[j];
                    arrayEmployee[j]=buffer;
                    employee_sortEmployeesBySector(arrayEmployee,lenEmployee,order);
                }
                else if((order==0)&&(strcmp(arrayEmployee[i].surname,arrayEmployee[j].surname)<0))
                {
                    buffer=arrayEmployee[i];
                    arrayEmployee[i]=arrayEmployee[j];
                    arrayEmployee[j]=buffer;
                    employee_sortEmployeesBySector(arrayEmployee,lenEmployee,order);
                }
            }
        }
    }
    return retorno;
}*/

/** \brief  Sort the elements in the array of employees,
*           UP or DOWN according to its order parameter
*           by Surname and Sector.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int employee_sortEmployees(Employee* arrayEmployee, int lenEmployee,int order)///1up 0down
{
    int i;
    int flagNoEstaOrdenado=1;
    int retorno=-1;
    Employee buffer;
    if(arrayEmployee!=NULL && lenEmployee>0 && (order==0 || order==1))
    {
        while(flagNoEstaOrdenado==1)
        {
            flagNoEstaOrdenado=0;
            for(i=1;i<lenEmployee;i++)
            {
                if((order==1)&&(strcmp(arrayEmployee[i-1].surname,arrayEmployee[i].surname)>0))///Creciente
                {
                    buffer=arrayEmployee[i-1];
                    arrayEmployee[i-1]=arrayEmployee[i];
                    arrayEmployee[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
                else if((order==0)&&(strcmp(arrayEmployee[i-1].surname,arrayEmployee[i].surname)<0))///Decreciente
                {
                    buffer=arrayEmployee[i-1];
                    arrayEmployee[i-1]=arrayEmployee[i];
                    arrayEmployee[i]=buffer;
                    flagNoEstaOrdenado=1;
                    retorno=0;
                }
            }
        }
        if(flagNoEstaOrdenado==0)
        {
            employee_sortEmployeesBySector(arrayEmployee,lenEmployee,order);
        }
    }
    return retorno;
}

/** \brief  Sort the elements in the array of employees,
*           UP or DOWN according to its order parameter
*           by Sector if two Employees have the same surname.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    order Int number that indicates
*           the growing order [1]
*           the decreasing order[0]
* \return   return (-1) if wrong, (0) if OK.
**/
int employee_sortEmployeesBySector(Employee* arrayEmployee,int lenEmployee,int order)
{
    int i;
    Employee buffer;

    for(i=1;i<lenEmployee;i++)
    {
        if(strcmp(arrayEmployee[i-1].surname,arrayEmployee[i].surname)==0)
        {
            if((order==1)&&(arrayEmployee[i-1].sector>arrayEmployee[i].sector))
            {
                buffer=arrayEmployee[i-1];
                arrayEmployee[i-1]=arrayEmployee[i];
                arrayEmployee[i]=buffer;
            }
            else if((order==0)&&(arrayEmployee[i-1].sector<arrayEmployee[i].sector))
            {
                buffer=arrayEmployee[i-1];
                arrayEmployee[i-1]=arrayEmployee[i];
                arrayEmployee[i]=buffer;
            }
        }
    }
    return 0;
}

/** \brief  Shows the total amount of salary between employees,
*           the average salary and the number of employees
*           over the average.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \return   return (-1) if wrong, (0) if OK.
**/
int employee_informarTotalSalariosPromedio(Employee* arrayEmployee,int lenEmployee)
{
    int i;
    float totalResult;
    float promedioResult;
    int employeeloyeeOverPromedio;
    int contadorPromedio=0;
    float sum=0;
    int ret=-1;
    if(arrayEmployee!=NULL && lenEmployee>0)
    {
        for(i=0;i<lenEmployee;i++)
        {
            if(arrayEmployee[i].isEmpty==0)
            {
                sum+=arrayEmployee[i].salary;
                contadorPromedio++;
            }
        }
        totalResult=sum;
        promedioResult=totalResult/contadorPromedio;
        employee_salaryOverPromedio(arrayEmployee,lenEmployee,promedioResult,&employeeloyeeOverPromedio);
        ret=0;
        if(ret==0)
        {
            printf("\nEL TOTAL DE SALARIOS ES: %.2f\nEL PROMEDIO DE SALARIOS ES: %.2f\n"
                    "LOS EMPLEADOS QUE SUPERAN EL SALARIO PROMEDIO SON: %d\n",
                    totalResult,promedioResult,employeeloyeeOverPromedio);
        }
    }
    return ret;
}

/** \brief  Calculates the number of employees over
*           the average salary.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    promedioResult The average salary
* \param    valor Pointer that keeps the
*           number of employees that are
*           over the average salary.
* \return   return (-1) if wrong, (0) if OK.
**/
int employee_salaryOverPromedio(Employee* arrayEmployee,int lenEmployee,float promedioResult,int* valor)
{
    int i;
    int contadorEmployee=0;
    int ret=-1;
    if(arrayEmployee!=NULL && lenEmployee>0 && valor!=NULL)
    {
        for(i=0;i<lenEmployee;i++)
        {
            if(arrayEmployee[i].isEmpty==0)
            {
                if(arrayEmployee[i].salary>promedioResult)
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

/** \brief  Indicates that all positions in the array are employeety
*           by setting the flag isEmpty in 0 in all positions.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \return   return 0.
**/
int employee_initEmployees(Employee* arrayEmployee,int lenEmployee)
{
    int i;
    if(arrayEmployee!=NULL && lenEmployee>0)
    {
        for(i=0; i<lenEmployee;i++)
        {
            arrayEmployee[i].isEmpty=1;
        }
    }
    return 0;
}

/** \brief  Searchs through the array for an employeety position.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \return   return (-1) if no position found,
*           (Empty position) if employeety position.
**/
int employee_findFree(Employee* arrayEmployee, int lenEmployee)
{
    int i;
    int ret=-1;
    if(arrayEmployee!=NULL && lenEmployee>0)
    {
        for(i=0;i<lenEmployee;i++)
        {
            if(arrayEmployee[i].isEmpty==1)
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

/** \brief  Searchs through the array for a
*           specific value(ID).
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    idE Value to be found and matched in the array.
* \return   return (-1) if not found,
*           (position) if position matched.
**/
int employee_findEmployeeById(Employee* arrayEmployee, int lenEmployee, int idE)
{
    int i;
    int ret=-1;
    for(i=0;i<lenEmployee;i++)
    {
        if((arrayEmployee[i].isEmpty==0)&&(arrayEmployee[i].idEmployee==idE))
        {
            ret=i;
        }
    }
    return ret;
}

/** \brief  Asks the user to enter an ID.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return (-1) if error, (ID) if OK
**/
int employee_getID (Employee* arrayEmployee,int lenEmployee,char* msgE,int tries)
{
    int retorno=-1;
    char bufferID[20];
    int auxID;
    if(arrayEmployee!=NULL && lenEmployee>0)
    {
        if(!getStringNumeros(bufferID,"\nIngrese ID: ",msgE,tries))
        {
            auxID=atoi(bufferID);
            retorno=auxID;
        }
    }
    return retorno;
}

/** \brief  Shows the values of occupied positions.
* \param    arrayEmployee Employee* Pointer to array of employees
* \param    lenEmployee int Array len of emplyee
* \param    msgE char Shows an error message to be printed
* \param    tries The times user can try to enter
*           a valid value if something goes wrong.
* \return   return 0.
**/
int employee_printEmployees(Employee* arrayEmployee,int lenEmployee)
{
    int i;
    int flag=1;
    for(i=0;i<lenEmployee;i++)
    {
        if(arrayEmployee[i].isEmpty==0)
        {
            printf("\nID: %d\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\n-------",
                   arrayEmployee[i].idEmployee,arrayEmployee[i].name,arrayEmployee[i].surname,arrayEmployee[i].salary,arrayEmployee[i].sector);
            flag=0;
        }
    }
    if(flag)
    {
        printf("\n----El listado se encuentra vacio----\n");
    }
    return 0;
}

/** \brief  Generates a unique ID.
* \param    receives void
* \return   return void.
**/
static int generarId(void)
{
    static int idEmp=0;
    return idEmp++;
}
