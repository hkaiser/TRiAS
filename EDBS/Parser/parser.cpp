// parser.cpp : Implementierung von Cparser
#include "stdafx.h"
#include "Edbs.h"
#include "CStringEx.h"
#include "parser.h"
#include "EDBS_Linie.h"
#include "EDBS_BesondereInformation.h"

/////////////////////////////////////////////////////////////////////////////
// Cparser


Cparser::Cparser()
{
	msModus = 0;
	lBytesParsed = 0;
 	m_pIStatus = NULL;
	m_tStatusCreated = false;
	mpobjsEDBS = NULL;
}

Cparser::~Cparser()
{
	if( mpobjsEDBS ) {
		if(mpobjsEDBS->Release())
			ASSERT(0);
		mpobjsEDBS = NULL;
	}
}

//	CreateStatusDialog  -----------------------------------------------
void Cparser::CreateProgressIndicator()
{
	HRESULT hr;
	
	if( NULL == m_pIStatus ) {
		hr = CoCreateInstance(
			CLSID_ProgressIndicator,    //Class identifier (CLSID) of the object
			NULL,						//Pointer to controlling IUnknown
			CLSCTX_ALL ,		//Context for running executable code
			IID_IProgressIndicator,     //Reference to the identifier of the interface
			(LPVOID*)&m_pIStatus        //Address of output variable that receives 
										// the interface pointer requested in riid
			);
		if( NULL != m_pIStatus )
			m_tStatusCreated = true;
	}

	if( NULL != m_pIStatus ) {
//		HWND	hNewWnd = m_pIStatus -> InitNew (__hWndM, 0L);
		HWND	hNewWnd = m_pIStatus -> InitNew( m_hWnd, 0L);

		if( NULL == hNewWnd && m_tStatusCreated ) {
			m_pIStatus -> Release();
			m_pIStatus = NULL;
			m_tStatusCreated = false;
		}
	}
}	// CreateStatusDialog

//	SetDefaultStatusTexte  --------------------------------------------
void Cparser::SetDefaultStatusTexte( const char *status1,
		const char *status2, const char *filename, const char *file )
{
	if( file )
		m_strStatFile = file;
	else
		m_strStatFile.Empty();
	if( filename )
		m_strStatFilename = filename;
	else
		m_strStatFilename.Empty();
	if( status1 )
		m_strStatusText1 = status1;
	else
		m_strStatusText1.Empty();
	if( status2 )
		m_strStatusText2 = status2;
	else
		m_strStatusText2.Empty();
}	// SetDefaultStatusTexte


//	InitStatusDialog  -------------------------------------------------
HRESULT Cparser::InitProgressIndicator( const char *filename, ULONG filesize, const char *text )
{	HRESULT		hr = NOERROR;
	CString		txt;

	if ( m_pIStatus != NULL ) {	
		hr = m_pIStatus -> Restart (0L, filesize, PIFLAG_FILE|PIFLAG_FILENAME|
					PIFLAG_STATUS|PIFLAG_RESULT|
					PIFLAG_ADJUSTPERCENT|PIFLAG_INIT_SHOWWINDOW );
//					PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
		if (FAILED(hr))
			return hr;

// diverse Text initialisieren
		txt = "Status des aktuellen Imports";
		m_pIStatus -> ChangeText (PIFLAG_CAPTION, txt );
		if ( !m_strStatFile.IsEmpty())
			m_pIStatus -> ChangeText (PIFLAG_FILE, m_strStatFile );

		if ( filename )
			m_pIStatus -> ChangeText (PIFLAG_FILENAME, filename );
		else
			if ( !m_strStatFilename.IsEmpty())
				m_pIStatus -> ChangeText (PIFLAG_FILENAME, m_strStatFilename );

		if ( text )
			m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, text );
		else
			if ( !m_strStatusText1.IsEmpty())
				m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, m_strStatusText1 );

		if ( !m_strStatusText2.IsEmpty())
			m_pIStatus -> ChangeText (PIFLAG_RESULT, m_strStatusText2 );

	}
	return hr;
}	// InitStatusDialog

//	ChangeStatusText  -------------------------------------------------
void Cparser::ChangeStatusText( const char *txt1, const char *txt2 )
{
	if (( txt1 != NULL ) && ( m_pIStatus != NULL ))
		m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, txt1 );
	
	if (( txt2 != NULL ) && ( m_pIStatus != NULL ))
		m_pIStatus -> ChangeText (PIFLAG_RESULT, txt2 );
}	// ChangeStatusText

//	SetupStatus  ------------------------------------------------------
int Cparser::SetProgressIndicator( ULONG pos )
{	if( m_pIStatus != NULL )
		return m_pIStatus -> SetPosition( pos );
	else
		return 0;
}	// SetupStatus

