

#ifndef _map_h_ /* Tue Jan 26 22:08:12 1993 */
#define _map_h_





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




#ifdef __GNUC__
#pragma interface
#endif


#ifdef __IBMCPP__
#pragma implementation("mapimp.cxx")
#endif

#include "base/objseq.h"
#include "base/iterator.h"
#include "base/string.h"


template <class Key, class Value>
class YACL_BASE  CL_MapIterator;


// A MapAssoc is simply a key-value pair that functions as a single entry
// in a Map. It overrides Object's {\tt Compare} method with code that uses
// the key in the MapAssoc to determine relative order.

template <class Key, class Value>
class YACL_BASE  CL_MapAssoc: public CL_Object {

public:
    //[ Local
    // Public data members:
    Key key;
    Value value;
    //] Local

    CL_MapAssoc ();
    // Default constructor.

    CL_MapAssoc (const Key& k, const Value& v);
    // Build a MapAssoc with given key and value.
    
    CL_MapAssoc (const CL_MapAssoc<Key,Value>& a);
    // Copy constructor.

    ~CL_MapAssoc () {};
    // Destructor.
    
    void operator= (const CL_Object& o)
    { if (CheckClassType (o, "CL_MapAssoc::op="))
            *this = ((const CL_MapAssoc<Key, Value>&) o); };
    // Override method inherited from {\tt CL_Object}. The
    // implementation checks that {\tt o}'s class id is the same as ours,
    // casts down {\tt o} and invokes the MapAssoc assignment.

    void operator= (const CL_MapAssoc<Key,Value>& o);
    // Assign the MapAssoc {\tt o} to this object.

    short Compare (const CL_Object& o) const;
    // Cast {\tt o} down to a MapAssoc and use
    
    CL_String AsString () const;
    // Return a String in the form ``{\tt k --> v}'' where {\tt k} is
    // {\tt key.AsString()} and {\tt v} is {\tt value.AsString()}.

    // --------------------- Basic operations ---------------------
    
    CL_Object* Clone () const
        { return new CL_MapAssoc<Key, Value> (*this); };
    // Override the method inherited from {\tt CL_Object}.

    const char* ClassName () const {return "CL_MapAssoc";};
    // Override the method inherited from {\small\tt CL_Object}.
    


};




// A  Map is an object   that  maintains a key-value mapping.  Duplicate keys
// are {\it not\/}   allowed.  The {\tt Key} and {\tt Value} types must have
// basic operations defined on them (see {\tt basicops.h}). The Map uses
// these basic operations for all key- and value-related operations.  All
// methods that return boolean values return \TRUE\ on success and \FALSE\ on
// error.
// 
// A Map stores MapAssoc objects, which are key-value pairs.
// 
// A MapIterator object is also provided; this object allows inspecting
// the  key-value pairs (associations) contained in  a  map, in ascending
// order of keys. It provides methods {\tt Reset}, {\tt More} and {\tt
// Next}, so that iteration in the following form is possible:
// \par\begin{verbatim}
//           CL_StringIntMapIterator iter (myMap);
//           CL_StringIntAssoc assoc;
//           for (iter.Reset(); iter.More(); ) {
//               assoc = iter.Next();
//               // Process the pair "assoc" here....
//           }
// \end{verbatim}
//
// Keys in associations returned by the {\tt Next()} method of the iterator
// may not be modified, although values can be. It is not  advisable to
// remove  elements from a map while an
// iterator on the map is active.
//
// When the Map is instantiated as a container for pointers (as are
// several Maps -- see {\tt mapdef.h}), the Map
// does not own the objects that the pointers point to, and
// therefore does not delete them when it is destroyed. The MapIterator
// can be used to iterate over the map's contents and destroy pointed-to
// objects.
//
// The implementation uses a sorted {\tt CL_Sequence}, so that it is
// possible to create maps with size up to approximately 89
// million, even under MS-Windows, thus alleviating the 64K  limitation
// under MS-Windows (provided, of course, there is enough main memory
// available).



template <class Key, class Value>
class YACL_BASE  CL_Map: public CL_Object {

public:

    // ---------------------- Construction and destruction ---------------

    CL_Map ();
    // Default constructor: build an empty map. 

    CL_Map (CL_MapAssoc<Key, Value> assoc[], long count);
    // Convenience constructor: build a map from a C-style array of
    // associations.
    
