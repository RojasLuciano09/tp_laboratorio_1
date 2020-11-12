#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"
#include <limits.h>
#include "parser.h"


/** \brief Loads employee data from data.csv file (text mode).
 *
 * \param path char* : Path of the file to upload
 * \param pArrayListEmployee LinkedList* : list to which the loaded data will belong
 * \return int output : (-1) If there was an error (0) if the process was successful
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
			output=0;
		}
		else
		{
			printf("\nThe file does not exists");
		}
	}
    return output;
}

/** \brief Loads employee data from data.csv file (binary mode).
 *
 * \param path char* : Path of the file to upload
 * \param pArrayListEmployee LinkedList* : list to which the loaded data will belong
 * \return int output : (-1) If there was an error (0) if the process was successful
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile!=NULL && !parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			output=0;
		}
	}
	return output;
}

/** \brief Iterate the list in search of the id with the highest value
 *
 * \param pArrayListEmployee LinkedList* : list which is iterated
 * \return int output : it will return the id with the highest value or (-1) If there was an error
 */
int controller_searchMaxId(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Employee* bufferEmp;
	int id;
	int maxId;
	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
			employee_getId(bufferEmp, &id);
			if(i==0 || id>maxId)
			{
				maxId = id;
				retornar = maxId+1;
			}
		}
	}
	return retornar;
}