//	ReleaseStatusDialog  ----------------------------------------------
void Cparser::ReleaseProgressIndicator()
{	
	if( m_pIStatus != NULL && m_tStatusCreated ) {
		m_pIStatus->Release();
		m_pIStatus = NULL;
		m_tStatusCreated = false;
	}
}

//	NutzerAbbruch  ----------------------------------------------------
bool Cparser::CheckUserBreak()
{
	bool result = false;
	if ( m_pIStatus != NULL )
		result = (NULL != (m_pIStatus -> WasCanceled()));
	return result;
}	// NutzerAbbruch

//	ResetAbbruch  -----------------------------------------------------
void Cparser::ResetUserBreak()
{
	if ( m_pIStatus != NULL )
		m_pIStatus -> Restart (0L, 0L, PIFLAG_RESETCANCEL );
}	// ResetAbbruch


STDMETHODIMP Cparser::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_Iparser
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP Cparser::get_SourceFileName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrDatenquelle(mstrSourceFileName);

	*pVal = bstrDatenquelle.Detach();

	return S_OK;
}

STDMETHODIMP Cparser::put_SourceFileName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrSourceFileName = newVal;

	return S_OK;
}

STDMETHODIMP Cparser::LoadObjects(long *plResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
Dim fStatus As New frmStatus
*/
 HRESULT hResult;
 CStringEx strReadBuffer;
 int iSatzlaenge;
 int iSuchkriterienAnfang;
 CStringEx strIN;
 CStringEx strZugehoerigkeitsschluessel;
 bool tFehler;

//	CreateProgressIndicator();

	if( mpobjsEDBS ) {
		if(mpobjsEDBS->Release())
			ASSERT(0);
		mpobjsEDBS = NULL;
	}
	hResult = CComObject<CEDBS_Objekte>::CreateInstance(&mpobjsEDBS); 
	mpobjsEDBS->AddRef();

	lBytesParsed = 0;
    strBuffer = "";
    tFehler = false;

	if(	mSourceFile.Open(mstrSourceFileName, CFile::typeText | CFile::modeRead, NULL) ) {
		
//		InitProgressIndicator( mstrSourceFileName, mSourceFile.GetLength(), NULL );

		while( mSourceFile.ReadString(strReadBuffer) ) {
			lBytesParsed += strReadBuffer.GetLength() + 2;

//			SetProgressIndicator( lBytesParsed );

			if( strReadBuffer.Left(4) != _T("EDBS")  )
				MessageBox(0,"Syntaxfehler, Zeile beginnt nicht mit EDBS!","EDBS-Parser",0);
			else {
	//           rsEDBS!SA = Mid(strReadBuffer, 1, 4)
	//           rsEDBS!SL = Mid(strReadBuffer, 5, 8)
				iSatzlaenge = atoi(strReadBuffer.Mid( 4, 4));
				if( iSatzlaenge != strReadBuffer.GetLength() - 12 ) {
					MessageBox(0,"Fehlerhafte Satzlänge" + strReadBuffer.Mid( 4, 4),"EDBS-Parser",0);
					tFehler = true;
				}
				iSuchkriterienAnfang = atoi(strReadBuffer.Mid( 8, 4));
	//           rsEDBS!SuchkriterienAnfang = iSuchkriterienAnfang
				if( iSuchkriterienAnfang != 0 ) {
	//                rsEDBS!Suchkriterien = Mid(strReadBuffer, iSuchkriterienAnfang)
					strSearchCriteria = strReadBuffer.Mid(11 + iSuchkriterienAnfang);
					strReadBuffer = strReadBuffer.Left( 11 + iSuchkriterienAnfang);
				}
	//            rsEDBS!OP = Mid(strReadBuffer, 13, 4)
	//            rsEDBS!QU = Mid(strReadBuffer, 17, 12)
	//            rsEDBS!Satznummer = Mid(strReadBuffer, 17, 6)
				strZugehoerigkeitsschluessel = strReadBuffer.Mid(22, 2);
	//            rsEDBS!Zugehörigkeitsschlüssel = Mid(strReadBuffer, 23, 2)
	//            rsEDBS!Quittungsschlüssel = Mid(strReadBuffer, 25, 4)

				strIN = strReadBuffer.Mid( 28, 8);
	//          rsEDBS!IN = Mid(strReadBuffer, 29, 8)
	//          rsEDBS!Namenstyp = Mid(strReadBuffer, 29, 1)
	//          rsEDBS!Hauptdatei = Mid(strReadBuffer, 30, 1)
	//          rsEDBS!Unterdatei = Mid(strReadBuffer, 31, 1)
        
				strReadBuffer = strReadBuffer.Mid(36);
				strBuffer = strBuffer + strReadBuffer;

				if( strZugehoerigkeitsschluessel != "A " && strZugehoerigkeitsschluessel != "F " ) {
	//                strLogBuffer = strBuffer
	//                rsEDBS!Daten = strBuffer
					if( tFehler )
						tFehler = false;
					else {
						if( "ULOBNN  " == strIN ) {
							bSourceFileType = EDBS;
							readULO();
						}
						else if( "ULO8ALK " == strIN ) {
							bSourceFileType = ALK;
							readULO();
						}
						else if( "DLOB2005" == strIN ) {
							readDLOB2005();
						}
						else if( "ULQA0000" == strIN ) {
							readULQA0000();
						}
					}
					strBuffer = "";
				}
	//            rsEDBS.Update
			}
		}

		mSourceFile.Close();
		mpobjsEDBS->get_Count(plResult);
	}
	else
		*plResult = -1;

//  fStatus.Hide

//	ReleaseProgressIndicator();

	return S_OK;
}

