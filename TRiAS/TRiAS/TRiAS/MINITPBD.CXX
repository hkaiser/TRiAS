// Initialisieren diverser PBD-Eintraege --------------------------------------
// File: MINITPBD.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "minitpbd.hxx"

//
// Im Header der GeoDB befinden sich jeweils die MerkmalsCodes, unter denen
// am jeweiligen Target die gesuchte Information zu finden ist.
//
static INITPBDRESID NEAR locRESID[] = {
// Objektbezogene HeaderEinträge
	{ MITypMerkmal | ObjTarget /*| MISystemMerkmal */, 
		IDS_TEXTOBJMCODE, IDS_TEXTOBJKTEXT, IDS_TEXTOBJLTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, 99999100L },
	{ MITypMerkmal | ObjTarget /*| MISystemMerkmal */, 
		IDS_OBJNAME, IDS_OBJNAMEKTEXT, IDS_OBJNAMELTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, 51100000L },
	{ MITypMerkmal | ObjTarget | MIReadOnlyMerkmal /*| MISystemMerkmal */,
		IDS_UNIQUEIDENT, IDS_UNIQUEIDENTKTEXT, IDS_UNIQUEIDENTLTEXT, 
		HEADER_NORMAL | HEADER_READONLY, 51200000L },
	{ MITypMerkmal | ObjTarget | MIReadOnlyMerkmal /*| MISystemMerkmal */,
		IDS_OLDUNIQUEIDENT, IDS_OLDUNIQUEIDENTKTEXT, IDS_OLDUNIQUEIDENTLTEXT, 
		HEADER_NORMAL | HEADER_READONLY, 51300000L },
	{ MITypMerkmal | ObjTarget | MISystemMerkmal,
 		IDS_LEGENDINFOMCODE, IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },

// Identifikatorbezogene HeaderEinträge
	{ MITypMerkmal | IdentTarget | MISystemMerkmal, 
		IDS_OBJCLASSMCODE, IDS_OBJCLASSDESC_KT, IDS_OBJCLASSDESC_KT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },

	// support für IdentScale (Sicht und Ident verwenden identische MCodes)
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_P_SCALEVIEWMCODE, IDS_P_SCALEVIEWMCODE_KT, IDS_P_SCALEVIEWMCODE_KT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_L_SCALEVIEWMCODE, IDS_L_SCALEVIEWMCODE_KT, IDS_L_SCALEVIEWMCODE_KT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_A_SCALEVIEWMCODE, IDS_A_SCALEVIEWMCODE_KT, IDS_A_SCALEVIEWMCODE_KT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_T_SCALEVIEWMCODE, IDS_T_SCALEVIEWMCODE_KT, IDS_T_SCALEVIEWMCODE_KT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },

// Sichtbezogene HeaderEinträge
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_OBJVISINFO, IDS_OBJVISINFOKTEXT, IDS_OBJVISINFOLTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, 99999000L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal, 
		IDS_HDRSICHTBMASSTAB, IDS_BMASSTABKTEXT, IDS_BMASSTABLTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal,
		IDS_HDRSICHTCONTAINER, IDS_SICHTCONTKTEXT, IDS_SICHTCONTLTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal,
		IDS_CAPTIONMCODE, IDS_CAPTIONMCODEKTEXT, IDS_CAPTIONMCODELTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },
	{ MITypMerkmal | SichtTarget | MISystemMerkmal,
		IDS_LEGENDAREAMODE, IDS_AREAMODEKTEXT, IDS_AREAMODELTEXT, 
		HEADER_SYSTEM | HEADER_READONLY, -1L },

// EndeKennung
	{ 0, 0, 0, 0, 0, -1L },
};