    CL_Map (const CL_Map<Key,Value>& s);
    // Copy constructor.

    ~CL_Map ();
    // Destructor.
    
    //
    // ---------------------- Element access -----------------------------
    //

    inline long Size () const;
    // Return the number of entries in the map.
    
    bool IncludesKey (const Key& key) const;
    // Tell whether the map includes the given key.

    Value& operator[]  (const Key& key);
    // Return the value associated with the given key. The
    // return value is a reference, and may be modified, resulting in
    // modification of the Map. If the key is not found, this operator
    // returns a reference to an object of type Value whose contents
    // are the null value of the class Value.
    //
    // The implementation uses binary search when the number of keys exceeds
    // seven.

    const Value& operator[] (const Key& key) const;
    // Same as the other {\tt operator[\,]}, except that this is a {\tt const}
    // method that returns a {\tt const} reference.
    
    virtual const CL_MapAssoc<Key,Value>& ItemWithRank (long i)
        const;
    // Given an index $i$ between 0 and Size()-1, return the MapAssoc of rank
    // $i$, i.e., the MapAssoc that has $i$ keys less than it in the map.
    // If $i \le 0$, this returns the MapAssoc with smallest key, and if $i
    // \ge {\tt Size()}$, this returns the one with the largest key.
    //
    // This is a {\tt const} method; even if this
    // is a Map of pointers, it is not safe to modify the object pointed
    // to by the return value because the Map's internal representation
    // may be affected and its algorithms may perform incorrectly.
    //   Note that it is possible to iterate through the elements of the map
    // via calls to this method, varying the index from 0 to ${\tt Size()}-1$;
    // however, depending on the implementation, this may lead to very
    // inefficient iteration. Use of the MapIterator is the recommended way
    // to inspect all elements of the set.
    
    virtual long RankOf (const Key& k) const;
    // Return the number of MapAssoc's in this Map whose keys are less than
    // {\tt k}. The key {\tt k} need not be in the Map. The ordering
    // relationship used is that defined by {\tt Key};
    // if the latter does not define a Compare method or an {\tt
    // operator<} method, {\tt RankOf} does not return anything useful.
    
    
    // ------------------------- Modification ---------------------------

    virtual bool Add  (const Key& key, const Value& value);
    // Add a key-value pair to the map.  Return TRUE on success, FALSE if
    // there was already a MapAssoc with the given key.

    virtual CL_MapAssoc<Key, Value> Remove  (const Key& key);
    // Remove the given key and its associated value from the map. Return
    // the Assoc that was removed; return the null value of the MapAssoc if
    // the removal failed, either because there was no such key or because
    // of memory allocation failure.

    virtual void MakeEmpty ();
    // Remove all the key-value pairs in the Map. If this Map uses
    // pointers in either key or value, the pointed-to objects are {\it
    // not\/} deleted.

    virtual void DestroyContents ();
    // Remove all key-value pairs  in the map. If this map uses
    // pointers in either key or value, the pointed-to objects {\it are also\/}
    // deleted.
    
    void operator= (const CL_Map<Key,Value>&);
    // Assign the given Map to ourselves.
    
    void operator= (const CL_Object& o);
    // Check that the given object has the same class id as this one,
    // and then perform a Map assignment after casting down.
    

    // -------------------- Storage and retrieval ---------------------

    long StorableFormWidth () const;
    // Override the method inherited from {\small\tt CL_Object}. Returns
    // the number of bytes needed to store this Map on a Stream.

    bool ReadFrom (const CL_Stream&);
    // Override the method inherited from {\small\tt CL_Object}. Reads the
    // contents of this Map from the given Stream.

    bool WriteTo  (CL_Stream&) const;
    // Override the method inherited from {\small\tt CL_Object}. Writes
    // the contents of this Map to the given Stream.

    void IntoStream (ostream& strm) const;
    // Override the method inherited from {\small\tt CL_Object}. Writes a
    // textual representation of this Map to the given {\tt ostream}.

    
    //
    // -------------------- Basic inherited methods ---------------------
    //
    CL_Object* Clone () const
        {return new CL_Map<Key,Value> (*this);};
    
    virtual const char* ClassName() const
        { return "CL_Map";};
    
    virtual CL_ClassId ClassId () const
        {return _CL_Map_CLASSID;};




