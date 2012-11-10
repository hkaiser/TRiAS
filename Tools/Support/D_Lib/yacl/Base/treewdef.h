

#ifndef _treewdef_h_ /* Tue Mar 15 12:29:50 1994 */
#define _treewdef_h_





/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */



typedef CL_PreOrderWalker<long>          CL_IntegerTreePreWalker;
typedef CL_PostOrderWalker<long>         CL_IntegerTreePostWalker;

// If you uncomment the following two lines, the Borland C++ 3.1 TLIB runs
// out of memory:
// typedef CL_PostOrderWalker<CL_ObjectPtr> CL_GenericTreePostWalker;
// typedef CL_PreOrderWalker<CL_ObjectPtr>  CL_GenericTreePreWalker;


#endif /* _treewdef_h_ */
