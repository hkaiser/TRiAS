// SpatialTree.cpp : Implementation of CRaumzugriffApp and DLL registration.

#include "stdafx.h"
#include "Raumzugriff.h"
#include "SpatialTree.h"
#include "Hilfsfunktionen.h"
#include "objdispatch.h"

DefineSmartInterface(TestObjekt);
DefineSmartInterface(SpatialTreeQuery);
//DefineSmartInterface(EnumWUnknown);

DimensionMapEntry::DimensionMapEntry(DISPID amin,DISPID amax,VARTYPE acomptype)
{
    if (AcceptVartype(acomptype))
    {
        m_nmin=amin;
        m_nmax=amax;
        m_ncomptype=acomptype;
    }
    else
        ::DimensionMapEntry();
}

bool operator<(const Objectentry& x, const Objectentry& y)
{
    return x.m_ID<y.m_ID;
}


CLeafnode::CLeafnode(CSpatialTree* pSpatialTree)
    :m_vecpObj()
{
#ifdef _DEBUG
    m_a = 'L';
    m_b = 'E';
    m_c = 'A';
    m_d = 'F';    // Typ des Objektes
#endif

    m_nFill = 0;
    m_pSpatialTree=pSpatialTree;
    // evtl. ARRAY noch mit NULL initialisieren
}

CLeafnode::~CLeafnode()
{
    TRACE("CLeafnode::Destruktor\n");
}

// S_FALSE als Rückgabewert ->
//      bucket muß gesplittet , und anschließend neu eingefügt werden (Insert)
//      bucket muß gemerged werden (Delete);

HRESULT CLeafnode::Insert(Objectentry* pobj)
{
    // Input testen
    ASSERT(pobj);
    if (NULL == pobj)
    {
        TRACE("*** CLeafnode::Insert *** Fehler : E_POINTER (0x%x) *** Zeiger auf Objekt = NULL ***\n",E_POINTER);
        return E_POINTER;
    }

    // Füllstand testen
    if (MAXBUCKETENTRIES == m_nFill)
    {
        TRACE("*** CLeafnode::Insert *** Ausnahmereturn : S_FALSE (0x%x) *** Leafnode voll, bitte splitten ***\n",S_FALSE);
        return S_FALSE; // kann nicht jetzt einfügen
    }

    // Einfügen
    m_vecpObj[m_nFill]=pobj;
    m_nFill++;  // m_nFill muß jetzt eins weiter zeigen
    return S_OK;
} // end of insert

HRESULT CLeafnode::Delete(Objectentry* pobj,CKnoten* pcaller)
{
    // Input testen
    ASSERT(pobj);
    if (NULL == pobj)
    {
        TRACE("*** CLeafnode::Delete *** Fehler : E_POINTER (0x%x) *** Objektzeiger auf NULL ***\n",E_POINTER);
        return E_POINTER;
    }

    ASSERT(pcaller);
    if (NULL == pcaller)
    {
        TRACE("*** CLeafnode::Delete *** Fehler : E_POINTER (0x%x) *** Aufrufendes Objekt auf NULL ***\n",E_POINTER);
        return E_POINTER;
    }
    // suchen
    for (int i=0;i<m_nFill;i++)
    {
        // steht in dem Feld überhaupt was drin
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
        {
            TRACE("*** CLeafnode::Delete *** Fehler : E_POINTER (0x%x) *** Leerer Eintrag im Leaf ***\n",E_POINTER);
            return E_POINTER;
        }
        // gefunden ? (könnte auch pointer vergleichen)
        if (m_vecpObj[i]->m_ID == pobj->m_ID)
        {
            // aktuellen mit dem letzten Eintrag überschreiben
            m_nFill--;
            m_vecpObj[i] = m_vecpObj[m_nFill];
            m_vecpObj[m_nFill] = NULL;

            // Füllstand testen
            if (m_nFill < (MAXBUCKETENTRIES / 2))
            {
                TRACE("*** CLeafnode::Delete *** Ausnahmebehandlung : S_FALSE (0x%x) *** Objekt wurde gelöscht, Knoten bitte mergen ***\n",S_FALSE);
                return S_FALSE;     // hallo bitte mergen
            }
            else
                return S_OK;        // OK, alles klar gegangen
        }   
    }
    
    // nicht gefunden
    TRACE("*** CLeafnode::Delete *** Ausnahme : E_FAIL (0x%x) *** Objekt nicht gefunden ***\n",E_FAIL);
    return E_FAIL;
}   // end of CLeafNode::Delete

HRESULT CLeafnode::WriteToList(OBJLISTE& objlst)
{   
    for (int i=0;i<m_nFill;i++)
    {
        // sicher ist sicher
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
        {
            TRACE("*** CLeafnode::WriteToList *** Fehler : E_POINTER (0x%x) *** Leerer Eintrag im Leaf ***\n",E_POINTER);
            return E_POINTER;
        }
        objlst.push_back(m_vecpObj[i]);
    }
    return S_OK;
}

bool    CLeafnode::IsLeaf()
{ return TRUE;}

HRESULT CLeafnode::Getmin(CComVariant& aktmin,long disc)
{
    // benötigte Member testen
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
    {
        TRACE("*** CLeafnode::Getmin *** Fehler : E_POINTER (0x%x) *** Member m_pSpatialTree nicht initialisiert***\n",E_POINTER);
        return E_POINTER;
    }
    CComVariant objmin;
    CComVariant objmax;

    for (int i=0;i<m_nFill;i++)
    {
        // sicher ist sicher
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
        {
            TRACE("*** CLeafnode::Getmin *** Fehler : E_POINTER (0x%x) *** Leerer Eintrag im Leaf ***\n",E_POINTER);
            return E_POINTER;
        }        
        m_pSpatialTree->GetValues(m_vecpObj[i]->m_Interface,objmin,objmax,disc);
        if  ((0 == i)||(aktmin > objmin))
            aktmin = objmin;
    }
    return S_OK;
}

HRESULT CLeafnode::Getmax(CComVariant& aktmax,long disc)
{
    // benötigte Member testen
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    CComVariant objmin;
    CComVariant objmax;
    
    for (int i=0;i<m_nFill;i++)
    {
        // sicher ist sicher
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
            return E_POINTER;
        
        m_pSpatialTree->GetValues(m_vecpObj[i]->m_Interface,objmin,objmax,disc);
        if ((0 == i)||(aktmax < objmax))
            aktmax = objmax;
    }
    return S_OK;
}

HRESULT CLeafnode::UpdateSon(CKnoten* alt,CKnoten* neu)
{
    TRACE("** FEHLER ** CLeafnode::UpdateSon ** Unmögliche Aktion!\n");
    return E_FAIL;
}

HRESULT CLeafnode::Intersection(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;

    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    ASSERT(pReturn);
    if (NULL == pReturn)
        return E_POINTER;

    for (int i=0;i<m_nFill;i++)
    {
        // sicher ist sicher
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
            return E_POINTER;

        ASSERT(m_vecpObj[i]->m_Interface);
/*        if (NULL == m_vecpObj[i]->m_Interface)
            return E_POINTER;*/

        if (m_pSpatialTree->Intersect(m_vecpObj[i]->m_Interface,pIQuestion))
            if (!pICallback)
            // wenn keine Callbackfunktion gleich ausgeben
                    pReturn->Add(m_vecpObj[i]->m_Interface);
            else
            // sonst erst höflich fragen
                if (SUCCEEDED(pICallback->Accept(m_vecpObj[i]->m_Interface))) 
                    pReturn->Add(m_vecpObj[i]->m_Interface);
    }

    return S_OK;
};

