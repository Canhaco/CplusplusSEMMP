/* indexes for fluid properties tables */
#define PRESS			0						// IOSEMMP.H
#define FVF			1 						// IOSEMMP.H
#define INV_FVF			1						// IOSEMMP.H
#define VISC			2 						// IOSEMMP.H
#define INV_FVFVISC		2 						// IOSEMMP.H
#define GAMMA			3 						// IOSEMMP.H
#define NCOLPROPS		4 						// IOSEMMP.H

/*max column*/
#define MAXCOLDISPLAY	5   					// IOSEMMP.H
#define MAXCOLREPORT	100  					// IOSEMMP.H

/* strings length */
#define SIDENAME		6		 //Side name: North, South, East, West 					// IOSEMMP.H
#define LENGTHSN		20		 //section name length 									// IOSEMMP.H
#define LENGTHFN		70		 //file name length 									// IOSEMMP.H 		// PARAMETERS.H
#define LENGTHSP		25		 //section properties length 							// IOSEMMP.H 		// WELL.H
#define LINESIZE		1313	 //0.0.2 max line size in report (MAXCOLREPORT) 		// IOSEMMP.H
#define LENBCTYPE		30		 //boundary condition type 								// IOSEMMP.H
#define LENWELLTYPE		20		 //see: /* well types */  								// IOSEMMP.H
#define LENBLOCKTYPE	9		 //block type: ACTIVE, INACTIVE 						// IOSEMMP.H

/* extensions for output files*/
#define REPORTEXT		".txt"   //report extension 						// IOSEMMP.H
#define OUTPRESSUREEXT	".vtk"   //output pressure extension 				// IOSEMMP.H

/* default values */
#define NONP			-1		 //do not print Np 							// IOSEMMP.H
#define NOWELL			-1		 //block does not have a well 				// IOSEMMP.H
#define ACTIVEBLOCK		+1		 //active block 							// IOSEMMP.H
#define INVALIDBLOCK	 0		 //invalid enter 							// IOSEMMP.H
#define INACTIVEBLOCK	-1		 //inactive block 							// IOSEMMP.H
#define NOBOUNDARY		-1		 //block does not have boundary condition 	// IOSEMMP.H
#define UNDEF       "**UNDEF**"  //file name not found 						// IOSEMMP.H
//#define CALCULATEG      -1	     //flag to calculate G            		// IOSEMMP.H
#define ISBONDARY       -3		 //flag to verify if face is bondary 		// IOSEMMP.H
#define NOTRANSMISSIBILITY -1 												// IOSEMMP.H

/* boundary conditions */
#define PRESSURE_GRADIENT_ESPECIFIED  1 		// BOUNDARY.H
//#define PRESSURE_ESPECIFIED	        2 		// BOUNDARY.H
#define NORTH			'N'						// BOUNDARY.H
#define EAST			'E'						// BOUNDARY.H
#define WEST			'W'						// BOUNDARY.H
#define SOUTH			'S'						// BOUNDARY.H

/* bools */
#define TRUE			1   					// BOUNDARY.H
#define FALSE			0						// BOUNDARY.H

/* well types */
#define RATE_ESPECIFIED		1    //well type 				// WELL.H
#define PRESSURE_ESPECIFIED	2	 //well type 				// WELL.H
#define DING				0.25 //Ding's coupling model 	// WELL.H

/* constants */
#define BETAC			(double)1.127 						// WELL.H
#define ALPHAC			(double)5.614583 					// IOSEMMP.H
#define GAMMAC			(double)0.21584e-3 					// SEMMP.H
#define GRAV			(double)32.174 						// SEMMP.H
#define EPSILON			(double)1e-8						// GRID.H
#define PI				(double)3.14159265358979 			// WELL.H

#define BARREL_TO_CF	(double)5.614584 					// SEMMP.H