int Cparser :: GetWHF()
{
 int iWHF;
    if( strBuffer.GetLength() < 4 ) {
        MessageBox( NULL, "Fehler: GetWHF Len(strBuffer) < 4","EDBS-Parser, GetWHF" ,0);
		iWHF = -1;
    }
	else {
        iWHF = atoi(strBuffer.Left( 4 ));
        if( iWHF != 0 ) {
			if( strBuffer.GetLength() < 4 ) {
				MessageBox( NULL, "Fehler: GetWHF WHF != 0 And Len(strBuffer) < 4","EDBS-Parser, GetWHF" ,0);
				iWHF = -1;
            }
        }
        strBuffer = strBuffer.Mid( 4 );
    }
	return iWHF;
}

long Cparser :: GetKoordinate( CStringEx &strRH )
{
// Format des KoordinatenPaares in txt:
//      rrhhr_h_rrrrrrhhhhhh in ATKIS
//      rrhhrrhhrrrrrrhhhhhh in ALK
//      +hhhhhhhhh+rrrrrrrrr in Soldner-Berlin
 long lResult = 0;

	if( strBuffer.GetLength() < 20 ) 
		lResult = -1;
	else {
		if( strBuffer.Left( 2 ) == "TT" ) {		// Drehwinkel für Text
			strRH = strBuffer.Left(20);
			lResult = 1;
		}
		else if( strBuffer.GetAt(0) == '+' )	// SOLDNER
			strRH = strBuffer.Mid(10,10) + strBuffer.Left(10);
		else if( strBuffer.GetAt(5) == ' ' )	// ATKIS
			strRH = strBuffer.Mid(2,2) + strBuffer.Mid(6,1)
					+ strBuffer.Mid(14,6) + "0" + strBuffer.Mid(0,2)
					+ strBuffer.Mid(4,1) + strBuffer.Mid(8,6) + "0";
		else                                    // ALK
			strRH = strBuffer.Mid(2,2) + strBuffer.Mid(6,2)
					+ strBuffer.Mid(14,6) + strBuffer.Mid(0,2)
					+ strBuffer.Mid(4,2) + strBuffer.Mid(8,6);
		strBuffer = strBuffer.Mid( 20 );
	}
	return lResult;
}