HRESULT CLeafnode::Containment(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;

    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    ASSERT(pReturn);
    if (NULL == pReturn)
        return E_POINTER;

    for (int i=0;i<m_nFill;i++)
    {
        // sicher ist sicher
        ASSERT(m_vecpObj[i]);
        if (NULL == m_vecpObj[i])
            return E_POINTER;

        ASSERT(m_vecpObj[i]->m_Interface);
/*        if (NULL == m_vecpObj[i]->m_Interface)
            return E_POINTER;*/

        if (m_pSpatialTree->Contained(m_vecpObj[i]->m_Interface,pIQuestion))
            if (!pICallback)
            // wenn keine Callbackfunktion gleich ausgeben
                    pReturn->Add(m_vecpObj[i]->m_Interface);
            else
            // sonst erst höflich fragen
                if (SUCCEEDED(pICallback->Accept(m_vecpObj[i]->m_Interface))) 
                    pReturn->Add(m_vecpObj[i]->m_Interface);
    }
   
    return S_OK;
};

// Internalnode

CInternalnode::CInternalnode(CSpatialTree* pSpatialTree)
    :m_discvalue(0,VT_I4),
     m_maxLoson(0,VT_I4),
     m_minHison(0,VT_I4)
{
#ifdef _DEBUG
    m_a = 'I';
    m_b = 'N';
    m_c = 'T';
    m_d = 'E';    // Typ des Objektes
#endif

    m_pHison = NULL;
    m_pLoson = NULL;
    m_ndisc = 0;
    m_pSpatialTree = pSpatialTree;
} // end of CInternalnode cstructor

CInternalnode::CInternalnode(CKnoten* loson,
              CKnoten* hison,
              long newDisc,
              CComVariant& newDiscval,
              CComVariant& newminhison,
              CComVariant& newmaxloson,
              CSpatialTree* pSpatialTree)
{
    ASSERT(m_pHison);
    ASSERT(m_pLoson);
    ASSERT(m_pSpatialTree);

#ifdef _DEBUG
    m_a = 'I';
    m_b = 'N';
    m_c = 'T';
    m_d = 'E';    // Typ des Objektes
#endif

    m_discvalue=newDiscval;
    m_maxLoson=newmaxloson;
    m_minHison=newminhison;
    m_pHison = hison;
    m_pLoson = loson;
    m_ndisc = newDisc;
    m_pSpatialTree = pSpatialTree;
} // end of cstructor

void CInternalnode::Sort(OBJLISTE& templist)
{
    // templist ist ein vector
    TRACE("CInternalnode::Sort %d Elemente",templist.size());
    
    ASSERT(m_pSpatialTree);
    if ( NULL == m_pSpatialTree) 
        return;

    // lediglich mittleres Element einordnen, Elemente der linken Seite sind druch gehend kleiner, rechts alle größer 
    // anhand LessObjOnDim wird entlang der Dimension dieses Knotens unterteilt
    nth_element(   templist.begin(),
                   templist.begin()+(templist.size()/2),
                   templist.end(),
                   LessObjOnDim(m_ndisc,m_pSpatialTree));

//  old code
//     clear() Löscht alle Elemente
/*   
    list<Objectentry*>::iterator i; // äußere Schleife
    list<Objectentry*>::iterator j; // innere Schleife
    Objectentry*    temp;           // zum Umkopieren
    CComVariant     tempmin;        
    CComVariant     tempmax;
    CComVariant     tempcent;
    CComVariant     objcenter;
    CComVariant     newDiscval;
    CComVariant     newminhison;
    CComVariant     newmaxloson;


// Selection Sort
    for(i=templist.begin();i!=templist.end();i++)
    {   
        m_pSpatialTree->GetValues((*i)->m_Interface,tempmin,tempmax,m_ndisc);
        calculatecenter(objcenter,tempmin,tempmax);
        j=i;
        j++;
        for(;j!=templist.end();j++)
        {
            m_pSpatialTree->GetValues((*j)->m_Interface,tempmin,tempmax,m_ndisc);
            calculatecenter(tempcent,tempmin,tempmax);
            if (tempcent<objcenter)
            {
                // kopieren
                objcenter=tempcent;
                // heute tauschen wir aus
                temp=*j;*j=*i;*i=temp;
            }       // end of Austausch
        }           // end of inner cycle
    }               // end of outer cycle*/
}

CInternalnode::CInternalnode(OBJLISTE& objlst,long dimension,CSpatialTree* pSpatialTree)
{
    OBJLISTE::iterator i,j; // äußere Schleife
    CComVariant     tempmin;        
    CComVariant     tempmax;
    CComVariant     tempcent;
    CComVariant     objcenter;
    CComVariant     newDiscval;
    OBJLISTE        hilist;
    OBJLISTE        lolist;

#ifdef _DEBUG
    m_a = 'I';
    m_b = 'N';
    m_c = 'T';
    m_d = 'E';    // Typ des Objektes
#endif
    
    ASSERT(pSpatialTree);
    if (NULL == pSpatialTree) 
        return;
    
    m_pSpatialTree = pSpatialTree;

    // dimension testen
    if (m_pSpatialTree->m_nDimension<=dimension) 
        dimension = 0;
    m_ndisc = dimension;

    // Liste sortieren lassen
    Sort(objlst);

    // Liste teilen
    long half=objlst.size() / 2;
    long count;


    //kleinere Werte zuerst
    i=objlst.begin();
    // erste Werte initialisieren
    m_pSpatialTree->GetValues((*i)->m_Interface,m_minLoson,m_maxLoson,m_ndisc);
    
    // kleinere Werte in LoList
    for(count=0;count<half;count++)
    {
        ASSERT(*i);

        if (NULL == *i)
            return; //E_POINTER;
        // dabei den größten Maximumwert speichern
        m_pSpatialTree->GetValues((*i)->m_Interface,tempmin,tempmax,m_ndisc);

        // Grenzen merken
        if (m_maxLoson < tempmax)
            m_maxLoson = tempmax;
        if (m_minLoson > tempmin)
            m_minLoson = tempmin;

        // kopieren
        lolist.push_back(*i);
        
        // altes löschen
        objlst.pop_front();

        // nächstes Element
        i = objlst.begin();
    }

    //aktuelles Zentrum als discval merken
    m_pSpatialTree->GetValues((*i)->m_Interface,m_minHison,m_maxHison,m_ndisc);
    calculatecenter(m_discvalue,m_minHison,m_maxHison);

    // kleinere Werte in loson
    while (0<objlst.size())
    {
        // nächstes Element
        i = objlst.begin();

        // dabei den größten Maximumwert speichern
        m_pSpatialTree->GetValues((*i)->m_Interface,tempmin,tempmax,m_ndisc);

        // Grenzen merken
        if (m_maxHison < tempmax)
            m_maxHison = tempmax;
        if (m_minHison > tempmin)
            m_minHison = tempmin;

        // kopieren
        hilist.push_back(*i);
        // altes löschen
        objlst.pop_front();
    }

    // Lolist splitten
    if (lolist.size() < MAXBUCKETENTRIES)
    {
        // neuen Leaf anlegen
        m_pLoson = (CKnoten*) new CLeafnode(m_pSpatialTree);
            // wird vom übergeordneten Obvjekt wieder gelöscht
        ASSERT(m_pLoson);
        if (NULL == m_pLoson)
            return; // E_OUTOFMEMORY;

        // Daten aus Liste in den Leaf kopieren
        
        while (lolist.size() != 0)
        {
            i=lolist.begin();
            if (m_pLoson->Insert(*i)!=S_OK)
            {
                TRACE("** CInternalnode:Cstor ** Fehler beim Umkopieren **\n");
                return;
            }
            lolist.pop_front();
        }
    }
    else //Liste zu groß um in leaf zu speichern
    {
        m_pLoson = new CInternalnode(lolist,m_ndisc+1,m_pSpatialTree);
            // wird von übergeordnetem Objekt wieder gelöscht
        ASSERT(m_pLoson);
        if (NULL == m_pLoson)
            return;// E_OUTOFMEMORY;
    }

    // hilist umkopieren
    if (hilist.size() < MAXBUCKETENTRIES)
    {
        // neuen Leaf anlegen
        m_pHison = (CKnoten*) new CLeafnode(m_pSpatialTree);
            // wird vom übergeordnetem Objekt wieder gelöscht
        ASSERT(m_pHison);
        if (NULL == m_pHison)
            return; // E_OUTOFMEMORY;

        // Daten aus Liste in den Leaf kopieren
        
        while (hilist.size() != 0)
        {
            i=hilist.begin();
            if (m_pHison->Insert(*i)!=S_OK)
            {
                TRACE("** CInternalnode:Cstor ** Fehler beim Umkopieren **\n");
                return;
            }
            hilist.pop_front();
        }
    }
    else
    {
        // einen neuen internen Knoten anlegen
        m_pHison = new CInternalnode(hilist,m_ndisc+1,m_pSpatialTree);
            // wird vom Vater wieder gelöscht
        ASSERT(m_pHison);
        if (NULL == m_pHison)
            return;// E_OUTOFMEMORY;
    }
} // end of cstructor

