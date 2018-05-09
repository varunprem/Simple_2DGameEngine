#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

 

void  matrix_print( Matrix m, int num_rows, int num_columns ) {
    int i, j;
    for ( i=0; i<num_rows; ++i ) {
        for ( j=0; j<num_columns; ++j ) {
            printf( "%4i ", m[i][j] );
        }
        printf( "\n" );
    }
}

Matrix matrix_create( int num_rows, int num_columns ){
	Matrix m;
	int i;
	
    m = (int**)malloc(num_rows * sizeof(int*));
	
	for(i=0;i<num_rows;i++)
		m[i] = (int*) malloc(num_columns * sizeof(int));
		
	
	return m;
}

void matrix_add( Matrix m1, Matrix m2, Matrix result, int num_rows, int num_columns ){
	int i;
	int j;
	
	for(i=0;i<num_rows;i++){
		for(j=0;j<num_columns;j++){
			
			result[i][j] = m1[i][j] + m2[i][j];
		}
		
	}	
	
}

Matrix matrix_transpose( Matrix m, int num_rows, int num_columns ){
	int i,j;
    Matrix result;
    result = matrix_create(num_columns,num_rows);
	
    for(i=0; i<num_rows;i++)
    {
        for(j = 0; j<num_columns;j++)
        {
            result[j][i] = m[i][j];
        }
    }
    return result;
}


void matrix_delete( Matrix m, int num_rows ){
	
	int i;
 
	
	for(i=0;i<num_rows;i++)
		free(m[i]);
	
	free(m);
	
	
}

void  matrix_delete_row( Matrix m, int r, int num_rows ){
	
	
	int totalHeight = num_rows;
	totalHeight--;
	free(m[r]);
	
	while(r < totalHeight)
	{
		m[r] = m[r+1];
		r++;
	}
	
}
void   matrix_delete_column( Matrix m, int c, int num_rows, int num_columns ){
		
	int i;
	int deleteColumn;
	int totalWidth;
	
	totalWidth = num_columns;
	
	
	deleteColumn = c;
	
	totalWidth = totalWidth - 1;
	
	for(i=0;i<num_rows;i++){
		c = deleteColumn;
			while(c != num_columns -1){
				*(*(m + i) + c) = *(*(m + i) + (c+1));
				c++;
			}
		//*(m+i) =  realloc( *(m+i),sizeof(int) * totalWidth);			
	}
	
	
}