void Cparser :: readULQA0000( void ) {
/*
	On Error GoTo Err_readULQA0000
 Dim iWHF1 As Integer
    iWHF1 = GetWHF()
'    If iWHF1 = 0 Then
'        MsgBox "Auftragskennsatz mit Wiederholungsfaktor = 0"
'        rsAuftragskennsatz.AddNew
'        IDAuftragskennsatz = rsAuftragskennsatz!IDAuftragskennsatz
'        rsAuftragskennsatz.Update
'    ElseIf iWHF1 = 1 Then
'        rsAuftragskennsatz.AddNew
'        IDAuftragskennsatz = rsAuftragskennsatz!IDAuftragskennsatz
'        rsAuftragskennsatz!Dateiname = strFileName
'        rsAuftragskennsatz!AuftragskennzeichenDienststelle = Mid(strBuffer, 1, 14)
'        rsAuftragskennsatz!AuftragskennzeichenAuftragsnummer = Mid(strBuffer, 15, 5)
'        rsAuftragskennsatz!AuftragskennzeichenWeitereGliederung = Mid(strBuffer, 20, 1)
'        rsAuftragskennsatz!Prüfzeichen = Mid(strBuffer, 21, 1)
'        rsAuftragskennsatz!Auftragsart = Mid(strBuffer, 22, 1)
'        rsAuftragskennsatz!AktualitätDesAuftrags = Mid(strBuffer, 23, 2)
'        rsAuftragskennsatz!Integrationshinweis = Mid(strBuffer, 25, 1)
'        rsAuftragskennsatz!Bezirksgrundstücksdatenbank = Mid(strBuffer, 26, 2)
'        rsAuftragskennsatz!Antragshinweis = Mid(strBuffer, 28, 11)
'        rsAuftragskennsatz!VerarbeitungssteuerungAuftragskennung = Mid(strBuffer, 39, 1)
'        rsAuftragskennsatz!VerarbeitungssteuerungBenutzungsart = Mid(strBuffer, 40, 8)
'        rsAuftragskennsatz!VerarbeitungssteuerungTextFürAusgabe = Mid(strBuffer, 48, 32)
'        rsAuftragskennsatz!VerarbeitungssteuerungVerarbeitungsmodus = Mid(strBuffer, 80, 2)
'        rsAuftragskennsatz!VerarbeitungssteuerungAnzahlDerAusfertigungen = Mid(strBuffer, 82, 2)
'        rsAuftragskennsatz!AuftragsinhaltPunktdatenkennung = Mid(strBuffer, 84, 2)
'        rsAuftragskennsatz!AuftragsinhaltDatenkennungALK = Mid(strBuffer, 86, 2)
'        rsAuftragskennsatz!AuftragsinhaltMessungselementekennung = Mid(strBuffer, 88, 2)
'        rsAuftragskennsatz!AuftragsinhaltDatenkennungDLM = Mid(strBuffer, 90, 2)
'        rsAuftragskennsatz!AuftragsinhaltDatenkennungDKM = Mid(strBuffer, 92, 2)
'        rsAuftragskennsatz!AuftragsinhaltUnbelegt = Mid(strBuffer, 94, 50)
'        rsAuftragskennsatz!Meridianstreifensystem = Mid(strBuffer, 144, 1)
'        rsAuftragskennsatz!Verarbeitungsstop = Mid(strBuffer, 145, 1)
'        rsAuftragskennsatz!VerarbeitungsstatusAusgabe = Mid(strBuffer, 146, 1)
'        rsAuftragskennsatz!VerarbeitungsstatusErgebnisDesVerarbeitungsschrittes = Mid(strBuffer, 147, 1)
'        rsAuftragskennsatz!VerarbeitungsstatusArtDesVerarbeitungsschrittes = Mid(strBuffer, 148, 1)
'        rsAuftragskennsatz!HöchsteEDBSSatznummerBeiEingabe = Mid(strBuffer, 149, 6)
'        rsAuftragskennsatz!AnzahlWeitererEDBSSätzeBeiAusgabe = Mid(strBuffer, 155, 6)
'        rsAuftragskennsatz!DatumErsteintragAuftragsbuch = Mid(strBuffer, 161, 6)
'        rsAuftragskennsatz!DatumLetzteVerarbeitung = Mid(strBuffer, 167, 6)
'        rsAuftragskennsatz!DatumAusgabeDesErledigtenAuftrages = Mid(strBuffer, 173, 6)
'        rsAuftragskennsatz!ZuständigeStellePunktnummer = Mid(strBuffer, 179, 14)
'        rsAuftragskennsatz!Plausibilitätssteuerung = Mid(strBuffer, 192, 12)
'        rsAuftragskennsatz!HinweisFürGeometriebehandlung = Mid(strBuffer, 204, 1)
'        rsAuftragskennsatz!FolgeverarbeitungTerminalErgebnisdaten = Mid(strBuffer, 205, 8)
'        rsAuftragskennsatz!FolgeverarbeitungFolgeprogrammErgebnisdaten = Mid(strBuffer, 213, 8)
'        rsAuftragskennsatz!FolgeverarbeitungTerminalnameVerarbeitungsprotokoll = Mid(strBuffer, 221, 8)
'        rsAuftragskennsatz!FolgeverarbeitungFolgeprogrammVerarbeitungsprotokoll = Mid(strBuffer, 229, 8)
'        rsAuftragskennsatz!Prioritätssteurung = Mid(strBuffer, 237, 1)
'        rsAuftragskennsatz!Auftragssteuerung = Mid(strBuffer, 238, 10)
'        rsAuftragskennsatz!Antragsnummer = Mid(strBuffer, 248, 10)
'        rsAuftragskennsatz.Update
'    Else
'        MsgBox "Auftragskennsatz mit Wiederholungsfaktor > 1"
'    End If
Exit Sub

Err_readULQA0000:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "EDBS, Auftragskenndaten"
    Resume Next
End Sub
*/
}


void Cparser :: readULO( void ) {
 int iWHF1;
    iWHF1 = GetWHF();
    if( iWHF1 < 0 )
       _ASSERT(0);
	else {
		while( iWHF1 > 0 ) {
	        iWHF1--;
			if( GetAnfangspunktDerLinie() < 0 )
				break;      
		}
	}
}


