

#ifndef _object_h_
#define _object_h_





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




// The class Object is the root of YACL's  inheritance tree.
// It provides  simple mechanisms for comparison, runtime type
// identification (via class id's or class names), cloning (copying)
// of objects (via the Clone() method), and dependent notification.
//
// Every Object instance maintains two sets of  dependents, who are to be
// notified just before and just  after the  object  is modified. (It  is
// upto the individual  object  to decide  exactly what its  modification
// means;    for  example,  all  base  objects   regard ``modification'' as
// alteration of their   value in some way.)  An   object A can  register
// itself  as  a  (post-modification)  dependent  on   object B  via  the
// {\tt AddDependent} call on   B,  which  also  specifies  a  method on   A.
// Subsequently,  whenever B invokes  {\tt Notify}  on itself, the  specified
// method    on A  is   called, with  B  and  the    notification code as
// parameters.
// 
// Similarly,  object  A  can    register itself  as   a pre-modification
// dependent of object B via the call to {\tt AddPreChangeDependent}. If B is
// any   base  object that   has    a nonempty  set  of  pre-modification
// dependents, then B consults all  of these dependents before  modifying
// itself, and remains unaltered if any of the dependent bindings returns
// a \FALSE\ value.
// 
// The  sets of dependents   are implemented  via  a  single  pointer  as
// instance variable, to minimize  overhead on  objects  that do not  use
// dependents. These sets are {\it not\/} copied when the object is copied.




#ifdef __GNUC__
#pragma interface
#endif

#include "base/defs.h"
#include "base/classid.h"
#include "base/error.h"




#if defined(CHECK_LEAKS)
#include "base/memory.h"     // DEBUG only!
#endif


class YACL_BASE  CL_Object;
class YACL_BASE  CL_AbstractBinding;
class YACL_BASE  CL_ByteArray;
class YACL_BASE  CL_ByteString;
class YACL_BASE  CL_String;
class YACL_BASE  CL_Stream;
class YACL_BASE  CL_Integer;
class YACL_BASE  CL_ClientSet;
template <class K, class V>
class YACL_BASE  CL_Map;



/*
  The iostream classes are declared this way, rather than including
  iostream.h, to minimize preprocessing time:
*/

#if defined(__BORLANDC__) && (defined(__MS_DOS__) \
    || defined(__MS_WINDOWS__) || defined(__MS_WIN32__))
class  _CLASSTYPE istream;
class  _CLASSTYPE ostream;
#else
class   istream;
class   ostream;
#endif


//[ Global
enum CL_ComparisonOperator {
     CL_CMP_EQUAL = 0,   CL_CMP_LESSTHAN,   CL_CMP_GTRTHAN,
     CL_CMP_LESSEQ,      CL_CMP_GTREQ,      CL_CMP_PREFIX,
     CL_CMP_CONTAINS,    CL_CMP_NOTEQUAL};
// The ComparisonOperator enumeration is used for ``indirect''
// comparison by the {\tt CompareWith} methods.
// \par\bigskip
//] Global


typedef CL_Object*  CL_ObjectPtr;
typedef CL_Object*  (*CL_Creator) (); // For persistence support

typedef long        CL_ClassId; // This class id representation may be
                                // changed in future.

struct CL_DependStruct;

class YACL_BASE CL_Object {

public:
    
    CL_Object();
    // Default constructor.

    CL_Object (const CL_Object&);
    // Copy constructor.
    
    virtual ~CL_Object() = 0;
    // Destructor is pure virtual.


    // ------------------ Object identification --------------------------

    virtual const char* ClassName() const { return "CL_Object";};
    // Return the class name of this object.
    
    virtual CL_ClassId ClassId () const {return _CL_Object_CLASSID;};
    // Return the class id of this object.

    bool IsA (const CL_Object& obj) const
        {return ClassId() == obj.ClassId();};
    // Return TRUE if this object's class is the same as or derived
    // from that of {\tt obj}. The current implementation only checks
    // equality of ClassId values.

    bool CheckClassType (const CL_Object& o, const char* msg) const;
    // Check that {\tt o} has the same type as this object (via {\tt
    // IsA}), and issue an error message containing {\tt msg} otherwise.
    // Return  the value returned by {\tt IsA}.
    
