// Macros.h: ein paar kleine Macros für dieses Projekt
// myhelper.h

#ifndef __MYHELPER_H__FILE
#define __MYHELPER_H__FILE

#include <ospace/std/list>

bool InvalidIdent(ulong id);
HRESULT EnumAllProjects(list<HPROJECT>& cont);	//JG enumeriert alle Datenquellen

// testen eines Pointers p und verlassen der Funktion mit 
// angegebenem Fehlercode erg, wenn Ptr ungültig
#define CHECKPOINTER(p, erg)	\
	ASSERT(p);					\
	if (NULL == p)				\
		return erg;

// dito, mit E_POINTER
#define CHECKPOINTERHR(p) \
	CHECKPOINTER(p, E_POINTER);

// define für kommentierende Pragmas
// Usage : #pragma MSG("Das ist ein sinnloser Kommentar der beim kompilieren erscheint")
#define MSG3(x) #x 
#define MSG2(x) MSG3(x)
#define MSG(a) message(__FILE__ "("MSG2(__LINE__)") : " a)

#define CHECKPOINT MSG("Compiler Checkpoint")

#endif //__MYHELPER_H__FILE
