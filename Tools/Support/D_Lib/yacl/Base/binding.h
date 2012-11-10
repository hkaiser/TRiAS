

#ifndef _binding_h_ /* Mon Sep 20 08:44:42 1993 */
#define _binding_h_





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



// A ``binding'' is the C++ equivalent of C's callback. Conceptually, a
// binding is simply an object-method pair. It remembers an object
// (called the binding's {\it client\/}) and a
// method of the object's class (called the binding's {\it client method}).
// Bindings are used for notification and inter-object communication. An
// abstract binding (class {\tt CL_AbstractBinding}) describes the protocol for
// a binding; the derived class templates {\tt CL_Binding0}, {\tt
// CL_Binding1} and {\tt CL_Binding2} are used to build
// bindings for each class that needs one.
//
// The most important method in the AbstractBinding's protocol is {\tt
// Execute}, which invokes the client method on the client.
// 
// The AbstractBinding is derived from Object, in order to allow it to be
// stored in an ObjectSet. (That's how the ClientSet class is built.)

#include "base/object.h"


class YACL_BASE CL_AbstractBinding: public CL_Object {

public:
    ~CL_AbstractBinding () {};
    // The destructor does nothing. It is provided because Object's
    // destructor is pure virtual.
    
    virtual bool Execute (CL_Object&) const = 0;
    // Execute the binding, i.e., call the contained method on the contained
    // object. Return the return value of the invoked method.

    virtual bool Valid () const = 0;
    // Return whether this is a valid binding, i.e., whether both the
    // contained object pointer and method pointer are non-null.

    virtual const  char* ClassName() const
        {return "CL_AbstractBinding";};
    // Returns the string ``{\tt CL_AbstractBinding}.''

    CL_ClassId ClassId () const = 0;
    // [Pure virtual.]
    
};


// {\tt CL_Binding0} is a class template that specializes AbstractBinding,
// in that its client is of class {\tt Client} (the template parameter) and
// its client method takes no parameters. It defines {\tt operator==} to
// return TRUE if the object pointers in the two bindings are the same. This
// means that you can have an object A registered as dependent on object
// B at most once; you cannot have A registered as dependent on B with two
// different A methods.


template <class Client>
class YACL_BASE CL_Binding0: public CL_AbstractBinding {

public:
    //[ Local
    typedef bool YACL_BASEFUNC (Client::*MethodPtr) ();
    // {\tt MethodPtr} is a pointer to a client method.
    //] Local

    //  ---------------------- Construction ----------------------
    
    CL_Binding0 (Client* client, MethodPtr method)
        {_client = client;  _method = method;};
    // Construct a binding for an object {\tt client} of type {\tt Client},
    // that has a method {\tt method}.

    CL_Binding0 ()
        { _client = 0; _method = 0;};
    // Construct a null binding, one whose object and method pointers are
    // both NULL, for an object of type Client.

    CL_Binding0 (const CL_Binding0<Client>& b)
        {_client = b._client; _method = b._method;};
    // Copy constructor.

    bool Valid () const { return _client != 0 && _method != 0; };
    // Return TRUE if both object and method pointers of this binding are
    // non-NULL.
    
    bool Execute (CL_Object&) const
        { return (_client != 0 && _method != 0)
                ? (_client->*_method) () : FALSE; };
    // Override the virtual method inherited from {\tt AbstractBinding}. The
    // implementation of {\tt Execute} ignores the parameter; it simply
    // invokes the client method and returns its return value.

    void operator= (const CL_Object& o)
        {*this = ((const CL_Binding0<Client>&) o);};
    // Assignment operator: needed by YACL containers.
    
    CL_Binding0<Client>& operator= (const CL_Binding0<Client>& o)
        {_client = o._client; _method = o._method; return *this;};
    // Assignment operator: needed by YACL containers.
    
    bool operator== (const CL_Object& o) const
        {return *this == (const CL_Binding0<Client>&) o;};
    // Cast the given object {\tt o} down to a {\tt CL_Binding0} and invoke
    // operator== (i.e., the other op== in this class) on the result of the
    // cast.
    
    bool operator== (const CL_Binding0<Client>& o) const
        { return _client == o._client; };
    // Return TRUE if this object's client pointer is the same
    // as that of  {\tt o}.