    // ------------------- Copying -----------------------------------

    virtual CL_Object* Clone () const;
    // Return a copy of this object. Whether this is a shallow or deep
    // copy depends on the derived class.  The caller
    // must destroy the returned object. The default implementation issues a
    // ``Not implemented'' error message.

    
    // -------------------- Comparison operators -------------------

    
    virtual bool operator<  (const CL_Object& obj) const;
    // This and operator {\tt ==} constitute the two basic comparison
    // operators.
    // Either this operator or the {\tt Compare} method must be implemented
    // by every derived class that can
    // be thought of as defining an ``orderable'' type. The default
    // implementation uses addresses for comparison; therefore, if the
    // derived class doesn't care about ordering, this operator need not
    // be overridden.
    
    virtual bool operator== (const CL_Object& obj) const;
    // The default implementation checks for equality of addresses.


    virtual bool operator<= (const CL_Object& obj) const
        { return (*this == obj || *this < obj);};
    // This and the other three relational operators ({\tt >}, {\tt >=}
    // and {\tt !=}) have
    // default implementations that invoke the operators {\tt ==} and {\tt
    // <}. Thus a derived class that defines an ``orderable'' object need
    // only override the {\tt ==} and {\tt <} operators.

    virtual bool operator>  (const CL_Object& obj) const
        {return (! (*this <= obj));} ;

    virtual bool operator>= (const CL_Object& obj) const
        {return (! (*this < obj));};

    virtual bool operator!= (const CL_Object& obj) const
        {return (! (*this == obj));};

    virtual short Compare (const CL_Object& obj) const
        { return (*this == obj) ? 0 : ((*this < obj) ? -1 : 1);};
    // This method defines {\tt strcmp}-style comparison. The default
    // implementation invokes (only) the operators {\tt ==} and {\tt <} on this
    // object, in that order. Therefore, if a derived class chooses to
    // override only the {\tt operator<}, then {\tt operator==} is still
    // used on addresses.

    
    virtual bool CompareWith (const CL_Object& obj,
                              CL_ComparisonOperator op) const;
    // ``Indirect'' comparison, given a comparison operator:
    // compare this object with {\tt obj} (after ensuring
    // correct class id), and return a boolean value according to whether
    // the required relationship holds between us and the given
    // object. E.g., given objects p and q, {\tt p.CompareWith (q,
    // CL_CMP_LESSTHAN)} yields TRUE if p is less than q. For the {\tt
    // PREFIX} and {\tt CONTAINS} operators on non-string objects, the {\tt
    // AsString()} method 
    // is applied to both operands before doing the comparison.

    virtual bool CompareWith (const CL_String& obj,
                              CL_ComparisonOperator op) const;
    // This is similar to {\tt Compare}, except the given object is a
    // string, so this object obtains a String representation of itself
    // (via the {\small\tt AsString()} method) before comparing.
    
    // ---------------------- Assignment ----------------------------

    virtual void operator= (const CL_Object&);
    // This assignment operator is declared virtual so that heterogeneous
    // containers can support assignments.  The default implementation
    // issues a ``Not implemented'' error message. 

    
    // ------------------- Passive representations of object -----------

    // ----- Representation as a printable string ---
    
    virtual CL_String AsString () const; 
    // Return a representation of this object in String
    // form. The default implementation issues a ``Not implemented''
    // warning message via the {\small\tt NotImplemented} method, and
    // returns the null string; this method must be overridden by derived
    // classes.


    virtual void IntoStream (ostream& strm) const;
    // Write this object's string representation onto the given {\small\tt
    // ostream}.  The default implementation invokes {\small\tt
    // AsString()} and writes the result to the stream; this method may be
    // overridden by derived classes if necessary.


    virtual void FromStream (istream& stream);
    // Read this object's value from its string representation in the
    // given {\small\tt istream}.  The default implementation does
    // nothing; this method must be overridden by derived classes.


    // ----- Saving and restoration in binary form ----
    
    virtual long StorableFormWidth () const {return 0;};
    // Return the number of bytes in the binary storable representation
    // of this object. The default implementation returns 0.

