#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

typedef struct
{
    char name[50];
    char surname[50];
    int sector;
    float salary;
    int idEmployee;
    int isEmpty; //1 free - 0 full
}Employee;

int emp_addEmployees(Employee* pEmployee,int len,int pIndex,char* msgE,int tries);
int emp_alter(Employee* pEmployee, int len,char* msgE,int tries);
int emp_removeEmployee(Employee* pEmployee, int len,char* msgE,int tries);
//int emp_sortEmployees(Empleado* pEmpleado, int len,int order);
int emp_totalPromedio(Employee* pEmployee, int len,float* totalResult,float* promedioResult);
int emp_salaryOverPromedio(Employee* pEmployee,int len,float promedioResult,int* employeeOverPromedio);

int emp_initEmployees(Employee* pEmployee,int len);
int emp_findFree(Employee* pEmployee, int len);
int emp_findEmployeeById(Employee* pEmployee, int len, int idE);
int emp_getID (Employee* pEmpleado,int len,char* msgE,int tries);

int emp_printEmployees(Employee* pEmployee,int len);



#endif // EMPLEADO_H_INCLUDED
