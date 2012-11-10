//==============================================================================
// Public domain variant streaming code.
// By Kenneth Kasajian (kasajian@simply-solutions.com)
// Special thanks to Gorti, Durgaprasad (durgaprasad.gorti@intel.com)
//
// Variant streaming code.  Use global methods WriteVariantToStream and
// ReadVariantFromStream
//==============================================================================

#pragma once

#include <atlbase.h>


//==============================================================================
// COM support code (from comvector.h)
//==============================================================================

#ifndef HR
#define HR(_ex) { HRESULT _hr = _ex; if( FAILED(_hr) ) return _hr; }
#endif


//==============================================================================
// namespace VariantStreaming
// Internal namespace used to keep support calls in this header file private.
//==============================================================================

namespace VariantStreaming
{


//==============================================================================
// Prototype
//==============================================================================

inline HRESULT  WriteDataToStream( const VARIANT* variant, IStream* pStream );
inline HRESULT  ReadDataFromStream( VARTYPE vt, IStream* pStream, CComVariant& variant );



//==============================================================================
// Types
//==============================================================================

const long variantVersion = 1;


//==============================================================================
// CWalkSafeArrayElements
// Walks the elements of a multi-dimensional safe array.  Array must have at
// least one element.
// Example:
//      bool more = true;
//
//      CWalkSafeArrayElements  walk( safeArray );
//
//      // Walk the list.
//      while( more )
//          {
//          ... walk.GetIndex( index ) ...
//
//          more = walk.Next();
//          }
//==============================================================================

class CWalkSafeArrayElements
{
public:
    CWalkSafeArrayElements( SAFEARRAY* safeArray )
        :   m_SafeArray( safeArray ),
            m_index( NULL ),
            m_isInitialized( false )
    {
    }
    
    inline ~CWalkSafeArrayElements()
    {
        ::CoTaskMemFree( m_index );
    }
    
    inline HRESULT GetIndex( long*& index )
    {
        if ( !m_isInitialized )
            HR( Initialize() );

        index = m_index;
        return S_OK;
    }
    
    HRESULT Next( bool& more )
    {
        if ( !m_isInitialized )
            HR( Initialize() );

        more = false;
        
        // Increment the index and determine if we've hit the end.
        for ( int dimension = 0; dimension < m_SafeArray->cDims; dimension++ )
        {
            m_index[m_SafeArray->cDims - dimension - 1]++;
            
            if (    m_index[m_SafeArray->cDims - dimension - 1] >=
                m_SafeArray->rgsabound[dimension].lLbound + (long)m_SafeArray->rgsabound[dimension].cElements )
            {
                m_index[m_SafeArray->cDims - dimension - 1] = m_SafeArray->rgsabound[dimension].lLbound;
            }
            else
            {
                more = true;
                break;
            }
        }
        
        return S_OK;
    }

private:
    HRESULT Initialize()
    {
        // Allocate an index
        m_index = (long*)::CoTaskMemAlloc( m_SafeArray->cDims * sizeof( long ) );
        if ( !m_index )
            HR( E_OUTOFMEMORY );
        
        // Initialize the index.
        for ( int dimension = 0; dimension < m_SafeArray->cDims; dimension++ )
            m_index[m_SafeArray->cDims - dimension - 1] = m_SafeArray->rgsabound[dimension].lLbound;

        m_isInitialized = true;

        return S_OK;
    }
    
private:
    bool                m_isInitialized;
    SAFEARRAY*          m_SafeArray;
    long*               m_index;
    
}; // class CWalkSafeArrayElements


//==============================================================================
// Wrapper for IStream.  Supplies template Read and Write method so that 
// data sizes are automatically calculated.  Standard overload assumes
// an intrinsic type and uses the & operator on the parameter to to get to the data
// to be read or written and the sizeof operator on the parameter to determine
// the size of the data to be read or written.
// A BSTR operator is supplied for reading and writing strings.
// Example:
//        IStream*    pStream = ...;
//        ...
//        CStream     stream( pStream );
//    
//        stream.Write( longVal );
//        stream.Write( shortVal );
//        stream.Write( floatVal );
//        stream.Write( bstrVal );
//        stream.Write( (BSTR)CComBSTR( lpszStringVal ) );
//    
// ToDo:
//   Could add support for LPCSTR, LPWSTR, string and wstring.
//==============================================================================

class CStream
{
public:
    //------------------------------------------------------------------------------
    // Construct using an IStream pointer
    //------------------------------------------------------------------------------
    
