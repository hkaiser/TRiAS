/* (c)Copyright Sequiter Software Inc., 1990-1991. All rights reserved.

   s4quick.c   

   Iteritive Quick Sort Algorithm

   This algorithm is superior to the more traditional recursive
   Quick Sort as the worst case stack size is proportional to 'log(n)'.
   In this algorithm the stack is explicitly maintained.

   In the recursive algorithm, the worst case depth of recursion
   proportional to 'n'.  For example, if there were 1000 items to
   sort, the Quick Sort could, in the worst case, call itself
   1000 times.

   This routine assumes that there is a record number, after the sort
   data, for final
   comparison resolutions in case that two keys are the same.
*/

#include <d4all.h>

extern "C" {
#include <string.h>
}

class QuickSort
{
public:
   void  flip( int i, int j ) ;
   int   greater( int i, int j ) ;
   void  sort() ;

   void **pointers ;
   int	n_pointers ;
   int	sort_len ;
   SORT_CALL_BACK *cmp ;
} ;

void  QuickSort::flip( int i, int j )
{
   void *flip_data  =  pointers[i] ;
   pointers[i] =  pointers[j] ;
   pointers[j] =  flip_data ;
}

int  QuickSort::greater( int i, int j )
{
   int rc = (*cmp)( pointers[i], pointers[j], sort_len ) ;
   if ( rc > 0 )  return 1 ;
   if ( rc < 0 )  return 0 ;

   long  l1, l2 ;
   memcpy( &l1, ((char *)pointers[i])+sort_len, sizeof(long) ) ;
   memcpy( &l2, ((char *)pointers[j])+sort_len, sizeof(long) ) ;
   return l1 > l2 ;
}

void  s4quick( void **p, int p_n, SORT_CALL_BACK *cmp, int width )
{
   QuickSort quick ;
   quick.cmp =  cmp ;
   quick.pointers =  p ;
   quick.n_pointers =  p_n ;
   quick.sort_len =  width ;

   quick.sort() ;
}

void  QuickSort::sort()
{
   /* A stack size of 32 is enough to sort four billion items. */
   int	 stack_start[32], stack_end[32], f, l, num, j, i, middle ;
   int	 stack_on ;

   stack_on	   =  0 ;
   stack_start[0] =  0 ;
   stack_end[0]   =  n_pointers - 1 ;

   while( stack_on >= 0 )
   {
	  f =  stack_start[stack_on] ;
	  l =  stack_end[stack_on] ;
	  stack_on-- ;

	  /* Sort items 'f' to 'l' */
	  while ( f < l )
	  {
		 /* Pick the middle item based on a sample of 3 items. */
		 num =  l - f ;
		 if ( num < 2 )
		 {
				if ( num == 1 )
			{
			   /* Two Items */
			   if ( greater(f,l) )
				  flip(f,l) ;
			}
			break ;
		 }

		 /* Choose 'ptr_ptr[f]' to be a median of three values */
		 middle =  (l+f) / 2 ;

		 if ( greater(middle,l) )
			flip(middle,l) ;

		 if ( greater(middle,f) )
			flip(f,middle) ;
		 else
			if ( greater(f,l) )
			   flip(f,l) ;

		 if ( num == 2 )   /* Special Optimization on Three Items */
		 {
			flip(f,middle) ;
			break ;
		 }

		 i = f + 1 ;
		 while( greater(f,i) )
		 {
			i++ ;
			#ifdef DEBUG
			   if ( i >= n_pointers ) 
				  e4severe( e4result, "QuickSort::sort()", (char *) 0 ) ;
			#endif
		 }

		 j =  l ;
		 while( greater(j,f) )  j-- ;

		 while ( i<j )
		 {
			flip( i,j ) ;
			i++ ;

			while( greater(f,i) )
			{
			   i++ ;
			   #ifdef DEBUG
				  if ( i >= n_pointers ) 
					 e4severe( e4result, "QuickSort::sort()", (char *) 0 ) ;
			   #endif
			}
			j-- ;

			while( greater(j,f) )  j-- ;
		 }

		 flip( f,j ) ;

		 /* Both Sides are non-trivial */
		 if ( j-f > l-j )
		 {
			/* Left sort is larger, put it on the stack */
			stack_start[++stack_on] =  f ;
			stack_end[stack_on]	 =  j-1 ;

			f = j+ 1 ;
		 }
		 else
		 {
			/* Right sort is larger, put it on the stack */
			stack_start[++stack_on] =  j+1 ;
			stack_end[stack_on]	 =  l ;

			l = j- 1 ;
		 }
	  }
   }
}
