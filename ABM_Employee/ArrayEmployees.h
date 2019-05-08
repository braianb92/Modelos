#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

typedef struct
{
    char name[50];
    char surname[50];
    int sector;
    float salary;
    int idEmployee;
    int isEmpty; //1 free - 0 full
}Employee;

int emp_menu(Employee* pEmployee,int len, char* menuText,
             int exitMenuNumber,int tries);

int emp_addEmployees(Employee* pEmployee,int len,char* msgE,int tries);
int emp_alter(Employee* pEmployee, int len,char* generalMsgE,int exitAlterMenuNumber,int tries);
int emp_removeEmployee(Employee* pEmployee, int len,char* msgE,int tries);
int emp_sortEmployees(Employee* pEmployee, int len,int order);

int emp_printEmployees(Employee* pEmployee,int len);
int emp_informarTotalSalariosPromedio(Employee* pEmployee,int len);
int emp_salaryOverPromedio(Employee* pEmployee,int len,float promedioResult,int* valor);

int emp_initEmployees(Employee* pEmployee,int len);
int emp_findFree(Employee* pEmployee, int len);
int emp_findEmployeeById(Employee* pEmployee, int len, int idE);
int emp_getID (Employee* pEmpleado,int len,char* msgE,int tries);

#endif // ARRAYEMPLOYEES_H_INCLUDED
