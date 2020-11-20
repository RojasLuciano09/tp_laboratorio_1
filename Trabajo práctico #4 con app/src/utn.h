/*
 * utn.h
 * Author: Nicolas Luciano Rojas
 */

#ifndef UTN_H_
#define UTN_H_




int utn_getCadena(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
int utn_getString(char mensaje[], char mensajeError[], char pResultado[], int attemps, int limit);
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max);
int utn_getCharInt(char msg[],char msrError[],char pResult[],int attempts,int limit);
int utn_getMenu(int *pResult, int attemps, int min, int max);
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max);
int isAlphaNum(char* pResultado);
int isString(char string[]);
int esLetrasYEspacios(char* cadena, int len);
int isInt(char string[]);

#endif /* UTN_H_ */
