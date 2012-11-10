// gist_ball.h							-*- c++ -*-
// Copyright (c) 1995, David A. White
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_ball.h,v 1.4 1998/06/18 00:56:39 aoki Exp $

#ifndef _BALL_H
#define _BALL_H

#include <stdio.h>		// for NULL

#include "gist_defs.h"		// for uint4

//
// void EnclosingBall(---)
//
// Find enclosing ball of points or balls:
//   num_dim: Dimensionality of data (ie. 3 = 3D)
//   num_points: Number of points or balls to be enclosed
//   centers: An array of size num_points of double arrays of size num_dim
//	      that represent points or centers of balls
//   radii: If points, this is NULL.  Otherwise this is an array of radii
//          of the internal balls of size num_points.
//   out_center: The center of the enclosing ball.
//   radius: The radius of the enclosing ball
//   weights: If not NULL, this specifies that weighted euclidean distance
//            should be used so ellipses can be used instead of balls.
//	      BTW, these weights are squared weights since they are used
//	      directly when calculating the squared distance. (optional)
//   boundary_elem: If non-NULL, this is an array used to hold the
//		    boundary elements on input (if in_boundary_size>0)
//		    and output (if out_boundary_elem is not NULL).  This
//		    array should be assumed to be modified if non-NULL.
//   in_boundary_size: This specifies how many elements of boundary_elem
//		       are valid boundary points.  These points are
//		       considered first.  All other points are permuted
//		       and considered in random order.  If zero, all
//		       elements are considered in random order.
//   out_boundary_size: If non-NULL, this points to an integer that specifies
//		        the size of the output array and on output holds
//			the size of the output boundary (it can only
//			decrease in value).
//   work: If non-NULL, it is a pointer to a block of memory to use for
//	   calculations.  The size of the work memory must also be specified
//	   or else this memory will be ignored.
//   work_size: Size of that block of memory.  If it is not enough memory,
//              then the work memory is ignored and more memory is allocated.
//
void
EnclosingBall(uint4 num_dim, uint4 num_points,
	      const double*const* centers, const double* radii,
	      double* out_center, double& radius,
	      const double* weights=NULL, uint4* boundary_arr=NULL, 
	      uint4 in_boundary_size = 0, uint4* out_boundary_size=NULL,
	      void* work=NULL, uint4 work_size=0);

#endif // #ifndef _BALL_H