    virtual bool ReadFrom (const CL_Stream&);
    // Read and reconstruct this object from the binary representation in
    // the given Stream. Return TRUE on success, FALSE if failed for any
    // reason, including when a pre-change dependent disallows the change.
    // The default implementation issues a ``Not implemented'' message.

    virtual bool WriteTo  (CL_Stream&) const;
    // Write the passive binary representation of this object into the
    // given stream. Return TRUE if successful, FALSE otherwise. The
    // default implementation issues a ``Not implemented'' error message.

    // ------------------ Dependents and notification -------------------


    // ----- Post-change dependency methods:
    
    void Notify ();
    // Notify all dependents by calling the associated methods,
    // with this object as parameter to the Binding method.
    
    void AddDependent (const CL_AbstractBinding& binding);
    // Add a dependent to this object's dependent set. The given
    // method will be called on the given object when {\tt Notify} is
    // called. A binding can only appear once in a dependent set; so we
    // cannot add the same binding with different codes as dependents.
    
    void RemoveDependent (const CL_AbstractBinding& binding);
    // Remove a binding from this Object's dependent set.
    
    bool HasDependent (const CL_AbstractBinding& b) const;
    // Is the given binding in this object's dependent set?


    // ----- Pre-change dependency methods:

    bool PrepareToChange ();
    // Ask all pre-change dependents whether it's ok to change our
    // value; return FALSE if any of them returns FALSE, and TRUE if
    // all of them return TRUE.

    void AddPreChangeDependent (const CL_AbstractBinding& binding);
    // Add a pre-change dependent to this object.
    
    void RemovePreChangeDependent (const CL_AbstractBinding& binding);
    // Remove {\tt binding} from our pre-change dependent set.
    
    bool HasPreChangeDependent (const CL_AbstractBinding& b) const;
    // Is the given binding in this object's pre-change dependent set?


    // ------------------- End public protocol ----------------------------

protected:
    void NotImplemented (const char* method_name) const;
    // This method issues an error message (via {\tt CL_Error}'s {\tt Fatal}
    // method) of the form ``{\tt Class foo does not implement method bar}''
    // where  {\tt foo} is the string returned by the {\tt ClassName} method
    // and {\tt bar} is the parameter to {\tt NotImplemented}.

    bool ReadClassId (const CL_Stream&) const;

    static CL_Map<long,long>& _ClassIdMap;

    const CL_ClientSet* PreChangeDependents() const;
    // Return a pointer to the set of pre-change dependent bindings. Return
    // NULL if no such dependents.
    
    const CL_ClientSet* PostChangeDependents() const;
    // Return the set of post-change dependent bindings. Return
    // NULL if no such dependents.
    
private:
    CL_DependStruct* _dependSet;
};


// The ClassIdEntryMaker object is used to make an entry in the class id
// map, for creating persistent objects.

class YACL_BASE CL_ClassIdEntryMaker: public CL_Object {

public:
    CL_ClassIdEntryMaker (CL_ClassId id, CL_Creator func);

    ~CL_ClassIdEntryMaker ();

};


#define CL_DEFINE_CLASS(cls, cls_id)                            \
     CL_Object* CL_Creator__ ## cls ()                          \
     {                                                          \
         return new cls;                                        \
     }                                                          \
     static CL_ClassIdEntryMaker CL_AddEntry__ ## cls ## __instance \
     (cls_id, CL_Creator__ ## cls)



// --------------------------- Operator definitions --------------

//[ Global
istream& YACL_BASEFUNC operator>> (istream& s, CL_Object& o);

// Read {\tt o} from the stream {\tt s}. The implementation of this function
// uses the call {\tt o.FromStream (s)}.

ostream& YACL_BASEFUNC operator<< (ostream& s, const CL_Object& o);

// Write {\tt o} to the stream {\tt s}. The implementation of this function
// uses the call {\tt o.IntoStream (s)}.
//] Global


// -------------------------- Inline methods ----------------------

inline CL_Object::CL_Object()
{
    _dependSet = NULL;
}


inline CL_Object::CL_Object (const CL_Object&)
{
    _dependSet = NULL;
}


#endif