    CL_String AsString () const;
    // Override the method inherited from Object. This is useful for
    // debugging.
    
    CL_Object* Clone () const
        { return new CL_Binding0<Client> (_client, _method);};
    // Override the method inherited from {\tt CL_Object}. Return a copy of
    // this Binding0.

    const  char* ClassName () const {return "CL_Binding0";};
    // Return the string ``{\tt CL_Binding0}.''
    
    CL_ClassId ClassId () const {return _CL_Binding0_CLASSID;};

protected:
    Client*   _client;
    MethodPtr _method;
};


template <class Client>
inline CL_String CL_Binding0<Client>::AsString() const
{
    CL_String s;
    s.AssignWithFormat ("CL_Binding0: object %08x", _client);
    return s;
}


// {\tt CL_Binding1} is a class template that specializes AbstractBinding,
// with two template parameters, {\tt Sponsor} and {\tt Client}. Its
// client is of class {\tt Client}, and its client method takes a single
// parameter that is a reference to a {\tt Sponsor}.
//
// Binding1 defines {\tt operator==} to
// return TRUE if the object pointers in the two bindings are the same. This
// means that you can have an object A registered as dependent on object
// B at most once; you cannot have A registered as dependent on B with two
// different A methods.


template <class Sponsor, class Client>
class YACL_BASE CL_Binding1: public CL_AbstractBinding {

public:
    //[ Local
    typedef bool (Client::*MethodPtr) (Sponsor&);
    // {\tt MethodPtr} is a pointer to a client method.
    //] Local

    //  ---------------------- Construction ----------------------
    
    CL_Binding1 (Client* client, MethodPtr method)
        {_client = client;  _method = method;};
    // Construct a binding for an object of type {\tt Client}, that has a
    // method {\tt method}.

    CL_Binding1 ()
        {_client = 0; _method = 0;};
    // Construct a null binding, one whose object and method pointers are
    // both NULL, for an object of type Client.

    CL_Binding1 (const CL_Binding1<Sponsor,Client>& b)
        {*this = b;};
    // Copy constructor.

    bool Valid () const { return _client != 0 && _method != 0; };
    // Return TRUE if both object and method pointers of this binding are
    // non-NULL.
    
    bool Execute (CL_Object&) const;
    // Override the virtual method inherited from {\tt AbstractBinding}. The
    // implementation casts down  {\tt sponsor} to the type
    // {\tt Sponsor} and uses it as parameter to the client method. It
    // returns the value returned by the client method.

    void operator= (const CL_Object& o)
        {*this = (const CL_Binding1<Sponsor, Client>&) o;};
    // Assignment operator: needed by YACL containers.
    
    CL_Binding1<Sponsor, Client>& operator= (const CL_Binding1<Sponsor,
                                             Client>& b)
        {_client = b._client; _method = b._method; return *this;};
    // Assignment operator: needed by YACL containers.
    
    bool operator== (const CL_Object& o) const
        {return *this == (const CL_Binding1<Sponsor,Client>&) o;};
    // Cast the given object {\tt o} down to a Binding, and return TRUE if the
    // pointers in it are the same as the pointers in this object. 
    
    bool operator== (const CL_Binding1<Sponsor, Client>& o) const
        { return _client == o._client; };
    // Return TRUE if the client  pointer in this object is the
    // same as that in {\tt o}.

    CL_String AsString () const;
    // Override the method inherited from Object. This is useful for
    // debugging.
    
    CL_Object* Clone () const
        { return new CL_Binding1<Sponsor, Client> (_client, _method);};
    // Override the method inherited from {\tt CL_Object}. Returns a copy of
    // this Binding1.

    const  char* ClassName () const {return "CL_Binding1";};
    // Returns the string ``{\tt CL_Binding1}.''
    
    CL_ClassId ClassId () const {return _CL_Binding1_CLASSID;};

protected:
    Client*   _client;
    MethodPtr _method;
};

template <class Sponsor, class Client>
inline bool CL_Binding1<Sponsor, Client>::Execute (CL_Object& sponsor) const
{
    return Valid() ? (_client->*_method) ((Sponsor&) sponsor) : FALSE;
}



template <class Sponsor, class Client>
inline CL_String CL_Binding1<Sponsor, Client>::AsString() const
{
    CL_String s;
    s.AssignWithFormat ("CL_Binding1: object %08x", _client);
    return s;
}



