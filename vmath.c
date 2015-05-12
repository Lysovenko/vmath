/*  vmath.c
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

#include <math.h>
#include <string.h>
#include "vmath.h"


vector
CrossProd (vector a, vector b)
{
  vector x;
  x.x = a.y * b.z - b.y * a.z;
  x.y = a.z * b.x - a.x * b.z;
  x.z = a.x * b.y - a.y * b.x;
  return x;
}

double
DotProd (vector a, vector b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double
VecAbs2 (vector a)
{
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

vector
ProdScal (double i, vector a)
{
  vector r;
  r.x = a.x * i;
  r.y = a.y * i;
  r.z = a.z * i;
  return r;
}

vector
VecIneq (vector a, vector b)
{
  vector x;
  x.x = a.x - b.x;
  x.y = a.y - b.y;
  x.z = a.z - b.z;
  return x;
}

vector
VecSum (vector a, vector b)
{
  vector x;
  x.x = a.x + b.x;
  x.y = a.y + b.y;
  x.z = a.z + b.z;
  return x;
}

int
IsVecZerro (vector a)
{
  if (a.x == 0. && a.y == 0. && a.z == 0.)
    return 1;
  else
    return 0;
}

vector
TriangCircum (vector a, vector b, vector c)
{
  vector x;
  double x1, y1, z1, x2, y2, z2, x3, y3, z3, d1, d2, d3, d;
  x1 = b.x - a.x;
  y1 = b.y - a.y;
  z1 = b.z - a.z;
  d1 =
    (b.x * b.x - a.x * a.x + b.y * b.y - a.y * a.y + b.z * b.z -
     a.z * a.z) / 2.;
  x2 = b.x - c.x;
  y2 = b.y - c.y;
  z2 = b.z - c.z;
  d2 =
    (b.x * b.x - c.x * c.x + b.y * b.y - c.y * c.y + b.z * b.z -
     c.z * c.z) / 2.;
  x = CrossProd (VecIneq (b, a), VecIneq (c, a));
  x3 = x.x;
  y3 = x.y;
  z3 = x.z;
  d3 = x.x * a.x + x.y * a.y + x.z * a.z;
  d =
    x1 * y2 * z3 + x2 * y3 * z1 + y1 * z2 * x3 - z1 * y2 * x3 - x2 * y1 * z3 -
    y3 * z2 * x1;
  x.x =
    (d1 * y2 * z3 + d2 * y3 * z1 + y1 * z2 * d3 - z1 * y2 * d3 -
     d2 * y1 * z3 - y3 * z2 * d1) / d;
  x.y =
    (x1 * d2 * z3 + x2 * d3 * z1 + d1 * z2 * x3 - z1 * d2 * x3 -
     x2 * d1 * z3 - d3 * z2 * x1) / d;
  x.z =
    (x1 * y2 * d3 + x2 * y3 * d1 + y1 * d2 * x3 - d1 * y2 * x3 -
     x2 * y1 * d3 - y3 * d2 * x1) / d;
  return x;
}

int
ThruTriang (vector a, vector b, vector c, vector d, vector e)
{
  double i, j, s2;
  vector n, x, s, Vx, Vs;
  n = CrossProd (VecIneq (b, a), VecIneq (c, a));
  if (IsVecZerro (n))
    return 0;
  i = DotProd (VecIneq (a, d), n) / DotProd (VecIneq (e, d), n);
  if (i > 1 || i < 0)
    return 0;
  x = VecSum (ProdScal (i, VecIneq (e, d)), d);
  s = VecIneq (b, a);
  s2 = DotProd (s, s);
  j = DotProd (VecIneq (x, a), s) / s2;
  Vx = VecIneq (x, VecSum (ProdScal (j, s), a));
  j = DotProd (VecIneq (c, a), s) / s2;
  Vs = VecIneq (c, VecSum (ProdScal (j, s), a));
  j = DotProd (Vx, Vs) / DotProd (Vs, Vs);
  if (j < 0. || j > 1.)
    return 0;

  s = VecIneq (c, a);
  s2 = DotProd (s, s);
  j = DotProd (VecIneq (x, a), s) / s2;
  Vx = VecIneq (x, VecSum (ProdScal (j, s), a));
  j = DotProd (VecIneq (b, a), s) / s2;
  Vs = VecIneq (b, VecSum (ProdScal (j, s), a));
  j = DotProd (Vx, Vs) / DotProd (Vs, Vs);
  if (j < 0. || j > 1.)
    return 0;

  s = VecIneq (c, b);
  s2 = DotProd (s, s);
  j = DotProd (VecIneq (x, b), s) / s2;
  Vx = VecIneq (x, VecSum (ProdScal (j, s), b));
  j = DotProd (VecIneq (a, b), s) / s2;
  Vs = VecIneq (a, VecSum (ProdScal (j, s), b));
  j = DotProd (Vx, Vs) / DotProd (Vs, Vs);
  if (j < 0. || j > 1.)
    return 0;
  return 1;
}

/*          */
vector
TriPlane (vector n1, double d1, vector n2, double d2, vector n3, double d3,
	  int *err)
{
  double det;
  vector res = {0,0,0};
  det =
    n1.x * (n2.y * n3.z - n3.y * n2.z) + n2.x * (n3.y * n1.z - n1.y * n3.z) +
    n3.x * (n1.y * n2.z - n2.y * n1.z);
  if (det == 0.)
    {
      *err = 1;
      return res;
    }
  res.x =
    (d1 * (n2.y * n3.z - n3.y * n2.z) + d2 * (n3.y * n1.z - n1.y * n3.z) +
     d3 * (n1.y * n2.z - n2.y * n1.z)) / det;
  res.y =
    (n1.x * (d2 * n3.z - d3 * n2.z) + n2.x * (d3 * n1.z - d1 * n3.z) +
     n3.x * (d1 * n2.z - d2 * n1.z)) / det;
  res.z =
    (n1.x * (n2.y * d3 - n3.y * d2) + n2.x * (n3.y * d1 - n1.y * d3) +
     n3.x * (n1.y * d2 - n2.y * d1)) / det;
  *err = 0;
  return res;
}

