/*  testm.c
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

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vmath.h"

/*#include <stdio.h>
#include "fun_fs.h"*/
double expf__ (double x);
main ()
{
  vector a, b, m, tetravec[4] /*,c,r */ ;
  double res;
  double rr, r;
  int i;
  float x;
/*printf("sqrt(2.)=%g\n",sqrt(2.));
printf("input vector a\n");
scanf("%f",&x);
a.x=x;
scanf("%f",&x);
a.y=x;
scanf("%f",&x);
a.z=x;
printf("input vector b\n");
scanf("%f",&x);
b.x=x;
scanf("%f",&x);
b.y=x;
scanf("%f",&x);
b.z=x;
printf("Rc: ");
scanf("%f",&x);
r=x;
/*printf("input vector c\n");
scanf("%f",&x);
c.x=x;
scanf("%f",&x);
c.y=x;
scanf("%f",&x);
c.z=x;
r=TriangCircum(a,b,c);*/
/*rr=sqrt(VecAbs2(VecIneq(a, b)));
rr=r/rr;
m=ProdScal(0.5,VecSum(a,b));
a=VecSum(m,ProdScal(rr,VecIneq(a,m)));
b=VecSum(m,ProdScal(rr,VecIneq(b,m)));
printf("result a is: %g %g %g\n",a.x,a.y,a.z);
printf("result b is: %g %g %g\n",b.x,b.y,b.z);
if(sqrt(VecAbs2(VecIneq(a,b)))>r)printf("idiotozm\n");
{
double start,sstep;
int times;
printf("start,sstep : ");
scanf("%f",&x);
start=x;
scanf("%f",&x);
sstep=x;
printf("times = ");scanf("%d",&times);
printf("position=%g\n",FindLocalMin(start,sstep,times,expf__,(void*)0)) ;
}
{
int DiagMatrix(double*mat,int n);
void LoadXY2Matrix(double *mat,int n,double x,double y);
void FillMatrix(double *mat,int n);
double GetYfm(double*mat,int n,double x);
void ClearMatrix(double*mat,int n);
int n,points,i;
double *mat,x,y;
puts("matrix test");
puts("Hight of matrix -? (i.e. elements of linear equation)");
scanf("%d",&n);
mat=InitMatrix(n);
puts("number of points");
scanf("%d",&points);
for(i=0;i<points;i++)
{
printf("X,Y (%d): ",i+1);
scanf("%lf %lf",&x,&y);
LoadXY2Matrix(mat,n,x,y);
}
FillMatrix(mat,n);
if(DiagMatrix(mat,n))printf("BAD matrix\n");
for(i=0;i<n;i++)printf("%lg * X^%d %c ",mat[i],n-i-1,i<(n-1)?'+':'\n');
}*/
  for (i = 0; i < 4; i++)
    {
      printf ("input vector %d\n", i);
      scanf ("%lf", &a.x);
      scanf ("%lf", &a.y);
      scanf ("%lf", &a.z);
      tetravec[i] = a;
    }
  printf ("input vector dot \n");
  scanf ("%lf", &a.x);
  scanf ("%lf", &a.y);
  scanf ("%lf", &a.z);
  printf ("result is %d\n", InPiramide (tetravec, a));
/*for(i=0;i<4;i++)
{
printf("vec[%d]= %lg %lg %lg\n",tetravec[i].x,tetravec[i].y,tetravec[i].z);
}*/
  return 0;
}


double
expf__ (double x)
{
  return x * x + 6. * x;
}
