/*
 ============================================================================
 Name        : tp02.c
 Author      : Nicolas Luciano Rojas
 Version     : Final
 Description :Una empresa requiere un sistema para administrar su n�mina de empleados.
 Se sabe que dicha n�mina bajo ninguna circunstancia superara los 1000 empleados.

 El sistema deber� tener el siguiente men� de opciones:
 1. ALTAS: Se debe permitir ingresar un empleado calculando autom�ticamente el n�mero
 de Id. El resto de los campos se le pedir� al usuario.
 2. MODIFICAR: Se ingresar� el N�mero de Id, permitiendo modificar: o Nombre o Apellido
 o Salario o Sector
 3. BAJA: Se ingresar� el N�mero de Id y se eliminar� el empleado del sistema.
 4. INFORMAR:
 A. Listado de los empleados ordenados alfab�ticamente por Apellido y Sector.
 B. Total y promedio de los salarios, y cu�ntos empleados superan el salario promedio.
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
					printf("\nEmpleado a�adido exitosamente.\n");
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