CInternalnode::~CInternalnode()
{
    TRACE("CInternalnode::Destruktor\n");
    if (NULL != m_pHison) 
        delete m_pHison;
    m_pHison = NULL;

    if (NULL != m_pLoson) 
        delete m_pLoson;
    m_pLoson = NULL;
} // end of CInternalnode dstructor

HRESULT CInternalnode::Insert(Objectentry* pobj)
{
    // Input testen
    ASSERT(pobj);
    if (NULL == pobj)
        return E_POINTER;

    // Member testen
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    ASSERT(m_pLoson);
    if (NULL == m_pLoson)
        return E_POINTER;

    ASSERT(m_pHison);
    if (NULL == m_pHison)
        return E_POINTER;

    CComVariant objmin;
    CComVariant objmax;
    CComVariant objcenter;
    CKnoten*    pEinf;
    BOOL        bHison;

#ifdef _DEBUG
    // zählen der Elemente vor dem Löschen
    OBJLISTE templist;
    WriteToList(templist);
    long nDebug_vor_Loeschen = templist.size();
#endif

    // Werte holen
    m_pSpatialTree->GetValues(pobj->m_Interface,objmin,objmax,m_ndisc);
    calculatecenter(objcenter,objmin,objmax);

    // auf welcher Seite einfügen
    if (objcenter <= m_discvalue)
    {
        // Grenzen updaten
        if (m_maxLoson < objmax)
            m_maxLoson = objmax;
        if (m_minLoson > objmin)
            m_minLoson = objmin;

        pEinf = m_pLoson;
        bHison = FALSE;
    } else {
        // Grenzen updaten
        if (m_maxHison < objmax)
            m_maxHison = objmax;
        if (m_minHison > objmin)
            m_minHison = objmin;

        pEinf = m_pHison;
        bHison = TRUE;
    }
    
    // sicher ist sicher
    ASSERT(pEinf);
    if (NULL == pEinf)
        return E_POINTER;
  
    // weiter nach unten geben
    HRESULT hr = pEinf->Insert(pobj);

    // kann ich noch etwas tun?
    if (hr != S_FALSE)
    {
#ifdef _DEBUG
                // zählen der Elemente vor dem Löschen
                OBJLISTE templist1;
                WriteToList(templist1);
                long nDebug_nach_Loeschen=templist1.size();
                ASSERT(nDebug_nach_Loeschen == nDebug_vor_Loeschen + 1);
#endif

       return hr;
    }

    // ja,splitten
    hr = split(bHison);
    
    // diesen Leafknoten gibt es jetzt nicht mehr
    pEinf = NULL;
#ifdef _DEBUG
                // zählen der Elemente vor dem Löschen
                OBJLISTE templist2;
                WriteToList(templist2);
                long nDebug_nach_Loeschen=templist2.size();
                ASSERT(nDebug_nach_Loeschen == nDebug_vor_Loeschen );
#endif

    if (hr != S_OK)
        return hr;

    // und natürlich obj einfügen
    hr = Insert(pobj);
#ifdef _DEBUG
                // zählen der Elemente vor dem Löschen
                OBJLISTE templist3;
                WriteToList(templist3);
                nDebug_nach_Loeschen=templist3.size();
                ASSERT(nDebug_nach_Loeschen == nDebug_vor_Loeschen +1);
#endif
    return hr;

} //end of Insert

HRESULT CInternalnode::split(bool bHison)
{
    // splittet Leafknoten
    // bHison = TRUE Hison splitten
    // bHison == FALSE Loson splitten
    
    OBJLISTE    templist;

    if (TRUE == bHison)
    {   
        ASSERT(m_pHison);
        if (NULL == m_pHison)
            return E_POINTER;
        // Werte retten
        m_pHison->WriteToList(templist);
#ifdef _DEBUG
        long ndeb_anzahl1 = templist.size();
#endif
        // Knoten löschen
        delete  m_pHison;
        
        // neuen Knoten erzeugen und Wertte einfügen
        m_pHison = new CInternalnode(templist,m_ndisc+1,m_pSpatialTree);
            // wird vom Vater wieder gelöscht
#ifdef _DEBUG
        ASSERT(templist.size() == 0);
        m_pHison->WriteToList(templist);
        long ndeb_anzahl2 = templist.size();
        ASSERT(ndeb_anzahl2 == ndeb_anzahl1);
#endif

        if (NULL == m_pHison)
        {
            return E_OUTOFMEMORY;
        }
    } else {
        ASSERT(m_pLoson);
        if (NULL == m_pLoson)
            return E_POINTER;
        // Werte retten
        m_pLoson->WriteToList(templist);
#ifdef _DEBUG
        long ndeb_anzahl1 = templist.size();
#endif

        // Knoten löschen
        delete  m_pLoson;
        
        // neuen Knoten erzeugen und Wertte einfügen
        m_pLoson = new CInternalnode(templist,m_ndisc+1,m_pSpatialTree);
            // wird vom Vater wiedere gelöscht

#ifdef _DEBUG
        ASSERT(templist.size() == 0);
        m_pLoson->WriteToList(templist);
        long ndeb_anzahl2 = templist.size();
        ASSERT(ndeb_anzahl2 == ndeb_anzahl1);
#endif

        if (NULL == m_pLoson)
        {
            return E_OUTOFMEMORY;
        }
    }
    return S_OK;
}        

