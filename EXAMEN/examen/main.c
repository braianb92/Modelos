#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "baldino_validation.h"
#include "entregas.h"
#include "controller.h"
#include "informe.h"

int main()
{
    LinkedList* listaEntregas=ll_newLinkedList();

    controller_loadFromText("data.csv",listaEntregas);

    generarArchivoInformes("informes.txt",listaEntregas);
    return 0;
}
