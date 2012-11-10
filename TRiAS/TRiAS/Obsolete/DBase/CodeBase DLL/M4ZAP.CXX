// m4zap.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

DataMemo::zap( long r1, long r2 )
{
   DataIndex::zap(r1,r2) ;
   return compress() ;
}


