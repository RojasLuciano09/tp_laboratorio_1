/*
 ============================================================================
 Name        : tp02.c
 Author      : Nicolas Luciano Rojas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ArrayEmployees.h"
#include "utn.h"

int main(void) {
	setbuf(stdout, NULL);

	int op=0;
	int flagFirstLoad=FALSE;
	Employee EmployeeArray[QTY_EMPLOYEE];
	if(initEmployees(EmployeeArray, length)==0)
	{
		printf("\nBienvenido al ABM de empleados.");
	do{
		utn_getNumberInt("\nOpciones: \n1-ALTA\n2-MODIFICAR\n3-BAJA\n4-INFORMAR\n5-EXIT",  "Error en menu\n", &op, ATTEMPTS, 1, 5);
		switch(op)
		{
			case 1:
				if(employee_AddEmployeeData(EmployeeArray, length,&flagFirstLoad)==0)
				{
					printf("\nEmpleado añadido exitosamente.\n");
				}else
				{
					printf("\nHubo un error cargando el empleado..\n");
				}
			break;

			case 2:
				if(employee_ModifyData(EmployeeArray, length,flagFirstLoad)==0)
				{
					printf("\nEmpleado modificado exitosamente.\n");
				}else
				{
					printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
				}
			break;

			case 3:
				if(employee_removeEmployee(EmployeeArray,length,flagFirstLoad)==0)
				{
					printf("\nEmpleado eliminado.\n");
				}else
				{
					printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
				}
				break;

			case 4:
				if(employee_Report(EmployeeArray, length,flagFirstLoad)==0)
				{
					printf("\nREPORTE DE EMPLEADOS.\n");
				}else
				{
					printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
				}
				break;
	 }
   }while(op!=5);
	printf("\nShutting down application...\n");
 }

	return EXIT_SUCCESS;
}
