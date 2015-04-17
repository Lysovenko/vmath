/*  addition.c
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

#include "vmath.h"

double
FindLocalMin (double start, double sstep, int times,
	      double (*ExplFunc) (double, void *), void *data)
{
  int time = 0;
  double sval, pos, step, nval;
  pos = start;
  step = sstep;
  sval = ExplFunc (pos, data);
  while (time < times)
    {
      nval = ExplFunc (pos + step, data);
      if (nval < sval)
	{
	  sval = nval;
	  pos += step;
	}
      else
	{
	  step /= -2.;
	  time++;
	}
    }
  return pos;
}

long double
IntegralDifSp (double *vX, double *vY, int N)
{
  long double res;
  int i;
  if (N < 2)
    return 0.L;
  res = 0.L;
  for (i = 1; i < N; i++)
    res += (vY[i] + vY[i - 1]) * (vX[i] - vX[i - 1]) / 2.L;
  return res;
}