    inline CStream( IStream* stream )
        :   stream( stream )
    {
    }
    
    //------------------------------------------------------------------------------
    // Alows code to get the IStream pointer.
    //------------------------------------------------------------------------------
    
    inline operator IStream*()
    {
        return stream;
    }
    
    
    //------------------------------------------------------------------------------
    // Template method that will write any data type that supports & to return
    // the address of the data and sizeof that will return the size of the data.
    //------------------------------------------------------------------------------
    
    template <class Q>
    inline HRESULT Write( Q value )
    {
        ULONG   written;
        HR( stream->Write( &value, sizeof( value ), &written ) );
        if ( written != sizeof( value ) )
            HR( E_FAIL );

        return S_OK;
    }
    
    
    //------------------------------------------------------------------------------
    // Special code for writing BSTRs
    //------------------------------------------------------------------------------
    
    inline HRESULT Write( BSTR value )
    {
        ULONG   written;
        UINT    bufferSize = ::SysStringLen( value ) * sizeof( WCHAR );
        
        HR( Write( bufferSize ) );
        HR( stream->Write( value, bufferSize, &written ) );
        if ( written != bufferSize )
            HR( E_FAIL );

        return S_OK;
    }
    
    
    //------------------------------------------------------------------------------
    // Template method that will read any data type that supports & to return
    // the address of the data and sizeof that will return the size of the data.
    //------------------------------------------------------------------------------
    
    template <class Q>
    inline HRESULT Read( Q& value )
    {
        ULONG   read;
        HR( stream->Read( &value, sizeof( value ), &read ) );
        if ( read != sizeof( value ) )
            HR( E_FAIL );

        return S_OK;
    }
    
    
    //------------------------------------------------------------------------------
    // Special code for reading BSTRs
    //------------------------------------------------------------------------------
    
