#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"
#include <limits.h>
#include "parser.h"

/** \brief Recorre la lista en busca del id con maximo valor.
 * \param pArrayListEmployee LinkedList* lista sobre la cual se itera.
 * \return int : Devuelve el id con maximo valor.
 */
int controller_searchMaxId(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int idAux;
	int idMax;
	Employee* buffer;
	int len = ll_len(pArrayListEmployee);
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			buffer = ll_get(pArrayListEmployee, i); // recorro y obtengo por indice de -> i
			if(employee_getId(buffer, &idAux)==0)
			{
				if(i==0 || idAux>idMax)
				{
					idMax = idAux;
					output = idMax;
				}
			}
		}

	}
	return output;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList* : lista a la cual se agregara el empleado nuevo.
 * \return int output: (-1) Error (0) todo OK
 */
int controller_addEmployee(LinkedList* pArrayListEmployee,int firstLoad)
{
	int output=-1;
	char bufferName[LONG_NAME];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	char bufferID[SIZE];

	Employee* buffer;
	if(pArrayListEmployee!=NULL)
	{
		if(utn_getCadena("Ingrese nombre: ",ERROR,bufferName, ATTEMPTS, LONG_NAME)==0    &&
		   utn_getCharInt("Ingrese horas: ",ERROR,bufferHours, ATTEMPTS, SIZE)==0 	 	 &&
		   utn_getCharInt("Ingrese sueldo: ",ERROR,bufferSalary, ATTEMPTS, SIZE)==0  	 )
		{
			sprintf(bufferID, "%d",controller_searchMaxId(pArrayListEmployee));
			//sprintf(bufferID, "%d",newid(pArrayListEmployee,firstLoad)); // revisar que controller solo ejecute 1 vez
			buffer = employee_newParametros(bufferID, bufferName, bufferHours, bufferSalary);
			ll_add(pArrayListEmployee,buffer);
			printf("\nAlta de empleado exitosa. \n");

		}
		else
		{
			printf("\nError en -->>> controller_addEmployee ");
		}
	}

    return output;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int output: (-1) Error (0) todo OK
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_EmployeeFromText(pFile, pArrayListEmployee))
		{
			printf("\nDatos cargados.\n");
			output=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
	}
    return output;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int output: (-1) Error (0) todo OK
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile!=NULL && parser_EmployeeFromBinary(pFile, pArrayListEmployee)==0)
		{
			printf("\nDatos cargados.\n");
			output=0;
		}
	}
	return output;
}



/** \brief : Recorre la lista en busqueda de un id, y devuelve por puntero su indice.
 *\param  int id : Id a buscar.
 * \param int *index : Puntero  que tendra el indice del ID.
 * \param pArrayListEmployee LinkedList* : lista en la cual se bucara el id
 * \return int output: (-1) Error (0) todo OK
 */
