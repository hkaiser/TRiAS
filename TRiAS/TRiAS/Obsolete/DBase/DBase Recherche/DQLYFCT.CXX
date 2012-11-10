/*
Datei: DQLYFCT.CXX

Das Modul enthält ergänzende Funktionen des Parsers.

Erarbeitet: J.Benkenstein				   Stand vom: 13.11.1995
*/

#include "pheader.h"

extern "C" {                                    
	#include "komplexr.hr"	   	// Resourcen-Defines
}

#include "dqlyfct.htp"		  	// Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>
#include <relation.hxx>		 	// RelationList
#include <dbliste.hxx>		  	// DBaseFiles
#include <dbasekey.hxx>		 	// MasterTerm, SlaveTerm
#include <dbasprof.hxx>		 	// DBaseProfile
#include <dbaserel.hxx>		 	// DBaseRel

//  externe Variablen
extern Bool groupActive;
extern RelationList *pLocalRL;
extern RelationList *pGlobalRL;
extern DBaseFiles *pDBFs;

//  neue Relation in Liste aufnehmen
ErrCode AddRelation (MasterTerm &Master, SlaveTerm &Slave) {

	if (groupActive) {
		pLocalRL = new RelationList;
		if (!pLocalRL) {
			DEX_Error (RC_DQLParser, EC_NOMEMORY);
			return EC_NOMEMORY;
		}
	} else {
		if (!pGlobalRL) {

			pGlobalRL = new RelationList;
			if (!pGlobalRL) {
				DEX_Error (RC_DQLParser, EC_NOMEMORY);
				return EC_NOMEMORY;
			}
		}
	}

//  ggf. neue Datenliste erzeugen
	if (!pDBFs) {
		pDBFs = new DBaseFiles;
		if (!pDBFs) {
			DEX_Error (RC_DQLParser, EC_NOMEMORY);
			return EC_NOMEMORY;
		}
	}

//  Relation in Liste aufehmen
	RelationCreator RCr (groupActive ? *pLocalRL : *pGlobalRL);
	Create (RCr, Relation) (*pDBFs, &Master, &Slave);

	return EC_OKAY;
}

//  "Default"-Relationliste erzeugen
RelationList *CreateRelationList (CodeBase *pCB,
								  pchar pMasterFile, pchar pMasterField) {
//  prüfe Parameter
	if (!pMasterFile || !*pMasterFile || !pMasterField || !*pMasterField ||
		!pCB) 
		return NULL;

//  ggf. neue Datenliste erzeugen
	if (!pDBFs) {
		pDBFs = new DBaseFiles;
		if (!pDBFs) {
			DEX_Error (RC_DQLParser, EC_NOMEMORY);
			return NULL;
		}
	}

//  neue Liste erzeugen
	RelationList *pRel = new RelationList;
	if (!pRel) {
		DEX_Error (RC_DQLParser, EC_NOMEMORY);
		return NULL;
	}

//  lese Einträge aus INI-Datei
	DBaseRel Master (pMasterFile, pMasterField);	// Master-Infos
	DBaseRel **ppSlaveRel = NULL;				   // Slave-Infos
	DBaseProFile PF;
	short Cnt = PF.ReadDBaseRelations (Master, &ppSlaveRel);
	if (!Cnt) {
		return pRel;	   // keine Relationen gefunden
	}

//  alle Relations in Liste übernehmen
	MasterTerm MT (pMasterFile, pMasterField);  // bleibt unverändert
	Relation *pRL = NULL;
	for (short i = 0; i < Cnt; i++) {
	//  Master-Slave-Term in Liste
		SlaveTerm ST (ppSlaveRel [i] -> GetDBName (),
					  ppSlaveRel [i] -> GetFieldName ());
		RelationCreator RCr (*pRel);
		if (! (pRL = Create (RCr, Relation) (*pDBFs, &MT, &ST))) {
			DEX_Error (RC_DQLParser, EC_NOMEMORY);
			DELETE_OBJ (pRel);
			break;
		}

	//  Slave-DB zu den DBaseFiles
		if (!pDBFs -> AddDataIndex (pCB, ppSlaveRel [i] -> GetDBName ())) {
			DEX_Error (RC_DQLParser, EC_NOMEMORY);
			DELETE_OBJ (pRel);
			break;
		}
	}

//  alten SlaveRel löschen
	for (short j = 0; j < Cnt; j++)
		DELETE_OBJ (ppSlaveRel [j]);
	DELETE_OBJ (ppSlaveRel);

	return pRel;		// mit Liste zurück
}

// alle dBase-Dateien aus Projekt-Ini lesen
Bool ReadAlldBaseFiles (CodeBase *pCB, DBaseFiles *pData, ResourceFile *pRF) {
	const short BufferSize = 1024;	  // ID-Key-Buffer-Size

//  prüfe übergebene Parameter
	if (!pCB || !pData || !pRF) {
		DEX_Error (RC_DQLParser, EC_SYSERROR);
		return False;
	}

//  prüfe CodeBase
	if (pCB -> error () != r4success)
		return False;

//  alle Keys aus dBase-Section lesen
	DBaseProFile Profile;			   // Name der Projekt-Ini-Datei
	pchar pBuffer = new char [BufferSize];
	if (!pBuffer) {
		DEX_Error (RC_DQLParser, EC_NOMEMORY);
		return False;
	}
	ResString Section (ResID (IDS_DBASESECTION, pRF), 10);
	ulong Len = GetPrivateProfileString (Section.Addr (), NULL, "", pBuffer,
										 BufferSize, Profile.GetProFileName ());
	if (Len == 0) {
		DEX_Error (RC_DQLParser, WC_NOALIASNAMESFOUND);
		DELETE_VEC (pBuffer);
		return False;		   // keine Einträge gefunden
	}

//  zu den gefundenen Schlüssel die zugeh. Enträge lesen und ausgeben
	long *pMCodes = NULL;
	char **ppMStrs = NULL;
	short NumMCodes = 0;
	ulong ulIdent = 0;
	for (pchar pActKey = pBuffer; pActKey < pBuffer + Len;
		 pActKey += lstrlen (pActKey) + 1) {
		if (lstrlen (pActKey) < 3)
			continue;
		if (FAILED(IdentFromClassX (pActKey + 2, &ulIdent, FALSE)))
			continue;
		NumMCodes = Profile.ReadDBaseCodes (&pMCodes, &ppMStrs, ulIdent);
		if (pMCodes == NULL)		  // keine DBaseMerkmale
			continue;
		pDBFs -> AddDataIndex (pCB, ppMStrs [0]);

	//	Aufräumen
		DELETE_VEC (pMCodes);
		if (ppMStrs) {
			for (short i = 0; i < NumMCodes; i++)
				DELETE_VEC (ppMStrs[i]);
				DELETE_VEC (ppMStrs);
		}
	}

	DELETE_VEC (pBuffer);
	return True;
}
