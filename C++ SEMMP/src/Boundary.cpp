#include "Boundary.h" 

void Boundary::SetBoundaryConditions(int *j, int *Map, double *Ax, double *b, 
									 double N, double E, double W, double S, 
									 Boundary* boundary, Block *block)
{
	
	setprogname("boundary conditions"); //Função de eprintf

	for(k = block -> nBoundary - 1; k >= 0; k--)
	{
		i = block->boundary[k];
		
		if (boundary[i].type == PRESSURE_ESPECIFIED)
		{
			if(boundary[i].side == EAST && bool_E == 1)
			{
				Ax[Map[diag_index]] -= E;
				*b -= 2*E*boundary[i].value;
				bool_E = 0;
			}
			else if(boundary[i].side == WEST && bool_W == 1)
			{
				Ax[Map[diag_index]] -= W;
				*b -= 2*W*boundary[i].value;
				bool_W = 0;
			}
			else if(boundary[i].side == NORTH && bool_N == 1)
			{
				Ax[Map[diag_index]] -= N;
				*b -= 2*N*boundary[i].value;
				bool_N = 0;
			}
			else if(boundary[i].side == SOUTH && bool_S == 1)
			{
				Ax[Map[diag_index]] -= S;
				*b -= 2*S*boundary[i].value;
				bool_S = 0;
			}
			else
			{
				weprintf(
"There are more than one boundary conditions to the same\
                         block. Forgeting [Boundary %i] for block (%d,%d).", 
					i, block->row, block->col);	
				for(m = i; m < block->nBoundary-1; m++)
				{
					tmp = block->boundary[m+1];
					block->boundary[m+1] = block->boundary[m];
					block->boundary[m] = tmp;
				}
				block->nBoundary--;
			}
		}
	
		else if (boundary[i].type == PRESSURE_GRADIENT_ESPECIFIED)
		{
			if(boundary[i].side == EAST && bool_E == 1)
			{
				Ax[Map[diag_index]] += E;
				*b += block->dx*E*boundary[i].value;
				bool_E = 0;
			}
			else if(boundary[i].side == WEST && bool_W == 1)
			{
				Ax[Map[diag_index]] += W;
				*b -= block->dx*W*boundary[i].value;
				bool_W = 0;
			}
			else if(boundary[i].side == NORTH && bool_N == 1)
			{
				Ax[Map[diag_index]] += N;
				*b -= block->dy*N*boundary[i].value;
				bool_N = 0;
			}
			else if(boundary[i].side == SOUTH && bool_S == 1)
			{
				Ax[Map[diag_index]] += S;
				*b -= block->dy*S*boundary[i].value;
				bool_S = 0;
			}
			else
			{
				weprintf(
"There are more than one boundary conditions to the same\
                         block. Forgeting [Boundary %i] for block (%d,%d).", 
				  i, block->row, block->col);	
				for(m = i; m < block->nBoundary-1; m++)
				{
					tmp = block->boundary[m+1];
					block->boundary[m+1] = block->boundary[m];
					block->boundary[m] = tmp;
				}
				block->nBoundary--;
			}
		}
	}

	(*j)++;
	if(E > 0.0 && bool_E == 1)
	{
		Ax[Map[*j]] = E;
		(*j)++;
	}
	if(W > 0.0 && bool_W == 1)
	{
		Ax[Map[*j]] = W;
		(*j)++;
	}
	if(N > 0.0 && bool_N == 1)
	{
		Ax[Map[*j]] = N;
		(*j)++;
	}
	if(S > 0.0 && bool_S == 1)
	{
		Ax[Map[*j]] = S;
		(*j)++;
	}

	unsetprogname();
}

/*************************************************************************************************************/

