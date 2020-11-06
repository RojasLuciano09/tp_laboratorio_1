#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"


/* \brief Parse the employee data from the data.csv file (binary mode).
 *
 * \param pFile FILE* :  File from which the data will be obtained.
 * \param pArrayListEmployee LinkedList* : List in which the obtained data will be stored
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output = -1;
	Employee* bufferEmployee;
	int read;
	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			bufferEmployee = employee_new();
			if(bufferEmployee != NULL)
			{
				read = fread(bufferEmployee,sizeof(Employee),1,pFile);
				if(read == 1)
				{
					ll_add(pArrayListEmployee, bufferEmployee);
				}
				else
				{
					employee_delete(bufferEmployee);
					break;
				}
			}
		}while(!feof(pFile));
		output = 0;
	}
	return output;
}
/** \brief Parse the employee data from the data.csv file (text mode).
 *
 * \param pFile FILE* :  File from which the data will be obtained.
 * \param pArrayListEmployee LinkedList* : List in which the obtained data will be stored
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferId[SIZE];
	char bufferName[SIZE];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	Employee* bufferEmp;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		ll_clear(pArrayListEmployee);
		do
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferHours,bufferSalary)==4)
			{
				bufferEmp = employee_newParametros(bufferId, bufferName, bufferHours, bufferSalary);
				ll_add(pArrayListEmployee, bufferEmp);
				output=0;
			}
			else
			{
				employee_delete(bufferEmp);
			}
		}while(feof(pFile)==0);
	}
    return output;
}
