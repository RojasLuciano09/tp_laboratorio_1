/*
 * ArrayEmployees.c
 * Author: Nicolas Luciano Rojas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "ArrayEmployees.h"
#include <ctype.h>

static int generateNewID(void);
static int searchForEmpty(Employee *list, int len);
static int receiveMoreThanAverage(Employee *list, int len, float salaryAverage,int *pQTYemployeesWhoReceiveMoreThanAverage);
static int sortEmployeeBySector(Employee *list, int len, int order);
static int sortEmployeeByLastName(Employee *list, int len, int order);
static int calculateTotalAndAverageSalary(Employee *list, int len,float *pSalaryTotal, float *pAverage);
static int UpperFirstChar(char *string);

/**
 * \brief Function to converts an string to lowercase and it first letter to uppercase.
 * \param char *string: receive an string.
 */
static int UpperFirstChar(char *string)
{
	int functionReturn = -1;
	if(string!=NULL)
	{
		char bufferName[LONG_NOMBRE];
		strncpy(bufferName, string, LONG_NOMBRE);
		bufferName[0] = toupper(bufferName[0]);
		for(int i=1;i<LONG_NOMBRE;i++)
		{
		bufferName[i] = tolower(bufferName[i]);
		}
		strncpy(string, bufferName, LONG_NOMBRE);
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Add a new employee to the list
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param pFlagFirstLoad: if it is true we can use the function
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int employee_AddEmployeeData(Employee *list, int len)
{
	int functionReturn = -1;
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int index;
	if(list!=NULL && len>0)
	{
		if ((employee_seachFreeIndex(list, len, &index) == 0)
			&& (utn_getString("\nIngresar nombre: ", "\n Error! Ingrese un dato valido.\n", name, ATTEMPTS,
					LONG_NOMBRE) == 0)

			&& (utn_getString("Ingresar apellido: ","\n Error! Ingrese un dato valido.\n", lastName,
					ATTEMPTS, LONG_NOMBRE) == 0)

			&& (utn_getInt("Ingresar sector <1-2-3-4-5> : ", "\n Error! Ingrese un dato valido.\n",
					&sector, ATTEMPTS, 1, 5) == 0)

			&& (utn_getFloat("Ingrese su salario: ","\n Error! Ingrese un dato valido.\n", &salary,
					ATTEMPTS, 0, INT_MAX) == 0))
	{
		id = generateNewID();
		AddEmployees(list, len, id, name, lastName, salary, sector,index);
		functionReturn = 0;
		printf("\nEmpleado añadido exitosamente.\n");
	} else
	{
		printf("\nHubo un error cargando el empleado..\n");
	}

	}
	return functionReturn;
}

/** \brief: Sort the list according to the last name of each employee
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param order 		: value (1) sorts descending , value (2) sorts ascending
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
static int sortEmployeeByLastName(Employee *list, int len, int order) {
	int functionReturn = -1;
	int sorted;
	Employee bufferEmployee;
	if(list!=NULL && searchForEmpty(list, len) == 0)
	{
		do{
		sorted = TRUE;
		for (int i = 0; i < (len - 1); i++)
		{
			switch (order)
			{
			case 1:
				if (strncmp(list[i].lastName, list[i + 1].lastName, LONG_NOMBRE)
						> 0
						|| (strncmp(list[i].lastName, list[i + 1].lastName,
								LONG_NOMBRE) == 0
								&& strncmp(list[i].name, list[i + 1].name,
										LONG_NOMBRE) > 0))
				{
					bufferEmployee = list[i];
					list[i] = list[i + 1];
					list[i + 1] = bufferEmployee;
					sorted = FALSE;
				}
				break;
			case 2:
				if (strncmp(list[i].lastName, list[i + 1].lastName, LONG_NOMBRE)
						< 0
						|| (strncmp(list[i].lastName, list[i + 1].lastName,
								LONG_NOMBRE) == 0
								&& strncmp(list[i].name, list[i + 1].name,
										LONG_NOMBRE) < 0))
				{
					bufferEmployee = list[i];
					list[i] = list[i + 1];
					list[i + 1] = bufferEmployee;
					sorted = FALSE;
				}
				break;
			}
		}
	} while (sorted == FALSE);
	functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Sort the list according to the sector of each employee
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param order 		: value (1) sorts descending value (2) sorts ascending
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
static int sortEmployeeBySector(Employee *list, int len, int order) {
	int functionReturn = -1;
	int sorted;
	Employee bufferEmployee;
	if(list!=NULL && searchForEmpty(list, len) == 0)
	{
	do {
		sorted = TRUE;
		for (int i = 0; i < (len - 1); i++)
		{
			switch (order)
			{
			case 1:
				if (list[i].sector > list[i + 1].sector)
				{
					bufferEmployee = list[i];
					list[i] = list[i + 1];
					list[i + 1] = bufferEmployee;
					sorted = FALSE;
				}
				break;
			case 2:
				if (list[i].sector < list[i + 1].sector)
				{
					bufferEmployee = list[i];
					list[i] = list[i + 1];
					list[i + 1] = bufferEmployee;
					sorted = FALSE;
				}
				break;
			}
		}
	} while (sorted == FALSE);
	functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Report of all employees on the list with descending and ascending options
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param flagFirstLoad : if it is true we can use the function
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int employee_Report(Employee *list, int len) {
	int functionReturn = -1;
	int orderBy;
	float totalSalary;
	float averageSalary;
	int moreThanAverage;
	if (list != NULL && searchForEmpty(list, len) == 0)
	{
		if (utn_getInt(
				"\nIngrese un valor para ordenar: \n1-Descendante \n2-Ascendente ",
				"\n Error! Ingrese un dato valido.\n", &orderBy, ATTEMPTS, 0, 2) == 0)
		{
			sortEmployeeByLastName(list, len, orderBy);
			sortEmployeeBySector(list, len, orderBy);
			calculateTotalAndAverageSalary(list, len, &totalSalary,&averageSalary);
			receiveMoreThanAverage(list, len, averageSalary, &moreThanAverage);
			functionReturn = 0;
		}
		printf("\nREPORTE DE EMPLEADOS.\n");
		printEmployees(list, len);
		printf("\nEl salario total es : %.2f "
				"\nEl promedio del salario es : %2.f "
				"\nCantidad de empleados que superan el promedio es: %d \n",
				totalSalary, averageSalary, moreThanAverage);
	}else
	{
		printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
	}
	return functionReturn;
}

/** \brief: Calculate the sum of the salaries of all employees
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param pSalaryTotal  : it is a pointer that save the total salary
 * \param pAverage 		: it is a pointer that save the average salary
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
static int calculateTotalAndAverageSalary(Employee *list, int len,float *pSalaryTotal, float *pAverage)
{
	int functionReturn = -1;
	float totalSalary = 0;
	int counterSalary = 0;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == FALSE)
			{
				totalSalary += list[i].salary;
				counterSalary++;
			}
		}
		*pSalaryTotal = totalSalary;
		*pAverage = (float) totalSalary / counterSalary;
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Calculate the number of employees who exceed the average salary
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param salaryAverage : average salary
 * \param pQTYemployeesWhoReceiveMoreThanAverage : it is a pointer that save the number of employees who are above average salary
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
static int receiveMoreThanAverage(Employee *list, int len, float salaryAverage,int *pQTYemployeesWhoReceiveMoreThanAverage)
{
	int functionReturn = -1;
	int receiveMoreThanAverage = 0;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == FALSE && list[i].salary > salaryAverage)
			{
				receiveMoreThanAverage++;
				functionReturn = 0;
			}
		}
		*pQTYemployeesWhoReceiveMoreThanAverage = receiveMoreThanAverage;
	}
	return functionReturn;
}

/** \brief: Modify an employee from the list using their ID
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param flagFirstLoad : if it is true we can use the function
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int employee_ModifyData(Employee *list, int len)
{
	int functionReturn = -1;
	int index;
	int ID;
	int fieldToModify;
	int modifyFlag;
	if (list != NULL && searchForEmpty(list, len) == 0)
	{
		printEmployees(list, len);
		if (utn_getInt("\nIngrese el ID del empleado a modificar: ",
				"\n Error! Ingrese un dato valido.\n", &ID, ATTEMPTS, 0, INT_MAX)
				== 0)
		{
			index = findEmployeeById(list, ID, len);
			if (index != -1) //isEmpty == TRUE
					{
				Employee bufferEmployee = list[index];
				modifyFlag = FALSE;

				do {

					utn_getInt(
							"\n¿Que campo desea modificar? \n1-Nombre: \n2-Apellido: \n3-Salario: \n4-Sector: \n5-FINALIZAR EDICION: ",
							"\n Error! Ingrese un dato valido.\n",
							&fieldToModify,
							ATTEMPTS, 1, 5);
					switch (fieldToModify)
					{
					case 1:
						if (utn_getString(
								"\nIngrese el nuevo nombre del empleado: ",
								"\n Error! Ingrese un dato valido.\n",
								bufferEmployee.name, ATTEMPTS, LONG_NOMBRE)
								== 0)
								{
							printf("\nSe actualizo correctamente el empleado\n");
							modifyFlag = TRUE;
							functionReturn = 0;
						}
						break;

					case 2:
						if (utn_getString(
								"\nIngrese el nuevo apellido del empleado: ",
								"\n Error! Ingrese un dato valido.\n",
								bufferEmployee.lastName, ATTEMPTS, LONG_NOMBRE)
								== 0) {
							printf("\nSe actualizo correctamente el empleado\n");
							modifyFlag = TRUE;
							functionReturn = 0;
						}
						break;

					case 3:
						if (utn_getFloat(
								"\nIngrese el nuevo salario del empleado: ",
								"\n Error! Ingrese un dato valido.\n",
								&bufferEmployee.salary, ATTEMPTS, 0, 9999.00)
								== 0) {
							printf("\nSe actualizo correctamente el empleado\n");
							modifyFlag = TRUE;
							functionReturn = 0;
						}
						break;
					case 4:
						if (

						utn_getInt(
								"\nIngrese el nuevo sector del empleado <1-2-3-4-5>: ",
								"\n Error! Ingrese un dato valido.\n",
								&bufferEmployee.sector, ATTEMPTS, 1, 5) == 0)

						{
							printf("\nSe actualizo correctamente el empleado\n");
							modifyFlag = TRUE;
							functionReturn = 0;
						}
						break;
					}

					if (modifyFlag == TRUE) {
						AddEmployees(list, len, ID, bufferEmployee.name,
								bufferEmployee.lastName, bufferEmployee.salary,
								bufferEmployee.sector, index);
					}

				} while (fieldToModify != 5);

			} else {
				printf("\nID inexistente \n ");
			}

		} else {
			printf("\nError. ");
		}
	}else
	{
		printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
	}
	return functionReturn;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid len or NULL pointer or if can't find a employee] - (0) if Ok
 */
int removeEmployee(Employee *list, int len, int id)
{
	int functionReturn = -1;
	int bufferIndex;
	if (list != NULL && len > 0)
	{
		bufferIndex = findEmployeeById(list, len, id);
		if (bufferIndex != -1)
		{
			list[bufferIndex].isEmpty = TRUE;
			functionReturn = 0;
		}
	}
	return functionReturn;
}

/** \brief: Remove an employee from the list using their ID
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param flagFirstLoad : if it is true we can use the function
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int employee_removeEmployee(Employee *list, int len)
{
	int idToFind;
	int functionReturn = -1;
	int flagRemove = 2;
	if (list != NULL && searchForEmpty(list, len) == 0)
	{
		do {
			printEmployees(list, len);
			if (utn_getInt("\nIngrese el id a eliminar: ",
					"\n Error! Ingrese un dato valido.\n", &idToFind, ATTEMPTS,
					0, INT_MAX) == 0)
			{
				if (removeEmployee(list, idToFind, len) == 0)
				{
					functionReturn = 0;
					flagRemove = 2;
					printf("\nEmpleado eliminado.\n");
				} else
				{
					flagRemove = 1;
					utn_getInt(
							"\nEmpleado inexiste. Desde intentar nuevamente? \n1-Si \n2-No",
							"\n Error! Ingrese un dato valido.\n", &flagRemove,
							ATTEMPTS, 1, 2);
				}
			}
		} while (flagRemove != 2);
	}else
	{
		printf("\nNo puede ingresar a esta opcion sin antes cargar un empleado.\n");
	}
	return functionReturn;
}

/** \brief find an Employee by Id en returns the index position in array.
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param id 			: id of an employee
 * \param pFreeIndex 	: save a free index
 * \return functionReturn : (-1) if Error [Invalid len or the list is out of data or  id is less than 0] - (0) if Ok
 */
int findEmployeeById(Employee *list, int id, int len) {
	int functionReturn = -1;
	if (list != NULL && len > 0 && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].id == id && list[i].isEmpty == FALSE)
			{
				functionReturn = i;
			}
		}
	}
	return functionReturn;
}

