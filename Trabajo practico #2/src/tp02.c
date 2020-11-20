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
	Employee EmployeeArray[QTY_EMPLOYEE];
	if(initEmployees(EmployeeArray, length)==0)
	{
		printf("\nBienvenido al ABM de empleados.");
	do{
		utn_getInt("\nOpciones: \n1-ALTA\n2-MODIFICAR\n3-BAJA\n4-INFORMAR\n5-EXIT",  "Error en menu\n", &op, ATTEMPTS, 1, 5);
		switch(op)
		{
			case 1:
			employee_AddEmployeeData(EmployeeArray, length);
			break;

			case 2:
			employee_ModifyData(EmployeeArray, length);
			break;

			case 3:
			employee_removeEmployee(EmployeeArray,length);
			break;

			case 4:
			employee_Report(EmployeeArray, length);
			break;
	 }
   }while(op!=5);
	printf("\nShutting down application...\n");
 }

	return EXIT_SUCCESS;
}