HRESULT CInternalnode::Merge(bool bHison,CKnoten* pCaller)
{
    // Bei Überarbeitung vielleicht einfach Kopierziel bestimmen,
    // dahin kopieren und entsprechenden Rückgabewert returnen

    OBJLISTE    templist;
    CKnoten*    temp = NULL; // Bruderknoten, in ihn können evtl. Werte eingefügt werden
                             // da this gelöscht wird, muß der Member mit dem Verweis 
                             // auf diesen Knoten vorher genullt werden 
                             // (sonst wird Knoten im this::Destruktor automatisch mitgelöscht)
    HRESULT     hr = E_FAIL;
    CKnoten*    pnewNode = NULL;
    HRESULT     retval = E_FAIL;
    BOOL        update = TRUE;

    // Member testen
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    ASSERT(m_pLoson);
    if (NULL == m_pLoson)
        return E_POINTER;

    ASSERT(m_pHison);
    if (NULL == m_pHison)
        return E_POINTER;


    if (bHison)
    {
        
        // Loson retten
        temp = m_pLoson;
        // Loson Verbindung aufheben, wird sonst im destruktor mitgelöscht
        m_pLoson = NULL;

        m_pHison->WriteToList(templist);
        delete m_pHison;    // wird nicht mehr gebraucht
        m_pHison = NULL;
    }
    else
    {
        // Hison retten
        temp = m_pHison;
        // Überschreiben, um nicht im destruktor mitzulöschen
        m_pHison = NULL;

        // Inhalt retten 
        m_pLoson->WriteToList(templist);
        delete m_pLoson;    // wird nicht mehr gebraucht
        m_pLoson = NULL;
    }

    ASSERT(temp);
    if (NULL == temp)
        return E_POINTER;

    // in der Wurzel gehts ja noch, aber hier!!!
    ASSERT(pCaller);
    if (NULL == pCaller)
        return E_POINTER;

    if (FALSE == temp->IsLeaf())
    {
        // angeben welcher Knoten diesen ersetzen soll
        // ein Sohn wird der Stellvertreter
        pnewNode = temp;
        retval = S_OK;
        update = FALSE;
    }
    else // leaf
    {
        // hier wird der Sohn gelöscht
        temp->WriteToList(templist);
        delete temp;
        
        // Neuer Zweig ist immer noch zu leer, weiter oben weiter zusammenfassen (return S_FALSE)
        if (templist.size() < (MAXBUCKETENTRIES / 2))
        {
            // neuen Leaf anlegen
            pnewNode = (CKnoten*) new CLeafnode(m_pSpatialTree);
                // wird vom Vater wieder gelöscht
            retval = S_FALSE;
        }
        else    // nicht weitermergen
        {
            // reicht ein neuer Leaf als Stellvertreter?
            if (MAXBUCKETENTRIES >= templist.size())
            {
                // neuen Knoten anlegen
                pnewNode = (CKnoten*) new CLeafnode(m_pSpatialTree);
                    // wird vom Vater wieder gelöscht
                retval = S_OK;
            }
            else
            // Leafnode reicht nicht (sollte nach bisherigem Aufruf nie passieren, aber sicher ist sicher
            {
                // neuen Knoten mit Listenelementen erzeugen
                pnewNode = 
                    new CInternalnode(templist,
                                      m_ndisc,
                                      m_pSpatialTree);
                    // wird vom Vater wieder gelöscht
                retval = S_OK;
            }
        }   // end of nicht weitermergen
    }   // end of leaf

    // einfach in den angegebenen Zweig kopieren
    OBJLISTE::iterator i;

    while (templist.size()!=0)
    {
        i = templist.begin();
        hr = pnewNode->Insert(*i);
        if (hr != S_OK)     // hier tritt der Fehler auf (
        {
            ASSERT(FALSE);  // schließlich sollte genügend Platz da sein
            return hr;
        }
        templist.pop_front();
    }

    ASSERT(pnewNode);
    if (NULL == pnewNode)
        return E_POINTER;

    // Selbstzerstörung ankündigen
    if (NULL != pCaller)
        hr = pCaller->UpdateSon(this,pnewNode);
    else
        return E_POINTER;
    // Selbstzerstörung
    delete this;
    return retval;
}
        
HRESULT CInternalnode::Delete(Objectentry* pobj,CKnoten* pcaller)
{
    // Input testen
    ASSERT(pobj);
    if (NULL == pobj)
    {
        TRACE("*** CInternalnode::Delete *** Fehler: E_POINTER (0x%x) *** Objektzeiger ist NULL ***\n",E_POINTER);
        return E_POINTER;
    }

    // Member testen
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    ASSERT(m_pLoson);
    if (NULL == m_pLoson)
        return E_POINTER;

    ASSERT(m_pHison);
    if (NULL == m_pHison)
        return E_POINTER;

    bool found=FALSE;
    bool dirtymin=FALSE;
    bool dirtymax=FALSE;
    HRESULT hr = E_FAIL;

    CComVariant objmin;
    CComVariant objmax;
    CComVariant objcenter;
#ifdef _DEBUG
    // Merken wieviele Elemente vor Löschen
    OBJLISTE    templist;
    WriteToList(templist);
    long ndeb_anzahl1 = templist.size();
#endif
    // Werte holen
    m_pSpatialTree->GetValues(pobj->m_Interface,objmin,objmax,m_ndisc);
    calculatecenter(objcenter,objmin,objmax);
    
    if (objcenter <= m_discvalue)
    {
        // Versuch zu löschen
        if (m_pLoson)
            hr = m_pLoson->Delete(pobj,this);
        else 
        {
            TRACE("*** CInternalnode::Delete *** Fehler: E_POINTER (0x%x) *** Member p_Loson ist NULL ***\n",E_POINTER);
            // sicher ist sicher
            return E_POINTER;
        }

        if (S_OK == hr)
        // merken, daß gefunden wurde
            found = TRUE;

        if (S_FALSE == hr)    // ich muß splitten
            // updaten macht keinen Sinn, da this in Merge gelöscht wird
        {
            TRACE("*** CInternalnode::Delete *** Ausnahmebehandlung : S_FALSE (0x%x) *** Muß Mergen ***\n",S_FALSE);
            return Merge(FALSE,pcaller);
        }

        // Grenzen updaten wenn gefunden und gelöscht
        if (TRUE == found)
        {
            if (objmin<=m_minLoson)
                m_pLoson->Getmin(m_minLoson,m_ndisc);
            if (objmax>=m_maxLoson)
                m_pLoson->Getmax(m_maxLoson,m_ndisc);
        }
    }
    // er könnte ja noch im anderen ast sein
    if ((FALSE == found)&&(objcenter >= m_discvalue))
    {
        // Versuch zu löschen
        if (NULL != m_pHison)
        {
            hr = m_pHison->Delete(pobj,this);
        }
        if (S_OK == hr)
        // merken, daß gefunden wurde
            found = TRUE;

        if (S_FALSE == hr) // ich muß splitten
        {
            // updaten macht keinen Sinn, da this in Merge gelöscht wird
            TRACE("*** CInternalnode::Delete *** Ausnahmebehandlung : S_FALSE (0x%x) *** Muß Mergen ***\n",S_FALSE);
            return  Merge(TRUE,pcaller);
        }

        // Grenzen updaten wenn gefunden und gelöscht
        if (TRUE == found)
        {
            if (objmin<=m_minHison)
                m_pHison->Getmin(m_minHison,m_ndisc);
            if (objmax>=m_maxHison)
                m_pHison->Getmax(m_maxHison,m_ndisc);
        }
    }


    // Ergebnis zurückgeben
    if (TRUE == found)
    {

#ifdef _DEBUG
    //    Test, jetzt muß ein Element weniger da sein
    OBJLISTE templist2;
    WriteToList(templist2);
    long ndeb_anzahl2 = templist2.size();
    ASSERT(ndeb_anzahl2 == ndeb_anzahl1 -1);
#endif

        return S_OK;
    }
    else
    {
        TRACE("*** CInternalnode::Delete *** Ausnahmebehandlung : E_FAIL (0x%x) *** Objekt nicht gefunden ***\n",E_FAIL);
#ifdef _DEBUG
    //    Test, es müssen genausoviele Elemente da sein
    OBJLISTE templist2;
    WriteToList(templist2);
    long ndeb_anzahl2 = templist2.size();
    ASSERT(ndeb_anzahl2 == ndeb_anzahl1 );
#endif

        return E_FAIL;
    }
} // end of Delete

