/*
 * ArrayEmployees.h
 * Author: Nicolas Luciano Rojas
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_
#define TRUE 1
#define FALSE 0
#define LONG_NOMBRE 51
#define length 999
#define QTY_EMPLOYEE 1000
#define ATTEMPTS 3


struct
{
int id;
char name[51];
char lastName[51];
float salary;
int sector;
int isEmpty;
}typedef Employee;

int initEmployees(Employee* EmployeList, int limite);
int AddEmployees(Employee list[],int len,int id,char name[],char lastName[],float salary,int sector,int index);
int findEmployeeById(Employee* EmployeeList,int id, int limite);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* list, int len, int order);
int printEmployees(Employee* list, int limite);
int employee_AddEmployeeData(Employee *list, int len,int *pFlagFirstLoad);
int employee_seachFreeIndex(Employee* EmployeeList, int limite,int *pIndiceLibre);
int employee_ModifyData(Employee *list, int len, int flagFirstLoad);
int employee_calculateAverageSalary(Employee* list, int len, float *pAvg, int *pSAvg, float *acumulatorSalary);
int employee_Report(Employee *list, int len,int flagFirstLoad);
int employee_removeEmployee(Employee *list, int len, int flagFirstLoad);




#endif /* ARRAYEMPLOYEES_H_ */