///////////////////////////////////////////////////////////////////////////////
// Nachtragen fehlender Systemeinträge in der zugehörigen PBD 
ErrCode DatenBasisObjekt::MainInitPbd (
	GeoDB &rDB, uint resID, BOOL iEnterNewCode, long lNewCode)
{
	if (!rDB.IsTRiASDataSource())
		return EC_OKAY;		// so tun, als obs ok wäre

INITPBDRESID *pIR = locRESID;

	while (pIR -> iTyp) {
		if (resID != 0 && resID != pIR -> uiHeaderKey) {
		// wenn nur ein Eintrag gesetzt werden soll dann diesen suchen
			pIR++;
			continue;
		}

#if defined(_FORCE_LEGACY_CODE)
	// entweder für alle Einträge oder Eintrag gefunden			
		if (rDB.GetDBVersion() < VERSION05000008 && (pIR -> iTyp & (IdentTarget|SichtTarget))) {
		// weitermachen, alte GeoDB
			pIR++;
			continue;
		}
#endif // defined(_USE_LEGACY_CODE)
		
	HeaderEntry HE (rDB, pIR -> uiHeaderKey);
	long lMCode = HE.EntryLong (-1);

        if (0 == lMCode)
            lMCode = -1L;

		if (lMCode == -1L && 
            (iEnterNewCode || pIR -> m_lMCode != -1L)) 
        {
		// Neuer Code soll in Header eingetragen werden
			switch (pIR -> iTyp & MITyp) {
			case MITypIdentifikator:	// neuer Identifikator
			case MITypRelation:		// neuer RelationsCode
				break;			// not supported yet
				
			case MITypMerkmal:	// neuer MerkmalsCode
				{ 
				// neuen MCode in Header eintragen				
				char tmpBuff[30];
				ErrCode RC;

					if (-1L != lNewCode)
						lMCode = lNewCode;
					else if (-1L != pIR -> m_lMCode)
						lMCode = pIR -> m_lMCode;
					else
						lMCode = rDB.GetUniqueMCode ((pIR -> iTyp & MISystemMerkmal) ? true : false);

					HE.SetEntryText (ltoa (lMCode, tmpBuff, 10));
					HE.Flags() = pIR -> dwHdrFlags;
					DBASSERT (HE.WriteBack());
				}
				break;
			}
		}
		
	// evtl. diesen Code in Pbd nachtragen		
		if (lMCode != -1L) {
		// HeaderEintrag existiert
		PBDMERKMALEX PD;
		ErrCode RC;
		ErrInstall E1 (WC_NOMERKMAL);

		// Daten initialisieren
			memset (&PD, '\0', sizeof (PBDMERKMALEX));
			switch (pIR -> iTyp & MITyp) {
			case MITypIdentifikator:
				PD.dwSize = sizeof (PBDDATA); 	// !!!
				PD.pbdTyp = 'i';	// Identifikator
				break;
				
			case MITypRelation:
				PD.dwSize = sizeof (PBDDATA); 	// !!!
				PD.pbdTyp = 'r';	// RelationsCode
				break;
				
			case MITypMerkmal:
			default:
				PD.dwSize = sizeof (PBDMERKMALEX); 	// !!!
				PD.pbdTyp = 'm';	// MerkmalsCode
				switch (pIR -> iTyp & TargetTyp) {
				case ObjTarget:		// ObjektMerkmal
				default:
					PD.ipbdMTyp = 'A';
					break;
					
				case SichtTarget:	// SichtMerkmal
					PD.ipbdMTyp = 'B';
					break;
					
				case IdentTarget:	// IdentifikatorMerkmal
					PD.ipbdMTyp = 'C';                     
					break;
                        	}
				if (pIR -> iTyp & MISystemMerkmal)
					PD.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
				if (pIR -> iTyp & MIReadOnlyMerkmal)
					PD.ipbdMTyp |= PBDMERKMAL_READONLY;
				PD.ipbdMLen = 256;
				PD.lIdent = -1L;
				break;
			}
			
			PD.pbdCode = rDB.MapMCodeToHandle (lMCode, TRUE);	// TargetCode in entsprechende Datenquelle mappen
//			PD.pbdKText = NULL;
//			PD.pbdLText = NULL;
//			PD.pbdKTextLen = 0;
//			PD.pbdLTextLen = 0;

		// abfragen, ob Eintrag bereits existiert
			RC = DEX_GetPBDDataEx (rDB.DBDesc(), PD);
			if (EC_OKAY != RC/* && WC_RETURN != RC*/) {
			// existiert noch nicht - Eintrag wegschreiben
			ResString KText (pIR -> uiKurzText, 33);
			ResString LText (pIR -> uiLangText, 256);

				PD.pbdKText = (char *)(const char *)KText;
				PD.pbdLText = (char *)(const char *)LText;
				PD.pbdKTextLen = strlen (KText);
				PD.pbdLTextLen = strlen (LText);
			
				DBASSERT (DEX_ModPBDDataEx (rDB.DBDesc(), PD));

			// die Welt informieren, das Merkmal modifiziert wurde
				switch (pIR -> iTyp & MITyp) {
				case MITypIdentifikator:
					DEXN_PBDIdentChanged (lMCode);
					break;
				
				case MITypRelation:
					DEXN_PBDRCodeChanged (lMCode);
					break;
				
				case MITypMerkmal:
				default:
					DEXN_PBDMCodeChanged (lMCode);
					break;
				}
			}
		}
		pIR++;		// nächster Eintrag
	}
	return EC_OKAY;
}

