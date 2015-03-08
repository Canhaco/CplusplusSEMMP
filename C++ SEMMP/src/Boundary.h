#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Block.h"
#include "Eprintf.h"
#include "Parameters.h" 
#include "Grid.h" //Contém double N, E, S, W
#include "Dictionary.h"

/** Boundary conditions */
const char NORTH = 'N';
const char EAST = 'E';
const char WEST = 'W';
const char SOUTH = 'S';

const int PRESSURE_GRADIENT_ESPECIFIED = 1; 
const int PRESSURE_ESPECIFIED = 2;
const int LENGTHSN = 20;		//section name length
const int SIDENAME = 6;			//Side name: North, South, East, West
const int LENGTHSP = 25;		//section properties length
const int LENBCTYPE = 30;		//boundary condition type
const int LENGTHFN = 70;		//file name length

/** Classe que define as condições de contorno do simulador.
* @class Boundary
* @file Boundary.h
*/

class Boundary
{
  protected:
  char num[3];			///<Armazena a string convertida de um inteiro
  char SectionName[LENGTHSN];	///<Nome da seção
  char side[SIDENAME];		///<Lado: NORTH (Norte), EAST (Leste), SOUTH (Sul), WEST (Oeste)
  char str[LENGTHSP];		///<Propriedades da seção
  char type[LENBCTYPE];		///<Tipo de condição de fronteira
  char dirFileName[LENGTHFN];	///<Nome do arquivo
    
  bool bool_E;			///<Booleano para lado leste
  bool bool_W;			///<Booleano para lado oeste
  bool bool_N;			///<Booleano para lado norte
  bool bool_S;			///<Booleano para lado sul
  
  int row;			///<Linha do primeiro ou do único bloco 
  int col;			///<Coluna do primeiro ou do único bloco 
  int rowf;			///<Linha do último bloco 
  int colf;			///<Coluna do último bloco
  int type;			///<Tipo de condição de fronteira
  int i;			///<Índice do bloco???
  int k;			///<Contador
  int m;			///<Contador
  int tmp;			///<Variável temporária
  int diag_index = *j;		///<
  int j;			///<Contador
  int nsec;			///<
  int localIndex;		///<
  int add_col;			///<
  int add_row;			///<
  int drow;			///<
  int dcol;			///<
  int nblocks;			///<
  int *Map;			///<
  int **geom;			///<Array temporário para geometria
  
  double value;			///<Valor da condição de fronteira
  double *Ax;			///<
  double *b;			///<
    
  Boundary* boundary;
  Block *block;
  Parameters *par;
  Block *grid;
  Dictionary *ini;
  
  public: 
/** Método que "seta" as condições de fronteira.
* @fn SetBoundaryConditions
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
void SetBoundaryConditions(int *j, int *Map, double *Ax, double *b, 
									double N, double E, double W, double S, 
										 Boundary* boundary, Block *block);

/** Método que lê e "seta" as condições de fronteira.
* @fn ReadAndSetBoundaryConditions
* @param Parameters *par
* @param int **geom
* @param Block *grid
*/
Boundary *ReadAndSetBoundaryConditions(Parameters *par, int **geom, Block *grid);

};

#endif