Boundary* Boundary::ReadAndSetBoundaryConditions(Parameters *par, int **geom, Block *grid)
{	
	setprogname("boundary conditions"); //Função de eprintf

	if(strcmp(par->bcFile, UNDEF) == 0)
	{
		par->nBoundary = 0;
		return 0;
	}

	sprintf(dirFileName, "%s%s", par->projectDir, par->bcFile);
	ini = iniparser_load(dirFileName);
	if(ini == NULL)
	{
		eprintf("cannot parse boundaryfile:");
	}
	
	/**** Number of sections ****/
	nsec = 0;			// Number of sections in file
	i = 0;
	while(i < iniparser_getnsec(ini))
	{
		sprintf(str, "Boundary %i", nsec + 1); 
		if (iniparser_find_entry(ini, str)) 
		{
		  nsec++;
		}
		i++;
	}
	/****************************/

	par->nBoundary = iniparser_getint(ini, "main:nboundary", -1);
	
	if (nsec > par->nBoundary)
	{
		weprintf("inconsistencies in the boundary configuration file");
		weprintf("the last %i boundary are not being considered", 
			   nsec-par->nBoundary);
	}
	else if(nsec < par->nBoundary )
	{
		weprintf("inconsistencies in the boundary configuration file");
		weprintf("there are only %i boundary sections. adopting nboundary = %i",
			   nsec, par->nBoundary = nsec);
	}

	boundary = new Boundary[par->nBoundary]; //boundary = (Boundary *)calloc(par->nBoundary, sizeof(Boundary));
	
	if (!boundary) 
	{
	  eprintf("allocation failure for boundary struct:");
	}
	
	for(i = 0; i < par->nBoundary; i++)
	{
		itoa(i + 1, num, 10); //Converte inteiro para string
		sprintf(SectionName, "Boundary %s:", num);
		
		sprintf(str, "%s%s", SectionName, "row");
		boundary[i].row = iniparser_getint(ini, str, -1);

		sprintf(str, "%s%s", SectionName, "col");
		boundary[i].col = iniparser_getint(ini, str, -1);

		sprintf(str, "%s%s", SectionName, "rowf");
		boundary[i].rowf = iniparser_getint(ini, str, boundary[i].row);

		sprintf(str, "%s%s", SectionName, "colf");
		boundary[i].colf = iniparser_getint(ini, str, boundary[i].col);
		
		sprintf(str, "%s%s", SectionName, "type");
		strcpy(type, _strupr(iniparser_getstring(ini, str, NULL)));
		
		sprintf(str, "%s%s", SectionName, "side");
		strcpy(side, _strupr(iniparser_getstring(ini, str, NULL)));
		
		sprintf(str, "%s%s", SectionName, "value");
		boundary[i].value = iniparser_getdouble(ini, str, NOBOUNDARY);

		if(boundary[i].row < 0 || boundary[i].row >= par->nrow)
		{
			eprintf("row in [Boundary %i] outside of reservoir geometry", i + 1); 
		}
		if(boundary[i].col < 0 || boundary[i].col >= par->ncol)
		{
			eprintf("col in [Boundary %i] outside of reservoir geometry", i + 1); 
		}
		if(boundary[i].rowf < 0 || boundary[i].rowf >= par->nrow)
		{
			eprintf("rowf in [Boundary %i] outside of reservoir geometry", i + 1); 
		}
		if(boundary[i].colf < 0 || boundary[i].colf >= par->ncol)
		{
			eprintf("colf in [Boundary %i] outside of reservoir geometry", i + 1); 
		}		

		if (strcmp(side, "E")  == 0  || strcmp(side, "EAST")  == 0)
		{
			boundary[i].side = EAST;
		}
		else if (strcmp(side, "W")  == 0  || strcmp(side, "WEST")  == 0)
		{
			boundary[i].side = WEST;
		}
		else if (strcmp(side, "N")  == 0  || strcmp(side, "NORTH") == 0)
		{
			boundary[i].side = NORTH;
		}
		else if (strcmp(side, "S")  == 0  || strcmp(side, "SOUTH") == 0)
		{
			boundary[i].side = SOUTH;
		}
		else 
		{
			eprintf("side in [Boundary %i] is invalid", i + 1); 
		}
		
		if (strcmp(type, "PRESSURE_GRADIENT_ESPECIFIED") == 0 ||
			strcmp(type, "GRADIENT_ESPECIFIED") == 0 || 
			strcmp(type, "GRADIENT") == 0)
		{
			boundary[i].type = PRESSURE_GRADIENT_ESPECIFIED;
		}
		else if (strcmp(type, "PRESSURE_ESPECIFIED") == 0 ||
			strcmp(type, "PRESSURE") == 0)
		{
			boundary[i].type = PRESSURE_ESPECIFIED;
		}
		else
		{
			eprintf("type in [Boundary %i] is invalid", i + 1); //0.0.2
		}
		
		//Setting
		add_row = boundary[i].rowf > boundary[i].row  ? 1 : 
				  boundary[i].rowf == boundary[i].row ? 0 : -1;
		add_col = boundary[i].colf > boundary[i].col  ? 1 : 
				  boundary[i].colf == boundary[i].col ? 0 : -1;

		drow = abs(boundary[i].rowf - boundary[i].row);
		dcol = abs(boundary[i].colf - boundary[i].col);

		if ( drow != 0 && dcol != 0 && drow != dcol ) 
		{
			eprintf("[Boundary %i] are not vertical, horizontal or diagonal", i + 1);
		}

		nblocks = drow == dcol ? drow : abs(drow - dcol); 

		for(j = 0; j <= nblocks ; j++)
		{
			localIndex = 
				geom[boundary[i].row + add_row*j][boundary[i].col + add_col*j] - 1;
			
			grid[localIndex].boundary = 
				(int*) realloc(grid[localIndex].boundary, 
							   (++grid[localIndex].nBoundary)*sizeof(int));
			grid[localIndex].boundary[grid[localIndex].nBoundary-1] = i;

			switch(boundary[i].side)
			{
				case NORTH:
					if (grid[localIndex].N != ISBONDARY)
					{
						grid[grid[localIndex].N].S = ISBONDARY;
						grid[localIndex].N = ISBONDARY;
					}
					break;
				case SOUTH:
					if (grid[localIndex].S != ISBONDARY)
					{
						grid[grid[localIndex].S].N = ISBONDARY;
						grid[localIndex].S = ISBONDARY;
					}
					break;
				case WEST:
					if (grid[localIndex].W != ISBONDARY)
					{
						grid[grid[localIndex].W].E = ISBONDARY;
						grid[localIndex].W = ISBONDARY;
					}
					break;
				case EAST:
					if (grid[localIndex].E != ISBONDARY)
					{
						grid[grid[localIndex].E].W = ISBONDARY;
						grid[localIndex].E = ISBONDARY;
					}
					break;
					
			}
		}
	}

	iniparser_freedict(ini);

	unsetprogname();
	
	return boundary;
}