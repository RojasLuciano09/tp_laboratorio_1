/*
 * rojasLibrary.c
 *
 *  Created on: 3 sep. 2020
 *        Author: Nicolas Luciano Rojas
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Solicita un entero al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int maximo, valor maximo admitido
 * \param int minimo, valor maximo admitido
 * \return (-1) Error / (0) Ok
 *
 */
int function_pedirNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo)
{
	int retorno = -1;
	int bufferInt;
	int resultadoScanf;
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			maximo >= minimo)
	{
		do
		{
			printf("\n%s",mensaje);
			fflush(stdin);
			resultadoScanf = scanf("%d" , &bufferInt);
			if(resultadoScanf == 1 && bufferInt >= minimo && bufferInt <= maximo)
			{
				retorno = 0;
				*pResultado = bufferInt;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**
 * \brief Realiza una operacion de suma entre dos parametros.
 * \param char* primerNumero, Es el primer valor que ingreso el usuario.
 * \param char* primerNumero, Es el segundo valor que ingreso el usuario,
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */
int function_sumar(int *pResultado, int primerNumero, int segundoNumero) {
	int retorno = -1;
	if(pResultado!=NULL){
		*pResultado = (primerNumero + segundoNumero);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Realiza una operacion de resta entre dos parametros.
 * \param char* primerNumero, Es el primer valor que ingreso el usuario.
 * \param char* primerNumero, Es el segundo valor que ingreso el usuario,
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */
int function_resta(int *pResultado, int primerNumero, int segundoNumero) {
	int retorno = -1;
	if(pResultado!=NULL){
		*pResultado = (primerNumero - segundoNumero);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Realiza una operacion de multiplicacion entre dos parametros.
 * \param char* primerNumero, Es el primer valor que ingreso el usuario.
 * \param char* primerNumero, Es el segundo valor que ingreso el usuario,
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */
int function_multiplicar(int *pResultado, int primerNumero, int segundoNumero) {
	int retorno = -1;
	if(pResultado!=NULL){
		*pResultado = (primerNumero * segundoNumero);
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Realiza una operacion de division entre dos parametros.
 * \param char* primerNumero, Es el primer valor que ingreso el usuario.
 * \param char* primerNumero, Es el segundo valor que ingreso el usuario,
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */
int function_dividir(float *pResultado, int primerNumero, int segundoNumero) {
	int retorno = -1;

	if (segundoNumero != 0 && (pResultado!=NULL)) {
		*pResultado = (primerNumero / segundoNumero);
		retorno = 0;
	}else {
	printf("\nNo es posible dividir por cero");
	}
	return retorno;
}

/**
 * \brief Realiza una operacion de factorial del numero ingresado.
 * \param int numero_ingresado : Es el valor numerico al cual se le realizara el factorial.
*  \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenid
 */
int function_factorial(int* pResultado,int numero_ingresado)
{
	int temporal_factorial=1;
	int iteraciones;
	int retorno = -1;
	if(pResultado!=NULL && numero_ingresado>-1)
	{
		if(numero_ingresado!=0)
		{
			for(iteraciones=numero_ingresado; iteraciones>1; iteraciones--)
			{
				temporal_factorial=temporal_factorial*iteraciones;
			}
			retorno = 0;
		}
		else
		{
			temporal_factorial=1;
			retorno = 0;
		}
	}
	*pResultado=temporal_factorial;
	return retorno;
}



/**
 * \brief Realiza las operaciones matematicas individualmente y posee un case que muestra todas las operaciones juntas.
 * \param int options :  El valor ingresado ejecutara el case correspondiente a la funcion que se desea realizar.
 * \param int primerNumero : primer operando ingresado
 * \param int segundoNumero : segundo operando ingresado
 */
void resultados(int options, int primerNumero, int segundoNumero) {
	float resultado_division;
	int resultado;

	switch (options) {
	case 1:
		if (function_sumar(&resultado, primerNumero, segundoNumero) == 0)
			printf("\nEl resultado de %d + %d  es: %d \n", primerNumero,
					segundoNumero, resultado);
		else{printf("Syntax Error.");}
		break;

	case 2:
		if (function_resta(&resultado, primerNumero, segundoNumero) == 0) {
			printf("\nEl resultado de %d - %d  es: %d \n", primerNumero,
					segundoNumero, resultado);
		}
		else{printf("Syntax Error.");}
		break;

	case 3:
		if (function_dividir(&resultado_division, primerNumero, segundoNumero)
				== 0) {
			printf("\nEl resultado de %d / %d  es: %2.f \n", primerNumero,
					segundoNumero, resultado_division);
		}
		else{printf("Syntax Error.");}
		break;

	case 4:
		if (function_multiplicar(&resultado, primerNumero, segundoNumero)
				== 0) {
			printf("\nEl resultado de %d * %d  es: %d \n", primerNumero,
					segundoNumero, resultado);
		}
		else
		{
			printf("Syntax Error.");
		}
		break;

	case 5:
		if (function_factorial(&resultado, primerNumero) == 0) {
			printf("\nEl factorial de %d es: %d ", primerNumero, resultado);

		} else {
			printf("\nNo se pudo obtener el factorial de %d ", primerNumero);
		}

		if (function_factorial(&resultado, segundoNumero) == 0) {
			printf(" \nEl factorial de %d es: %d \n", segundoNumero, resultado);
		} else {
			printf("\nNo se pudo obtener el factorial de %d \n", segundoNumero);
		}
		break;

	case 6:
		function_sumar(&resultado, primerNumero, segundoNumero);
		printf("\nEl resultado de %d + %d  es: %d \n", primerNumero,
				segundoNumero, resultado);
		function_resta(&resultado, primerNumero, segundoNumero);
		printf("\nEl resultado de %d - %d  es: %d \n", primerNumero,
				segundoNumero, resultado);
		function_dividir(&resultado_division, primerNumero, segundoNumero);

		printf("\nEl resultado de %d / %d  es: %2.f \n", primerNumero,
				segundoNumero, resultado_division);
		function_multiplicar(&resultado, primerNumero, segundoNumero);
		printf("\nEl resultado de %d * %d  es: %d \n", primerNumero,
				segundoNumero, resultado);
		if (function_factorial(&resultado, primerNumero) == 0) {
			printf("\nEl factorial de %d es: %d ", primerNumero, resultado);

		} else {
			printf("\nNo se pudo obtener el factorial de %d ", primerNumero);
		}

		if (function_factorial(&resultado, segundoNumero) == 0) {
			printf(" \nEl factorial de %d es: %d \n", segundoNumero, resultado);
		} else {
			printf("\nNo se pudo obtener el factorial de %d \n", segundoNumero);
		}

		break;
	}

}
