#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

///ESTE PROGRAMA FUE COMPILADO EN WINDOWS. AUTOR BRAIAN BALDINO.
typedef struct
{
    char name[51];
    char surname[51];
    int sector;
    float salary;
    int idEmployee;
    int isEmpty; //1 free - 0 full
}Employee;

int employee_menu(Employee* arrayEmployee,int lenEmployee, char* menuText,
                    int exitMenuNumber,int tries);

int employee_addEmployees(Employee* arrayEmployee,int lenEmployee,char* msgE,int tries);
int employee_alter(Employee* arrayEmployee, int lenEmployee,char* generalMsgE,int exitAlterMenuNumber,int tries);
int employee_removeEmployee(Employee* arrayEmployee, int lenEmployee,char* msgE,int tries);
//int employee_sortEmployeesSimple(Employee* arrayEmployee, int lenEmployee,int order)
int employee_sortEmployees(Employee* arrayEmployee, int lenEmployee,int order);
int employee_sortEmployeesBySector(Employee* arrayEmployee,int lenEmployee,int order);

int employee_printEmployees(Employee* arrayEmployee,int lenEmployee);
int employee_informarTotalSalariosPromedio(Employee* arrayEmployee,int lenEmployee);
int employee_salaryOverPromedio(Employee* arrayEmployee,int lenEmployee,float promedioResult,int* valor);

int employee_initEmployees(Employee* arrayEmployee,int lenEmployee);
int employee_findFree(Employee* arrayEmployee, int lenEmployee);
int employee_findEmployeeById(Employee* arrayEmployee, int lenEmployee, int idE);
int employee_getID (Employee* arrayEmployee,int lenEmployee,char* msgE,int tries);

#endif // ARRAYEMPLOYEES_H_INCLUDED