typedef struct {
	double iniTime;				// PARAMETERS.H
	double cf; 					// PARAMETERS.H
	double cphi;				// PARAMETERS.H
	double dpprops;				// PARAMETERS.H
	double p0;					// PARAMETERS.H
	double z0;					// PARAMETERS.H
	double invBSC;				// PARAMETERS.H
	double rhoSC;				// PARAMETERS.H
	double dt;					// PARAMETERS.H
	double dtMultiplier;		// PARAMETERS.H
	
	int dtLogScale;				// PARAMETERS.H
	int ncol;					// PARAMETERS.H
	int nrow;					// PARAMETERS.H
	int nSteps;					// PARAMETERS.H
	int outPressureSteps; 		// PARAMETERS.H
	int nBlocks;				// PARAMETERS.H
	int nfprop;					// PARAMETERS.H
	int nwells;					// PARAMETERS.H
	int nMatrix;				// PARAMETERS.H
	int displaySteps;		// steps for display on terminal						// PARAMETERS.H
	int reportSteps;		// steps for print report of blocks (in reportFile) 	// PARAMETERS.H
	int nDisplayBlocks;		// number of blocks to display on terminal 				// PARAMETERS.H
	int nReportBlocks;		// number of blocks to the report (in outputFile)		// PARAMETERS.H
	int nBoundary;          // number of boundary contitions (in bcFile)			// PARAMETERS.H
	int isCylindrical;		// bool for cylindrical coordenates						// PARAMETERS.H

	char reportFile[LENGTHFN];  									// PARAMETERS.H
	char outPressureFile[LENGTHFN];									// PARAMETERS.H
	char projectDir[LENGTHFN];										// PARAMETERS.H
	char projectName[LENGTHFN];  //0.0.2 							// PARAMETERS.H
	char iniFile[LENGTHFN];											// PARAMETERS.H
	char geometryFile[LENGTHFN];									// PARAMETERS.H
	char modifiedBlocksFile[LENGTHFN]; 								// PARAMETERS.H
	char modTransmissibilityFile[LENGTHFN]; //0.0.3 				// PARAMETERS.H
	char porosityFile[LENGTHFN];									// PARAMETERS.H
	char kxFile[LENGTHFN];											// PARAMETERS.H
	char kyFile[LENGTHFN];											// PARAMETERS.H
	char thicknessFile[LENGTHFN];									// PARAMETERS.H
	char zTopFile[LENGTHFN]; 										// PARAMETERS.H
	char dxFile[LENGTHFN];											// PARAMETERS.H
	char dyFile[LENGTHFN];											// PARAMETERS.H
	char fluidPropFile[LENGTHFN];									// PARAMETERS.H
	char wellsFile[LENGTHFN];   									// PARAMETERS.H
	char outputFile[LENGTHFN];  									// PARAMETERS.H
	char bcFile[LENGTHFN];      //boundary conditions file 			// PARAMETERS.H
} Parameters;

typedef struct {
	/* constant part of the transmissibilities */
	double Gxph; /* Gx_i+1/2 */  	//BLOCK.H
	double Gxmh; /* Gx_i-1/2 */  	//BLOCK.H
	double Gyph; /* Gy_j+1/2 */		//BLOCK.H
	double Gymh; /* Gy_j-1/2 */		//BLOCK.H
	
	double dx;						//BLOCK.H
	double dy;						//BLOCK.H
	double dz;						//BLOCK.H
	double z;						//BLOCK.H
	double Vac;  //V_b*alpha_c		//BLOCK.H
	double phi;						//BLOCK.H
	double kx;						//BLOCK.H
	double ky;						//BLOCK.H

	int isWellBlock;				//BLOCK.H

	int isBoundary;					//BLOCK.H
	int* boundary;					//BLOCK.H
	int nBoundary;					//BLOCK.H

	int row;						//BLOCK.H
	int col;						//BLOCK.H
	
	int H; /* Here */				//BLOCK.H
	int E; /* East */				//BLOCK.H
	int W; /* West */				//BLOCK.H
	int N; /* North */				//BLOCK.H
	int S; /* South */				//BLOCK.H
} Block;

typedef struct {
	int		row; 												// WELL.H
	int		col; 												// WELL.H
	int		type;	// pressure or flow rated specified 		// WELL.H
	double	dx;		// x distance to the block's SW corner		// WELL.H
	double	dy;		// y distance to the block's SW corner 		// WELL.H
	double	rw;		// wellbore radius 							// WELL.H
	double	s;		// skin factor 								// WELL.H
	double	h;		// height 									// WELL.H
	double	gw;		// constant part of well index 				// WELL.H
	double	qw;		// flow rate 								// WELL.H
	double	pwf;	// bottom hole pressure 					// WELL.H
	double  np;		// cumulative oil production 				// WELL.H
} Well;

