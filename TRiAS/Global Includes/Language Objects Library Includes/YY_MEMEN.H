
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1998, Compiler Resources, Inc.
//
//  FILENAME:             yy_memen.h
//  
//  FILE DESCRIPTION:     header file with memento object declarations
//
//  CLASS HIERARCHY:
//
//               +------------------------+
//               |    memento abstract    |
//               |      base class        |
//               |     (yy_memen.h)       |
//               +------------------------+
//                           | derives      
//                           |
//               +------------------------+
//               |     parser memento     |
//               |  abstract base class   |
//               |     (yy_psrmm.h)       |
//               +------------------------+
//                           | derives      
//                           |
//             +-----------------------------+
//             |  generated parser memento   |
//             | class(es) from your grammar |
//             |       (yy_mypsr.h)          |
//             +-----------------------------+
//
//    
//  MODIFICATION HISTORY:
//  
//  08/24/98    cc      Solaris C++ needed an extra return in yy_data_ptr().
//  04/29/98	cc	coding and final review completed.
//  
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_memen_h_
#define yy_memen_h_

//////////////////////////////////////////////////////////////////////////////
//
//  HEADER FILES:
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_asrt.h"
#include "yy_strng.h"
#include "yy_err.h"

//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_memento_ptr      is a typedef which defines a pointer to a memento
//  			object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_memento_obj     	*yy_memento_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_memento_obj
//
//  The yy_memento_obj is the base class which provides the interface to
//  mementos (saved objects).  
//
//  No memento objects of this class can actually be created.  This is why
//  the constructors (and assignment operators) are protected.  All memento
//  objects must be created of classes derived from this one.  This is to
//  help protect users from accidentally assigning one type of memento to
//  another (thus filling a memento with the wrong kind of internal data).
//
//  Note that these memento objects provide access to their internal data
//  areas (as a void pointer) so that they can be read and written to files.
//  In using this interface you, the user, must be careful to avoid reading
//  data into a memento which was not originally written from the same kind
//  of memento.  Otherwise, you can corrupt the internal data just as if one
//  type of memento was assigned to another.
//
//  
// PUBLIC FUNCTIONS:
//
//  ~yy_memento_obj()   destructor for a memento object.
//		     
//  yy_sizeof_data()	returns a reference to the memento data area size.
//
//  yy_data_ptr()	returns a pointer to the memento data area.
//
//
//  INTERNAL FUNCTIONS (only for use in derived objects):
//
//  yy_memento_obj()    constructor for a memento object.
//		     
//  yy_memento_obj(yy_old_memento)
//			copy constructor for a memento object.
//		     
//  operator=		assignment operator for a memento object.
//
//
//  INTERNAL STATE:
//
//  yy_memento_sizeof_data
//		        is the sizeof the data about to be stored in this
//		        memento object.
//
//  yy_memento_sizeof_data_max
//			is the sizeof the space allocated for data stored in
//			this memento object.
//
//  yy_memento_data_ptr points to the area allocated for data stored in this
//  			memento object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_memento_obj
{

 public:

    virtual ~yy_memento_obj();

    inline size_t &yy_sizeof_data(void);
    
    inline char *yy_data_ptr(void) const;
    
 protected:

    yy_memento_obj();
    
    yy_memento_obj(
	const yy_memento_obj	&yy_old_memento);

    yy_memento_obj &operator=(
	const yy_memento_obj	&yy_old_memento);

    size_t			yy_memento_sizeof_data;
    size_t			yy_memento_sizeof_data_max;
    char			*yy_memento_data_ptr;
    
};  // yy_memento_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the inline function definitions for the memento object
//  declared above.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   size_t &yy_sizeof_data()
//
//  yy_sizeof_data returns a reference to the memento data area size.  Note
//  this can be set to increase the data area size for the next time the
//  data area is referenced.
//
//////////////////////////////////////////////////////////////////////////////

inline size_t &yy_memento_obj::yy_sizeof_data(void)
{
    return(yy_memento_sizeof_data); 

}   // yy_sizeof_data


//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   char *yy_data_ptr()
//
//  yy_data_ptr returns a pointer to the memento data area.
//
//////////////////////////////////////////////////////////////////////////////

inline char *yy_memento_obj::yy_data_ptr() const
{
    char		*yy_new_data_ptr;
    
    if (yy_memento_sizeof_data_max < yy_memento_sizeof_data) {

	yy_new_data_ptr = new char[yy_memento_sizeof_data];

	if (yy_new_data_ptr == NULL) {
	    yy_err_report(406);
	    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
	    return(yy_memento_data_ptr);
	    }
	
	if (yy_memento_data_ptr != NULL) {
	    yy_memmove(yy_new_data_ptr, yy_memento_data_ptr, 
		       yy_memento_sizeof_data);
	    delete [] yy_memento_data_ptr;
	    }
	yy_memento_ptr(this)->yy_memento_data_ptr = 
	    yy_new_data_ptr;
	yy_memento_ptr(this)->yy_memento_sizeof_data_max = 
	    yy_memento_sizeof_data;
	return(yy_memento_data_ptr);
	}
    
    return(yy_memento_data_ptr); 

}   // yy_data_ptr


#endif /* yy_memen_h_ */
