// m4pack.c   (c)Copyright Sequiter Software Inc., 1990-1991.  All rights reserved.

#include "d4all.h"

DataMemo::pack()
{
   DataIndex::pack() ;
   return compress() ;
}