typedef struct {
	int row;													//BLOCK.H
	int col;													//BLOCK.H
	int p;			// bool for display pressure 				//BLOCK.H
	int qw;			// bool for display flow rate 				//BLOCK.H
	int np;			// cumulative oil production				//BLOCK.H
	int pwf;		// bool for display bottom hole pressure 	//BLOCK.H
	int localIndex;	// block index in grid						//BLOCK.H
} Out;

typedef struct{
	int row;		//row of first block or unique block 	// BOUNDARY.H
	int col;		//col of first block or unique block  	// BOUNDARY.H
	int rowf;		//row of last block  					// BOUNDARY.H
	int colf;		//col of last block  					// BOUNDARY.H
	int type;		//type of boundary condition 			// BOUNDARY.H
	char side;      //side: NORTH, EAST, SOUTH, WEST 		// BOUNDARY.H
	double value;	//value of boundary condition 			// BOUNDARY.H
} Boundary;


/********************************************/
/******* memory allocation utilities ********/
int *iVector(int); 								// MEMORY.H
int **iMatrix(int, int);						// MEMORY.H
void freeiVector(int *);						// MEMORY.H
void freeiMatrix(int **, int, int);				// MEMORY.H
double *rVector(int);							// MEMORY.H
double **rMatrix(int, int);						// MEMORY.H
void freerVector(double *);						// MEMORY.H
void freerMatrix(double **, int, int);			// MEMORY.H
/********************************************/

/********************************************/
/******* file input/output utilities ********/
void rTableFile(char [], double **, int, int); 				// NEW FUNCTION IN IOSEMMP.H ????
void iTableFile(char [], int **, int, int); 				// NEW FUNCTION IN IOSEMMP.H ????
void readIniFile(int, char *[], Parameters *); 				// IOSEMMP.H
Block *readAndSetGeometry(Parameters *, int **);			// IOSEMMP.H
double **readFluidProperties(Parameters *);					// IOSEMMP.H
/********************************************/

void setInitialPressure(Parameters *, Block *, Well *, double **, double *, 			// GRID.H
						double *, double *);

double normDelta(double *, double *, int);												// GRID.H

double getTableVal(double **, int, double, int, double, int);							// IOSEMMP.H

void setMatrixStructure(Parameters *, Block *, int *, int *, double *,int *, 			// GRID.H
						int *, double *, int *);

void setTransmissibilityMatrix(Parameters *, Block *, Well *, double **, 				// GRID.H
							   double *, double *, double *, double *, int *, 
							   Boundary*);

void writePressureFile(Parameters *, int, Block *, double *);							// IOSEMMP.H

void setCartesianTransmissibilities(Parameters *, Block *, Boundary *); 				// GRID.H

void setCylindricalTransmissibilities(Parameters *, Block *, Boundary *, 				// GRID.H
									  Well *);

Well *readAndSetWellParameters(Parameters *);											// IOSEMMP.H

void setWells(Parameters *, Block *, int **, Well *); 									// GRID.H

double reqAbouKassemAziz(Block *, int); 												// WELL.H

double reqPeaceman(Block *, int); 														// WELL.H

double reqDing(Block*, int, double);													// WELL.H

void modifyGeometry(int**, Parameters*);												// IOSEMMP.H

void modifyTransmissibilities(int **, Block *, Parameters *);							// IOSEMMP.H

Boundary *readAndSetBoundaryConditions(Parameters*, int**, Block*);						// IOSEMMP.H

void setBoundaryConditions(int*, int*, double*, double*, double, 						// BOUNDARY.H
						   double, double, double, Boundary*, Block*);

Out *readAndSetOuts(Parameters*, Block*, int**, char*, double*);						// IOSEMMP.H

void *readAndSetMainOut(Parameters*, double*);											// IOSEMMP.H

void writeOuts(FILE*, int, Block*, Well *, Out*, double, double*, double*);				// IOSEMMP.H

void writeTableHeader(FILE*, Parameters*, Out*, int, double*);							// IOSEMMP.H

void header(FILE *, Parameters *);														// IOSEMMP.H