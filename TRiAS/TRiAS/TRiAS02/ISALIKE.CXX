/*
isalike()	Determins whether two character strings are
		sufficiently equal using the 'Levenstein lev_dist'
		algorithm.

Limitation:	For memory space conservation and execution speed
		this implementation compares the first 20
		characters of both string only. See l_lev_dist.c()
		listing.
		'#define COMP_LEN' may be changed to decrease or
		increase the number of characters compared.

Returns:	The constant ACCEPTED or REJECTED.

		De-commenting the following '#define DEBUG' will
		create a stand-alone program, which enables you
		to experiment with different values for the
		constants 'addition', 'change' and 'deletion'.
*/

#include "trias02p.hxx"

#include <math.h>
#include <ctype.h>

const int addition = 1;		/* change constants in this block */
const int change   = 2;		/* of four lines if needed.       */
const int deletion = 3;

#define COMP_LEN		20
#define TU(x)			toupper(x)
#define ARR_SIZE		COMP_LEN + 1
#define SMALLEST_OF(x,y,z)  	( (x<y) ? min(x,z) : min(y,z) )
#define ZERO_IF_EQUAL(x,y)  	(TU(requested[x-1]) == TU(found[y-1]) ? 0 : change)
#define ACCEPTED		1
#define REJECTED		0

static int lev_dist[ARR_SIZE][ARR_SIZE];

extern "C" 
int EXPORT02 FUNCTYPE isalike (char *requested, char *found) 
{
register int i,j;
int r_len, f_len, threshold;

	r_len = (strlen (requested) > COMP_LEN ? COMP_LEN : strlen (requested));
	f_len = (strlen (found) > COMP_LEN ? COMP_LEN : strlen (found));

	/* comparing string length */
	threshold = (int)  floor( (double) 1 + ((r_len + 2) / 4));
	if ( abs(r_len - f_len) > threshold)  
		return(REJECTED);		/* length difference too big */


	lev_dist[0] [0] = 0;
	for (j = 1; j < ARR_SIZE ; j++)
		lev_dist[0][j] = lev_dist[0][j-1] + addition;
	for (j = 1; j < ARR_SIZE ; j++)
		lev_dist[j][0] = lev_dist[j-1][0] + deletion;

	for (i = 1; i <= r_len; i++) {
		for (j = 1; j <= f_len; j++) {
			lev_dist[i][j] = SMALLEST_OF(
				(lev_dist[i-1][j-1] + ZERO_IF_EQUAL (i, j)),
				(lev_dist[i][j-1]   + addition),
				(lev_dist[i-1][j]   + deletion));
		}
	}

	/* Levenstein lev_dist within threshold limit ? */
	if ( lev_dist[r_len][f_len] <= threshold )
		return(ACCEPTED);		/* lev_dist within limits */
	else
		return(REJECTED);		/* lev_dist too big */
}