HRESULT CInternalnode::WriteToList(OBJLISTE& objlst)
{   
    if (NULL != m_pLoson)
        m_pLoson->WriteToList(objlst);
    if (NULL != m_pHison)
        m_pHison->WriteToList(objlst);
    return S_OK;
}

bool    CInternalnode::IsLeaf()
{ return FALSE;}

HRESULT CInternalnode::Getmin(CComVariant& aktmin,long disc)
{
    if (disc == m_ndisc)
    {
        // habe schon alle Werte
        if (m_minLoson > m_minHison)
            aktmin = m_minHison;
        else
            aktmin = m_minLoson;
        return S_OK;
    }
    else
    {
        // Werte holen
        CComVariant lomin;
        CComVariant himin;

        HRESULT hr = m_pHison->Getmin(himin,disc);
        if (FAILED(hr))
        {
            TRACE("*** CInternalnode::Getmin *** Fehler : (0x%x) *** Untergeordneter Knoten m_phison liefert keinen minwert ***\n",hr);
            return hr;
        }
        hr = m_pLoson->Getmin(lomin,disc);
        if (FAILED(hr))
        {
            TRACE("*** CInternalnode::Getmin *** Fehler : (0x%x) *** Untergeordneter Knoten m_pLoson liefert keinen minwert ***\n",hr);
            return hr;
        }
        // aktmin = min wäre einfacher
        if (lomin < himin)
            aktmin = lomin;
        else
            aktmin = himin;
        return S_OK;
    }
}

HRESULT CInternalnode::Getmax(CComVariant& aktmax,long disc)
{
    if (disc == m_ndisc)
    {
        // OK ich habe schon alle Werte
        if (m_maxLoson < m_maxHison)
            aktmax = m_maxHison;
        else
            aktmax = m_maxLoson;
        return S_OK;
    }
    else
    {
        // muß mir die werte besorgen
        CComVariant lomax;
        CComVariant himax;

        HRESULT hr = m_pHison->Getmax(himax,disc);
        if (FAILED(hr))
        {
            TRACE("*** CInternalnode::Getmax *** Fehler : (0x%x) *** Untergeordneter Knoten m_pHison liefert keinen maxwert ***\n",hr);
            return hr;
        }
        hr = m_pLoson->Getmax(lomax,disc);
        if (FAILED(hr))
        {
            TRACE("*** CInternalnode::Getmax *** Fehler : (0x%x) *** Untergeordneter Knoten m_pLoson liefert keinen maxwert ***\n",hr);
            return hr;
        }
        
        // aktmax = max wäre einfacher
        if (lomax > himax)
            aktmax = lomax;
        else
            aktmax = himax;
        return S_OK;
    }
}

HRESULT CInternalnode::UpdateSon(CKnoten* alt,CKnoten* neu)
{
    ASSERT(neu);
    if (NULL == neu)
    {
        TRACE("*** CInternalnode::UpdateSon *** Fehler : E_POINTER (0x%x) *** Argument neu ist NULL",E_POINTER);
        return E_POINTER;
    }

    if (alt == m_pHison)
    {
        m_pHison = neu;
        return S_OK;
    }

    if (alt == m_pLoson)
    {
        m_pLoson = neu;
        return S_OK;
    }

    TRACE("*** CInternalnode::UpdateSon *** Fehler : E_FAIL (0x%x) *** Argument alt entspreicht keinem Sohn",E_FAIL );
    return E_FAIL;
}

HRESULT CInternalnode::Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;
    
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;
    
    CComVariant winmin,winmax;

    pIQuestion->GetBorder(m_ndisc,&winmin,&winmax);

    if ((winmin <= m_maxLoson)&&(winmax >= m_minLoson))
    {
        HRESULT hr = m_pLoson->Intersection(pIQuestion,pICallback,pReturn);
    }

    if ((winmin <= m_maxHison)&&(winmax >= m_minHison))
    {
        HRESULT hr = m_pHison->Intersection(pIQuestion,pICallback,pReturn);
    }

    return S_OK;
}

HRESULT CInternalnode::Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;
    
    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;
    
    CComVariant winmin,winmax;

    pIQuestion->GetBorder(m_ndisc,&winmin,&winmax);

    if (winmin<=m_discvalue)
        if ((winmin <= m_maxLoson)&&(winmax >= m_minLoson))
            m_pLoson->Intersection(pIQuestion,pICallback,pReturn);

    if (winmax>=m_discvalue)
        if ((winmin <= m_maxHison)&&(winmax >= m_minHison))
            m_pHison->Intersection(pIQuestion,pICallback,pReturn);

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
//
//  CRootnode   
//
//////////////////////////////////////////////////////////////////////////

CRootnode::CRootnode(CSpatialTree* pSpatialTree)
{
#ifdef _DEBUG
    m_a = 'R';
    m_b = 'O';
    m_c = 'O';
    m_d = 'T';    // Typ des Objektes
#endif

    m_pSpatialTree = pSpatialTree;
    m_pSon = (CKnoten*)new CLeafnode(pSpatialTree);
}

CRootnode::CRootnode(OBJLISTE& objlst,long dimension,CSpatialTree* pSpatialTree)
{
#ifdef _DEBUG
    m_a = 'R';
    m_b = 'O';
    m_c = 'O';
    m_d = 'T';    // Typ des Objektes
#endif

    m_pSpatialTree = pSpatialTree;
    m_pSon = (CKnoten*)new CInternalnode(objlst,dimension,pSpatialTree);
    Test();
}

CRootnode::~CRootnode()
{
    TRACE("\n\n Entering CRootnode::Destruktor \n\n\n");
    Test();
    if (NULL != m_pSon)
    {
        TRACE("CRootnode::Destruktor deleting m_pSon\n");
        delete m_pSon;
    }
}

HRESULT CRootnode::Insert(Objectentry* pobj)
{
    // Member testen
    if (NULL == m_pSon)
    {   
        TRACE("*** CRootnode::Insert *** Fehler : E_POINTER (0x%x) *** Member m_pSon = NULL",E_POINTER);
        return E_POINTER;
    }

    if (NULL == m_pSpatialTree)
    {   
        TRACE("*** CRootnode::Insert *** Fehler : E_POINTER (0x%x) *** Member m_pSpatialTree = NULL",E_POINTER);
        return E_POINTER;
    }

    // Parameter testen
    if (NULL == pobj)
    {   
        TRACE("*** CRootnode::Insert *** Fehler : E_POINTER (0x%x) *** Parameter pobj = NULL",E_POINTER);
        return E_POINTER;
    }

    HRESULT hr = m_pSon->Insert(pobj);
    Test();
    if (hr != S_FALSE)
        return hr;

    // hr ist S_FALSE -> splitten
    // alles Verwertbare holen
    OBJLISTE templiste;
    m_pSon->WriteToList(templiste);

    // Sohn löschen
    delete m_pSon;
    
    // alles in neuen Baum schieben
    m_pSon = (CKnoten*) new CInternalnode(templiste,0,m_pSpatialTree);

    Test();
    if (NULL == m_pSon)
    {   
        TRACE("*** CRootnode::Insert *** Fehler : E_OUTOFMEMORY (0x%x) *** kein Speicher für neuanlegen eines internen Knotens",E_OUTOFMEMORY);
        return E_OUTOFMEMORY;
    }

    // das eigentliche Objekt konnte vorher nicht eingefügt werden
    hr = m_pSon->Insert(pobj);
    Test();
    if (S_OK != hr)
    {
        TRACE("*** CRootnode::Insert *** Ausnahme : ??? (0x%x) *** beim erneuten Einfügen des neuen Objektes",hr);
        return hr;
    }
    
   
    // alles andere fliegt mit TRACE raus
    return S_OK;
}

