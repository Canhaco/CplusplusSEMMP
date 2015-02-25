#include "memory.h"

int *Memory::iVector(int size)
{
	int *v;
   
	v =  new int[size];
	if (!v) eprintf("allocation failure in ivector()");
	
	return v;
}
/*****************************************************************************/

double *Memory::rVector(int size)
{
	double *v;
   
	v =  new double[size];
	if (!v) eprintf("allocation failure in rvector()");
	
	return v;
}
/*****************************************************************************/

double **Memory::rMatrix(int rows, int cols)
{
	int i;
	double **m;
	
	m =  new double *[rows];
	if (!m) eprintf("allocation failure 1 in rmatrix():");
	
	for (i = 0; i < rows; i++) {
		m[i] = new double[cols];
		if (!m[i]) eprintf("allocation failure 2 in rmatrix():");
	}
	
	return m;
}
/*****************************************************************************/

int **Memory::iMatrix(int rows, int cols)
{
	int i;
	int **m;
	
	m =  new int *[rows];
	if (!m) eprintf("allocation failure 1 in imatrix():");
	
	for (i = 0; i < rows; i++) {
		m[i] = new int[cols];
		if (!m[i]) eprintf("allocation failure 2 in imatrix():");
	}
	
	return m;
}
/*****************************************************************************/

void Memory::freeiVector(int *v)
{
	delete [] v;
	v = NULL;

	return;
}
/*****************************************************************************/

void Memory::freerVector(double *v)
{
	delete [] v;
	v = NULL;
	
	return; 
}
/*****************************************************************************/

void Memory::freeiMatrix(int **m, int rows, int cols)
{
	int i;

	for(i = 0; i < rows; i++){
		delete [] m[i];
		m[i] = NULL;
	}
	delete [] m;
	m = NULL;
	
	return;
}
/*****************************************************************************/

void Memory::freerMatrix(double **m, int rows, int cols)
{
	int i;

	for(i = 0; i < rows; i++){
		delete [] m[i];
		m[i] = NULL;
	}
	delete [] m;
	m = NULL;

	return;
}
/*****************************************************************************/