// {\tt CL_Binding2} is a class template that specializes AbstractBinding,
// with two template parameters, {\tt Sponsor} and {\tt Client}. Its
// client is of class {\tt Client}, and its client method takes two
// parameters: a reference to a {\tt Sponsor} and a {\tt long} value that is
// the notification code.
//
// Binding1 defines {\tt operator==} to
// return TRUE if the object pointers in the two bindings are the same. This
// means that you can have an object A registered as dependent on object
// B at most once; you cannot have A registered as dependent on B with two
// different A methods.


template <class Sponsor, class Client>
class YACL_BASE CL_Binding2: public CL_AbstractBinding {

public:
    //[ Local
    typedef bool (Client::*MethodPtr) (Sponsor&, long);
    // {\tt MethodPtr} is a pointer to a client method.
    //] Local

    //  ---------------------- Construction ----------------------
    
    CL_Binding2 (Client* client, MethodPtr method, long code)
        {_client = client;  _method = method; _code = code;};
    // Construct a binding for an object of type {\tt Client}, that has a
    // method {\tt method}. The last parameter is a notification code
    // specified by the creator of the Binding2.

    CL_Binding2 ()
        {_client = 0;  _method = 0;_code = 0;};
    // Construct a null binding, one whose object and method pointers are
    // both NULL, for an object of type Client.

    CL_Binding2 (const CL_Binding2<Sponsor, Client>& b)
        {*this = b;};
    // Copy constructor.

    bool Valid () const { return _client != 0 && _method != 0; };
    // Return TRUE if both object and method pointers of this binding are
    // non-NULL.

    bool Execute (CL_Object&) const;
    // Override the virtual method inherited from {\tt AbstractBinding}.
    // The implementation invokes the client method with two parameters: the
    // object {\tt s} cast down to {\tt Sponsor}, and the notification code
    // in this Binding2. It returns the return value of the client method.

    void operator= (const CL_Object& o)
        {*this = (const CL_Binding2<Sponsor,Client>&) o;};
    // Assignment operator: needed by YACL containers. The implementation
    // casts down {\tt o} to a Binding2 and calls the other assignment
    // operator.
    
    CL_Binding2<Sponsor, Client>& operator= (const CL_Binding2<Sponsor,
                                             Client>& b)
        { _client = b._client; _method = b._method;
          _code = b._code; return *this;};
    // Assignment operator: needed by YACL containers. The implementation
    // copies the client and method pointers and the notification code.
    
    bool operator== (const CL_Object& o) const
        {return *this == ((const CL_Binding2<Sponsor, Client>&) o);};
    // Cast the given object {\tt o} down to a Binding, and return TRUE if the
    // pointers in it are the same as the pointers in this object. The
    // notification codes in this object and {\tt o} are not used for the
    // comparison; only the object and method pointers are used.
    
    bool operator== (const CL_Binding2<Sponsor, Client>& o) const
        { return _client == o._client && _method == o._method; };
    // Return TRUE if the client
    // pointer in {\tt o} is the same as the client pointer in this object.
    // The method and  notification code in this object and {\tt o} are not
    // used for the  comparison; only the object pointer is used.
    

    CL_Object* Clone () const
        { return new CL_Binding2<Sponsor, Client> (_client, _method, _code);};
    // Override the method inherited from {\tt CL_Object}. Return a copy of
    // this Binding2.

    CL_String AsString () const;
    // Override the method inherited from Object. This is useful for
    // debugging.
    
    const  char* ClassName () const {return "CL_Binding2";};
    // Return the string ``{\tt CL_Binding2}.''
    
    CL_ClassId ClassId () const {return _CL_Binding2_CLASSID;};

protected:
    Client*   _client;
    MethodPtr _method;
    long      _code;
};



template <class Sponsor, class Client>
inline bool CL_Binding2<Sponsor, Client>::Execute (CL_Object& sponsor) const
{
    return Valid() ? (_client->*_method) ((Sponsor&) sponsor, _code) : FALSE;
}

template <class Sponsor, class Client>
inline CL_String CL_Binding2<Sponsor, Client>::AsString() const
{
    CL_String s;
    s.AssignWithFormat ("CL_Binding2: object %08x", _client);
    return s;
}



#endif