/** \brief Request for employee registration
 *
 * \param pArrayListEmployee LinkedList* : List to which an employee will be added.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[LONG_NAME];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	char bufferID[SIZE];

	Employee* buffer;
	if(pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getCadena("\nPlease write the name of the employee: ",ERROR,bufferName, ATTEMPTS, LONG_NAME)==0    &&
		   utn_getCharInt("\nPlease enter the hours worked: ",ERROR,bufferHours, ATTEMPTS, SIZE)==0 	 	 &&
		   utn_getCharInt("\nPlease enter salary: ",ERROR,bufferSalary, ATTEMPTS, SIZE)==0  	 )
		{
			sprintf(bufferID, "%d",controller_searchMaxId(pArrayListEmployee));
			printf("\nYour id is: %s\n",bufferID);
			buffer = employee_newParametros(bufferID, bufferName, bufferHours, bufferSalary);
			ll_add(pArrayListEmployee,buffer);
		}
		else
		{
			printf("\nThe operation couldn´t be completed at -> controller_addEmployee ");
		}
	}
	else
	{
		printf("\nYou must first upload the employee list.\n ");
	}
    return output;
}

/**\brief It goes through the list in search of a specific id and returns its index
 *
 * \param pArrayListEmployee LinkedList* :  list in which the id will be searched
 * \param id int : requested id
 * \param index int* : Pointer that will have the memory address of the index obtained
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_findById(LinkedList* pArrayListEmployee,int id, int *index)
{
	int output=-1;
	int bufferId;
	int len = ll_len(pArrayListEmployee);
	Employee* buffer;

	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			buffer = ll_get(pArrayListEmployee, i);
			if(employee_getId(buffer,&bufferId)==0 && bufferId == id )
			{
				output=0;
				*index = i;
				break;
			}
		}
	}
	return output;
}

/** \brief Modify employee data
 *
 * \param pArrayListEmployee LinkedList* : list of which an employee will be modified
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int bufferId;
	int index;
	int option;
	char bufferName[LONG_NAME];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	Employee* buffer;

	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nEnter the id of the employee to modify: ",ERROR,&bufferId,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, bufferId, &index)==0 && index>-1		    )
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nSelect the field to modify: \n1)Name \n2)Hours \n3)Salary \n0)EXIT \n>:",ERROR,&option,ATTEMPTS,-1,3)==0)
			{
				switch(option)
				{
				case 1:
					if(utn_getString("\nEnter the new name: ",ERROR,bufferName,ATTEMPTS,LONG_NAME)==0 &&
					   employee_setNombre(buffer, bufferName)==0 											)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;

				case 2:
					if(utn_getString("\nEnter the number of hours: ",ERROR,bufferHours,ATTEMPTS,LONG_NAME)==0   &&
					   employee_setHoursWorkedStr(buffer, bufferHours)==0                                            )
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;

				case 3:
					if(utn_getString("\nEnter the new salary: ",ERROR,bufferSalary,ATTEMPTS,LONG_NAME)==0 		&&
					   employee_setSalaryStr(buffer,bufferSalary)==0  												)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;
				}
			}
		}
	}
	else
	{
		printf("\nNo data to edit...\n");
	}
	return output;
}

/** \brief Unsubscribe employee
 *
 * \param pArrayListEmployee LinkedList* : list from which an employee will be unsubscribe.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int bufferId;
	int index;
	int option;
	Employee* buffer;

	if(pArrayListEmployee!=NULL &&  !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nEnter the id to unsubscribe: ",ERROR,&bufferId,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, bufferId, &index)==0 && index>-1		      )
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nPress 1 to delete.\nPress 2 to cancel.\n->:",ERROR,&option,ATTEMPTS,1,2)==0 	   &&
			   option==1																									)
			{
				ll_remove(pArrayListEmployee, index);
				output=0;
				printf("\nEmployee removed...");
			}else
			{
				printf("\nDeletion canceled, returning to the main menu..");
			}
		}else
		{
			printf("\nThe employee with that ID was not found.");
		}
	}
	else
	{
		printf("\nNo data to delete...\n");
	}
	return output;
}

/** \brief Prints the employee data uploaded.
 *
 * \param pArrayListEmployee LinkedList* : List from which the data to be printed will be obtained
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL)
	{
		printf("\nID       Name                 Hours      Salary\n");
		ll_map(pArrayListEmployee, employee_printConMap);
		output=0;
	}
    return output;
}

/** \brief Save the employee data in the file data.csv (text mode).
 *
 * \param path char* : Path where the file will be stored
 * \param pArrayListEmployee LinkedList* : List from which the data to be saved will be obtained.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[SIZE];
	char bufferId[SIZE];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL && ll_len(pArrayListEmployee)>0)
		{
			pFile = fopen(path, "w");
			if(pFile!=NULL)
			{
				printf("\nWork in progress..\n");
				ll_sort(pArrayListEmployee,employee_sortID,1);
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, bufferName)==0			    	&&
						employee_getIdStr(buffer, bufferId)==0						&&
						employee_getHorasTrabajadasStr(buffer, bufferHours)==0   	&&
						employee_getSueldoStr(buffer, bufferSalary)==0			 	)
					{
						fprintf(pFile, "%s,%s,%s,%s\n",bufferId, bufferName, bufferHours, bufferSalary);
						output=0;
					}
				}
				fclose(pFile);
				printf("\nData saved successfully.\n");
			}
		}
		else
		{
			printf("\nNo data to save...\n");
		}
	return output;
}

/** \brief Save the employee data in the data.csv file (binary mode).
 *
 * \param path char* : Path where the file will be stored
 * \param pArrayListEmployee LinkedList* : List from which the data to be saved will be obtained.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[LONG_NAME];
	int bufferId;
	int bufferHours;
	int bufferSalary;
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
		{
			pFile = fopen(path, "wb");
			if(pFile!=NULL)
			{
				ll_sort(pArrayListEmployee,employee_sortID,1);
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, bufferName)==0			    	&&
						employee_getId(buffer, &bufferId)==0						&&
						employee_getHorasTrabajadas(buffer, &bufferHours)==0   		&&
						employee_getSueldo(buffer, &bufferSalary)==0			     )
					{
						fwrite(&bufferId,sizeof(int),1,pFile);
						fwrite(bufferName, LONG_NAME,1,pFile);
						fwrite(&bufferHours,sizeof(int),1,pFile);
						fwrite(&bufferSalary,sizeof(int),1,pFile);
						output=0;
					}
				}
				fclose(pFile);
				printf("\nData saved successfully.\n");
			}
		}
		else
		{
			printf("\nNo data to save...\n");
		}
    return output;
}

/** \brief Sort employees
 *
 * \param pArrayListEmployee LinkedList* : list which will be ordered
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int op;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee) &&  utn_getInt("\nSelect sort order \n1-Desc \n0-Asc \n>:",ERROR,&op,ATTEMPTS,-1,1)==0)
	{
		printf("\nWork in progress..\n");
		ll_sort(pArrayListEmployee,employee_sort,op);
		printf("\nData ordered alphabetically ...\n");
		output=0;
	}
	else
	{
		printf("\nNo data to sort..\n");
	}
return output;
}

/* \brief
 *
 *
 */
int controller_removeEmployeeBySalary(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL)
	{
		ll_filterBorrarBajoUnaCondicion(pArrayListEmployee, employee_removeBy_Salary);
		output=0;
	}
	return output;
}























































