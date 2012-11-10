// gist_ball.cc							-*- c++ -*-
// Copyright (c) 1995, David A. White <dwhite@vision.ucsd.edu>
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_ball.cc,v 1.12 2000/03/15 00:24:50 mashah Exp $

#include "gist_compat.h"

#include <memory.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "gist_defs.h"
#include "gist_ball.h"

#ifndef NDEBUG

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#define WARN_MSG(str) cerr << str
#else
#define WARN_MSG(str)
#endif

inline uint4
dalign(uint4 len)
{
    return((len + sizeof(double) - 1) & ~(sizeof(double) - 1));
}

inline void*
pdalign(void* p)
{
    return((void*) dalign((uint4) p));
}

static double
CalcDistSqrd(uint4 num_dim, const double* v1, const double* v2)
{
    assert(num_dim > 1);
    assert(v1 != NULL && v2 != NULL);
    double dist;

    uint4 jj;
    double diff;
    diff = v1[0] - v2[0];
    dist = diff * diff;
    for ( jj = 1; jj < num_dim; jj++ )
    {
	diff = v1[jj] - v2[jj];
	dist += diff * diff;
    }
    return dist;
}

//
// This calculates a weighted quadratic distance between vectors
//
static double
CalcDistSqrd(uint4 num_dim, const double* v1, const double* v2,
	     const double* ww)
{
    if (ww == NULL) return CalcDistSqrd(num_dim, v1, v2);
    assert(num_dim > 1);
    assert(v1 != NULL && v2 != NULL);

    uint4 jj;
    double dist, diff;

    diff = v1[0] - v2[0];
    dist = ww[0] * diff * diff;
    for ( jj = 1; jj < num_dim; jj++ )
    {
	diff = v1[jj] - v2[jj];
	dist += ww[jj] * diff * diff;
    }
    return dist;
}

static double
CalcDist(uint4 num_dim, const double* v1, const double* v2)
{
    return sqrt(CalcDistSqrd(num_dim, v1, v2));
}

static double
CalcDist(uint4 num_dim, const double* v1, const double* v2,
	 const double* ww)
{
    return sqrt(CalcDistSqrd(num_dim, v1, v2, ww));
}

//
// This code uses "Numerical Recipes in C" code to do single precision SVD
// Other packages offering SVD, such as fortran packages, would also work,
// but this code will require modifications.  For example, the
// vectors and arrays use with numerical recipies are 1 relative
// instead of 0 relative.
//

inline double
nr_pythag(double a, double b)
{
    a = fabs(a);
    b = fabs(b);
    double c;

    if (a > b) {   // "&& a > 0.0"
	c = b / a;
	return(a * sqrt(1.0 + c * c));
    }
    if (b > 0.0) { // "&& b >= a"
	c = a / b;
	return(b * sqrt(1.0 + c * c));
    }
    return(0.0);
}

inline double
nr_max(double a, double b)
{
    return((a > b) ? a : b);
}

inline double
nr_sign(double a, double b)
{
    return((b) >= 0.0 ? fabs(a) : -fabs(a));
}

inline double*
_vector(int l, int h)
{
    return((new double[(h)-(l)+1]) - l);
}

inline void
free_vector(double* p, int l, int h)
{
    delete [] ((p) + (l));
}

