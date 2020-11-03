#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#define ARRAY_SIZE 4096
#define LONG_NOMBRE 50

static int myGets(char cadena[], int longitud);


static int isFloat(char string[]);

/*
 * utn_getNumero : Pide al usuario un numero
 * pResultado: Direccion de memoria de la variable donde escribe el valor ingresado por el usuario
 * min: valor minimo valido (inclusive)
 * max: valor maximo valido (no inclusive)
 * msg: El mensaje que imprime para pedir un valor
 * msgError: mensaje que imprime si el rango no es valido
 * output: 0: si esta todo OK. -1: Si hubo un error
 */
static int myGets(char cadena[], int longitud)
{
	int output=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n' && cadena[0] != '\n')
		{
		cadena[strlen(cadena)-1] = '\0';
		}
		output=0;
	}
	return output;
}

int isString(char string[])
{
	int output = 1;
	if(string != NULL && strlen(string) > 0)
	{
		for(int i = 0;string[i] != '\0'; i++)
		{
			if((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32)
			{
				output = 0;
				break;
			}
		}
	}
	return output;
}






static int isFloat(char string[])
{
	int output = 1;
	int i = 0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for( ; string[i] != '\0' ; i++)
		{
			if((string[i] > '9' || string[i] < '0') && string[i] != '.')
			{
				output = 0;
				break;
			}
		}
	}
	return output;
}


int isInt(char string[])
{
	int output = 1;
	int i = 0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for( ; string[i] != '\0' ; i++)
		{
			if(string[i] > '9' || string[i] < '0')
			{
				output = 0;
				break;
			}
		}
	}
	return output;
}

int utn_getString(char msg[], char msgError[], char pResult[], int attemps, int limit)
{
	int output = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isString(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)
			{
				output = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}
		}while(attemps >= 0);
	}
	return output;
}

int utn_getCharInt(char msg[],char msrError[],char pResult[],int attempts,int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(pResult != NULL && msg != NULL && msrError != NULL  && attempts >= 0)
	{
		do
		{
			printf("%s",msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1 )
			{
				strcpy(pResult, bufferString);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",msrError);
				attempts--;
			}
		}
		while(ATTEMPTS > 0);
	}
	return retorno;
}



int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max)
{
	int output = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					output = 0;
					break;
				}
				else
				{
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return output;
}

int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max)
{
	int output = -1;
	char bufferString[ARRAY_SIZE];
	float bufferFloat;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isFloat(bufferString) == 1)
			{
				bufferFloat = atof(bufferString);
				if(bufferFloat >= min && bufferFloat<= max)
				{
					*pResult = bufferFloat;
					output = 0;
					break;
				}
				else
				{
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return output;
}

int utn_getMenu(int *pResult, int attemps, int min, int max)
{
	int output = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;
	if(pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf(CHOOSE_MENU);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					output = 0;
					break;
				}
				else
				{
					printf("\nError! elija una opcion valida");
					attemps--;
				}

			}
			else
			{
				printf("Error! elija una opcion valida");
				attemps--;
			}

		}while(attemps >= 0);
	}
	return output;
}

int isAlphaNum(char* pResultado){
	int output = 1;
	int i;
	if(pResultado != NULL){
		for(i=0;pResultado[i] != '\0';i++){
			if((pResultado[i] != ' ') && (pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z') && (pResultado[i] < '0' || pResultado[i] > '9')){
				output = 0;
				break;
			}
		}
	}
	return output;
}

int esLetrasYEspacios(char* cadena, int len)
{
	int retorno = 1;
	int i;

	for(i=0 ;  i<len && cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}


int utn_getCadena(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	char bufferString[SIZE];
	int retorno = -1;
	if(pMensaje != NULL && pMensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, SIZE)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(esLetrasYEspacios(bufferString, limite) != 0))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos>=0);
		if(reintentos < 0)
		{
			printf("Te quedaste sin intentos\n");
		}
	}
	return retorno;
}