long Cparser :: GetAnfangspunktDerLinie( void )
{
 long lResult = 0;
 CStringEx strRH;
 int iWHF1;
 int iWHF2;
 double dblHA, dblRA;

	iWHF1 = GetWHF();
    if( iWHF1 < 0 ) {
        lResult = -1;
	}
    else {
		while( iWHF1 > 0 && lResult >= 0 ) {
			iWHF1--;
//	'        rsAnfangspunktDerLinie.AddNew
//	'        rsAnfangspunktDerLinie!IDAuftragskennsatz = IDAuftragskennsatz
//	'        IDAnfangspunktDerLinie = rsAnfangspunktDerLinie!IDAnfangspunktDerLinie
			lResult = GetKoordinate( strRH );
//	'        rsAnfangspunktDerLinie!AnfangspunktDerLinieH = Left(strRH, 10)
//	'        rsAnfangspunktDerLinie!AnfangspunktDerLinieR = Right(strRH, 10)
//	'        rsAnfangspunktDerLinie!Prüfzeichen = Mid(strBuffer, 21, 1)
			dblHA = atof(strRH.Left(10));
			dblRA = atof(strRH.Right(10));
        
			strBuffer = strBuffer.Mid(1);
			iWHF2 = GetWHF();
			if( iWHF2 < 0 ) {
				lResult = -1;
				break;
			}
			else {
//	'        rsAnfangspunktDerLinie!WHFEndpunktDerLinie = iWHF2
				while( iWHF2 > 0 ) {
					iWHF2--;
					if( GetEndpunktDerLinie(dblRA, dblHA) < 0 ) {
						lResult = -1;
						break;
					}
				}
				iWHF2 = GetWHF();
				if( iWHF2 < 0 ) {
					lResult = -1;
				}
				else {
//					rsAnfangspunktDerLinie!WHFFunktionDesObjekts = iWHF2
					while( iWHF2 > 0 ) {
						iWHF2--;
						if( GetFunktionDesObjekts(dblRA, dblHA) < 0 ) {
							lResult = -1;
							break;
						}
					}
				}
//		        rsAnfangspunktDerLinie.Update
			}
		}
	}
    return lResult;
/*
Exit Function

Err_GetAnfangspunktDerLinie:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "EDBS, Anfangspunkt der Linie"
    GetAnfangspunktDerLinie = False
    Exit Function
*/
}


long Cparser :: GetEndpunktDerLinie( double dblRA, double dblHA )
{
 HRESULT hResult;
 long lResult = 0;
 CStringEx strRH;
 int iWHF1;
 int iWHF2;
 CComObject<CEDBS_Geometrie> *pobjGeometrie;
 int ix;
 
    iWHF1 = GetWHF();
    if( iWHF1 < 0 ) {
        lResult = -1;
    }
	else {
		while( iWHF1 > 0 && lResult >= 0 ) {
			iWHF1--;
			lResult = GetKoordinate( strRH );
        
			hResult = CComObject<CEDBS_Geometrie>::CreateInstance(&pobjGeometrie); 
			pobjGeometrie->mbGeometrieart = atoi(strBuffer.Left(2));
			pobjGeometrie->dblRA = dblRA;
			pobjGeometrie->dblHA = dblHA;
			pobjGeometrie->dblHE = atof(strRH.Left(10));
			pobjGeometrie->dblRE = atof(strRH.Right(10));
                
			strBuffer = strBuffer.Mid(2);

			if( bSourceFileType != ALK ) {
				iWHF2 = GetWHF();
				if( iWHF2 < 0 ) {
					lResult = -1;
					break;
				}
			}
			else {
				iWHF2 = 1;
				// Funktion der Linie ist nicht weiter untergliedert, es gibt also keinen WHF für Struktur
			}
			while( iWHF2 > 0 ) {
				iWHF2--;
				if( GetFunktionDerLinie( pobjGeometrie ) < 0 ) {
					lResult = -1;
				}
			}
			iWHF2 = GetWHF();
			if( iWHF2 < 0 ) {
					lResult = -1;
			}
			else {
				if( iWHF2 > 0 ) {
					if( msModus > 0 ) {
						strBuffer = strBuffer.Mid(20 * iWHF2);
					}
					else {
						pobjGeometrie->Dim( iWHF2 );
						ix = 0;
						while( iWHF2 > 0 ) {
							iWHF2--;
							if( GetLageparameter( pobjGeometrie->padblR[ix], pobjGeometrie->padblH[ix] ) < 0 ) {
								lResult = -1;
								break;
							}
							ix++;
						}
					}
				}
			}
		}
	}
	return lResult;
}

