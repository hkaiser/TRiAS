/* 
	File: IMASCHEN.HPP
	
	Erarbeitet: J. Benkenstein						Stand vom 11.4.1997
*/

#ifndef _IMASCHEN_HPP
#define _IMASCHEN_HPP

class CMaschenBildungI;
class CMaschenBildungI :
	public CComObjectRoot,
	public CComCoClass<CMaschenBildungI, &CLSID_ExtLinienVerfolgung>,
	public CComDualImpl<IExtLinienVerfolgung, &IID_IExtLinienVerfolgung, &LIBID_LinienVerfolgung>,
	public CComDualImpl<IExtLinienVerfolgungEx, &IID_IExtLinienVerfolgungEx, &LIBID_LinienVerfolgung>,
	public CComISupportErrorInfoImpl<&IID_IExtLinienVerfolgung> 	
{
public:
// 	Konstruktor / Destruktor
	CMaschenBildungI (void);

	BEGIN_COM_MAP(CMaschenBildungI)
		COM_INTERFACE_ENTRY(IExtLinienVerfolgung)
		COM_INTERFACE_ENTRY(IExtLinienVerfolgungEx)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY2(IDispatch, IExtLinienVerfolgungEx)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CMaschenBildungI)
	DECLARE_REGISTRY_RESOURCEID(IDR_MASCHEN_INTERFACE)

//	Interface Methoden
	STDMETHOD(LinesUnion)(
		IEnumObjectsByNumber *pInput,					//	Objektnummern-Eingabe-Strom
		double	dTolerance,								//	Fangbereich zweier Stützpunkte
		VARIANT_BOOL bOutputMerkmal,					//	Merkmale der Vereinigten vererben
		VARIANT_BOOL bCreateAreas,						//	erzeuge Flächen (TRUE) bzw. Linien (FALSE)
		VARIANT /*IProgressIndicator2 *pPI*/,			//	optional: Fortschrittsanzeige
		VARIANT * /*IEnumObjectsByNumber **ppUsed)*/,	//	optional: Objektnummern der zur Vereinigung beitragenden
		IEnumObjectsByNumber **ppUnion);				//	Objektnummern der Vereinigten

	STDMETHOD(LinesUnion)(
		INT_PTR hPr,									//	Zieldatenquelle für die neu erzeugten Objekte
		IEnumObjectsByNumber *pInput,					//	Objektnummern-Eingabe-Strom
		double	dTolerance,								//	Fangbereich zweier Stützpunkte
		VARIANT_BOOL bOutputMerkmal,					//	Merkmale der Vereinigten vererben
		VARIANT_BOOL bCreateAreas,						//	erzeuge Flächen (TRUE) bzw. Linien (FALSE)
		VARIANT /*IProgressIndicator2 *pPI*/,			//	optional: Fortschrittsanzeige
		VARIANT * /*IEnumObjectsByNumber **ppUsed)*/,	//	optional: Objektnummern der zur Vereinigung beitragenden
		IEnumObjectsByNumber **ppUnion);				//	Objektnummern der Vereinigten

	HRESULT FinalConstruct (void);
	void FinalRelease (void);
};

#endif // _IMASCHEN_HPP




