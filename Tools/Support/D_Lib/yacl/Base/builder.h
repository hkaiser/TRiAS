

#ifndef _builder_h_ /* Wed Apr 20 22:49:51 1994 */
#define _builder_h_





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



// An ObjectBuilder is an object that can reconstruct another object from
// a given data stream. {\tt CL_ObjectBuilder} is an abstract class;
// each class that needs to be stored and retrieved must
// declare its own derived version of ObjectBuilder, perhaps using the class
// template {\tt CL_Builder}.

#ifdef __GNUC__
#pragma implementation
#endif

class YACL_BASE CL_Object;

class YACL_BASE CL_ObjectBuilder {

public:
    CL_ObjectBuilder () {};
    // The default constructor does nothing.

    CL_ObjectBuilder (const CL_ObjectBuilder&) {};
    // The copy constructor has an empty body.
    
    void operator= (const CL_ObjectBuilder&) {};
    
    virtual CL_Object* BuildFrom (const CL_Stream& s) = 0;
    // This method represents the main purpose of the ObjectBuilder class.
    // Its task is to build a new object from its representation in the
    // stream and return it. The caller of this method then owns the new
    // object, and must destroy it when done.
    
};



// A Builder is a template-based specialization of ObjectBuilder; its
// purpose is to build an object of the template parameter type from a
// Stream. The Builder template can be used in most
// situations in which an ObjectBuilder is called for, obviating the need
// for defining an explicit class derived from
// ObjectBuilder for every client class.

template <class Base>
class YACL_BASE CL_Builder: public CL_ObjectBuilder {

public:
    CL_Object* BuildFrom (const CL_Stream& s);
    // Override the inherited method. The implementation creates a new
    // object of type {\tt Base} using  {\tt Base}'s  default constructor.
    // It then invokes {\tt s.Read} on this object and returns the object.

};


template <class Base>
inline CL_Object* CL_Builder<Base>::BuildFrom (const CL_Stream& s)
{
    CL_Object* p = new Base;
    if (p)
        s.Read (*p);
    return p;
}


#endif /* _builder_h_ */
