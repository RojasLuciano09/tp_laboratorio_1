/*
 ============================================================================
 Name        : TrabajoPractico01.c
 Author      : Nicolas Luciano Rojas
 Version     :
 Copyright   : Your copyright notice
 Description : Calculadora
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rojasLibrary.h"

int main(void) {

	setbuf(stdout, NULL);
	int options = 0;
	int primerNumero;
	int segundoNumero;

	printf("Bienvenido.");
	do {
		if (function_pedirNumero("\nIngrese el primer numero", " Error",
				&primerNumero, 3, INT_MAX, INT_MIN) == 0) {

			if (function_pedirNumero("\nIngrese el segundo numero", " Error",
					&segundoNumero, 3, INT_MAX, INT_MIN) == 0) {

				function_pedirNumero(
						"\n¿Que operacion desea realizar?  \n1-Sumar\n2-Resta\n3-Dividir\n4-Multiplicar\n5-Factorial\n6-Mostrar todos los resultados\n7-Salir",
						"Error", &options, 3, 7, 1);
				resultados(options, primerNumero, segundoNumero);

			} else {
				printf("\nSe acabaron los intentos :( ");
				options = 7;
			}
		} else {
			printf("\nSe acabaron los intentos :( ");
			options = 7;
		}
	}
	while (options != 7);
	printf("\nHasta luego :)");

	return 0;
}

