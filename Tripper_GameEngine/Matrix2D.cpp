#include "Matrix2D.h"
#define PI (3.141592653589793)





/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for ( j = 0; j < 3; j++) {
			if (i == j) {
				pResult->m[i][j] = 1;

			}
			else {
				pResult->m[i][j] = 0;
			}
			
		}
	}
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	Matrix2DIdentity(pResult);

	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			pResult->m[i][j] = pMtx->m[j][i];

		}
	}


}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D temp;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp.m[i][j] = 0;
		}
	}
	
	float sum = 0;
	for (int i = 0; i< 3; i++) {

		for (int j = 0; j < 3; j++) {

			for (int k = 0; k<3; k++) {
				sum = sum + pMtx0->m[i][k] * pMtx1->m[k][j];

			}
			temp.m[i][j] = sum;
			sum = 0;

		}
	}

	//Copying it into result matrix
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			
			pMtx1->m[i][j] = temp.m[i][j];
			pResult->m[i][j] = temp.m[i][j];
			
			
		}
	}

	
	
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);

	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;

}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	Angle = (Angle * PI) / 180;

	Matrix2DRotRad(pResult, Angle);
	
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	
	Matrix2DIdentity(pResult);

	pResult->m[0][0] = cos(Angle);
	pResult->m[0][1] = -sin(Angle);
	pResult->m[1][0] = sin(Angle);
	pResult->m[1][1] = cos(Angle);

}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	float finalMat[3];
	float vector[] = { pVec->x, pVec->y, 1 };

	for (int i = 0; i < 3; i++) {
		
			finalMat[i] = 0;
		
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			
			finalMat[i] +=  pMtx->m[i][j] * vector[j];
			
		}
		
	}
	pVec->x = finalMat[0];
	pVec->y = finalMat[1];
	

}

// ---------------------------------------------------------------------------