static void
svdcmp(double** a, int m, int n, double* w, double** v)
{
	int flag,i,its,j,jj,k,l=-1,nm=-1;
	double c,f,h,s,x,y,z;
	double anorm=0.0,g=0.0,scale=0.0;
	double *rv1;

	assert(m >= n);
	rv1=_vector(1,n);
	for (i=1;i<=n;i++) {
		l=i+1;
		rv1[i]=scale*g;
		g=s=scale=0.0;
		if (i <= m) {
			for (k=i;k<=m;k++) scale += fabs(a[k][i]);
			if (scale) {
				for (k=i;k<=m;k++) {
					a[k][i] /= scale;
					s += a[k][i]*a[k][i];
				}
				f=a[i][i];
				g = -nr_sign(sqrt(s),f);
				h=f*g-s;
				a[i][i]=f-g;
				if (i != n) {
					for (j=l;j<=n;j++) {
						for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
						f=s/h;
						for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
					}
				}
				for (k=i;k<=m;k++) a[k][i] *= scale;
			}
		}
		w[i]=scale*g;
		g=s=scale=0.0;
		if (i <= m && i != n) {
			for (k=l;k<=n;k++) scale += fabs(a[i][k]);
			if (scale) {
				for (k=l;k<=n;k++) {
					a[i][k] /= scale;
					s += a[i][k]*a[i][k];
				}
				f=a[i][l];
				g = -nr_sign(sqrt(s),f);
				h=f*g-s;
				a[i][l]=f-g;
				for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
				if (i != m) {
					for (j=l;j<=m;j++) {
						for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
						for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
					}
				}
				for (k=l;k<=n;k++) a[i][k] *= scale;
			}
		}
		anorm=nr_max(anorm,(fabs(w[i])+fabs(rv1[i])));
	}
	for (i=n;i>=1;i--) {
		if (i < n) {
			if (g) {
				for (j=l;j<=n;j++)
					v[j][i]=(a[i][j]/a[i][l])/g;
				for (j=l;j<=n;j++) {
					for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
					for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
				}
			}
			for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
		}
		v[i][i]=1.0;
		g=rv1[i];
		l=i;
	}
	for (i=n;i>=1;i--) {
		l=i+1;
		g=w[i];
		if (i < n)
			for (j=l;j<=n;j++) a[i][j]=0.0;
		if (g) {
			g=1.0/g;
			if (i != n) {
				for (j=l;j<=n;j++) {
					for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
					f=(s/a[i][i])*g;
					for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
				}
			}
			for (j=i;j<=m;j++) a[j][i] *= g;
		} else {
			for (j=i;j<=m;j++) a[j][i]=0.0;
		}
		++a[i][i];
	}
	for (k=n;k>=1;k--) {
		for (its=1;its<=30;its++) {
			flag=1;
			for (l=k;l>=1;l--) {
				nm=l-1;
				if (fabs(rv1[l])+anorm == anorm) {
					flag=0;
					break;
				}
				if (fabs(w[nm])+anorm == anorm) break;
			}
			if (flag) {
				c=0.0;
				s=1.0;
				for (i=l;i<=k;i++) {
					f=s*rv1[i];
					if (fabs(f)+anorm != anorm) {
						g=w[i];
						h=nr_pythag(f,g);
						w[i]=h;
						h=1.0/h;
						c=g*h;
						s=(-f*h);
						for (j=1;j<=m;j++) {
							y=a[j][nm];
							z=a[j][i];
							a[j][nm]=y*c+z*s;
							a[j][i]=z*c-y*s;
						}
					}
				}
			}
			z=w[k];
			if (l == k) {
				if (z < 0.0) {
					w[k] = -z;
					for (j=1;j<=n;j++) v[j][k]=(-v[j][k]);
				}
				break;
			}
			assert(its != 30);
			x=w[l];
			nm=k-1;
			y=w[nm];
			g=rv1[nm];
			h=rv1[k];
			f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
			g=nr_pythag(f,1.0);
			f=((x-z)*(x+z)+h*((y/(f+nr_sign(g,f)))-h))/x;
			c=s=1.0;
			for (j=l;j<=nm;j++) {
				i=j+1;
				g=rv1[i];
				y=w[i];
				h=s*g;
				g=c*g;
				z=nr_pythag(f,h);
				rv1[j]=z;
				c=f/z;
				s=h/z;
				f=x*c+g*s;
				g=g*c-x*s;
				h=y*s;
				y=y*c;
				for (jj=1;jj<=n;jj++) {
					x=v[jj][j];
					z=v[jj][i];
					v[jj][j]=x*c+z*s;
					v[jj][i]=z*c-x*s;
				}
				z=nr_pythag(f,h);
				w[j]=z;
				if (z) {
					z=1.0/z;
					c=f*z;
					s=h*z;
				}
				f=(c*g)+(s*y);
				x=(c*y)-(s*g);
				for (jj=1;jj<=m;jj++) {
					y=a[jj][j];
					z=a[jj][i];
					a[jj][j]=y*c+z*s;
					a[jj][i]=z*c-y*s;
				}
			}
			rv1[l]=0.0;
			rv1[k]=f;
			w[k]=x;
		}
	}
	free_vector(rv1,1,n);
}

static void
svbksb(double** u, double w[], double** v, int m, int n, double b[], double x[])
{
	int jj,j,i;
	double s,*tmp;

	tmp=_vector(1,n);
	for (j=1;j<=n;j++) {
		s=0.0;
		if (w[j]) {
			for (i=1;i<=m;i++) s += u[i][j]*b[i];
			s /= w[j];
		}
		tmp[j]=s;
	}
	for (j=1;j<=n;j++) {
		s=0.0;
		for (jj=1;jj<=n;jj++) s += v[j][jj]*tmp[jj];
		x[j]=s;
	}
	free_vector(tmp,1,n);
}

// This is the percentage error allowed so that a ball is still
// considered enclosed.  The output of the algorithm could be off
// by this much, but it probably won't happen.
const double RAD_SLACK = 0.015;

// This is the percentage difference allowed between points that
// are supposed to be equidistant.  Singularities might cause this error.
// This is only used during debugging to check that calculations are OK...
const double BOUND_RAD_ERR = 0.01;

