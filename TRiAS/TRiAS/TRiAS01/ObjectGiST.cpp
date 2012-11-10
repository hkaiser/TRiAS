// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 25.01.2003 12:25:22 
//
// @doc
// @module ObjectGiST.cpp | Definition of the <c CObjectGiST> class

#include "trias01p.hxx"

#if defined(_USE_CONNECTFILTER)

#include "ObjectGiST.h"

///////////////////////////////////////////////////////////////////////////////
// 
CObjectGiST::CObjectGiST(CONNECTFILTER *pFilter)
{
// alle Stützstrecken des Filters einfügen
	if (pFilter->m_lCnt <= 3 ||									// Polygonzug ist entartet
		pFilter->m_pX[0] != pFilter->m_pX[pFilter->m_lCnt-1] || 
		pFilter->m_pY[0] != pFilter->m_pY[pFilter->m_lCnt-1])	// Polygonzug ist nicht geschlossen
	{
		return;
	}

char cbTempPath[_MAX_PATH];
char cbTempFileName[_MAX_PATH];

	if (0 == GetTempPath(sizeof(cbTempPath), cbTempPath))
		strcpy(cbTempPath, ".");
	if (0 != GetTempFileName(cbTempPath, "~CF", 0, cbTempFileName)) {
		m_rsTree.CreateNew(cbTempFileName);
		if (!IsValid())
			return;
		m_strTableName = cbTempFileName;
	}

	for (long i = 0; i < pFilter->m_lCnt-1; ++i) {
		using namespace trias_gist;

	RTkey key (pFilter->m_pX[i], pFilter->m_pX[i+1], 
			   pFilter->m_pY[i], pFilter->m_pY[i+1]);

		m_rsTree.Insert(RTentry(key, (GiSTpage)(i+1)));
	}
}

CObjectGiST::~CObjectGiST()
{
	if (IsValid()) {
		m_rsTree.Close();
		if (m_strTableName.size() > 0)
			DeleteFile(m_strTableName.c_str());
	}
}

///////////////////////////////////////////////////////////////////////////////
// Finden aller Stützstrecken, die mit dem gegebenen Container nicht disjoint
// sind
trias_gist::GiSTcursor *CObjectGiST::Search(double dXMin, double dXMax, 
	double dYMin, double dYMax)
{
	using namespace trias_gist;

RTpredicate pred(RTNotDisjoint, RTkey(dXMin, dXMax, dYMin, dYMax));

	return m_rsTree.Search(pred);
}

#endif // defined(_USE_CONNECTFILTER)