    // -------------------- End public protocol -------------------------

protected:

    // -------------------- Friend declarations ----------------------
    
    friend CL_MapIterator<Key,Value>;


    // -------------------- Protected methods -------------------------

    bool _ReadAssoc (CL_MapAssoc<Key,Value>& m,
                     const CL_Stream& s)
        {return _ReadKey (m.key, s) && _ReadValue (m.value, s);};
    // Read the data for a single MapAssoc into the parameter {\tt m}. If
    // the read fails, return a NULL pointer. This method is called by {\tt
    // ReadFrom}.

    virtual bool _ReadKey   (Key& key,     const CL_Stream& s);
    // This method is called by  {\tt _ReadAssoc} to read a single key. It
    // is virtual, to provide a hook for derived classes.
    
    virtual bool _ReadValue (Value& value, const CL_Stream& s);
    // This method is called by  {\tt _ReadAssoc} to read a single value. It
    // is virtual, to provide a hook for derived classes.
    
    bool _WriteAssoc (const CL_MapAssoc<Key,Value>& m,
                      CL_Stream& s) const
        {return _WriteKey (m.key, s) && _WriteValue (m.value, s);};
    // Write a single MapAssoc value into the stream. This method is called
    // for each contained Assoc by the {\tt WriteTo} method. 

    virtual bool _WriteKey   (const Key& key,     CL_Stream& s) const;
    // This method is called by  {\tt _WriteAssoc} to write a single key. It
    // is virtual, to provide a hook for derived classes.
    
    virtual bool _WriteValue (const Value& value, CL_Stream& s) const;
    // This method is called by  {\tt _WriteAssoc} to write a single value. It
    // is virtual, to provide a hook for derived classes.
    
    // -------------------- Instance variables -----------------------
    
    CL_ObjectSequence                 _data;
    CL_MapAssoc<Key, Value>           _nullValue;
    
};




// MapIterator is a class template with the same template parameters as Map.
// It provides iteration over all entries in a Map; consecutive calls to its
// {\tt Next} method return the MapAssoc's of the Map in ascending order of
// keys. For example:
//
// {\footnotesize\begin{verbatim}
//        CL_Map<CL_String, long> myMap;
//        // ..... Set up myMap here ....
//        CL_MapIterator<CL_String, long> iter (myMap);
//        for (iter.Reset(); iter.More();) {
//            CL_MapAssoc<CL_String, long> assoc = iter.Next();
//            cout << assoc.key << " corresponds to " << assoc.value << endl;
//        }
// \end{verbatim}
// }


template <class Key, class Value>
class YACL_BASE CL_MapIterator: public CL_Iterator<CL_MapAssoc<Key, Value> > {

public:
    CL_MapIterator (const CL_Map<Key,Value>& map);
    // Create a MapIterator for the given Map.

    CL_MapIterator (const CL_MapIterator<Key, Value>& itr);
    // Copy constructor. The copy inspects the same Map as {\tt itr}, and
    // (unless reset) begins  its iteration at the MapAssoc at which {\tt itr}
    // is currently positioned.
    
    void Reset ();
    // Reset the iterator to the beginning (lowest-valued key). The next
    // call to {\tt Next} will return the MapAssoc with the lowest-valued key.

    virtual void BeginFromRank (long i);
    // Start the iteration so that the first call to {\tt Next} returns the
    // MapAssoc of rank $i$. Thus {\tt BeginFromRank(0)} is equivalent to {\tt
    // Reset()}.
    
    bool More  ();
    // Return TRUE if there are more MapAssoc's in the Map we're
    // inspecting.
    
    const CL_MapAssoc<Key, Value>& Next ();
    // Return a reference to the next MapAssoc in the iteration. It is
    // {\it not\/} safe to modify the key in the returned MapAssoc,
    // although the value may be modified.



protected:
    const CL_Map<Key,Value>&  _map;
    long                      _index;

};





// ---------------------- Inline functions ------------------------



template <class Key, class Value>
inline long CL_Map<Key, Value>::Size () const
{
    return _data.Size ();
}







#ifndef _no_cl_map_typedefs_ /* Fri Nov 19 14:31:53 1993 */
#include "base/mapdef.h"
#endif /* _no_cl_map_typedefs_ */


#endif  /* _map_h_ */


