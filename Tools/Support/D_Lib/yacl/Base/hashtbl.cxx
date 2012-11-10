

#if defined(__GNUC__)
#pragma implementation
#endif


#include "base/htbl_imp.cxx"

#if defined(__GNUC__)
template class CL_HashTable<long>;
template class CL_HashTable<CL_String>;
template class CL_HashTable<CL_MapAssoc<long, long> >;
template class CL_HashMap<long, long>;

template class CL_HashFunction<long>;
template class CL_HashFunction<CL_String>;
template class CL_HashFunction<CL_MapAssoc<long, long> >;
template class CL_AssocHashFunction<long, long>;
#endif