inline double**
GrabMatrix(double**& ptr_curr, double*& fl_curr,
	   uint4 start1, uint4 end1,
	   uint4 start2, uint4 end2)
{
    double** mat = ptr_curr - start1;
    ptr_curr += end1 - start1 + 1;
    for (uint4 ii=start1; ii<=end1; ii++)
    {
	mat[ii] = fl_curr - start2;
	fl_curr += end2 - start2 + 1;
    }
    return (double**)mat;
}

inline double*
GrabVector(double*& fl_curr, uint4 start1, uint4 end1)
{
    double* vec = fl_curr - start1;
    fl_curr += end1 - start1 + 1;
    return vec;
}

inline uint4*
GrabIntVector(uint4*& i_curr, uint4 start1, uint4 end1)
{
    uint4* vec = i_curr - start1;
    i_curr += end1 - start1 + 1;
    return vec;
}

inline const double**
GrabPtrVector(double**& ptr_curr, uint4 start1, uint4 end1)
{
    const double** vec = (const double**)ptr_curr - start1;
    ptr_curr += end1 - start1 + 1;
    return vec;
}

//
// This routine determines the center of a ball given points
// on it, and weights determining it's ellipsoid shape
//
// This is done as follows:
// 1. Create a set of num_points - 1 linear equations to solve
// 2. Solve, and use to calculate the center point and radius
//
// The work memory required is calculated below...
// The work_size variable is provided for debugging purposes...
//
// NOTE: All points input to this routine must be on the boundary.  If not,
// the results will not be correct.
//
static void
BallFromBoundaryPoints(uint4 num_dim, uint4 num_points,
		       const double*const* centers, double* out_center,
		       double& radius_sqrd, const double* weights=NULL,
		       void* work=NULL, uint4 work_size=0)
{
    assert(num_dim >= num_points-1);
    uint4 ii, jj, kk;

    // Handle the easy cases explicitly...
    if (num_points <= 2)
	switch (num_points)
	{
	  case 0:
	    // Ball centered at origin with zero radius
	    for (ii=0; ii<num_dim; ii++)
		out_center[ii] = 0.0;
	    radius_sqrd = 0.0;
	    return;

	  case 1:
	    // Return the ball centered at that point of minimum size
	    memcpy((void*)out_center, (const void*)centers[0],
		   num_dim*sizeof(double));
	    radius_sqrd = 16*MINDOUBLE;
	    return;

	  case 2: {
	      double dist = 0.0;
	      for (ii=0; ii<num_dim; ii++)
	      {
		  double diff = centers[0][ii] - centers[1][ii];
		  dist += diff*diff;
		  out_center[ii] = (centers[0][ii] + centers[1][ii])/2.0;
	      }
	      radius_sqrd = dist/4.0;
	      return;
	  }
	}

    // Allocate all memory needed
    uint4 red_dim = num_points-1;
    unsigned char* work_mem;
    uint4 ptr_size = dalign(sizeof(double*)*(3 * red_dim));
    uint4 fl_size = sizeof(double)*
	(3*red_dim + (2*red_dim)*red_dim + red_dim*num_dim);
    uint4 mem_size = ptr_size + fl_size;

    assert((work==NULL && work_size==0) || (work!=NULL && work_size>0));
    bool need_alloc = (work==NULL || work_size < mem_size);
    if (need_alloc)
	work_mem = (unsigned char*) new double[dalign(mem_size)/sizeof(double)];
    else
	work_mem = (unsigned char*)work;

    double** ptr_mem = (double**)work_mem;
    double* fl_mem = (double*)(work_mem + ptr_size);

    double* b_vec = GrabVector(fl_mem, 1, red_dim);
    double* ww = GrabVector(fl_mem, 1, red_dim);
    double* x_vec = GrabVector(fl_mem, 1, red_dim);
    double** centers2 =
	GrabMatrix(ptr_mem, fl_mem, 1, red_dim, 1, num_dim);
    double** u_mat = GrabMatrix(ptr_mem, fl_mem, 1, red_dim, 1, red_dim);
    double** v_mat = GrabMatrix(ptr_mem, fl_mem, 1, red_dim, 1, red_dim);
    assert(pdalign(work_mem + ptr_size)==pdalign(ptr_mem));
    assert(pdalign(work_mem + mem_size)==pdalign(fl_mem));

    // Make center2 and b_vec: only mess with weights if needed
    if (weights!=NULL)
	for (ii=1; ii<=red_dim; ii++)
	{
	    double total = 0;
	    for (jj=0; jj<num_dim; jj++)
	    {
		double diff = (centers[ii][jj] - centers[0][jj])*weights[jj];
		centers2[ii][jj+1] = diff;
		total += diff*diff;
	    }
	    b_vec[ii] = total/2.0;
	}
    else
	for (ii=1; ii<=red_dim; ii++)
	{
	    double total = 0;
	    for (jj=0; jj<num_dim; jj++)
	    {
		double diff = centers[ii][jj] - centers[0][jj];
		centers2[ii][jj+1] = diff;
		total += diff*diff;
	    }
	    b_vec[ii] = total/2.0;
	}

    // Fill in u_mat using centers2
    // It is symmetric, so only do half the work...
    for (jj=1; jj<=red_dim; jj++)
	for (kk=1; kk<=jj; kk++)
	{
	    double total = 0;
	    for (ii=1; ii<=num_dim; ii++)
		total += centers2[jj][ii] * centers2[kk][ii];
	    u_mat[jj][kk] = total;
	    u_mat[kk][jj] = total;
	}

    // OK, we now have a system of linear equations, so solve it
    svdcmp(u_mat, red_dim, red_dim, ww, v_mat); // Augmented u_mat...
    double wmax = 0.0;
    for (jj=1; jj<=red_dim; jj++)
	if (ww[jj] > wmax)
	    wmax = ww[jj];
    double wmin = wmax*5.0e-8;
    for (jj=1; jj<=red_dim; jj++)
	if (ww[jj] < wmin)
	{
	    ww[jj] = 0.0;  // Try to "fix" the singularity
	    WARN_MSG("Singularity in matrix, ignoring: try increasing RAD_SLACK.");
	}

    svbksb(u_mat, ww, v_mat, red_dim, red_dim, b_vec, x_vec);

    // OK, now x_vec holds the center in the reduced dimensionality
    // so we just need to project it back...
    if (weights!=NULL)
	for (ii=0; ii<num_dim; ii++)
	{
	    double total = 0;
	    for (jj=1; jj<=red_dim; jj++)
		total += x_vec[jj] * centers2[jj][ii+1];
	    out_center[ii] = centers[0][ii] + total/weights[ii];
	}
    else
	for (ii=0; ii<num_dim; ii++)
	{
	    double total = centers[0][ii];
	    for (jj=1; jj<=red_dim; jj++)
		total += x_vec[jj] * centers2[jj][ii+1];
	    out_center[ii] = total;
	}

    double max_dist = 0;
    for (ii=0; ii<num_points; ii++)
    {
	double dist = CalcDistSqrd(num_dim, out_center, centers[ii], weights);
	assert(max_dist==0 || fabs(max_dist-dist) <= 2.0*BOUND_RAD_ERR*dist);
	if (dist > max_dist) max_dist = dist;
    }
    radius_sqrd = max_dist;

    if (need_alloc) delete[] work_mem;
}

