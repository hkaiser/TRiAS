/*
Datei: DQLYFCT.HXX

Das Modul enth„lt erg„nzende Funktionen des Parsers.

Erarbeitet: J.Benkenstein                   Stand vom: 12. Oktober 1993
*/

#ifndef DQLYFCT_HXX
#define DQLYFCT_HXX

//  neue Relation in Liste aufnehmen
class CodeBase;
class Master;
class Slave;

ErrCode AddRelation (MasterTerm &Master, SlaveTerm &Slave);
RelationList *CreateRelationList (CodeBase *pCodeBase,
				  pchar pMaster, pchar pMasterField);

// alle dBase-Dateien aus Projekt-Ini lesen
class DBaseFiles;
class ResourceFile;
Bool ReadAlldBaseFiles (CodeBase *pCB, DBaseFiles *pDataTree,
			ResourceFile *pRF);

#endif          // DQLYFCT_HXX
