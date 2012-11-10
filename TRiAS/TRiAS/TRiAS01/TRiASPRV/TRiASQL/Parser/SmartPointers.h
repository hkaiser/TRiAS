// smartptr.cpp : Defines the entry point for the console application.
//
#ifndef __SMARTPOINTERS_H
#define __SMARTPOINTERS_H

#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include "StdString.h"


class CObject;
CObject *SHPtrAssign(CObject** pp, CObject* lp);

template <class T>
class SHPtr
{
public:
	typedef T _PtrClass;
	SHPtr() {p=NULL;}
	SHPtr(T* lp)
	{
		if ((p = lp) != NULL)
			p->AddRef();
	}
	SHPtr(const SHPtr<T>& lp)
	{
		if ((p = lp.p) != NULL)
			p->AddRef();
	}
	~SHPtr() {if (p) p->Release();}
	void Release() {if (p) p->Release(); p=NULL;}
	operator T*() {return (T*)p;}
	T& operator*() {assert(p!=NULL); return *p; }
	//The assert on operator& usually indicates a bug.  If this is really
	//what is needed, however, take the address of the p member explicitly.
	T** operator&() { assert(p==NULL); return &p; }
	T* operator->() { assert(p!=NULL); return p; }
	T* operator=(T* lp){return (T*)SHPtrAssign((CObject**)&p, lp);}
	T* operator=(const SHPtr<T>& lp)
	{
		return (T*)SHPtrAssign((CObject**)&p, lp.p);
	}
#if _MSC_VER>1020
	bool operator!(){return (p == NULL);}
#else
	BOOL operator!(){return (p == NULL) ? TRUE : FALSE;}
#endif
	T* p;


	static T *CreateObject()
		{
		return new T;
		}

};



class CObject
{
public:
	CObject()
		{
		m_lRefCount = 0;
		}
	virtual ~CObject()
		{
		//printf("Deleting CObject\n");
		}
	long AddRef()
		{
		return InterlockedIncrement(&m_lRefCount);
		}
	long Release()
		{
		long lRet = InterlockedDecrement(&m_lRefCount);
		if ( lRet == 0 )
			delete this;
		return lRet;
		}
protected:
	long m_lRefCount;
};

template <class T>
class CObArrayTempl : public CObject
{
public:
	typedef vector<T> CListType;
	~CObArrayTempl()
		{
		RemoveAll();
		}

	bool IsEmpty()
		{
		return GetSize() == 0;
		}

	T GetTail()
		{
		if ( !GetSize() )
			return NULL;
		T pRet = m_List.back();
		return T;
		}

	T GetAt( int nIndex )
		{
		if ( nIndex >= GetSize() )
			return NULL;
		T pRet = m_List[ nIndex ];
		return pRet;
		}


	T RemoveTail()
		{
		if ( !GetSize() )
			return NULL;
		T pRet = m_List.back();
		m_List.erase( m_List.end()  -1 );
		pRet->Release();
		return pRet;
		}

	void AddTail( T pPointer )
		{
		pPointer->AddRef();
		m_List.push_back( pPointer );
		}
	void Add( T pPointer )
		{
		AddTail( pPointer );
		}

	void RemoveAll()
		{
		m_List.erase( m_List.begin(), m_List.end() );
		}
	int GetSize()
		{
		return m_List.size();
		}
	int GetUpperBound()
		{
		return GetSize()-1;
		}
protected:
	CListType m_List;
};


template <class T>
class CMapStringToObjectPtrTempl : public CObject
{
public:
	typedef map<CString, T> CListType;
	~CMapStringToObjectPtrTempl()
		{
		RemoveAll();
		}

	bool IsEmpty()
		{
		return GetSize() == 0;
		}

	T Lookup( CString strKey )
		{
		CListType::iterator theIterator = m_List.find( strKey );
		if ( theIterator == m_List.end() )
			return NULL;
		T pRet = (*theIterator).second;
		return pRet;
		}