    inline HRESULT Read( BSTR* value )
    {
        ULONG   read;
        UINT    bufferSize;
        
        HR( Read( bufferSize ) );
        LPWSTR buf = (LPWSTR)_alloca( bufferSize );
        HR( stream->Read( buf, bufferSize, &read ) );
        if ( read != bufferSize )
            HR( E_FAIL );

        UINT len = bufferSize / sizeof( WCHAR );
        buf[len] = L'\0';
        *value = ::SysAllocStringLen( buf, len );
        if ( !*value )
            HR( E_OUTOFMEMORY );

        return S_OK;
    }

private:
    // If these get accessed, change your code to explicitly cast the parameter to
    // a BSTR for writes and BSTR* for reads.
    HRESULT Write( CComBSTR value );
    HRESULT Read( CComBSTR* value );
    
private:
    CComPtr<IStream>    stream;
    
}; // class CStream


//------------------------------------------------------------------------------
// SafeArrayGetElementAsVariant
// Like SafeArrayGetElement, but returns the element value as a VARIANT.
//------------------------------------------------------------------------------

inline HRESULT SafeArrayGetElementAsVariant(    SAFEARRAY*      safeArray,
                                                long*           index,
                                                VARTYPE         vt,
                                                CComVariant&    variant )
{
    void*           entry;
    void*           element;

    // Allocate enough room to hold a single element of the array.
    element = _alloca( safeArray->cbElements );

    // Get the elemnt from the array.
    HR( SafeArrayGetElement( safeArray, index, element ) );

    // If it's a string, assign the string to the variant.
    if ( ( safeArray->fFeatures & FADF_BSTR ) == FADF_BSTR )
    {
        if ( VT_BSTR != vt )
            HR( DISP_E_TYPEMISMATCH );
    
        if ( sizeof( BSTR ) != safeArray->cbElements )
            HR( E_INVALIDARG );
    
        entry = *(void**)(void*)element;
        variant = (BSTR) (void*)entry;
    }
    // If it's a generic COM object, assign the IUnknown to the variant.
    else if ( ( safeArray->fFeatures & FADF_UNKNOWN ) == FADF_UNKNOWN )
    {
        if ( VT_UNKNOWN != vt )
            HR( DISP_E_TYPEMISMATCH );
    
        if ( sizeof( IUnknown* ) != safeArray->cbElements )
            HR( DISP_E_TYPEMISMATCH );
    
        entry = *(void**)(void*)element;
        variant = (IUnknown*)entry;
    }
    // If it's an Automation object, assign the IDispatch to the variant.
    else if ( ( safeArray->fFeatures & FADF_DISPATCH ) == FADF_DISPATCH )
    {
        if ( VT_DISPATCH != vt )
            HR( DISP_E_TYPEMISMATCH );
    
        if ( sizeof( IDispatch* ) != safeArray->cbElements )
            HR( DISP_E_TYPEMISMATCH );
    
        entry = *(void**)(void*)element;
    
        variant = (IDispatch*)entry;
    }
    // If the element itself is another variant, assign a dereferenced version
    // to the variant.
    else if ( ( safeArray->fFeatures & FADF_VARIANT ) == FADF_VARIANT )
    {
        if ( VT_VARIANT != vt )
            HR( DISP_E_TYPEMISMATCH );
    
        if ( sizeof( VARIANT ) != safeArray->cbElements )
            HR( DISP_E_TYPEMISMATCH );
    
        entry = element;
    
        HR( VariantCopyInd( &variant, (VARIANT*)entry ) );
    }
    // If it's a simple type, assign it based on the type.
    else
    {
        entry = element;
    
        switch( vt )
        {
        case VT_ERROR:
            variant.scode = *(SCODE*) entry;
            break;
        
        case VT_I4:
            variant.lVal = *(long*) entry;
            break;
        
        case VT_UI1:
            variant.bVal = *(BYTE*) entry;
            break;
        
        case VT_I2:
            variant.iVal = *(short*) entry;
            break;
        
        case VT_BOOL:
#pragma warning(disable: 4310) // cast truncates constant value
		    variant.boolVal = *(VARIANT_BOOL*) entry ? VARIANT_TRUE : VARIANT_FALSE;
#pragma warning(default: 4310) // cast truncates constant value
            break;
        
        case VT_R8:
            variant.dblVal = *(double*) entry;
            break;
        
        case VT_DATE:
            variant.date = *(DATE*) entry;
            break;
        
        case VT_R4:
            variant.fltVal = *(float*) entry;
            break;
        
        case VT_CY:
            variant.cyVal = *(CY*)entry;
        
        default:
            HR( DISP_E_TYPEMISMATCH );
        }
    
        // Set the variant's data type.
        variant.vt = vt;
    }

    // Return the variant to the caller.    
    return S_OK;

} // SafeArrayGetElementAsVariant


//------------------------------------------------------------------------------
// SafeArrayPutElementFromVariant
// Like SafeArrayPutElement, except that it gets the element's value from the
// variant
//------------------------------------------------------------------------------

inline HRESULT SafeArrayPutElementFromVariant(  SAFEARRAY*          safeArray,
                                                long*               index,
                                                const VARIANT&      variant )
{
    const void*     element = NULL;

    // If the array element type itself is a variant, then we just use
    // that variant directly.
    if ( ( safeArray->fFeatures & FADF_VARIANT ) == FADF_VARIANT )
    {
        element = &variant;
    }
    else
    {
        // Based on the data type of the variant, we obtain a direct reference
        // to the variant's data
        switch ( VT_TYPEMASK & variant.vt )
        {
        case VT_BSTR:
        case VT_UNKNOWN:
        case VT_DISPATCH:
            element = variant.byref;
            break;
        
        case VT_VARIANT:
            element = variant.pvarVal;
            break;
        
        case VT_ERROR:
        case VT_I4:
        case VT_UI1:
        case VT_I2:
        case VT_BOOL:
        case VT_R8:
        case VT_DATE:
        case VT_R4:
        case VT_CY:
            element = &variant.byref;
            break;
        
        default:
            HR( DISP_E_TYPEMISMATCH );
        }
    }

    // Put the element into the array.
    HR( SafeArrayPutElement( safeArray, index, const_cast<void*>( element ) ) );

    return S_OK;

} // SafeArrayPutElementFromVariant


//------------------------------------------------------------------------------
// GetTypeSize
// Given a variant type, determines how many bytes it takes to store data of
// that type.
//------------------------------------------------------------------------------

inline HRESULT GetTypeSize( VARTYPE vt, ULONG& size )
{
    switch ( vt ) 
    {
    case VT_BOOL:
        size = sizeof( VARIANT_BOOL );
        break;
    
    case VT_I2:
        size = sizeof( short );
        break;
    
    case VT_ERROR:
        size = sizeof( SCODE );
        break;
    
    case VT_I4:
        size = sizeof( long );
        break;
    
    case VT_BSTR:
        size = sizeof( BSTR );
        break;
    
    case VT_R4:
        size = sizeof( float );
        break;
    
    case VT_DATE:
        size = sizeof( DATE );
        break;
    
    case VT_R8:
        size = sizeof( double );
        break;
    
    case VT_UI1:
        size = sizeof( BYTE );
        break;
    
    case VT_CY:
        size = sizeof( CY );
        break;
    
    case VT_VARIANT:
        size = sizeof( VARIANT );
        break;
    
    case VT_DISPATCH:
        size = sizeof( IDispatch* );
        break;
    
    case VT_UNKNOWN:
        size = sizeof( IUnknown* );
        break;
    
    default:
        HR( DISP_E_TYPEMISMATCH );
    }

    return S_OK;

} // GetTypeSize


//------------------------------------------------------------------------------
// WriteSafeArrayHeader
// Writes the array's header information, such as the number of dimensions
// and the bounds of each dimension (lower/upper)
//------------------------------------------------------------------------------

inline HRESULT WriteSafeArrayHeader( SAFEARRAY* safeArray, IStream* pStream )
{
    unsigned int        dimension;
    CStream             stream( pStream );

    // Write out the dimension count
    HR( stream.Write( safeArray->cDims ) );

    // Write out the lower bound and the number of elements in each dimension.
    for ( dimension = 0; dimension < safeArray->cDims; dimension++ )
    {
        HR( stream.Write( safeArray->rgsabound[dimension].lLbound ) );
        HR( stream.Write( safeArray->rgsabound[dimension].cElements ) );
    }

    return S_OK;

} // WriteSafeArrayHeader


//------------------------------------------------------------------------------
// ReadSafeArrayHeader
//------------------------------------------------------------------------------

inline HRESULT ReadSafeArrayHeader( VARIANT* variant, VARTYPE vt, IStream* pStream )
{
    unsigned short      dimensions;
    unsigned short      dimension;
    CStream             stream( pStream );

    // Read the dimension count
    HR( stream.Read( dimensions ) );

    HR( SafeArrayAllocDescriptor( dimensions, &variant->parray ) );

    // Read the lower bound and the number of elements in this dimension.
    for ( dimension = 0; dimension < dimensions; dimension++ )
    {
        HR( stream.Read( variant->parray->rgsabound[dimension].lLbound ) );
        HR( stream.Read( variant->parray->rgsabound[dimension].cElements ) );
    }

    // Set the element size.
    HR( GetTypeSize( vt, variant->parray->cbElements ) );

    // Set the features mask.
    switch ( vt )
    {
    case VT_BSTR:
        variant->parray->fFeatures |= FADF_BSTR;
        break;
    
    case VT_UNKNOWN:
        variant->parray->fFeatures |= FADF_UNKNOWN;
        break;
    
    case VT_DISPATCH:
        variant->parray->fFeatures |= FADF_DISPATCH;
        break;
    
    case VT_VARIANT:
        variant->parray->fFeatures |= FADF_VARIANT;
        break;
    }

    HR( SafeArrayAllocData( variant->parray ) );

    // Set variant's type
    variant->vt = (VARTYPE) ( vt | VT_ARRAY );

    return S_OK;

} // ReadSafeArrayHeader



//------------------------------------------------------------------------------
// WriteSafeArrayElements
// Walks the elements of a multi-dimensional safe array, streaming each
// element out.
//------------------------------------------------------------------------------

inline HRESULT WriteSafeArrayElements( VARTYPE vt, SAFEARRAY* safeArray, IStream* pStream )
{
    bool                more = true;
    long*               index;
    CComVariant         tempVariant;
    CStream             stream( pStream );

    CWalkSafeArrayElements  walk( safeArray );

    // Walk the list.
    while( more )
    {
        // Get the variant for this element and stream it out.
        HR( walk.GetIndex( index ) );
        HR( SafeArrayGetElementAsVariant( safeArray, index, vt, tempVariant ) );
        HR( WriteDataToStream( &tempVariant, stream ) );
    
        // Increment the index and determine if we've hit the end.
        HR( walk.Next( more ) );
    }

    return S_OK;

} // WriteSafeArrayElements



//------------------------------------------------------------------------------
// ReadSafeArrayElements
// Read the elements from the stream into the safe array.
//------------------------------------------------------------------------------

inline HRESULT ReadSafeArrayElements( VARTYPE vt, SAFEARRAY* safeArray, IStream* stream )
{
    bool        more = true;
    long*       index;
    CComVariant tempVariant;

    CWalkSafeArrayElements  walk( safeArray );

    // Walk the list.
    while( more )
    {
        // Get the variant from the stream and put it in the array as an element.
        HR( ReadDataFromStream( vt, stream, tempVariant ) );
        HR( walk.GetIndex( index ) );
        HR( SafeArrayPutElementFromVariant( safeArray, index, tempVariant ) );
    
        // Increment the index and determine if we've hit the end.
        HR( walk.Next( more ) );
    }

    return S_OK;

} // ReadSafeArrayElements


//------------------------------------------------------------------------------
// GetPersistStreamInterface
// Get IPersistStream for the given object.
//------------------------------------------------------------------------------

inline HRESULT GetPersistStreamInterface( IUnknown* pUnknown, IPersistStream** ppPersistStream )
{
    CComPtr<IPersistStreamInit>     persistStreamInit;
    CComPtr<IPersistStream>         persistStream;
    HRESULT                         hr;

    // See if the object supports IPersistStreamInit.
    hr = pUnknown->QueryInterface( &persistStreamInit );
    if ( FAILED( hr ) && E_NOINTERFACE != hr )
        return hr;

    // If the object doesn't support IPersistStreamInit, see
    // if supports IPersistStream
    if ( !persistStreamInit )
    {
        hr = pUnknown->QueryInterface( &persistStream );
        if ( FAILED( hr ) && E_NOINTERFACE != hr )
            return hr;
    }

    // Return either IPersistStreamInit or IPersistStream, whichever
    // one was retrieved.  Since these interfaces are binary
    // compatible, we can use the same pointer to refer to either.
    if ( persistStream )
        *ppPersistStream = persistStream.Detach();
    else
        *ppPersistStream = (IPersistStream*)persistStreamInit.Detach();

    return S_OK;

} // GetPersistStreamInterface


//------------------------------------------------------------------------------
// SaveObjectToStream
// Wrapper for OleSaveToStream.  Difference is that this function
// takes an IUnknown instead of an IPersistStream and uses the IUnknown
// to get an IPersistStream using GetPersistStreamInterface, which is
// smart enough to QI for both IPersistStreamInit and IPersistStream.
// As with OleSaveToStream, the object pointer may be NULL.
//------------------------------------------------------------------------------

inline HRESULT SaveObjectToStream( IUnknown* pUnknown, IStream* pStream )
{
    CComPtr<IPersistStream>       persistStream;

    // Get IPersistStream interface for the object. 
    if ( pUnknown )
    {
        HR( GetPersistStreamInterface( pUnknown, &persistStream ) );

        // If we didn't get IPersistStream, then fail.  For now,
        // these are the only two interfaces we're supporting.
        // Later, we can add support for others such as IStorage,
        // IPersistMemory, IPersistStorage, IPersistPropertyBag, etc.
        if ( !persistStream )
            return E_NOINTERFACE;
    }

    // Save the object to the stream.
    HR( OleSaveToStream( persistStream, pStream ) );

    return S_OK;
    
} // SaveObjectToStream


//------------------------------------------------------------------------------
// WriteDataToStream
// Writes the given variant's data to the stream.
// Used by WriteToStream.
// The passed in variant is assumed to be fully dereferenced (i.e. no VT_BYREF)
//------------------------------------------------------------------------------

inline HRESULT WriteDataToStream( const VARIANT* variant, IStream* pStream )
{
    SAFEARRAY*          safeArray;
    IDispatch*          pDispatch;
    CComPtr<IUnknown>   unknown;
    CStream             stream( pStream );

    if ( !variant )
        HR( E_POINTER );

    // If it's an array write out individual value.
    if ( V_ISARRAY( variant ) )
    {
        // Get the array.
        if ( V_ISBYREF( variant ) )
            safeArray = *variant->pparray;
        else
            safeArray = variant->parray;
    
        HR( WriteSafeArrayHeader( safeArray, stream ) );
    
        // Write out the safe array elements.
        HR( WriteSafeArrayElements( (VARTYPE)( VT_TYPEMASK & variant->vt ), safeArray, stream ) );
    }
    // It's not an array, so write the individual value
    else
    {
        switch ( variant->vt )
        {
        case VT_EMPTY:
        case VT_NULL:
            break;
        
        case VT_BOOL:
            // A VARIANT_BOOL is 16 bits.
            HR( stream.Write( V_BOOL( variant ) ) );
            break;
        
        case VT_UI1:
            HR( stream.Write( V_UI1( variant ) ) );
            break;
        
        case VT_I2:
            HR( stream.Write( V_I2( variant ) ) );
            break;
        
        case VT_I4:
            HR( stream.Write( V_I4( variant ) ) );
            break;
        
        case VT_CY:
            HR( stream.Write( variant->cyVal.Lo ) );
            HR( stream.Write( variant->cyVal.Hi ) )
            break;
        
        case VT_R4:
            HR( stream.Write( V_R4( variant ) ) );
            break;
        
        case VT_R8:
            HR( stream.Write( V_R8( variant ) ) );
            break;
        
        case VT_DATE:
            // A Variant DATE is a double.
            HR( stream.Write( V_DATE( variant ) ) );
            break;
        
        case VT_BSTR:
            HR( stream.Write( V_BSTR( variant ) ) );
            break;
        
        case VT_ERROR:
            HR( stream.Write( V_ERROR( variant ) ) );
            break;
        
        case VT_DISPATCH:
            pDispatch = V_DISPATCH( variant );
            if ( pDispatch )
                HR( pDispatch->QueryInterface( &unknown ) );

            HR( SaveObjectToStream( unknown, stream ) );
            break;

        case VT_UNKNOWN:
            HR( SaveObjectToStream( V_UNKNOWN( variant ), stream ) );
            break;

        default:
            HR( DISP_E_TYPEMISMATCH );
        }
    }

    return S_OK;

} // WriteDataToStream


//------------------------------------------------------------------------------
// WriteToStream
// Writes the given variant to the stream.
// First writes out the data type of the variant followed by the 
// variant's data.
//------------------------------------------------------------------------------

inline HRESULT WriteToStream( const VARIANT* variantParam, IStream* pStream )
{
    CComVariant     variantCopy;
    const VARIANT*  variant;
    CStream         stream( pStream );

    if ( !variantParam )
        HR( E_POINTER );

    // Use dereferenced copy if incoming is byref.
    if ( V_ISBYREF( variantParam ) )
    {
        HR( VariantCopyInd( &variantCopy, (VARIANT*) variantParam ) );
        variant = &variantCopy;
    }
    else
    {
        variant = variantParam;
    }

    // Write the VT type.
    HR( stream.Write( variant->vt ) );

    // Write out the actual data.
    HR( WriteDataToStream( variant, pStream ) );

    return S_OK;

} // WriteToStream


//------------------------------------------------------------------------------
// ReadDataFromStream
// Given the variant's data type, reads the variant's data from the stream.
//------------------------------------------------------------------------------

inline HRESULT ReadDataFromStream( VARTYPE vt, IStream* pStream, CComVariant& variant )
{
    CComPtr<IUnknown>       unknown;
    CComPtr<IDispatch>      dispatch;
    CStream                 stream( pStream );

    // If it's a blob, then read it in as an array of bytes, otherwise read
    // individual value.
    if ( vt & VT_ARRAY )
    {
        VARTYPE elementVT = (VARTYPE) ( VT_TYPEMASK & vt );

        // Read the variant header.
        HR( ReadSafeArrayHeader( &variant, elementVT, stream ) );
    
        // Read the elements from the stream.
        HR( ReadSafeArrayElements( elementVT, variant.parray, stream ) );
    }
    // It's not an array, so read the individual value
    else
    {
        switch ( vt )
        {
        case VT_EMPTY:
        case VT_NULL:
            break;
        
        case VT_BOOL:
            // A VARIANT_BOOL is 16 bits.
            HR( stream.Read( V_BOOL( &variant ) ) );
            break;
        
        case VT_UI1:
            HR( stream.Read( V_UI1( &variant ) ) );
            break;
        
        case VT_I2:
            HR( stream.Read( V_I2( &variant ) ) );
            break;
        
        case VT_I4:
            HR( stream.Read( V_I4( &variant ) ) );
            break;
        
        case VT_CY:
            HR( stream.Read( variant.cyVal.Lo ) );
            HR( stream.Read( variant.cyVal.Hi ) );
            break;
        
        case VT_R4:
            HR( stream.Read( V_R4( &variant ) ) );
            break;
        
        case VT_R8:
            HR( stream.Read( V_R8( &variant ) ) );
            break;
        
        case VT_DATE:
            HR( stream.Read( V_DATE( &variant ) ) );
            break;
        
        case VT_BSTR:
            HR( stream.Read( &variant.bstrVal ) );
            break;
        
        case VT_ERROR:
            HR( stream.Read( V_ERROR( &variant ) ) );
            break;
        
        case VT_DISPATCH:
            HR( OleLoadFromStream( pStream, IID_IUnknown, (void**)(IUnknown*)&unknown ) );
            HR( unknown->QueryInterface( &dispatch ) );
            V_DISPATCH( &variant ) = dispatch.Detach();
            break;

        case VT_UNKNOWN:
            HR( OleLoadFromStream( pStream, IID_IUnknown, (void**)(IUnknown*)&unknown ) );
            V_UNKNOWN( &variant ) = unknown.Detach();
            break;
        
        default:
            HR( DISP_E_TYPEMISMATCH );
        }
    
        variant.vt = vt;
    }

    return S_OK;

} // ReadDataFromStream


//------------------------------------------------------------------------------
// ReadFromStream
// Reads the variant from the stream.
// First reads the variant's data type and then calls ReadDataFromStream
// to read the variant's data.
//------------------------------------------------------------------------------

inline HRESULT ReadFromStream( IStream* pStream, CComVariant& variant )
{
    VARTYPE             vt;
    CStream             stream( pStream );

    // Read the VT type.
    HR( stream.Read( vt ) );

    return ReadDataFromStream( vt, pStream, variant );

} // ReadFromStream


} // namespace VariantStreaming


//------------------------------------------------------------------------------
// WriteVariantToStream
// Writes the given variant to the stream.
//------------------------------------------------------------------------------

inline HRESULT WriteVariantToStream( const VARIANT* variant, IStream* pStream )
{
    // Write the version number of this class.
    HR( VariantStreaming::CStream( pStream ).Write( VariantStreaming::variantVersion ) );

    // Call the main routine to write a variant from the stream.
    return VariantStreaming::WriteToStream( variant, pStream );

} // WriteVariantToStream


//------------------------------------------------------------------------------
// ReadVariantFromStream
// The passed in variant should be initialized.
//------------------------------------------------------------------------------

inline HRESULT ReadVariantFromStream( IStream* pStream, CComVariant& variant )
{
    long    version;

    // Read the version.  If the version is later needed by the reading
    // code, it can be passed as parameter to ReadFromStream, and
    // internally in ReadSafeArrayElements.
    HR( VariantStreaming::CStream( pStream ).Read( version ) );

    // Call the main routine to read a variant from the stream.
    return VariantStreaming::ReadFromStream( pStream, variant );

} // ReadVariantFromStream
