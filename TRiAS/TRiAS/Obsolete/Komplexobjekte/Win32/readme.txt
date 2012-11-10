Übersicht über die Dateien des Projektes FEATURE.EXT:

Erweiterung selbst (Klasse CFeatureExtension):
PreCompiled Header:
	featurep.cxx, featurep.hxx
Eigentliche Erweiterung:
	featurex.cxx, feature.hxx
HilfsFunktionen für die ObjectProperty - Objekte:
	datahelp.cxx, 
	propactb.cxx, propactb.hxx
	clspropb.cxx, clspropb.hxx

EnumeratorObjekt für Objekte einer Gruppe (Klasse 
CEnumObjectNumbers):
	enumonr.cxx, enumonr.hxx

DataObject - Implementation (Klassen CImpIDataObject, CDataObject)
	dataobj.cxx, idataobj.cxx, pdataobj.hxx

Enumerator für FORMATETC (Klasse CEnumFormatEtc)
	ienumfe.cxx, pdataobj.hxx

PropertySequence - Objekt, welches prinzipiell auch von außen
verwendbar sein dürfte (Klasse CPropertySequence):
	propseq.cxx, propseq.hxx

Die Erweiterung stellt folgende PropertyAction - Objekte zur
Verfügung:
CLSPROP_ROOT\\Recherche\\Gruppieren von Objekten
	clsfyprp.cxx, clsfyprp.hxx (CClsfyPropAct)
	seloprop.cxx, seloprop.hxx (CClassifyDlg)
	seloprpt.cxx, seloprpt.hxx (CSelObjPropTree)

CLSPROP_ROOT\\Recherche\\Objektauswahl nach Identifikator und Typ
	selidprp.cxx, selidprp.hxx (CSelIDPropAct)
	selident.cxx, selident.hxx (CSelectIdentDlg)
	selidlst.cxx, selidlst.hxx (CSelIdentList)

CLSPROP_ROOT\\Recherche\\Bilden von Objektrelationen
	selrlprp.cxx, selrlprp.hxx (CGenKomplexObj)
	selrcode.cxx, selrcode.hxx (CSelectRCodeDlg)
	selrelst.cxx, selrelst.hxx (CSelPBDRelationList)
	selidpbd.cxx, selidpbd.hxx (CSelPBDIdentList)

CLSPROP_ROOT\\Recherche\\Objekte in Recherchefenster anzeigen
	dstobwnd.cxx, dstobwnd.hxx (CDestObjWndPropAct)
	dstobdlg.cxx, dstobdlg.hxx (CDestObjWndDlg)

CLSPROP_ROOT\\Recherche\\Objektauswahl aus Recherchefenster
	selobwnd.cxx, selobwnd.hxx (CSelObjWndPropAct)
	selobdlg.cxx, selobwnd.hxx (CSelectObjWndDlg)

