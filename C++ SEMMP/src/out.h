#ifndef OUT_H
#define OUT_H

class Out {

public:
	int row;
	int col;
	int p;			// bool for display pressure
	int qw;			// bool for display flow rate
	int np;			// cumulative oil production	
	int pwf;		// bool for display bottom hole pressure
	int localIndex;	// block index in grid
};
#endif