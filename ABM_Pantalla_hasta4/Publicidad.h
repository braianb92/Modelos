#ifndef PUBLICIDAD_H_INCLUDED
#define PUBLICIDAD_H_INCLUDED

typedef struct
{
    char cuit[50];
    char archivo[250];
    int dias;
    int isEmpty; ///1vacio - 0ocupado
    int idPublicidad; ///clave unica de identidad univoca
    int idPantalla;
}Publicidad;

int pub_initPublicidad(Publicidad* pPublicidad,int len);

int pub_addPub(Publicidad* pPublicidad,Pantalla* pPantalla,int len,char* msgE,int tries);
int pub_removePublicidad(Publicidad* pPublicidad, int len,char* msgE,int tries);

int pub_findCuit(Publicidad* pPublicidad, int len,char* cuit);
int pub_findPubById(Publicidad* pPublicidad, int len, int idE);
int pub_findFree(Publicidad* pPublicidad, int len);

int pub_getID (Publicidad* pPublicidad,int len,char* msgE,int tries);

int pub_printContDiasMenorA(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub,int valor);
int pub_printContrataciones(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub);
int pub_printPantallasByCuit(Publicidad* pPublicidad,Pantalla* pPantalla,int lenPan,int lenPub,char* valor);

#endif // PUBLICIDAD_H_INCLUDED
