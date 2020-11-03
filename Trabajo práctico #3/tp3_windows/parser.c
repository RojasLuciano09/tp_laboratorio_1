#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/* \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char nombreAux[LONG_NAME];
	int idAux;
	int horasAux;
	int sueldoAux;

	Employee* buffer;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{	//puedo poner un flag para evitar el primer renglon.
			if( fread(&idAux,sizeof(int),1,pFile)==1 				  &&
				fread(nombreAux, LONG_NAME, 1, pFile)==1	  		  &&
				fread(&horasAux,sizeof(int), 1, pFile)==1 			  &&
				fread(&sueldoAux,sizeof(int),1,pFile)				   )
			{
				buffer = employee_newParameters(idAux, nombreAux, horasAux, sueldoAux);
				ll_add(pArrayListEmployee, buffer);
				output=0;
			}
		}while(feof(pFile)==0);
		fclose(pFile);
	}

	return output;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char horasAux[SIZE];
	char sueldoAux[SIZE];
	Employee* bufferEmp;
	int read;
	int flagFirstLine=0;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{
			read = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",idAux,nombreAux,horasAux,sueldoAux);
			if (flagFirstLine == 0)
			{
				flagFirstLine = 1;
			}
			else
			{
				if(read==4)
				{
					bufferEmp = employee_newParametros(idAux, nombreAux, horasAux, sueldoAux);
					ll_add(pArrayListEmployee, bufferEmp);
					output=0;
				}
				else
				{
					printf("El archivo esta corrupto");
					break;
				}
			}
		}while(!feof(pFile));
		fclose(pFile);
	}
    return output;
}
/*

 	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{  //puedo poner un flag para evitar el primer renglon.
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",idAux,nombreAux,horasAux,sueldoAux)==4)
			{
				bufferEmp = employee_newParametros(idAux, nombreAux, horasAux, sueldoAux);
				ll_add(pArrayListEmployee, bufferEmp);
				output=0;
			}
		}while(feof(pFile)==0);
		fclose(pFile);
	}
    return output;



 */
