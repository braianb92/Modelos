#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

typedef struct
{
    char nombre[50];
    char apellido[50];
    int legajo;
    int isEmpty; ///1vacio - 0ocupado
    int idEmpleado; ///clave unica de identidad univoca
}Empleado;

int Empleado_inicializarArray(Empleado* pEmpleado,int len);
int Empleado_mostrarArray(Empleado* pEmpleado,int len);

int Empleado_alta(Empleado* pEmpleado,int len,int pIndex,int idE,char* msgE);
int Empleado_modifyFromLegajo(Empleado* pEmpleado, int len,char* msgE);
int Empleado_modifyFromID(Empleado* pEmpleado, int len,char* msgE);
int Empleado_bajaLogica(Empleado* pEmpleado, int len,char* msgE);


int Empleado_ordenarNameAtoZ(Empleado* pEmpleado, int len);
int Empleado_ordenarSurnameAtoZ(Empleado* pEmpleado, int len);
int Empleado_orderByLegajo(Empleado* pEmpleado, int len);
int Empleado_orderByID(Empleado* pEmpleado, int len);

int Empleado_findLegajo(Empleado* pEmpleado, int len, int valor);
int Empleado_findID(Empleado* pEmpleado, int len, int idE);
int Empleado_posLibre(Empleado* pEmpleado, int len);



#endif // EMPLEADO_H_INCLUDED