vector
TetrCircum (vector a, vector b, vector c, vector d, int *err)
{
  vector n1, n2, n3;
  double d1, d2, d3;
  n1 = VecIneq (a, b);
  n2 = VecIneq (a, c);
  n3 = VecIneq (a, d);
  d1 = DotProd (n1, ProdScal (0.5l, VecSum (a, b)));
  d2 = DotProd (n2, ProdScal (0.5l, VecSum (a, c)));
  d3 = DotProd (n3, ProdScal (0.5l, VecSum (a, d)));
  return TriPlane (n1, d1, n2, d2, n3, d3, err);
}

tensor
InitRotation (double alpha, double beta)
{
  tensor res;
  memset (&res, 0, sizeof (tensor));
  res.Xx = 1.;
  res.Yy = 1.;
  res.Zz = 1.;
  return RotateCoord (alpha, beta, res);
}

tensor
RotateCoord (double alpha, double beta, tensor C)
{
  tensor res;
  double x, y, z, r, cosa, sina;
  cosa = cos (alpha);
  sina = sin (alpha);
  if ((r = sqrt (C.Xy * C.Xy + C.Xz * C.Xz)) != 0)
    {
      y = C.Xy / r;
      z = C.Xz / r;
      res.Xz = (z * cosa + y * sina) * r;
      res.Xy = (y * cosa - z * sina) * r;
    }
  else
    {
      res.Xz = C.Xz;
      res.Xy = C.Xy;
    }
  res.Xx = C.Xx;
  if ((r = sqrt (C.Yy * C.Yy + C.Yz * C.Yz)) != 0)
    {
      y = C.Yy / r;
      z = C.Yz / r;
      res.Yz = (z * cosa + y * sina) * r;
      res.Yy = (y * cosa - z * sina) * r;
    }
  else
    {
      res.Yz = C.Yz;
      res.Yy = C.Yy;
    }
  res.Yx = C.Yx;
  if ((r = sqrt (C.Zy * C.Zy + C.Zz * C.Zz)) != 0)
    {
      y = C.Zy / r;
      z = C.Zz / r;
      res.Zz = (z * cosa + y * sina) * r;
      res.Zy = (y * cosa - z * sina) * r;
    }
  else
    {
      res.Zz = C.Zz;
      res.Zy = C.Zy;
    }
  res.Zx = C.Zx;
  cosa = cos (beta);
  sina = sin (beta);

  if ((r = sqrt (res.Xx * res.Xx + res.Xz * res.Xz)) != 0)
    {
      x = res.Xx / r;
      z = res.Xz / r;
      res.Xz = (z * cosa + x * sina) * r;
      res.Xx = (x * cosa - z * sina) * r;
    }
  if ((r = sqrt (res.Yx * res.Yx + res.Yz * res.Yz)) != 0)
    {
      x = res.Yx / r;
      z = res.Yz / r;
      res.Yz = (z * cosa + x * sina) * r;
      res.Yx = (x * cosa - z * sina) * r;
    }
  if ((r = sqrt (res.Zx * res.Zx + res.Zz * res.Zz)) != 0)
    {
      x = res.Zx / r;
      z = res.Zz / r;
      res.Zz = (z * cosa + x * sina) * r;
      res.Zx = (x * cosa - z * sina) * r;
    }
  res.Zx = res.Xy * res.Yz - res.Xz * res.Yy;
  res.Zy = res.Xz * res.Yx - res.Xx * res.Yz;
  res.Zz = res.Xx * res.Yy - res.Xy * res.Yx;

  res.Xx = res.Yy * res.Zz - res.Yz * res.Zy;
  res.Xy = res.Yz * res.Zx - res.Yx * res.Zz;
  res.Xz = res.Yx * res.Zy - res.Yy * res.Zx;

  res.Yx = res.Zy * res.Xz - res.Zz * res.Xy;
  res.Yy = res.Zz * res.Xx - res.Zx * res.Xz;
  res.Yz = res.Zx * res.Xy - res.Zy * res.Xx;

  r = sqrt (res.Zx * res.Zx + res.Zy * res.Zy + res.Zz * res.Zz);
  res.Zx /= r;
  res.Zy /= r;
  res.Zz /= r;

  r = sqrt (res.Xx * res.Xx + res.Xy * res.Xy + res.Xz * res.Xz);
  res.Xx /= r;
  res.Xy /= r;
  res.Xz /= r;

  r = sqrt (res.Yx * res.Yx + res.Yy * res.Yy + res.Yz * res.Yz);
  res.Yx /= r;
  res.Yy /= r;
  res.Yz /= r;

  return res;
}

vector
NewVector (vector v, tensor c)
{
  vector r;
  r.x = v.x * c.Xx + v.y * c.Yx + v.z * c.Zx;
  r.y = v.x * c.Xy + v.y * c.Yy + v.z * c.Zy;
  r.z = v.x * c.Xz + v.y * c.Yz + v.z * c.Zz;
  return r;
}