HRESULT CRootnode::Delete(Objectentry* pobj,CKnoten* pcaller)
{
    Test();
    // Member testen
    if (NULL == m_pSon)
    {   
        TRACE("*** CRootnode::Delete *** Fehler : E_POINTER (0x%x) *** Member m_pSon = NULL",E_POINTER);
        return E_POINTER;
    }

    if (NULL == m_pSpatialTree)
    {   
        TRACE("*** CRootnode::Delete *** Fehler : E_POINTER (0x%x) *** Member m_pSpatialTree = NULL",E_POINTER);
        return E_POINTER;
    }

    // Parameter testen
    if (NULL == pobj)
    {   
        TRACE("*** CRootnode::Delete *** Fehler : E_POINTER (0x%x) *** Parameter pobj = NULL",E_POINTER);
        return E_POINTER;
    }

    if (NULL != pcaller)
    {   
        TRACE("*** CRootnode::Delete *** Fehler : E_POINTER (0x%x) *** Parameter pCaller ungleich NULL",E_POINTER);
        return E_POINTER;
    }

    HRESULT hr = m_pSon->Delete(pobj,this);
    if (S_FALSE != hr)
    {
        Test();
        return hr;
    }

    Test();

    // Leafnodes können nicht gemergt werden
    if (TRUE == m_pSon->IsLeaf())
        return S_OK;

    // hr ist S_FALSE -> splitten
    // alles Verwertbare holen
    OBJLISTE templiste;
    m_pSon->WriteToList(templiste);

    // Sohn löschen
    delete m_pSon;
    
    // alles in neuen Baum schieben
    m_pSon = (CKnoten*) new CInternalnode(templiste,0,m_pSpatialTree);
    if (NULL == m_pSon)
    {   
        TRACE("*** CRootnode::Insert *** Fehler : E_OUTOFMEMORY (0x%x) *** kein Speicher für neuanlegen eines internen Knotens",E_OUTOFMEMORY);
        return E_OUTOFMEMORY;
    }

    Test();
    return S_OK;
}

HRESULT CRootnode::WriteToList(OBJLISTE& objlst)
{
    return m_pSon -> WriteToList(objlst);
}

CRootnode::IsLeaf()
{
    return FALSE;
}

HRESULT CRootnode::Getmin(CComVariant& aktmin,long disc)
{
    return m_pSon->Getmin(aktmin,disc);
}

HRESULT CRootnode::Getmax(CComVariant& aktmax,long disc)
{
    return m_pSon->Getmax(aktmax,disc);
}

HRESULT CRootnode::UpdateSon(CKnoten* alt,CKnoten* neu)
{
    ASSERT(neu);
    if (NULL == neu)
    {
        TRACE("*** CRootnode::UpdateSon *** Fehler : E_POINTER (0x%x) *** Parameter neu == NULL ***",E_POINTER);
        return E_POINTER;
    }

    if (alt == m_pSon)
    {
        m_pSon = neu;
        Test();
        return S_OK;
    }
    else
    {
        Test();
        TRACE("*** CRootnode::UpdateSon *** Fehler : E_FAIL (0x%x) ** Parameter 'alt' ist ungleich 'm_pson'\n",E_FAIL);
        return E_FAIL;
    }
}

HRESULT CRootnode::Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;

    ASSERT(m_pSon);
    if (NULL == m_pSon)
        return E_POINTER;

    return m_pSon->Intersection(pIQuestion,pICallback,pReturn);
}

HRESULT CRootnode::Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn)
{
    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return E_POINTER;

    ASSERT(m_pSon);
    if (NULL == m_pSon)
        return E_POINTER;

    return m_pSon->Containment(pIQuestion,pICallback,pReturn);
}

HRESULT CRootnode::Optimize()
{
    ASSERT(m_pSon);
    if (NULL == m_pSon)
        return E_POINTER;

    ASSERT(m_pSpatialTree);
    if (NULL == m_pSpatialTree)
        return E_POINTER;

    // ganzen Baum in Liste schreiben
    OBJLISTE templist;
    m_pSon -> WriteToList(templist);

    if (templist.size() <= MAXBUCKETENTRIES)
        // nur ein Leafnode, nichts zum optimieren da
        return S_OK;

    // ganzen Baum löschen
    delete m_pSon;

    // und neu erzeugen
    m_pSon = (CKnoten*) new CInternalnode(templist,0,m_pSpatialTree);
    if (NULL == m_pSon)
        return E_FAIL;
    else
        return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CSpatialTree::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpatialTreeInit,
		&IID_ISpatialTree,
		&IID_IPersistStream,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// Structuren
CSpatialTree::CSpatialTree()
    :m_treeRoot(this)
        {
            TRACE("Entering CSpatialTree::Constructor\n\n");
            m_nDimension=0;
        }

CSpatialTree::~CSpatialTree()
        {
            TRACE("Entering CSpatialTree::Destructor\n\n");

            // solange noch irgendetwas da ist
            while (m_treeID.size() != 0)
            {
                // Iterator auf Anfang holen und Inhalt deleten+nullen
                delete *m_treeID.begin();
                *m_treeID.begin() = NULL;
                // dann den iterator selbst erasen;
                m_treeID.erase(m_treeID.begin());
            }
        }

HRESULT CSpatialTree::GetValues(
            IDispatch* pInterface,CComVariant& amin,CComVariant& amax,int i)
        {
    // holt die Werte der Dimension i aus dem angegebenen Objekt 
    // und wandelt sie in den entsprechenden Typ um

//            TRACE("Entering CSpatialTree::GetValues\n\n");
            VARIANT vmin;
            VARIANT vmax;
            DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};

            ASSERT(pInterface);
            if (NULL==pInterface)
                return E_POINTER;

//            DefineSmartInterface(TestObjekt);
            WTestObjekt IpTestObj = pInterface;
            
            IpTestObj->get_xmin(&vmin);
            IpTestObj->get_xmax(&vmax);
  
/*            
            CObjDispatch wObjekt;
            wObjekt.AttachDispatch(pInterface);

            
            
/*
            try {   // Werte abfragen
                DISPID id=m_vecDimensionMap[i].m_nmin;
//                TRACE("DISPID min %x\n",id);
                wObjekt.get_value(id,&vmin);        
                
                id=m_vecDimensionMap[i].m_nmax;
//                TRACE("DISPID max %x\n",id);
                wObjekt.get_value(id,&vmax);
            } catch ( COleException e) {
		        TRACE("CSpatialTree::GetValues COleException\n");	
                return E_INVALIDARG;
            } catch ( COleDispatchException e){
		        TRACE("CSpatialTree::GetValues COleAutomationException\n");	
                return E_INVALIDARG;
            }*/
            
            // Typ umwandeln
            amin=vmin;
            amin.ChangeType(m_vecDimensionMap[i].m_ncomptype);

            amax=vmax;
            amax.ChangeType(m_vecDimensionMap[i].m_ncomptype);
            
            //wurde oben attached
//            wObjekt.DetachDispatch();
            return S_OK;
        }

