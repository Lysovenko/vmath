/*  vmath.h
 *
 * Copyright (C) 2007-2015 Serhii Lysovenko
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __VMATH_H__
#define __VMATH_H__

typedef struct vectors
{
  double x;
  double y;
  double z;
}
vector;
typedef struct
{
  double Xx, Xy, Xz, Yx, Yy, Yz, Zx, Zy, Zz;
} tensor;
vector CrossProd (vector a, vector b);	/* a x b */
double VecAbs2 (vector a);
double DotProd (vector a, vector b);
vector VecIneq (vector a, vector b);	/* a-b */
vector VecSum (vector a, vector b);
vector TriangCircum (vector a, vector b, vector c);
vector ProdScal (double i, vector a);
vector TetrCircum (vector a, vector b, vector c, vector d, int *err);
int ThruTriang (vector a, vector b, vector c, vector d, vector e);
vector TriPlane (vector n1, double d1, vector n2, double d2, vector n3,
		 double d3, int *err);
double FindLocalMin (double start, double sstep, int times, double (*ExplFunc) (double, void *), void *data);
long double IntegralDifSp (double *vX, double *vY, int N);
int DiagMatrix (double *mat, int n);
void LoadXY2Matrix (double *mat, int n, double x, double y);
void LoadXYs2Matrix (double *mat, int n, double x, double y, double sig2);
void FillMatrix (double *mat, int n);
double GetYfm (double *mat, int n, double x);
void ClearMatrix (double *mat, int n);
double *InitMatrix (int n);
tensor InitRotation (double alpha, double beta);
tensor RotateCoord (double alpha, double beta, tensor C);
vector NewVector (vector v, tensor c);
int InPiramide (vector * tetravec, vector dot);
#endif