/**
 * \brief : Start employee list
 * \param list  		: current list of employees
 * \param len 			: list length
 */
int initEmployees(Employee *list, int len)
{
	int functionReturn = -1;
	if (list != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			list[i].id = -1;
			list[i].isEmpty = TRUE;
		}
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Generate a new id
 */
static int generateNewID(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}

/** \brief: Print the information of the employees
 * \param list  		: current list of employees
 * \param len 			: list length
 * \param pFreeIndex 	: save a free index
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int employee_seachFreeIndex(Employee *list, int len, int *pFreeIndex) {
	int functionReturn = -1;
	if (list != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty == TRUE && list[i].id == -1)
			{
				*pFreeIndex = i;
				functionReturn = 0;
				break;
			}
		}
	}
	return functionReturn;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee* : list where employees will be stored
 * \param len int        : list length
 * \param id int         : Employee ID
 * \param name[] char	 : Employee name
 * \param lastName[] char: Employee lastName
 * \param salary float	 : Employee salary
 * \param sector int     : Employee sector
 * \return int Return (-1) if Error [Invalid len or NULL pointer or without
 free space] - (0) if Ok
 */
int AddEmployees(Employee *list, int len, int id, char name[], char lastName[],float salary, int sector, int index)
{
	int functionReturn = -1;
	if (list != NULL && len > 0)
	{
		list[index].id = id;
		strcpy(list[index].name, name);
		strcpy(list[index].lastName, lastName);
		UpperFirstChar(list[index].name);
		UpperFirstChar(list[index].lastName);
		list[index].salary = salary;
		list[index].sector = sector;
		list[index].isEmpty = FALSE;
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief: Print the information of the employees
 * \param list : current list of employees
 * \param len : list len
 * \return functionReturn : (-1) if Error [Invalid len or  the list is out of data] - (0) if Ok
 */
int printEmployees(Employee *list, int len) {
	int functionReturn = -1;
		if (list != NULL && searchForEmpty(list, len) == 0)
		{
			printf("\nLastName        Name            Sector     ID     Salary\n");
			for (int i = 0; i < len; i++)
			{
				if (list[i].isEmpty == FALSE)
				{
					printf("%-15s %-15s   %-6d   %-6d $%.2f\n", list[i].lastName,list[i].name, list[i].sector, list[i].id,list[i].salary);
				}
			}
			functionReturn = 0;
	    }
	return functionReturn;
}

/**
 * \brief Function to search in the Employee array for an empty field
 * \param Employee *list: Pointer to an Employee array
 * \param int len: Length of the array
 * \return (-1) if something went wrong, (0) if everything is OK
 */

static int searchForEmpty(Employee *list, int len)
{
	int retornar = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