long Cparser :: GetFunktionDerLinie( CComObject<CEDBS_Geometrie> *pobjGeometrie )
{ 
 HRESULT hResult;
 long lResult = 0;
 int iWHF1;
 int iWHF2;
 CStringEx strObjektnummerR;
 CStringEx strObjektnummerL;
 short sFolie;
 short sObjektart;

 CComObject<CEDBS_Objekt> *pobjEDBS;
 CComObject<CEDBS_Linie> *pobjLinie;
 CComObject<CEDBS_Fachparameter> *pobjFachparameter;

	iWHF1 = GetWHF();
    if( iWHF1 < 0 ) {
        lResult = -1;
    }
	else {
		while( iWHF1 > 0 && lResult >= 0 ) {
			iWHF1--;

			sFolie = atoi(strBuffer.Left(3));
			sObjektart = atoi(strBuffer.Mid(3, 4));

			strObjektnummerR = strBuffer.Mid(7, 7);
			strObjektnummerR.TrimRight();
			if( strObjektnummerR.GetLength() > 0 ) {
				hResult = CComObject<CEDBS_Linie>::CreateInstance(&pobjLinie); 
				pobjLinie->mpobjGeometrie = pobjGeometrie;
				pobjGeometrie->AddRef();
				pobjLinie->msFolie = sFolie;
				pobjLinie->msObjektart = sObjektart;
				if( bSourceFileType != ALK ) {
					pobjLinie->msObjektteilnummer = atoi(strBuffer.Mid(21, 3));
					pobjLinie->mbLinienteilung = atoi(strBuffer.Mid(27, 1));
				}
				else {
					pobjLinie->msObjektteilnummer = 0;
					pobjLinie->mbLinienteilung = atoi(strBuffer.Mid(21, 1));
				}
				pobjEDBS = mpobjsEDBS->GetObjekt(strObjektnummerR);
				pobjEDBS->mpobjsLinien->mlstLinien.AddTail((CObject*)pobjLinie);
				pobjLinie->AddRef();
			}
			strObjektnummerL = strBuffer.Mid(14, 7);
			strObjektnummerL.TrimRight();
			if( strObjektnummerL.GetLength() > 0 ) {
				hResult = CComObject<CEDBS_Linie>::CreateInstance(&pobjLinie); 
				pobjLinie->mpobjGeometrie = pobjGeometrie;
				pobjGeometrie->AddRef();
				pobjLinie->msFolie = sFolie;
				pobjLinie->msObjektart = sObjektart;
				if( bSourceFileType != ALK ) {
					pobjLinie->msObjektteilnummer = atoi(strBuffer.Mid(24, 3));
					pobjLinie->mbLinienteilung = atoi(strBuffer.Mid(29, 1));
				}
				else {
					pobjLinie->msObjektteilnummer = 0;
					pobjLinie->mbLinienteilung = atoi(strBuffer.Mid(22, 1));
				}
				pobjEDBS = mpobjsEDBS->GetObjekt(strObjektnummerL);
				pobjEDBS->mpobjsLinien->mlstLinien.AddTail((CObject*)pobjLinie);
				pobjLinie->AddRef();
			}

			if( bSourceFileType != ALK ) {
				strBuffer = strBuffer.Mid(29);
				iWHF2 = GetWHF();
				if( iWHF2 < 0 ) {
					lResult = -1;
				}
				else {
					if( msModus > 1 ) {
					    strBuffer = strBuffer.Mid(8 * iWHF2);
					}
					else {
						while( iWHF2 > 0 && lResult >= 0 ) {
							iWHF2--;
							hResult = CComObject<CEDBS_Fachparameter>::CreateInstance(&pobjFachparameter); 
							pobjLinie->mpobjsFachparameter->mlstFachparameter.AddTail((CObject*)pobjFachparameter);
							pobjFachparameter->AddRef();

							if( GetFachparameter(pobjFachparameter) < 0 ) {
								lResult = -1;
								break;
							}
						}
					}
				}
			}
			else
    			strBuffer = strBuffer.Mid(23);
		}
	}
	return lResult;
}

long Cparser :: GetLageparameter( double &pdblR, double &pdblH )
{
 long lResult = 0;
 CStringEx strRH;

	if( strBuffer.GetLength() < 20 )
		return -1;
	else {
		lResult = GetKoordinate( strRH );
		pdblH = atof(strRH.Left(10));
		pdblR = atof(strRH.Right(10));
		return 0;
	}
}

long Cparser :: GetFachparameter( CComObject<CEDBS_Fachparameter> *pobjFachparameter)
{
	pobjFachparameter->mstrArtDesFachparameters = strBuffer.Left(1);
	pobjFachparameter->mstrKennungDesFachparameters = strBuffer.Mid(1,1);
	pobjFachparameter->mstrWertDesFachparameters = strBuffer.Mid(2,7);

    strBuffer = strBuffer.Mid(8);

	return 0;
}

