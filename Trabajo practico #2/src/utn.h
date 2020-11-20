/*
 * utn.h
 * Author: Nicolas Luciano Rojas
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getString(char mensaje[], char mensajeError[], char pResultado[], int attemps, int limit);
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max);
int utn_getMenu(int *pResult, int attemps, int min, int max);
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max);

#endif /* UTN_H_ */
