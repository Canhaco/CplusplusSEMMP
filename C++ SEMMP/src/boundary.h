#ifndef boundary_h
#define boundary_h

#include "block.h"
#include "eprintf.h"

/** boundary conditions */
#define PRESSURE_GRADIENT_ESPECIFIED  1 
#define PRESSURE_ESPECIFIED	        2  //double definition (well.h)
#define NORTH			'N'
#define EAST			'E'
#define WEST			'W'
#define SOUTH			'S'

/** bools */
#define TRUE			1   
#define FALSE			0

/** Classe que define as condições de contorno do simulador.
* @class boundary
* @file boundary.h
*/

class boundary
{
  public:
    
  int row;		///<row of first block or unique block 
  int col;		///<col of first block or unique block 
  int rowf;		///<row of last block 
  int colf;		///<col of last block
  int type;		///<type of boundary condition
  char side;		///<side: NORTH, EAST, SOUTH, WEST
  double value;		///<value of boundary condition
  
  public:
    
/** Método que "seta" as condições de fronteira .
* @fn setBoundaryConditions
* @param int *j
* @param int *Map
* @param double *Ax
* @param double *b
* @param double N
* @param double E
* @param double W
* @param double S
* @param Boundary* boundary
* @param Block *block
* @return void
*/

  void setBoundaryConditions(int *j, int *Map, double *Ax, double *b, 
									double N, double E, double W, double S, 
										 Boundary* boundary, Block *block);
};

#endif
