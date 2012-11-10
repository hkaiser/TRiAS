/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVDlg.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_DIALOG_H_
#define  _LEAD_VECTOR_DIALOG_H_

/*----------------------------------------------------------------------------+
| Class     : LVectorDialog                                                   |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorDialog : public LBase
{
   LEAD_DECLAREOBJECT(LVectorDialog);
   private:  
      static LVectorDialog L_FAR* pActiveDlg;
      static L_VOID EXT_CALLBACK VectorDLGHelp ( L_UINT32, HWND, L_INT, L_VOID L_FAR* );
      
   protected:  
      LVectorBase L_FAR*    m_pLVector;  //points to LVectorBase object

      //from dictionary
      L_CHAR            m_szFilename[L_MAXPATH];
  
      //common to all dialogs
      L_BOOL              m_bShowPreview;
      L_BOOL              m_bAutoProcess;
      L_BOOL              m_bSelectedOnly; //newnew
      L_BOOL              m_bNoDuplicate;
      L_BOOL              m_bHelpEnabled;

      L_VOID      VectorHelpCallback( L_UINT32 uDlgID, HWND hElement, L_INT nCtlID );

   private:
      L_VOID      InitializeClass();  
      L_VOID      HandleAutoProcess(L_UINT DlgType, L_INT nRetCode);

         
   public : 
      LVectorDialog();
      LVectorDialog(LVectorBase L_FAR* pLVector);
      ~LVectorDialog();

      L_VOID      SetVector(LVectorBase L_FAR* pVector);
      LVectorBase L_FAR*  GetVector();
      L_BOOL      IsValid();

      L_BOOL      EnablePreview(L_BOOL bEnablePreview=TRUE);
      L_BOOL      EnableAutoProcess(L_BOOL bAuto=TRUE);
      L_BOOL      EnableHelp( L_BOOL bHelpEnabled = TRUE );
      L_BOOL      EnableSelectedOnly(L_BOOL bSelectedOnly = TRUE); //newnew
      L_BOOL      EnableNoDuplicate(L_BOOL bNoDuplicate = TRUE);   //newnew


      L_BOOL      IsPreviewEnabled() const;
      L_BOOL      IsAutoProcessEnabled() const;
      L_BOOL      IsHelpEnabled() const;
      L_BOOL      IsSelectedOnlyEnabled() const;          //newnew
      L_BOOL      IsNoDuplicateEnabled() const;           //newnew



//Operations:
      virtual L_INT  LVectorDialog::DoModalVectorRotate(HWND hWndParent=NULL, pVECTORPOINT pRotation=NULL, const pVECTORPOINT pOrigin=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorScale(HWND hWndParent=NULL, pVECTORPOINT pScale=NULL, const pVECTORPOINT pOrigin=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorTranslate(HWND hWndParent=NULL, pVECTORPOINT pTranslation=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorCamera(HWND hWndParent=NULL, pVECTORCAMERA pCamera=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorRender(HWND hWndParent=NULL, L_BOOL L_FAR *pbUseLights=NULL, COLORREF L_FAR *pColorAmbient=NULL, L_INT L_FAR *pnPolygonMode=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorViewMode(HWND hWndParent=NULL, L_INT L_FAR *pnViewMode=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorHitTest(HWND hWndParent=NULL, pVECTORHITTEST pHitTest=NULL);

      virtual L_INT  LVectorDialog::DoModalVectorEditAllLayers(HWND hWndParent=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorNewLayer(HWND hWndParent=NULL, LVectorLayer *pVectorLayer=NULL, L_BOOL L_FAR *pbActiveLayer=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorEditLayer(HWND hWndParent, LVectorLayer *pVectorLayer, L_BOOL L_FAR *pbActiveLayer=NULL);
      

      virtual L_INT  LVectorDialog::DoModalVectorEditAllGroups( HWND hWndParent=NULL);
      virtual L_INT  LVectorDialog::DoModalVectorNewGroup     ( HWND hWndParent,      LVectorGroup *pVectorGroup );
      virtual L_INT  LVectorDialog::DoModalVectorEditGroup    ( HWND hWndParent,      LVectorGroup *pVectorGroup );

      
      virtual L_INT  LVectorDialog::DoModalVectorNewObject(HWND hWndParent, 
                                                         L_INT nType,                 /* Must not be NULL */
                                                         LVectorLayer *pVectorLayer,  /* can be NULL */
                                                         LVectorObject *pVectorObject /* can be NULL */
                                                         );

      virtual L_INT  LVectorDialog::DoModalVectorNewObject(HWND hWndParent, 
                                                         LVectorLayer *pVectorLayer,    /* can be NULL */
                                                         LVectorObject *pVectorObject   /* Must not be NULL */
                                                         );

      
      virtual L_INT  LVectorDialog::DoModalVectorEditObject(
                                                            HWND hWndParent, 
                                                            LVectorObject *pVectorObject  /* Must not be NULL */
                                                            );

      static  L_INT  LVectorDialog::GetString(L_UINT32 uString, L_CHAR L_FAR * pString);
      static  L_INT  LVectorDialog::GetStringLen(L_UINT32 uString, L_UINT L_FAR * puLen);
      static  L_INT  LVectorDialog::SetString(L_UINT32 uString, L_CHAR L_FAR * pString);
      static  HFONT  LVectorDialog::SetFont(HFONT hFont);
};
#endif //_LEAD_VECTOR_DIALOG_H_
/*================================================================= EOF =====*/