long Cparser :: GetFunktionDesObjekts( double dblRA, double dblHA )
{
 long lResult = 0;
 int iWHF1;
 int iWHF2;
 CComObject<CEDBS_Objekt> *pobjEDBS;

	iWHF1 = GetWHF();
    if( iWHF1 < 0 ) {
        lResult = -1;
    }
	else {
		while( iWHF1 > 0 && lResult >= 0 ) {
			iWHF1--;
			pobjEDBS = mpobjsEDBS->GetObjekt(strBuffer.Mid(10, 7));
			pobjEDBS->put_Folie(atoi(strBuffer.Left(3)));
			pobjEDBS->put_Objektart(atoi(strBuffer.Mid(3,4)));
			pobjEDBS->put_Objekttyp(CComBSTR(strBuffer.Mid(9,1)));
			pobjEDBS->put_Aktualitaet(CComBSTR(strBuffer.Mid(7,2)));
			pobjEDBS->put_GrundpunktR( dblRA );
			pobjEDBS->put_GrundpunktH( dblHA );
			if( bSourceFileType != ALK ) {
				pobjEDBS->put_Modelltyp(CComBSTR(strBuffer.Mid(17,2)));
				pobjEDBS->put_Entstehungsdatum(CComBSTR(strBuffer.Mid(19,6)));
				pobjEDBS->put_Veraenderungskennung(CComBSTR(strBuffer.Mid(25,1)));
				strBuffer = strBuffer.Mid(26);
			}
			else {
				pobjEDBS->put_Entstehungsdatum(CComBSTR(strBuffer.Mid(17,6)));
				strBuffer = strBuffer.Mid(23);
			}
			iWHF2 = GetWHF();
			if( iWHF2 < 0 ) {
				lResult = -1;
			}
			else {
				while( iWHF2 > 0 && lResult >= 0 ) {
					iWHF2--;
					if( GetBesondereInformation( pobjEDBS ) < 0 ) {
						lResult = -1;
						break;
					}
				}
			}
		}
	}
	return lResult;
}

long Cparser :: GetBesondereInformation( CComObject<CEDBS_Objekt> *pobjEDBS )
{
 HRESULT hResult;
 long lResult = 0;
 int iWHF1;
 int iWHF2;
 int iNumBesondereInformation;
 CComObject<CEDBS_BesondereInformation> *pobjBesondereInformation;
 CComObject<CEDBS_Geometrie> *pobjGeometrie;
 int ix;
 BYTE bGeometrieart;

    iWHF1 = GetWHF();
    if( iWHF1 < 0 ) {
        lResult = -1;
    }
	else {
		iNumBesondereInformation = 0;
		while( iWHF1 > 0 && lResult >= 0 ) {
			iWHF1--;
	        iNumBesondereInformation++;
			hResult = CComObject<CEDBS_BesondereInformation>::CreateInstance(&pobjBesondereInformation); 
			pobjEDBS->mpobjsBesondereInformationen->mlstBesondereInformationen.AddTail((CObject*)pobjBesondereInformation);
			pobjBesondereInformation->AddRef();
//			Set objBesondereInformation = objEDBS.BesondereInformationen.Add(Format(iNumBesondereInformation, "0"))
			pobjBesondereInformation->mbArtDerInformation = atoi(strBuffer.Left(2));
			pobjBesondereInformation->mstrKartentyp = strBuffer.Mid( 2, 2);
			pobjBesondereInformation->mstrDarstellungsart = strBuffer.Mid( 4, 2);
			pobjBesondereInformation->msObjektart = atoi(strBuffer.Mid( 6, 4));
			pobjBesondereInformation->mstrTextdaten = strBuffer.Mid( 10, 33);
			pobjBesondereInformation->mstrTextdaten.TrimRight();
			bGeometrieart = atoi(strBuffer.Mid(43,2));

			if( bSourceFileType != ALK ) {
	            pobjBesondereInformation->msObjektteilnummer = atoi(strBuffer.Mid( 45, 3));
				strBuffer = strBuffer.Mid(48);
			}
			else {
				pobjBesondereInformation->msObjektteilnummer = 0;
				strBuffer = strBuffer.Mid(45);
			}
			iWHF2 = GetWHF();
			if( iWHF2 < 0 ) {
				lResult = -1;
			}
			else if( iWHF2 > 0) {
				if( msModus > 0 ) {
					strBuffer = strBuffer.Mid(20 * iWHF2);
				}
				else {
					hResult = CComObject<CEDBS_Geometrie>::CreateInstance(&pobjGeometrie); 
					pobjBesondereInformation->mpobjGeometrie = pobjGeometrie;
					pobjGeometrie->AddRef();
					pobjGeometrie->mbGeometrieart = bGeometrieart;

					iWHF2--;
					if( strBuffer.Left(2) == "tt" ) {
						pobjGeometrie->lTT = atoi(strBuffer.Mid(2,18));
						strBuffer = strBuffer.Mid(20);
						iWHF2--;
						if( GetGeometrieangaben( &pobjGeometrie->dblRA, &pobjGeometrie->dblHA) < 0 ) {
							lResult = -1;
						}
					}
					else if( GetGeometrieangaben( &pobjGeometrie->dblRA, &pobjGeometrie->dblHA) < 0 ) {
						lResult = -1;
					}
					if( iWHF2 > 0) {
						iWHF2--;
						if( GetGeometrieangaben( &pobjGeometrie->dblRE, &pobjGeometrie->dblHE) < 0 ) {
							lResult = -1;
						}
						if( iWHF2 > 0) {
							if( strBuffer.Mid(1,19) == "                   " ) {
								iWHF2--;
								strBuffer = strBuffer.Mid(20);
							}
							pobjGeometrie->Dim(iWHF2);
							ix = 0;
							while( iWHF2 > 0 && lResult >= 0 ) {
								iWHF2--;
								if( GetGeometrieangaben( &(pobjGeometrie->padblR[ix]), &(pobjGeometrie->padblH[ix]) ) < 0 ) {
									lResult = -1;
									break;
								}
								ix++;
							}
						}
					}
				}
			}
		}
	}
	return lResult;
}