bool CSpatialTree::IntersectDim(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion,ULONG dim)
{
    ASSERT(pInterface);
    if (NULL == pInterface)
        return FALSE;

    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return FALSE;

    ASSERT(dim<m_nDimension);
    if (dim >= m_nDimension)
        return FALSE;

    CComVariant objmin,objmax,winmin,winmax;

    GetValues(pInterface,objmin,objmax,dim);
    pIQuestion->GetBorder(dim,&winmin,&winmax);

    return ((winmin<=objmax)&&(winmax>=objmin));
}

bool CSpatialTree::Intersect(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion)
{
    ASSERT(pInterface);
    if (NULL == pInterface)
        return FALSE;

    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return FALSE;

    bool bErg = TRUE;
    for (ULONG i=0;(i<m_nDimension)&&(TRUE == bErg);i++)
        bErg = IntersectDim(pInterface,pIQuestion,i);

    return bErg;
}

bool CSpatialTree::ContainedDim(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion,ULONG dim)
{
    ASSERT(pInterface);
    if (NULL == pInterface)
        return FALSE;

    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return FALSE;

    ASSERT(dim<m_nDimension);
    if (dim >= m_nDimension)
        return FALSE;

    CComVariant objmin,objmax,winmin,winmax;

    GetValues(pInterface,objmin,objmax,dim);
    pIQuestion->GetBorder(dim,&winmin,&winmax);

    return ((winmin<=objmin)&&(winmax>=objmax));
}

bool CSpatialTree::Contained(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion)
{
    ASSERT(pInterface);
    if (NULL == pInterface)
        return FALSE;

    ASSERT(pIQuestion);
    if (NULL == pIQuestion)
        return FALSE;

    bool bErg = TRUE;
    for (ULONG i=0;(i<m_nDimension)&&(TRUE == bErg);i++)
        bErg = ContainedDim(pInterface,pIQuestion,i);

    return bErg;
}

// ISpatialTreeInit
STDMETHODIMP CSpatialTree::put_AddDimension(
            DISPID  amin,
            DISPID  amax,
            VARTYPE comptype,
            int*    pIndex)
        {   
            TRACE("Entering CSpatialTree::AddDimension\n");

            ASSERT(pIndex);
            if (NULL==pIndex)
                return E_POINTER;

            if (AcceptVartype(comptype))
            {
                // Einfügen in Dimensionmap
                DimensionMapEntry tNewDimEntry(amin,amax,comptype);
                m_vecDimensionMap.push_back(tNewDimEntry);

                // wir haben jetzt eine Dimension mehr
                *pIndex=m_nDimension;
                m_nDimension++;

/*                // TRACECODE
                #ifdef _DEBUG
                vector <DimensionMapEntry>::iterator i;
                int n;

                TRACE("%d Einträge\n\n",m_nDimension);
                for(i=m_vecDimensionMap.begin(),n=1;i!=m_vecDimensionMap.end();i++,n++)
                    TRACE("%d | %d %d\n",n,i->m_nmin,i->m_nmax);
                #endif
*/
                return S_OK;
            }
            else
            {
                TRACE("**  Error in CSpatialTree::AddDimension ** Nichtunterstützter VARTYP in Argument comptype**\n");
                *pIndex=m_nDimension;
                return E_INVALIDARG;
            }
        }

STDMETHODIMP CSpatialTree::put_SiteInterface(
            IUnknown *pSiteInterface)                          
        {   
            TRACE("Entering CSpatialTree::SiteInterface\n");

            // Inputs abtesten
            ASSERT(pSiteInterface);
            if (NULL==pSiteInterface)
                return E_POINTER;

            m_ISiteInterface=pSiteInterface;
            return S_OK;
        }

// ISpatialTree
    // basics

// Hilfsfunktion für Liste
// entfällt, da jetzt Baum eingesetzt wird
/*
bool CSpatialTree::findIdinList(list<Objectentry*>& liste,list<Objectentry*>::iterator& i,ULONG id)
{
    i = liste.begin();
    while (i != liste.end())
    {
        if ((*i)->m_ID == id)
        {
            return TRUE;
        }
        i++;
    }
    return FALSE;
} 
*/      

STDMETHODIMP CSpatialTree::Insert(
            IDispatch* pnewObj,
            ULONG ObjNr)
        {   TRACE("Entering CSpatialTree::Insert\n");

            // Inputs abtesten
            ASSERT(pnewObj);
            if (NULL==pnewObj)
                return E_POINTER;

            // member abtesten
            if (m_nDimension <= 0)
                // der Baum ist dimensions-, und damit sinnlos
                return E_INVALIDARG;

            // neues Objekt erzeugen
            Objectentry* pobj= new Objectentry(pnewObj,ObjNr);
            if (NULL == pobj)
                return E_POINTER;

            // in den ID Baum einordnen    
            if (m_treeID.insert(pobj).second == FALSE)
// 2 Zeilen eingefügt (Listencode)
//          list<Objectentry*>::iterator i = m_treeID.begin();
//          if (findIdinList(m_treeID,i,ObjNr))
            {
                // Fehlerbehandlung ID bereits vorhanden
                // aufräumen
                delete pobj;
                // und fein grüßen
                return E_INVALIDARG;
            }

// entfernt, da Listencode
//            m_treeID.push_back(pobj);
            // in den skd-Tree einordnen
            HRESULT hr = m_treeRoot.Insert(pobj);
            if (FAILED(hr))
            {
                set<Objectentry*,
                    Objectentry_pless>::iterator i;

                //aufräumen
// Listencode
/*                  if (!findIdinList(m_treeID,i,ObjNr))
                  {
                      TRACE("CSpatialTree::Insert Objekt in Liste geschrieben und nicht wieder gefunden\n");
                      ASSERT(FALSE);
                      return E_FAIL;
                  }*/
                    
                i = m_treeID.find(pobj);
//              m_treeID.erase(i);    // hier noch kontrollieren ob erase auch den inhalt von i löscht
//              *i = NULL;
                
                // aus ID-Tree entfernen
                m_treeID.erase(i);
                
                // Löschen
                delete pobj; // VORSICHT!!
                return hr;
            }
            // Erfolg: Objekt wurde in beide Bäume eingefügt
            return S_OK;
}

