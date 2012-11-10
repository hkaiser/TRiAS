// OLE2AUTO BAsicScript-Erweiterung -------------------------------------------
// File: OLEBSEXT.HXX

#if !defined(_OLEBSEXT_HXX)
#define _OLEBSEXT_HXX

///////////////////////////////////////////////////////////////////////////////
// Setzen des DatenQuellenKontextes und anderer wichter Kontextwerte
#define SETLONG_NAME		8		// harmonize with bscript.hxx!
#define SETLONG_HPROJECT	16
#define SETLONG_HINSTANCE	20

///////////////////////////////////////////////////////////////////////////////
// Function Prototypes 
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Base Object
void refcnt_BaseObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_BaseObject_isA (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_BaseObject_Parent (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_BaseObject_Application (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_BaseObject_IDispatch (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);


///////////////////////////////////////////////////////////////////////////////
// Application
void refcnt_Application (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Application_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Version (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_StartupPath (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Application_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Application_NewDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Application_OpenDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Application_GetDocuments (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Application_GetDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Application_AddDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Application_MakeActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Application_CloseDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Application_GetActiveDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Application_Advise (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Application_Unadvise (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Application_AddPropertyFunction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Application_RemovePropertyFunction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propset_Application_StatusBar (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Application_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Application_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Application_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void ToolBars_Application_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetToolBar_Application_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AddToolBar_Application_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RemoveToolBar_Application_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Application_LoadExtension (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Application_UnLoadExtension (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// All Collections: Documents, Views, GeoClasses, GeoObjects, GeoFeatures, GeoObjectWins
void propget_Collection_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Collection_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Collection_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Collection_Remove (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// for Documents Collection only
void function_Documents_New (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Documents_Open (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// for GeoObjects Collection only
void refcnt_GeoObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_CreateGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_GeometryAND (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_GeometryOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_SetIntersection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_SetUnion (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_SetDifference (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_SetSymmetricDifference (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GeometryLinesUnion_GeoObjects_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjects_MakeGeoClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// For..Each support
void propget_Documents_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Documents_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjects_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjects_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoViews_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoViews_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoClasses_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoClasses_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoFeatures_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoFeatures_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWins_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWins_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Refresh_Documents_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Refresh_GeoObjects_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Refresh_GeoClasses_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Refresh_GeoViews_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Refresh_GeoObjectWins_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Refresh_GeoFeatures_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObjectWins_ActGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Document
void propget_Document_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Document_GetActiveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Document_ActiveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Document_GeoObjectCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_GeoViewCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_GeoClassCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void command_Document_CloseIt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_Save (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_SaveAs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_AddView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_ReplaceView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_RemoveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_ReplaceClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_QueryObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_SetHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_RemoveHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void command_Document_RePaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_ReBuild (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetGeoObjectWins (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_Document_GetGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_Document_AddGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_Document_RemoveGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void CreateGeoObjectsCollection_Document_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Document_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Document_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Document_IsDirty (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_Document_IsDirty (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propset_Document_CanRepaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_CanRepaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_Document_ContextDataSource (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Document_Connections (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Connections
void propget_Connections_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_Connections_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

// Connection
void propget_Connection_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// View
void propget_View_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_View_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_View_ClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_ClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_ResetClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_ReplaceClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_View_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_View_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_View_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_View_Scale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_Scale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_View_Desc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_View_Desc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void command_View_GetConstraintRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_SetConstraintRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_GetActRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_View_SetActRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoClass
void propget_GeoClass_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoClass_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoClass_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoClass_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoClass_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoClass_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoClass_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoClass_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetObjectFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_AddObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoClass_ReplaceObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoClass_RemoveObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoClass_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoClass_Code (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoClass_Connection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoClass_Updatable (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoClass_Updatable (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoClass_IsQueryDef (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoObject
void propget_GeoObject_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObject_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_ObjType (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObject_ObjClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_ObjDistance (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_ClassDistance (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetGeometry1 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetGeometry2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetGeometryRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_PutGeometry1 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_PutGeometry2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_PutGeometry3 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_PutText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoObject_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void command_GeoObject_RePaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_TopRelation (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetTopRelationObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetBufferObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetBufferObjectsEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetCircleBufferObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetIntersectObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetIntersectObjectsColl (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GetIntersectObjectsClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GeometryAND (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GeometryOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_GeometryXOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void GetCommonContourObjects_GeoObject_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_Selected (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Selected (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObject_Activated (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Activated (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void cmd_GeoObject_Hilight (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void cmd_GeoObject_UnHilight (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_MakeRectangular (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_ShiftGeometrySection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_Guid (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Guid (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObject_UniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_UniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObject_OldUniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_OldUniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_GetRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void cmd_GeoObject_CreateRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_RemoveRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_AnalyzeGeometry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObject_AnalyzeGeometryObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObject_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObject_Connection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObject_CloneObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoFeature
void propget_GeoFeature_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoFeature_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoFeature_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoFeature_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoFeature_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoFeature_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoFeature_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoFeature_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoFeature_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoFeature_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoFeature_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoFeature_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoFeature_ConfigData (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoObjectWin
void propget_GeoObjectWin_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWin_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propput_GeoObjectWin_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObjectWin_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObjectWin_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObjectWin_ActGeoObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propput_GeoObjectWin_ActGeoObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObjectWin_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObjectWin_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjectWin_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoObjectWin_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObjectWin_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObjectWin_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjectWin_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoObjectWin_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void command_GeoObjectWin_SetShownFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void function_GeoObjectWin_AddMenuItem (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetSelectedObjects_GeoObjectWin_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_GeoObjectWin_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObjectWin_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWin_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObjectWin_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWin_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObjectWin_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoObjectWin_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_GeoObjectWin_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void command_GeoObjectWin_SetActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void function_GeoObjectWin_IsActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoDataSources
void propget_GeoDataSources_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_GeoDataSources_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// GeoDataSource
void propget_GeoDataSource_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Object Type Conversions
void func_FDoc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FObj (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FCls (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FFeat (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FObjWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void func_FDocs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FObjs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FClss (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FFeats (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_FObjWins (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void func_FBase (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// PROTO_... for Application
void cmd_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void cmd_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void func_NewDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_OpenDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void func_GetDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_AddDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void func_MakeActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void cmd_CloseDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Debug
void help_SetDebug (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// VisualisierungsInfo
void Style_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Style_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Priority_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Priority_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void MainColor_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void MainColor_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Changed_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Changed_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Visible_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Visible_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Locatable_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Locatable_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void SizeX_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeX_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeY_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeY_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Rotate_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Rotate_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkColor_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkColor_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Width_LineVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Width_LineVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Width_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Width_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Opaque_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Opaque_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkContour_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkContour_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkColor_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void BkColor_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void SizeX_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeX_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeY_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SizeY_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Bold_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Bold_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Italic_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Italic_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Underline_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Underline_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StrikeThrough_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StrikeThrough_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AlignStyle_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AlignStyle_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void FrameStyle_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void FrameStyle_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Rotate_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Rotate_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Slant_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Slant_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void RGB_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Red_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Green_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Blue_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void HSB_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Hue_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Saturation_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Brightness_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void GetPointVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetLineVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetAreaVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetTextVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SetVisInfo_GeoObject_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void ResetVisInfo_GeoObject_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void GetPointVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetLineVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetAreaVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void GetTextVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SetVisInfo_GeoClass_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void ResetVisInfo_GeoClass_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void refcnt_PointVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void refcnt_LineVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void refcnt_AreaVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void refcnt_TextVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// ToolBars support
void Refresh_ToolBars_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBars_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBars_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void cmd_ToolBars_SaveState (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void cmd_ToolBars_LoadState (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// ToolBar support
void refcnt_ToolBar (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Visible_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Visible_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DockState_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DockState_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Remove_ToolBar_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void InsertButton_ToolBar_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_ToolBar_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBar_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBar_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBar_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_ToolBar_CtrlID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_CtrlID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void propget_ToolBar_Style (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_Style (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propget_ToolBar_StyleEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void propset_ToolBar_StyleEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// ToolBarButton support
void refcnt_ToolBarButton (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Name_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Helptext_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Helptext_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void State_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void State_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Style_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Style_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AttachImage_ToolBarButton_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AttachImage_ToolBarButton_command2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void AttachImage_ToolBarButton_command3 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Value_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CmdID_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CmdID_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// support for PropertyActions
void PropertySequence_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_propget_Description (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_propset_Description (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_AddAction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_AddActionSequence (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_func_DoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_DoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_Save (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_Load (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_Init (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_func_RedoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void PropertySequence_cmd_RedoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void PropertyChoice_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void JoinPropertyActions_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void SplitPropertyActions_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// StatusIndicator
void StatusIndicator_propget_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_propset_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_propget_Field (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_propset_Field (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_cmd_Restart (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_SetPosition (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_WasCaceled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_InitNew (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_propset_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_propget_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_IncrementPosition (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_ChangeText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_func_RetrieveText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

// #HK001017
void StatusIndicator_method_Show (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void StatusIndicator_method_Hide (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Image support 
void refcnt_Picture (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Handle_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void hPal_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void hPal_Picture_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Type_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Width_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Height_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void LoadPicture_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void LoadResPicture_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void LoadResString_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
#if defined(DYNAMIC_BASIC)
extern HINSTANCE g_hBScript;			// BasicScript-Runtime
#endif // DYNAMIC_BASIC

#endif // _OLEBSEXT_HXX
