/*
 *  MatrixMath.h Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 *  Modified to work with Arduino 1.0/1.5 by randomvibe & robtillaart
 *  Made into a real library on GitHub by Vasilis Georgitzikis (tzikis)
 *  so that it's easy to use and install (March 2015)
 */

#ifndef MatrixMath_h
#define MatrixMath_h

#define mtx_type	double

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class MatrixMath
{
public:
	//MatrixMath();
	void Print(mtx_type* A, int m, int n, String label);
	void Copy(mtx_type* A, int n, int m, mtx_type* B);
	void Multiply(mtx_type* A, mtx_type* B, int m, int p, int n, mtx_type* C);
	void Add(mtx_type* A, mtx_type* B, int m, int n, mtx_type* C);
	void Subtract(mtx_type* A, mtx_type* B, int m, int n, mtx_type* C);
	void Transpose(mtx_type* A, int m, int n, mtx_type* C);
	void Scale(mtx_type* A, int m, int n, mtx_type k);
	int Invert(mtx_type* A, int n);
};

extern MatrixMath Matrix;
#endif
