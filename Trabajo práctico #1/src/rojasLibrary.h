/*
 * rojasLibrary.h
 *
 *  Created on: 3 sep. 2020
 *      Author: Nicolas Luciano Rojas
 */

#ifndef ROJASLIBRARY_H_
#define ROJASLIBRARY_H_

int function_factorial(int* pResultado,int operador);

int function_sumar(int *pResultado, int primerNumero, int segundoNumero);

int function_resta(int *pResultado, int primerNumero, int segundoNumero);

int function_multiplicar(int *pResultado, int primerNumero, int segundoNumero);

int function_dividir(float *pResultado, int primerNumero, int segundoNumero);

int function_pedirNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);

void resultados(int options, int primerNumero, int segundoNumero);

#endif /* ROJASLIBRARY_H_ */
