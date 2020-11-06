#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main(void)
{
	setbuf(stdout, NULL);
    int option = 0;
    int loadFlag=0;
    int optionFlag;
    LinkedList* listaEmpleados = ll_newLinkedList();

    printf("\nBienvenido al sistema de gesti�n de empleados.\n");
    do{
    	utn_getMenu(&option, ATTEMPTS, 1, 10);

        switch(option)
        {
            case 1:

                if(loadFlag==0 && controller_loadFromText("data.csv",listaEmpleados)==0)
                {
                	printf("\nDatos cargados.\n");
                	loadFlag=1;
                }
                else
                {
                	if(utn_getInt("\nLa lista ya existe, sobrescribir?: \n1-Si\n2-No \n>",ERROR,&optionFlag,ATTEMPTS,1,2) &&
                		optionFlag==1 && controller_loadFromText("data.csv",listaEmpleados)==0	)
                	{
                		printf("\nDatos cargados.\n");
                	}
                	else
                	{
                		printf("\nNo hay datos cargados.\n");
                	}
                }
                break;

            case 2:

                if(loadFlag==0 && controller_loadFromBinary("dataBinario.bin",listaEmpleados)==0)
                {
                	printf("\nDatos cargados.\n");
                	loadFlag=1;
                }
                else
                {
                	if(utn_getInt("\nLa lista ya existe, sobrescribir?: \n1-Si\n2-No \n>",ERROR,&optionFlag,ATTEMPTS,1,2) &&
                		optionFlag==1 && controller_loadFromBinary("dataBinario.bin",listaEmpleados)==0	)
                	{
                		printf("\nDatos cargados.\n");
                	}
                	else
                	{
                		printf("\nNo hay datos cargados.\n");
                	}
                }
                break;

            case 3:
            	controller_addEmployee(listaEmpleados);
                break;

            case 4:
            	controller_editEmployee(listaEmpleados);
                break;

            case 5:
            	controller_removeEmployee(listaEmpleados);
                break;

            case 6:
            	controller_ListEmployee(listaEmpleados);
                break;

            case 7:
            	controller_sortEmployee(listaEmpleados);
                break;

            case 8:
            	controller_saveAsText("data.csv",listaEmpleados);
                break;

            case 9:
            	controller_saveAsBinary("dataBinario.csv",listaEmpleados);
                break;


        }
    }while(option != 10);
    ll_deleteLinkedList(listaEmpleados);
    printf("\nExit");
    return 0;
}