//
// NOTE: All balls input to this routine must be on the boundary.  If not,
// the results will not be correct.  (ie. one ball encloses other balls)
// It is detected in the 2 ball case, but not handled in general.
//
static void
BallFromBoundaryBalls(uint4 num_dim, uint4 num_points,
		      const double*const* centers, const double* radii,
		      double* out_center, double& radius,
		      const double* weights=NULL,
		      void* work=NULL, uint4 work_size=0)
{
    assert(num_dim >= num_points-1);
    uint4 ii, jj, kk;

    // Handle the easy cases...
    if (num_points <= 2)
	switch (num_points)
	{
	  case 0:
	    // Ball centered at origin with zero radius
	    for (ii=0; ii<num_dim; ii++)
		out_center[ii] = 0.0;
	    radius = 0.0;
	    return;

	  case 1:
	    // Return the ball centered at that point of minimum size
	    memcpy((void*)out_center, (const void*)centers[0],
		   num_dim*sizeof(double));
	    radius = radii[0];
	    return;

	  case 2: {
	      double dist = CalcDist(num_dim, centers[0], centers[1], weights);

	      // Handle rare cases where one boundary covers the other side
	      uint4 low_rad, high_rad;
	      if (radii[0] >= radii[1]) { low_rad = 1; high_rad = 0; }
	      else { low_rad = 0; high_rad = 1; }

	      if (radii[high_rad] > dist + radii[low_rad])
	      {
#if 0
		  WARN_MSG("Weird case: one ball encloses all");
#endif
		  memcpy((void*)out_center, (const void*)centers[0],
			 sizeof(double)*num_dim);
		  radius = radii[high_rad];
	      }

	      double final_dist = (radii[0] + radii[1] + dist)/2.0;

	      // .5 is between centers
	      // 0 is at point1
	      // 1 is at point2
	      // Other values are as expected...
	      double center_ratio;
	      if (dist < MINDOUBLE*4)
	      {
		  center_ratio = 0.5;
		  final_dist += MINDOUBLE*4;
	      }
	      else
		  center_ratio = (dist - radii[0] + radii[1])/(2.0*dist);

	      for (jj=0; jj<num_dim; jj++)
		  out_center[jj] = centers[0][jj] +
		      (centers[1][jj] - centers[0][jj]) * center_ratio;

	      radius = final_dist;
	      return;
	      }
	}

    // Allocate all memory needed
    uint4 red_dim = num_points-1;
    uint4 ptr_size = dalign(sizeof(double*)*(2*red_dim + 2*(red_dim+1)));
    uint4 fl_size = sizeof(double)*
	(5*(red_dim+1) + 2*num_dim +
	 red_dim*num_dim + red_dim*(red_dim+1) +
	 2*(red_dim+1)*(red_dim+1));
    uint4 mem_size = ptr_size + fl_size;
    unsigned char* work_mem;

    assert((work==NULL && work_size==0) || (work!=NULL && work_size>0));
    bool need_alloc = (work==NULL || work_size < mem_size);
    if (need_alloc)
	work_mem = (unsigned char*) new double[dalign(mem_size)/sizeof(double)];
    else
	work_mem = (unsigned char*)work;

    double** ptr_mem = (double**)work_mem;
    double* fl_mem = (double*)(work_mem + ptr_size);

    double* line_vec = GrabVector(fl_mem, 1, red_dim+1);
    double* temp_vec = GrabVector(fl_mem, 1, red_dim+1);
    double* x_vec = GrabVector(fl_mem, 1, red_dim+1);
    double* b_vec = GrabVector(fl_mem, 1, red_dim+1);
    double* ww = GrabVector(fl_mem, 1, red_dim+1);
    double* base_vec = GrabVector(fl_mem, 1, num_dim);
    double* off_vec = GrabVector(fl_mem, 1, num_dim);
    double** centers2 = GrabMatrix(ptr_mem, fl_mem, 1, red_dim, 1, num_dim);
    double** temp_mat = GrabMatrix(ptr_mem, fl_mem, 1, red_dim, 1, red_dim+1);
    double** u_mat = GrabMatrix(ptr_mem, fl_mem, 1, red_dim+1, 1, red_dim+1);
    double** v_mat = GrabMatrix(ptr_mem, fl_mem, 1, red_dim+1, 1, red_dim+1);
    assert(pdalign(work_mem + ptr_size)==pdalign(ptr_mem));
    assert(pdalign(work_mem + mem_size)==pdalign(fl_mem));

    double radius0sqrd = radii[0] * radii[0];

    // Make center2 and b_vec: only mess with weights if needed
    if (weights!=NULL)
	for (ii=1; ii<=red_dim; ii++)
	{
	    double total = radius0sqrd - radii[ii]*radii[ii];
	    for (jj=0; jj<num_dim; jj++)
	    {
		double diff = (centers[ii][jj] - centers[0][jj])*weights[jj];
		centers2[ii][jj+1] = diff;
		total += diff*diff;
	    }
	    temp_vec[ii] = total/2.0;
	}
    else
	for (ii=1; ii<=red_dim; ii++)
	{
	    double total = radius0sqrd - radii[ii]*radii[ii];
	    for (jj=0; jj<num_dim; jj++)
	    {
		double diff = centers[ii][jj] - centers[0][jj];
		centers2[ii][jj+1] = diff;
		total += diff*diff;
	    }
	    temp_vec[ii] = total/2.0;
	}

    // Fill in temp_mat using centers2
    // It is symmetric, so only do half the work...
    for (jj=1; jj<=red_dim; jj++)
	for (kk=1; kk<=jj; kk++)
	{
	    double total = 0;
	    for (ii=1; ii<=num_dim; ii++)
		total += centers2[jj][ii] * centers2[kk][ii];
	    temp_mat[jj][kk] = total;
	    temp_mat[kk][jj] = total;
	}
    for (jj=1; jj<=red_dim; jj++)
	temp_mat[jj][red_dim+1] = radii[0] - radii[jj];

    // To make this solvable by SVD, multiply both sides by
    // the transpose of tempmat
    for (ii=1; ii<=red_dim+1; ii++)
    {
	double total = 0;
	for (kk=1; kk<=red_dim; kk++)
	    total += temp_vec[kk]*temp_mat[kk][ii];
	b_vec[ii] = total;
	for (jj=1; jj<=red_dim+1; jj++)
	{
	    double total = 0;
	    for (kk=1; kk<=red_dim; kk++)
		total += temp_mat[kk][ii]*temp_mat[kk][jj];
	    u_mat[ii][jj] = total;
	}
    }

    // OK, we now have a system of linear equations, so find the
    // solution space (which is one dimensional in this case)
    svdcmp(u_mat, red_dim+1, red_dim+1, ww, v_mat); // Augmented u_mat...
    double wmax = 0.0;
    for (jj=1; jj<=red_dim+1; jj++)
	if (ww[jj] > wmax) wmax = ww[jj];
    double wmin = wmax*5.0e-8;
    bool found_singularity = 0;
    for (jj=1; jj<=red_dim+1; jj++)
	if (ww[jj] < wmin)
	{
	    ww[jj] = 0.0;
	    if (found_singularity)
	    {
		WARN_MSG("Extra singularity: Automatically fixing: Try increasing RAD_SLACK");
		for (ii=1; ii<=red_dim+1; ii++)
		    line_vec[ii] = v_mat[ii][jj]*v_mat[red_dim+1][jj] +
			line_vec[ii]*line_vec[red_dim+1];
	    }
	    else
	    {
		found_singularity = 1;
		for (ii=1; ii<=red_dim+1; ii++)
		    line_vec[ii] = v_mat[ii][jj];
	    }
	}
    assert(found_singularity);  // Must find at least one singularity
    assert(fabs(line_vec[red_dim+1]) > MINDOUBLE*16);

    // Multiply vector so the r is 1 (Assume mult is slower than division)
    double factor = 1/line_vec[red_dim+1];
    for (ii=1; ii<=red_dim; ii++)
	line_vec[ii] *= factor;
    // line_vec[red_dim+1] = 1.0;

    svbksb(u_mat, ww, v_mat, red_dim+1, red_dim+1, b_vec, x_vec);

    // Subtract the line_vec so the r is 0
    for (ii=1; ii<=red_dim; ii++)
	x_vec[ii] -= line_vec[ii] * x_vec[red_dim+1];
    // x_vec[red_dim+1] = 0.0;  // This is ignored also, but should be 0.0

    // Project into full dimensionality
    for (ii=1; ii<=num_dim; ii++)
    {
	double base_total = 0;
	double off_total = 0;
	for (jj=1; jj<=red_dim; jj++)
	{
	    base_total += centers2[jj][ii] * x_vec[jj];
	    off_total += centers2[jj][ii] * line_vec[jj];
	}
	base_vec[ii] = base_total;
	off_vec[ii] = off_total;
    }

    double a_sqrd_sum=0;
    double b_sqrd_sum=0;
    double ab_sum=0;
    for (ii=1; ii<=num_dim; ii++)
    {
	a_sqrd_sum += off_vec[ii] * off_vec[ii];
	b_sqrd_sum += base_vec[ii] * base_vec[ii];
	ab_sum += base_vec[ii] * off_vec[ii];
    }

    double aa = 1 - a_sqrd_sum;
    double bb = -2.0 * (ab_sum + radii[0]);
    double cc = radii[0]*radii[0] - b_sqrd_sum;

    // Quadratic equation
    double sqrt_term = bb*bb - 4.0 * aa * cc;
    assert(sqrt_term >= 0.0);
    double rr;
    assert(aa != 0.0);
    if (aa>0)
	rr = (sqrt(sqrt_term) - bb)/(2.0*aa);
    else
	rr = (-sqrt(sqrt_term) - bb)/(2.0*aa);
    assert(rr>0.0);

    // Reuse x_vec[] for the values of the final center
    if (weights!=NULL)
	for (ii=1; ii<=num_dim; ii++)
	{
	    double weighted = base_vec[ii] + rr * off_vec[ii];
	    out_center[ii-1] = centers[0][ii-1] + weighted/weights[ii-1];
	}
    else
	for (ii=1; ii<=num_dim; ii++)
	    out_center[ii-1] =
		centers[0][ii-1] + base_vec[ii] + rr * off_vec[ii];

    // Double check the solution
    double max_dist = 0;
    for (ii=0; ii<num_points; ii++)
    {
	double dist =
	    radii[ii] + CalcDist(num_dim, out_center, centers[ii], weights);
	assert(fabs(rr - dist) <= BOUND_RAD_ERR*rr);
	if (dist > max_dist)
	    max_dist = dist;
    }
	
    // If the solution is incorrect, then there probably is a ball
    // included that is not on the outside of the bounding ball.
    // Therefore, we could try throwing away a point and redoing
    // the calculations, but I may not need this, so I'll put it off...
    radius = max_dist;
    if (need_alloc) delete[] work_mem;
}