long Cparser :: GetGeometrieangaben( double *pdblR, double *pdblH )
{
 long lResult = 0;
 CStringEx strRH;

	if( strBuffer.GetLength() < 20 )
		return -1;
	else {
		lResult = GetKoordinate( strRH );
		*pdblH = atof(strRH.Left(10));
		*pdblR = atof(strRH.Right(10));
		return 0;
	}
}

void Cparser :: readDLOB2005( void ) {
/*
'    rsFLOE.AddNew
'    rsFLOE!DLOB0001 = Mid(strSearchBuffer, 13, 8)
'    rsFLOE!DLOB0002 = Mid(strSearchBuffer, 33, 12)
'    rsFLOE!DLOB0003 = Mid(strSearchBuffer, 57, 1)
'    rsFLOE!DLOB2003 = Mid(strSearchBuffer, 70, 2)
'    rsFLOE!DLOB2005 = Mid(strSearchBuffer, 84, 7)
'    rsFLOE.Update
*/
 CComObject<CEDBS_Objekt> *pobjEDBS;
 CStringEx strObjektnummer;
 int pos;
	pos = strSearchCriteria.Find("DLOB2005EQ");
	if( pos >= 0 ) {
		strObjektnummer = strSearchCriteria.Mid( pos + 10, 7 );
		pobjEDBS = mpobjsEDBS->GetObjekt( strObjektnummer );
		pobjEDBS->mtFLOE = true;
		if( pobjEDBS->mstrAktualitaet.IsEmpty() ) {
			pos = strSearchCriteria.Find("DLOB2003EQ");
			if( pos >= 0 )
				pobjEDBS->mstrAktualitaet = strSearchCriteria.Mid( pos + 10, 2 );
		}
	}
	// die Koordinaten des Grundpunktes brauchen nicht übernommen zu werden,
	// da nur vorhandene Objekte auch gelöscht werden
	// und der Grundpunkt damit bekannt ist.
}


STDMETHODIMP Cparser::get_Objekte(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
 HRESULT hResult;
	if( mpobjsEDBS == NULL )
		*pVal = NULL;
	else {
		hResult = mpobjsEDBS->QueryInterface(IID_IEDBS_Objekte,(void**)pVal);
		if( hResult )
			*pVal = NULL;
	}
	return S_OK;
}

/*
IOBJ_EDBS *Cparser :: GetObject( CStringEx strKey )
{
	IOBJ_EDBS *pobjEDBS;
	HRESULT hResult;

	if( 0 == mmapObjects.Lookup( strKey, (void*&)pobjEDBS ) ) {
		hResult = CoCreateInstance( CLSID_OBJ_EDBS, NULL, CLSCTX_INPROC_SERVER, IID_IOBJ_EDBS, (LPVOID *)&pobjEDBS );
		pobjEDBS->put_Objektnummer(CComBSTR(strKey));
		mmapObjects.SetAt(strKey,pobjEDBS);
	}

	/*
Dim objEDBS As clsEDBSObjekt
    If Key = strLastObject Then
        Set GetObject = objLastObject
    Else
        Set objEDBS = colObjekte.Item(Key)
        If objEDBS Is Nothing Then
            Set objEDBS = colObjekte.Add(Key)
        End If
        Set objLastObject = objEDBS
        Set GetObject = objEDBS
    End If
End Function
* /
	return pobjEDBS;
}
*/

STDMETHODIMP Cparser::get_Modus(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msModus;

	return S_OK;
}

STDMETHODIMP Cparser::put_Modus(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msModus = newVal;

	return S_OK;
}

STDMETHODIMP Cparser::put_hWnd(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_hWnd = (HWND)newVal;

	return S_OK;
}
