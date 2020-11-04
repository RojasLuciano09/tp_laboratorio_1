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
	int output=-1;
	char bufferName[LONG_NAME];
	int bufferId;
	int bufferHours;
	int bufferSalary;

	Employee* buffer;
	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{
			if( fread(&bufferId,sizeof(int),1,pFile)==1 				  &&
				fread(bufferName, LONG_NAME, 1, pFile)==1	  		  &&
				fread(&bufferHours,sizeof(int), 1, pFile)==1 			  &&
				fread(&bufferSalary,sizeof(int),1,pFile)				   )
			{
				buffer = employee_newParameters(bufferId, bufferName, bufferHours, bufferSalary);
				ll_add(pArrayListEmployee, buffer);
				output=0;
			}
		}while(feof(pFile)==0);
		fclose(pFile);
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
	int read;

	if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		do
		{
			read = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferHours,bufferSalary);

				if(read==4)
				{
					bufferEmp = employee_newParametros(bufferId, bufferName, bufferHours, bufferSalary);
					ll_add(pArrayListEmployee, bufferEmp);
					output=0;
				}
				else
				{
					printf("\nThe file is corrupt\n");
					break;
				}

		}while(!feof(pFile));
		fclose(pFile);
	}
    return output;
}
