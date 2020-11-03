#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utn.h"
#include "employee.h"

static int UpperFirstChar(char *string);

/**
 * @fn
 * @brief
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
static int UpperFirstChar(char *string)
{
	int functionReturn = -1;
	if(string!=NULL)
	{
		char bufferName[LONG_NAME];
		strncpy(bufferName, string, LONG_NAME);
		bufferName[0] = toupper(bufferName[0]);
			for(int i=1;i<LONG_NAME;i++)
			{
				bufferName[i] = tolower(bufferName[i]);
			}
		strncpy(string, bufferName, LONG_NAME);
		functionReturn = 0;
	}
	return functionReturn;
}

/**
 * @fn
 * @brief 	asigna un valor entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setId(Employee* this,int id)
{
	int output=-1;
	if(this!=NULL && id>-1)
	{
		this->id = id;
		output=0;
	}
	return output;
}

/**
 * @fn
 * @brief 	Devuelve por puntero un entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int  employee_getId(Employee* this,int* id)
{
	int output=-1;
	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		output=0;
	}
	return output;
}

/**
 * @fn
 * @brief 	Este asigna un valor char
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int output=-1;
	if(this!=NULL && isString(nombre)==1 && nombre!=NULL)
	{
		strncpy(this->nombre,nombre,LONG_NAME);
		UpperFirstChar(this->nombre);
		output=0;
	}
	return output;
}

/**
 * @fn
 * @brief 	Devuelve por puntero un char
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retornar=-1;
	if(this!=NULL && nombre!=NULL)
	{
		strncpy(nombre, this->nombre, LONG_NAME);
		retornar=0;
	}
	return retornar;
}

/**
 * @fn
 * @brief 	Asigna un valor de tipo entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas>0)
	{
		this->horasTrabajadas = horasTrabajadas;
		output=0;
	}
	return output;

}

/**
 * @fn
 * @brief 	Devuelve por puntero un entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		output=0;
	}
	return output;

}

/**
 * @fn
 * @brief 	Asigna un valor de tipo entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo>0)
	{
		this->sueldo = sueldo;
		output=0;
	}
	return output;

}

/**
 * @fn
 * @brief 	Devuelve por puntero un entero
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo= this->sueldo;
		output=0;
	}
	return output;

}
//--------get & set STR --------------------------------------------------------

/**
 * @fn
 * @brief Asigna un id de tipo char a un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setIdStr(Employee* this, char* id)
{
	int retornar=-1;
	char bufferId[SIZE];
	if(this!=NULL && id!=NULL && isInt(id)==1)
	{
		strncpy(bufferId, id, SIZE);
		this->id = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

/**
 * @fn
 * @brief Devuelve por puntero de tipo char el id de un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getIdStr(Employee* this,char* id)
{
	int output=-1;

	if(this!=NULL && id!=NULL)
	{
		sprintf(id,"%d",this->id);
		output=0;
	}
	return output;
}

/**
 * @fn
 * @brief Asigna las horas trabajadas de tipo char a un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setHorasTrabajadasStr(Employee* this, char* horasTrabajadas)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && horasTrabajadas!=NULL && isInt(horasTrabajadas)==1)
	{
			strncpy(buffer, horasTrabajadas, SIZE);
			this->horasTrabajadas=atoi(buffer);
			output=0;
	}
	return output;
}

/**
 * @fn
 * @brief Devuelve por puntero de tipo char las horas trabajadas de un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas!=NULL)
	{
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
		output=0;
	}
	return output;
}

/**
 * @fn
 * @brief Asigna el sueldo de tipo char a un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_setSueldoStr(Employee* this, char* sueldo)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && sueldo!=NULL && isInt(sueldo)==1)
	{
			strncpy(buffer, sueldo, SIZE);
			this->sueldo=atoi(buffer);
			output=0;
	}
	return output;
}

/**
 * @fn
 * @brief Devuelve por puntero de tipo char el sueldo de un empleado.
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_getSueldoStr(Employee* this,char* sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo!=NULL)
	{
		sprintf(sueldo,"%d",this->sueldo);
		output=0;
	}
	return output;
}

//-----------------------------------------------------new's

/**
 * @fn
 * @brief
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
Employee* employee_new()
{
	Employee* this;
	this=(Employee*)malloc(sizeof(Employee));
	return this;
}

/**
 * @fn
 * @brief
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
void employee_delete(Employee* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/**
 * @fn
 * @brief 					GUARDA EN CHAR*
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setIdStr(this, idStr)!=-1 &&
		     employee_setNombre(this, nombreStr)!=-1 &&
			 employee_setHorasTrabajadasStr(this, horasTrabajadasStr)!=-1 &&
			 employee_setSueldoStr(this, sueldo)!=-1)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/**
 * @fn
 * @brief
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_print(Employee* this)
{
	int output=-1;
	char nombreAux[SIZE];
	char idAux[SIZE];
	char horasAux[SIZE];
	char salarioAux[SIZE];
	if(this!=NULL)
	{

		if( employee_getNombre(this, nombreAux)==0			    &&
			employee_getIdStr(this, idAux)==0					&&
			employee_getHorasTrabajadasStr(this, horasAux)==0   &&
			employee_getSueldoStr(this, salarioAux)==0			)
		{
			printf("\nID     Nombre        Horas      Sueldo\n");
			printf("%-6s %-10s  %5s %12s\n", idAux, nombreAux, horasAux, salarioAux);
			output = 0;
		}
	}
	return output;
}

/**
 * @fn
 * @brief 						GUARDA EN INT
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
Employee* employee_newParameters(int id,char* name,int hours, float salary)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setId(this, id)==0       				&&
		     employee_setNombre(this, name)==0 				&&
			 employee_setHorasTrabajadas(this, hours)==0    &&
			 employee_setSueldo(this, salary)==0			)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/**
 * @fn
 * @brief
 * @param
 * @param
 * @return (-1) Error (0) todo OK
 */
int employee_sort(void* itemOne,void* itemTwo)
{
	int output=0;
	Employee* buffer1;
	Employee* buffer2;

	buffer1	 = itemOne;
	buffer2	 = itemTwo;

	char name_1[LONG_NAME];
	char name_2[LONG_NAME];


	if(employee_getNombre(buffer1, name_1)==0   &&
	   employee_getNombre(buffer2, name_2)==0	)
	{
		if( strncmp(name_1, name_2,LONG_NAME)>0)
		{
			output = 1;
		}
		else
		{
			output=-1;
		}
	}
	else
	{
		printf("\nHubo un error en -> employee_sort(void* itemOne,void* itemTwo)");
	}

	return output;
}



