	bool SetAt( CString strKey, T pPointer )
		{
		pair<CListType::iterator,bool> RetPair = m_List.insert( CListType::value_type( strKey, pPointer ) );
		return RetPair.second;
		}

	T GetAtIndex( int nIndex )
		{
		CListType::iterator theIterator;

		for ( theIterator = m_List.begin(); theIterator != m_List.end(); 
					theIterator++ )
			{
			ATLTRACE( "%s\n", (const char *)(*theIterator).first );
			if ( nIndex == 0 )
				{
				T pRet = (*theIterator).second;
				return pRet;
				}
			nIndex--;
			}

		return NULL;
		}



	void RemoveAll()
		{
		m_List.erase( m_List.begin(), m_List.end() );
		}
	int GetSize()
		{
		return m_List.size();
		}
	int GetUpperBound()
		{
		return GetSize()-1;
		}
protected:
	CListType m_List;
};




inline CObject *SHPtrAssign(CObject** pp, CObject* lp)
{
	if (lp != NULL)
		lp->AddRef();
	if (*pp)
		(*pp)->Release();
	*pp = lp;
	return lp;
}






typedef	SHPtr<CObject> CObjectPtr;
typedef	CObArrayTempl<CObject> CObjectArray;
#define _SH_SMARTPTR(Interface) \
			typedef SHPtr< Interface > \
			Interface ## Ptr

//#define _SH_SMARTPTR_ARRAY(Interface) \
//			typedef CObArrayTempl< SHPtr<Interface> > \
//			Interface ## PtrArray
//
//
#define _SH_SMART_ARRAY(Interface) \
			typedef CObArrayTempl< Interface *> \
			Interface ## Array


//
//class CSQLNode : public CObject
//{
//public:
//	~CSQLNode()
//		{
//		printf("Deleting\n");
//		}	
//	void SetText( const char *szText )
//		{
//		strcpy( m_szText, szText );
//		}
//	char m_szText[20];
//};
//
//class CDerivedSQLNode : public CSQLNode
//{
//public:
//	~CDerivedSQLNode()
//		{
//		printf("Derived\n");
//		}
//};
//
//
//_SH_SMARTPTR( CSQLNode );
//_SH_SMART_ARRAY( CSQLNode );
//_SH_SMARTPTR( CDerivedSQLNode );
//
//typedef CMapStringToObjectPtrTempl<CSQLNodePtr> CSQLNodeMap;
//
//void Test()
//{
//	CSQLNodeArray Array;
//
//	CSQLNodePtr pNode;
//	CSQLNodeMap Map;
//	
//	
//	pNode = CSQLNodePtr::CreateObject();
//	pNode->SetText( "Nummer ett" );
//	Array.Add( pNode );
//	pNode = CSQLNodePtr::CreateObject();
//	pNode->SetText( "Nummer två" );
//	Array.Add( pNode );
//
//
//	CDerivedSQLNodePtr pDer = CDerivedSQLNodePtr::CreateObject();
//	Array.Add( pDer );
//
//
//	Map.SetAt( "Test!", pNode );
//	pNode = Map.Lookup( "Test!" );
//	pNode = Map.Lookup( "Test1111!" );
//
//	pNode = CSQLNodePtr::CreateObject();
//	pNode->SetText( "Nummer tre" );
//	Array.Add( pNode );
//
//	for ( int i = 0; i < Array.GetSize(); i++ )
//		{
//		pNode = Array.GetAt( i );
//		printf( "%s\n", pNode->m_szText );
//		}
//	pNode = Array.RemoveTail();
//	pDer = NULL;
//	pNode = Array.RemoveTail();	  
//	pNode = Array.RemoveTail();
//}
//
//
//
//int main(int argc, char* argv[])
//{
//	CString strHej;
//	strHej = "1";
//	strHej += "hopp";
//
//
//	printf( "%s\n", ( const char *)strHej );
//	//Map.SetAt( "Hej", ObjPtr );
//	//ObjPtr = ( CMyObject *)Map.Lookup( "Hej" );
//	Test();
//	return 0;
//}


#endif

