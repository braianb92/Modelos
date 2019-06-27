#ifndef entrega_H_INCLUDED
#define entrega_H_INCLUDED
typedef struct
{
    int id;
    char tipo[128];
    int cantidad;
    int peso;
}Entrega;

Entrega* entrega_new();
Entrega* entrega_newParametros(char* idStr,char* tipoStr,char* cantidadStr,char* peso);
int entrega_delete();

int entrega_setId(Entrega* this, char* value);
int entrega_getId(Entrega* this,int* value);

int entrega_setTipo(Entrega* this,char* value);
int entrega_getTipo(Entrega* this,char* value);

int entrega_setCantidad(Entrega* this,char* value);
int entrega_getCantidad(Entrega* this,int* value);

int entrega_setPeso(Entrega* this,char* value);
int entrega_getPeso(Entrega* this,int* value);

int entrega_sortByTipo(void* entregaA,void* entregaB);


#endif // entrega_H_INCLUDED
