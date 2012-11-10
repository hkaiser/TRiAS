// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PropSeq.h
// H. Kaiser

#ifndef _PROPSEQ_H
#define _PROPSEQ_H


static string MakeStreamName (LPCSTR pcDesc);
HRESULT InitPropertyActionSequence (LPCSTR pcDesc, IStorage *pIStg,
									IPropertyActionSequence **ppISeq);
HRESULT GetSubPropSeqStorage (IStorage **ppIStg);
HRESULT SavePropSeq (LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg);

#endif // _PROPSEQ_H