int controller_findById(LinkedList* pArrayListEmployee,int id, int *index)
{
	int output=-1;
	int idAux;
	int len = ll_len(pArrayListEmployee);
	Employee* buffer;

	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			buffer = ll_get(pArrayListEmployee, i); 			  // recorro y obtengo por indice de -> i
			if(employee_getId(buffer,&idAux)==0 && idAux == id )  // si son iguales, obtengo el index
			{
				output=0;
				*index = i;
				break;
			}
		}
	}
	return output;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int idAux;
	int index;
	int option;
	char nombreAux[LONG_NAME];
	char horasAux[SIZE];
	char sueldoAux[SIZE];
	Employee* buffer;

	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nIngrese el id a modificar: ",ERROR,&idAux,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, idAux, &index)==0 && index>-1		    ) //revisar index
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nCampo a modificar?: \n1)Nombre \n2)Horas \n3)Sueldo \n0)SALIR \n->:",ERROR,&option,ATTEMPTS,-1,3)==0)
			{
				switch(option)
				{
				case 1:
					if(utn_getString("\nIngrese el nuevo nombre: ",ERROR,nombreAux,ATTEMPTS,LONG_NAME)==0 &&
					   employee_setNombre(buffer, nombreAux)==0 											)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nDatos actualizados...\n");
					}
				break;

				case 2:
					if(utn_getString("\nIngrese la nueva cantidad de horas: ",ERROR,horasAux,ATTEMPTS,LONG_NAME)==0   &&
					   employee_setHorasTrabajadasStr(buffer, horasAux)==0                                            )
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nDatos actualizados...\n");
					}
				break;

				case 3:
					if(utn_getString("\nIngrese el nuevo sueldo: ",ERROR,sueldoAux,ATTEMPTS,LONG_NAME)==0 		&&
					   employee_setSueldoStr(buffer,sueldoAux)==0  												)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nDatos actualizados...\n");
					}
				break;
				}
			}
		}
	}
	else
	{
		printf("\nNo hay datos para editar...\n");
	}
	return output;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int idAux;
	int index;
	int option;
	Employee* buffer;

	if(pArrayListEmployee!=NULL &&  !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nIngrese el id a dar de baja: ",ERROR,&idAux,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, idAux, &index)==0 && index>-1		      ) //revisar index
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nPresione 1 para eliminar.\nPresione 2 para cancelar.\n->:",ERROR,&option,ATTEMPTS,1,2)==0 	   &&
			   option==1																									)
			{
				ll_remove(pArrayListEmployee, index);
				output=0;
				printf("\nEmpleado eliminado...");
			}else
			{
				printf("\nEliminacion cancelada, volviendo al menu principal..");
			}
		}else
		{
			printf("\nNo se encontro el empleado con ese ID.");
		}
	}
	else
	{
		printf("\nNo hay datos para eliminar...\n");
	}
	return output;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* buffer;
	char nombreAux[SIZE];
	char idAux[SIZE];
	char horasAux[SIZE];
	char sueldoAux[SIZE];

	if(pArrayListEmployee!=NULL &&  !ll_isEmpty(pArrayListEmployee))
	{
		printf("\nID     Nombre        Horas      Sueldo\n");
		for(int i=0; i<len;i++)
		{
			buffer = ll_get(pArrayListEmployee, i);
			if(
			employee_getNombre(buffer, nombreAux)==0				&&
			employee_getIdStr(buffer, idAux)==0						&&
			employee_getHorasTrabajadasStr(buffer, horasAux)==0 	&&
			employee_getSueldoStr(buffer, sueldoAux)==0				)
			{
			printf("%-6s %-10s  %5s %12s\n", idAux, nombreAux, horasAux, sueldoAux);
			output=0;
			}
		}
	}
	else
	{
		printf("\nNo hay datos para mostrar...\n");
	}
    return output;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int op;
	if(!ll_isEmpty(pArrayListEmployee) &&  utn_getInt("\nSeleccione el tipo de ordenamiento \n1-Desc \n0-Asc \n>:",ERROR,&op,ATTEMPTS,-1,1)==0 	  )
	{
		ll_sort(pArrayListEmployee,employee_sort,op);
		output=0;
	}
	else
	{
		printf("\nNo hay datos para ordenar..\n");
	}
return output;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char nombreAux[SIZE];
	char idAux[SIZE];
	char horasAux[SIZE];
	char sueldoAux[SIZE];
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL &&  !ll_isEmpty(pArrayListEmployee))
		{
			pFile = fopen(path, "w");
			if(pFile!=NULL)
			{
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, nombreAux)==0			    &&
						employee_getIdStr(buffer, idAux)==0						&&
						employee_getHorasTrabajadasStr(buffer, horasAux)==0   	&&
						employee_getSueldoStr(buffer, sueldoAux)==0			 ) 				   //obtengo los datos.
					{
						fprintf(pFile, "%s,%s,%s,%s\n",idAux, nombreAux, horasAux, sueldoAux); //los guardo.
						output=0;
					}
				}
				fclose(pFile); 																   //mucho muy importante.
			}
		}
		else
		{
			printf("\nNo hay datos para guardar...\n");
		}
	return output;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char nombreAux[LONG_NAME];
	int idAux;
	int horasAux;
	int sueldoAux;
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
		{
			pFile = fopen(path, "wb");														//escribir en binario
			if(pFile!=NULL)
			{
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, nombreAux)==0			    &&
						employee_getId(buffer, &idAux)==0						&&
						employee_getHorasTrabajadas(buffer, &horasAux)==0   	&&
						employee_getSueldo(buffer, &sueldoAux)==0			     ) 		    //obtengo los datos.
					{
						fwrite(&idAux,sizeof(int),1,pFile);
						fwrite(nombreAux, LONG_NAME,1,pFile);
						fwrite(&horasAux,sizeof(int),1,pFile);								//los guardo xd
						fwrite(&sueldoAux,sizeof(int),1,pFile);
						output=0;
					}
				}
				fclose(pFile); 																//mucho muy importante
			}
		}
		else
		{
			printf("\nNo hay datos para guardar...\n");
		}
    return output;
}