static int
int_comp(const void* p1, const void* p2)
{
    return *((long*)p1) - *((long*)p2);
}

static void
IntSort(uint4* bound_arr, uint4 num_entries)
{
    qsort((void*)bound_arr, num_entries, sizeof(uint4), int_comp);
}

void
EnclosingBall(uint4 num_dim, uint4 num_points,
	      const double*const* centers, const double* radii,
	      double* out_center, double& out_radius,
	      const double* weights, uint4* boundary_arr,
	      uint4 in_boundary_size, uint4* out_boundary_size,
	      void* work, uint4 work_size)
{
    assert(num_points>0);
    assert(num_dim>1);
    assert(centers!=NULL);
    assert(out_center!=NULL);
    assert((out_boundary_size==NULL) || (boundary_arr!=NULL));
    uint4 ii;
    double common_radius = 0;

    // Directly solve the easy cases
    if (num_points <= 2)
    {
	if (radii==NULL)
	{
	    BallFromBoundaryPoints(num_dim, num_points, centers,
				   out_center, out_radius, weights);
	    out_radius = sqrt(out_radius);
	}
	else
	    BallFromBoundaryBalls(num_dim, num_points, centers, radii,
				  out_center, out_radius, weights);
	if (out_boundary_size)
	{
	    *out_boundary_size = 1;
	    boundary_arr[0]=0;
	}
	return;
    }

    // If all the same radius, then just do the point calculation
    // and add on the extra radius at the end...
    if (radii!=NULL)
    {
	for (ii=1; ii<num_points; ii++)
	    if (radii[ii]!=radii[0])
		break;
	if (ii==num_points)
	{
	    common_radius = radii[0];
	    radii = NULL;
	}
    }

    // Maximum boundary points and level of recursion
    uint4 max_level = num_points > num_dim+1 ? num_dim+1: num_points;

    uint4 int_size = dalign(sizeof(uint4)*(2*num_points + 2*max_level));
    uint4 ptr_size = dalign(sizeof(double*)*max_level);
    uint4 fl_size = sizeof(double)*(radii!=NULL?max_level:0);
    uint4 mem_size = ptr_size + int_size + fl_size;
    uint4 extra_size;
    unsigned char* work_mem;
    void* extra_mem;
    assert((work==NULL && work_size==0) || (work!=NULL && work_size>0));
    bool need_alloc = (work==NULL || work_size < mem_size);
    if (need_alloc)
    {
	extra_size = sizeof(double*)*4*max_level +
	    sizeof(double)*(5*max_level + 2*num_dim + max_level*num_dim +
			   3*max_level*max_level);
	// Shouldn't happen, but handle this case
	if (mem_size > (1<<13))
	    extra_size = 0;
	else if (extra_size + mem_size > (1<<14))
	    extra_size = (1<<14) - mem_size;  // Limit total to 16K
	work_mem = (unsigned char*)
	    new double[dalign(mem_size + extra_size)/sizeof(double)];
	extra_mem = (void*)(work_mem + mem_size);
    }
    else
    {
	work_mem = (unsigned char*)work;
	extra_mem = (void*)(work_mem + mem_size);
	extra_size = work_size - mem_size;
    }

    double** ptr_mem = (double**)work_mem;
    uint4* int_mem = (uint4*)(work_mem + ptr_size);
    double* fl_mem = (double*)(work_mem + ptr_size + int_size);

    // Used to create permuted next_elem
    uint4* array = GrabIntVector(int_mem, 0, num_points-1);
    // Linked list of elements
    uint4* next_elem = GrabIntVector(int_mem, 0, num_points-1);
    // Array of boundary ball elements
    uint4* bound_elem = GrabIntVector(int_mem, 0, max_level-1);
    uint4* last_stack = GrabIntVector(int_mem, 0, max_level-1);
    const double** bound_centers = GrabPtrVector(ptr_mem, 0, max_level-1);
    double* bound_radii =
	radii!=NULL ? GrabVector(fl_mem, 0, max_level-1): (double*) NULL; 

    assert(pdalign(work_mem + ptr_size)==pdalign(ptr_mem));
    assert(pdalign(work_mem + ptr_size + int_size)==pdalign(int_mem));
    assert(pdalign(work_mem + mem_size)==pdalign(fl_mem));

    uint4 first;	// First in list of elements
    uint4 bound_size;
    uint4 curr_level;
    uint4 prev, curr, last;
    double radius, true_radius;	// Use local variable so a register can be used
    // BTW, radius is radius squared if dealing with points
#ifdef SHOW_WORK
    uint4 old_first_elem=1000000;
#endif

    for (ii=0; ii<num_points; ii++)
	array[ii] = ii;

    // If a boundary was given, make it the first elements
    assert(in_boundary_size <= num_points);
    if (in_boundary_size > 0)
    {
	// Sort to avoid swapping problems
	IntSort(boundary_arr, in_boundary_size);
	for (ii=0; ii<in_boundary_size; ii++)
	{
	    uint4 other = boundary_arr[ii];
	    assert(other < num_points);  // Valid element
	    assert(ii==0 || other!=boundary_arr[ii-1]); // No repeats...
	    uint4 tmp = array[ii];
	    array[ii] = array[other];
	    array[other] = tmp;
	}
    }

    // Permute the ordering other elements...
    for (ii=in_boundary_size; ii<num_points-1; ii++)
    {
	uint4 pick = rand()%(num_points-ii);
	uint4 tmp = array[ii];
	array[ii] = array[ii+pick];
	array[ii+pick] = tmp;
    }

    first = array[0];
    for (ii=1; ii<num_points; ii++)
	next_elem[array[ii-1]] = array[ii];
    next_elem[array[num_points-1]] = num_points;  // End list terminator

    // Init Center and boundary to enclose the first point
    // This avoid some special cases below
    memset((void*)out_center, 0, num_dim*sizeof(double));
    radius = MINDOUBLE;
    true_radius = MINDOUBLE;
    bound_elem[0] = first;
    bound_centers[0] = centers[first];
    if (radii!=NULL)
	bound_radii[0] = radii[first];
    bound_size = 1;

    curr_level = 0;
    prev = first;
    curr = next_elem[first];
    last = num_points;

    while (curr!=num_points)
    {
	while (1)
	{
	    // Is it in the ball...
	    double total_dist = (radii != NULL) ?
		CalcDist(num_dim, out_center, centers[curr], weights) +
		    radii[curr]:
		// Here total_dist and radius are squared
		CalcDistSqrd(num_dim, out_center, centers[curr], weights);

	    // Quit loop if enclosed by ball...
	    if (total_dist <= true_radius) break;
	    if (total_dist <= radius)
	    {
		// Yes quit loop but update true_radius
		true_radius = total_dist;
		break;
	    }

	    // This shouldn't happen, but might happen due to numeric error...
	    // I'll handle this later if necessary
	    assert(curr_level<=max_level);

	    bound_elem[curr_level] = curr;
	    bound_centers[curr_level] = centers[curr];
	    if (radii!=NULL)
		bound_radii[curr_level] = radii[curr];
	    bound_size = curr_level+1;

	    if (radii!=NULL)
	    {
		BallFromBoundaryBalls(num_dim, bound_size, bound_centers,
				      bound_radii, out_center,
				      true_radius, weights,
				      extra_mem, extra_size);
		// Add a little extra space (avoid singularities)
		radius = true_radius*(1.0 + RAD_SLACK);
	    }
	    else
	    {
		BallFromBoundaryPoints(num_dim, bound_size, bound_centers,
				       out_center, true_radius, weights,
				       extra_mem, extra_size);
		// Add a little extra space (avoid singularities)
		// This is squared dist so the error tolerance is doubled
		radius = true_radius*(1.0 + 2.0*RAD_SLACK);
	    }

	    if (curr==first) break;
	    last_stack[curr_level] = last;
	    curr_level++;
	    last = prev;
	    curr = first;
	}

#ifdef SHOW_WORK
	if (curr_level==0 && bound_size>1 && bound_elem[0]!=old_first_elem)
	{
	    for (ii=0; ii<bound_size; ii++)
		cout << bound_elem[ii] << " ";
	    cout << endl;
	    old_first_elem = bound_elem[0];
	}
#endif

	prev = curr;
	curr = next_elem[curr];

	uint4 test_prev = prev;
	while (test_prev==last)
	{
	    assert(curr_level != 0);
	    curr_level--;
	    last = last_stack[curr_level];
	    uint4 next = next_elem[curr];

	    // Now do move to front...
	    assert(curr!=first);
	    next_elem[prev] = next;
	    next_elem[curr] = first;
	    test_prev = first = curr;
	    curr = next;
	}
    }
    assert(curr_level==0);

    const double FLOAT_ERROR_SAFETY = 1.001;
    if (radii!=NULL)
	out_radius = true_radius*FLOAT_ERROR_SAFETY;
    else
	out_radius = (sqrt(true_radius) + common_radius)*FLOAT_ERROR_SAFETY;

    // Output boundary points
    if (boundary_arr!=NULL && out_boundary_size!=NULL)
    {
	if (bound_size < *out_boundary_size)
	    *out_boundary_size = bound_size;
	uint4 out_size = *out_boundary_size;
	for (ii=0; ii<out_size; ii++)
	    boundary_arr[ii] = bound_elem[ii];
    }

#ifndef NDEBUG
    if (radii==NULL)
	for (ii=0; ii<num_points; ii++)
	{
	    double dist = CalcDist(num_dim, out_center, centers[ii], weights);
	    if (dist > out_radius) {
		cerr << "EnclosingBall: increasing from "
		     << out_radius << " to "
		     << dist << endl;
		out_radius = dist;
	    }
	    assert(dist <= out_radius);
	}
    else
	for (ii=0; ii<num_points; ii++)
	{
	    double dist = CalcDist(num_dim, out_center, centers[ii], weights);
	    dist += radii[ii];
	    if (dist > out_radius) {
		cerr << "EnclosingBall: increasing from "
		     << out_radius << " to "
		     << dist << endl;
		out_radius = dist;
	    }
	    assert(dist <= out_radius);
	}
#endif

    if (need_alloc) delete[] work_mem;
}
