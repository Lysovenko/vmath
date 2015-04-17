/*  matr.c
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

#include <string.h>
#include <stdlib.h>
#include "vmath.h"
int
DiagMatrix (double *mat, int n)
{
  int N = n + 1;
  int i, j, k;
  double im;
  for (i = 0; i < n; i++)
    {
      if (mat[i * N + i] == 0.)
	for (j = i + 1; j < n; j++)
	  {
	    if (mat[j * N + i] == 0. && j == (n - 1))
	      return 1;
	    if (mat[j * N + i] != 0.)
	      {
		j = n;
		for (k = i; k < N; k++)
		  {
		    im = mat[j * N + k];
		    mat[j * N + k] = mat[i * N + k];
		    mat[i * N + k] = im;
		  }
	      }
	  }
      for (j = 0; j < n; j++)
	if (i != j && mat[j * N + i] != 0.)
	  {
	    im = mat[j * N + i] / mat[i * N + i];
	    for (k = i + 1; k < N; k++)
	      mat[j * N + k] -= mat[i * N + k] * im;	/*Not quite clear */
	  }
    }
  for (i = 0; i < n; i++)
    mat[i] = mat[i * N + n] / mat[i * N + i];
  return 0;

}

void
LoadXY2Matrix (double *mat, int n, double x, double y)
{
  int i, N, nm1;
  double ax;
  N = n + 1;
  nm1 = (n - 1) * N;
  for (i = n - 1, ax = 1.; i >= 0; i--, ax *= x)
    {
      mat[nm1 + i] += ax;
      mat[i * N + n] += ax * y;
    }
  for (i = n - 2; i >= 0; i--, ax *= x)
    mat[i * N] += ax;
}

void
LoadXYs2Matrix (double *mat, int n, double x, double y, double sig2)
{
  int i, N, nm1;
  double ax;
  N = n + 1;
  nm1 = (n - 1) * N;
  for (i = n - 1, ax = 1.; i >= 0; i--, ax *= x)
    {
      mat[nm1 + i] += ax / sig2;
      mat[i * N + n] += ax * y / sig2;
    }
  for (i = n - 2; i >= 0; i--, ax *= x)
    mat[i * N] += ax / sig2;
}

void
FillMatrix (double *mat, int n)
{
  int i, j, nm1n, nm1, N;
  double el;
  N = n + 1;
  nm1 = n - 1;
  nm1n = N * nm1;
  for (j = n - 2; j >= 0; j--)
    {
      el = mat[nm1n + j];
      for (i = n - 2; i >= j; i--)
	mat[i * N + j + nm1 - i] = el;
    }
  for (i = n - 2; i > 0; i--)
    {
      el = mat[i * N];
      for (j = 1; j <= i; j++)
	mat[(i - j) * N + j] = el;
    }
}

double
GetYfm (double *mat, int n, double x)
{
  double xe, y;
  int i;
  for (i = n - 1, xe = 1., y = 0.; i >= 0; i--, xe *= x)
    y += mat[i] * xe;
  return y;
}

void
ClearMatrix (double *mat, int n)
{
  memset ((void *) mat, 0, n * (n + 1) * sizeof (double));
}

double *
InitMatrix (int n)
{
  double *res;
  res = calloc (n * (n + 1), sizeof (double));
  return res;
}