STDMETHODIMP CSpatialTree::DeletebyNr(
            ULONG ObjNr)       
        {   TRACE("Entering CSpatialTree::DeletebyNr\n");
            set<Objectentry*,
                Objectentry_pless>::iterator i;
//            list<Objectentry*>::iterator     i;               

            Objectentry obj(NULL,ObjNr);    // Suchobjekt

            // member abtesten
            if (m_nDimension <= 0)
                // der Baum ist dimensions-, und damit sinnlos
                return E_INVALIDARG;

            // Ist Baum leer
            if (0 == m_treeID.size()) 
                return E_INVALIDARG;
    
            //aufräumen
            i = m_treeID.find(&obj);
            if ((*i)->m_ID == ObjNr)
            {
                // gefunden
                // aus skd-Tree entfernen, anhand des im ID Tree gefunden Objektes

                // zusätzlicher Test für Debugging
#ifdef _DEBUG
                // Elementanzahl in ID_Baum gleich Elementanzahl in Baum
                OBJLISTE templist;
                m_treeRoot.WriteToList(templist);
                ASSERT(templist.size() == m_treeID.size());
#endif
                // Ergebnis merken zum returnen
                HRESULT hr = m_treeRoot.Delete(*i,NULL);
                // wenn Fehler auftritt, dann sofort verlassen 

#ifdef _DEBUG
                OBJLISTE templist2;
                m_treeRoot.WriteToList(templist2);
                // Elementanzahl in ID_Baum gleich Elementanzahl in Baum
                ASSERT(templist2.size() == m_treeID.size()-1);
#endif

                // Objekt wurde nicht im Baum nicht gefunden, sehr schwerer Fehler 
                if (FAILED(hr))
                    return hr;

                Objectentry* ptemp = *i; // Eintrag merken
                *i = NULL;
            // aus ID-Tree entfernen
                m_treeID.erase(i);
            // Löschen
                delete ptemp;
                

                return hr;
            }
            else 
            // gibts doch gar nicht 
                return E_INVALIDARG;
        }

//	statistics
STDMETHODIMP CSpatialTree::get_Count(
            ULONG* pCount)
        {   TRACE("Entering CSpatialTree::get_Count\n");
            // Inputs abtesten
            ASSERT(pCount);
            if (NULL==pCount)
                return E_POINTER;

            *pCount=m_treeID.size();
            return S_OK;}

STDMETHODIMP CSpatialTree::get_Container(
            ISpatialTreeQuery** ppIQuestion)
        {   TRACE("Entering CSpatialTree::get_Container\n");

            ASSERT(ppIQuestion);
            if (NULL==ppIQuestion)
                return E_POINTER;

            *ppIQuestion=NULL;

            // Container erzeugen
            WSpatialTreeQuery clContainer(CLSID_CSpatialTreeQuery);

            // Containerwerte ermitteln
            CComVariant contmin,contmax;    // Werte für Container   
            
            for (int d=0;d<m_nDimension;d++)
            {
            // Minholen
                HRESULT hr = m_treeRoot.Getmin(contmin,d);
                if (FAILED(hr))
                    return hr; // clContainer geht out of scope-> wird Released 
                    
            // Maxholen
                hr = m_treeRoot.Getmax(contmax,d);
                if (FAILED(hr))
                    return hr; // clContainer geht out of scope-> wird Released 

            // in Container schreiben
                hr = clContainer->AddDim(
                    contmin,
                    contmax,
                    m_vecDimensionMap[d].m_ncomptype);

                if (FAILED(hr))
                    return hr; // clContainer geht out of scope-> wird Released 
            }
  
            *ppIQuestion=clContainer.detach(); // Eine Referenz wird noch gebraucht
            TRACE("Leaving CSpatialTree::get_Container\n");
            return S_OK;}

STDMETHODIMP CSpatialTree::get_Dimension(
            ULONG* pDim)
        {   TRACE("Entering CSpatialTree::get_Dimension\n");
            // Inputs abtesten
            ASSERT(pDim);
            if (NULL==pDim)
                return E_POINTER;

            *pDim=m_nDimension;

            return S_OK;}

STDMETHODIMP CSpatialTree::get_DimensionIDs(
            ULONG       Dim,
            DISPID*     pmin,
            DISPID*     pmax,
            VARTYPE*    pcomptype)
        {   TRACE("Entering CSpatialTree::get_DimensionIDs\n");
            // vorsicht Informatiker zählen bei 0 los, laso auch die Dim so wählen

            // Inputs abtesten
            ASSERT(pmin);
            ASSERT(pmax);
            ASSERT(pcomptype);

            if ((NULL==pmin)||(NULL==pmax)||(NULL==pcomptype))
                return E_POINTER;

            *pmin = -1;
            *pmax = -1;
            *pcomptype = -1;

            if (Dim>=m_nDimension)
                return E_INVALIDARG;

            *pmin=m_vecDimensionMap[Dim].m_nmin;
            *pmax=m_vecDimensionMap[Dim].m_nmax;
            *pcomptype=m_vecDimensionMap[Dim].m_ncomptype;

            return S_OK;}

STDMETHODIMP CSpatialTree::Optimize(void)
{
    return m_treeRoot.Optimize();
}

//	question
STDMETHODIMP CSpatialTree::Intersection(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            IEnumUnknown**          ppReturn)
        {   TRACE("Entering CSpatialTree::Intersection\n");

            ASSERT(pIQuestion);
//            ASSERT(pICallback);
            ASSERT(ppReturn);

            if ((NULL==pIQuestion)/*||(NULL==pICallback)*/||(NULL==ppReturn))
               return E_POINTER;
            
            *ppReturn = NULL;
            CComObject<CEnumUnknown> 
                *pclEnumUnknown=new CComObject<CEnumUnknown>;//(CLSID_CEnumUnknown);

            ULONG cRef=pclEnumUnknown->AddRef();
            TRACE("SpatialTree::Intersection pclEnumUnknown besitzt %d Referenzen.\n",cRef);

            HRESULT hr = m_treeRoot.Intersection(pIQuestion,pICallback,pclEnumUnknown);

//            ULONG cRef=pclEnumUnknown->AddRef();
            *ppReturn=pclEnumUnknown;//.detach();
            
            return hr;}

STDMETHODIMP CSpatialTree::Containment(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            IEnumUnknown**          ppReturn)
        {   TRACE("Entering CSpatialTree::Containment\n");

            ASSERT(pIQuestion);
//            ASSERT(pICallback);
            ASSERT(ppReturn);

            if ((NULL==pIQuestion)/*||(NULL==pICallback)*/||(NULL==ppReturn))
               return E_POINTER;
            
            *ppReturn = NULL;
            CComObject<CEnumUnknown> 
                *pclEnumUnknown=new CComObject<CEnumUnknown>;//(CLSID_CEnumUnknown);

            ULONG cRef=pclEnumUnknown->AddRef();
            TRACE("SpatialTree::containment pclEnumUnknown besitzt %d Referenzen.\n",cRef);

            HRESULT hr = m_treeRoot.Containment(pIQuestion,pICallback,pclEnumUnknown);

//            ULONG cRef=pclEnumUnknown->AddRef();
            *ppReturn=pclEnumUnknown;//.detach();
            
            return hr;}

// IPersistStream
STDMETHODIMP CSpatialTree::GetClassID(
            struct _GUID *)
        {   TRACE("Entering CSpatialTree::GetClassID\n");
            return E_NOTIMPL;}

STDMETHODIMP CSpatialTree::IsDirty(
            void)
        {   TRACE("Entering CSpatialTree::IsDirty\n");
            return E_NOTIMPL;}

STDMETHODIMP CSpatialTree::Load(
            IStream     *pStm)
        {   TRACE("Entering CSpatialTree::Load\n");
            return E_NOTIMPL;}

STDMETHODIMP CSpatialTree::Save(
            IStream     *pStm,
            BOOL        fClearDirty)
        {   TRACE("Entering CSpatialTree::Save\n");
            return E_NOTIMPL;}

STDMETHODIMP CSpatialTree::GetSizeMax(
            ULARGE_INTEGER *pcbSize)
        {   TRACE("Entering CSpatialTree::GetSizeMax\n");
            return E_NOTIMPL;}
