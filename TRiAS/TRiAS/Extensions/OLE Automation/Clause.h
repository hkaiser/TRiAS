///////////////////////////////////////////////////////////////////////////////
// Clause.h

#if !defined(_CLAUSE_H__79A32154_6740_11D1_9731_00A024D6F582__INCLUDED_)
#define _CLAUSE_H__79A32154_6740_11D1_9731_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// ExecuteModi
typedef enum tagEXECUTEMODE {
	EXECUTEMODE_Default = 0x00,		// StandardOperation
	EXECUTEMODE_Exists = 0x01,		// Existenz testen
	EXECUTEMODE_Equal = 0x02,		// Gleichheit
	EXECUTEMODE_Like = 0x03,		// Ähnlichkeit
	EXECUTEMODE_RegExpr = 0x04,		// regular expression matching
	EXECUTEMODE_And = 0x05,			// logisches UND
	EXECUTEMODE_Or = 0x06,			// logisches ODER
	EXECUTEMODE_OpMask = 0x0F,		// alles bisherige zusammen

	EXECUTEMODE_Negate = 0x10,		// GegenListe bilden
} EXECUTEMODE;

///////////////////////////////////////////////////////////////////////////////
// ResultTypen
typedef enum tagRESULTTYPE {
	RESULTTYPE_Error = -1,
	RESULTTYPE_EnumObjectsByNumer = 0,
	RESULTTYPE_Objectproperty = 1,
} RESULTTYPE;

///////////////////////////////////////////////////////////////////////////////
// BasisKlasse des ErgebnisObjektes
class clause_rslt_obj 
{
public:
    clause_rslt_obj (RESULTTYPE rgType = RESULTTYPE_Error, IUnknown *pIUnk = NULL);
    virtual ~clause_rslt_obj();

	bool IsValid() { return m_fIsValid; }

protected:
    RESULTTYPE m_rgType;
	WUnknown m_Unk;
	bool m_fIsValid;
};
typedef clause_rslt_obj *clause_rslt_ptr;

///////////////////////////////////////////////////////////////////////////////
// ErgebnisObjekt eines Term - tokens
class term_rslt_obj :
	public clause_rslt_obj 
{
public:
    term_rslt_obj (clause_rslt_ptr objprop, string_ptr strconst, EXECUTEMODE rgMode);
    term_rslt_obj (clause_rslt_ptr term1, clause_rslt_ptr term2, EXECUTEMODE rgMode);
    virtual ~term_rslt_obj();
};

///////////////////////////////////////////////////////////////////////////////
// ErgebnisObjekt einer ObjektEigenschaft (OBJPROPNAME)
class objprop_rslt_obj :
	public clause_rslt_obj 
{
public:
    objprop_rslt_obj (string_ptr objpropname);
    virtual ~objprop_rslt_obj();
};

#endif // !defined(_CLAUSE_H__79A32154_6740_11D1_9731_00A024D6F582__INCLUDED_)
