// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JUMPTAB.CPP

#include "precomp.hxx"

#include <limits.h>
#include <eb.h>

#include "olebsext.hxx"		// Prototypen
#include "jumptab.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (statisch/compilergeneriert)
static STATICEXTPROC s_StaticExtFcns[] = {
	{ refcnt_BaseObject, 1 },
	{ propget_BaseObject_isA, 2 },
	{ propget_BaseObject_Parent, 3 },
	{ propget_BaseObject_Application, 4 },
	{ propget_BaseObject_IDispatch, 317 },

// Application	
	{ refcnt_Application, 296 },
	{ propget_Application_Value, 5 },
	{ propget_Application_Version, 362 },
	{ propget_Application_Name, 6 },
	{ propget_Application_StartupPath, 7 },
	{ propget_Application_Path, 8 },
	{ propset_Application_Path, 9 },
	{ propget_Application_FullName, 10 },

	{ propget_Application_Visible, 11 },
	{ propset_Application_Visible, 12 },

	{ function_Application_NewDocument, 13 },
	{ function_Application_OpenDocument, 14 },

	{ propget_Application_GetDocuments, 15 },

	{ function_Application_GetDocument, 16 },
	{ function_Application_AddDocument, 17 },
	{ function_Application_MakeActive, 18 },
	{ command_Application_CloseDocument, 19 },

	{ propget_Application_GetActiveDocument, 20 },
	{ function_Application_Advise, 325 },
	{ command_Application_Unadvise, 326 },

	{ function_Application_AddPropertyFunction, 328 },
	{ command_Application_RemovePropertyFunction, 329 },

	{ propset_Application_StatusBar, 314 },
	{ propget_Application_Caption, 315 },
	{ propset_Application_Caption, 316 },

	{ propget_Application_Left, 305 },
	{ propset_Application_Left, 306 },
	{ propget_Application_Top, 307 },
	{ propset_Application_Top, 308 },
	{ propget_Application_Width, 309 },
	{ propset_Application_Width, 310 },
	{ propget_Application_Height, 311 },
	{ propset_Application_Height, 312 },

	{ ToolBars_Application_propget, 363 },
	{ GetToolBar_Application_func, 364 },
	{ AddToolBar_Application_func, 365 },
	{ RemoveToolBar_Application_cmd, 366 },

	{ function_Application_LoadExtension, 439 },
	{ function_Application_UnLoadExtension, 440 },

// All Collectons
	{ propget_Collection_Item, 21 },
	{ propget_Collection_Count, 22 },
	{ function_Collection_Add, 23 },
	{ command_Collection_Remove, 24 },

// Documents	
	{ function_Documents_New, 25 },
	{ function_Documents_Open, 26 },

// Document
	{ propget_Document_Value, 27 },
	{ propget_Document_Name, 28 },
	{ propget_Document_Path, 29 },
	{ propget_Document_FullName, 30 },
	{ propget_Document_GetActiveView, 31 },
	{ propset_Document_ActiveView, 302 },

	{ propget_Document_GeoObjectCount, 297 },
	{ propget_Document_GeoViewCount, 298 },
	{ propget_Document_GeoClassCount, 299 },

	{ command_Document_CloseIt, 32 },
	{ command_Document_Save, 33 },
	{ command_Document_SaveAs, 34 },

	{ function_Document_GetViews, 35 },
	
	{ function_Document_GetView, 36 },
	{ function_Document_AddView, 37 },
	{ function_Document_ReplaceView, 38 },
	{ command_Document_RemoveView, 39 },

	{ function_Document_GetClasses, 40 },

	{ function_Document_GetClass, 41 },
	{ function_Document_AddClass, 42 },
	{ function_Document_ReplaceClass, 43 },
	{ command_Document_RemoveClass, 44 },
	
	{ function_Document_GetObjects, 45 },
	{ function_Document_QueryObjects, 466 },

	{ function_Document_GetObject, 46 },
	{ function_Document_AddObject, 47 },
	{ function_Document_ReplaceObject, 48 },
	{ command_Document_RemoveObject, 49 },
	
	{ function_Document_GetHeaderEntry, 50 },
	{ function_Document_SetHeaderEntry, 51 },
	{ function_Document_RemoveHeaderEntry, 447 },

	{ command_Document_RePaint, 52 },
	{ command_Document_ReBuild, 53 },

	{ function_Document_GetGeoObjectWin, 54 },
	{ function_Document_GetGeoObjectWins, 146 },
	{ function_Document_AddGeoObjectWin, 159 },
	{ command_Document_RemoveGeoObjectWin, 160 },
	{ CreateGeoObjectsCollection_Document_command, 263 },
	{ propget_Document_RefScale, 371 },
	{ propset_Document_RefScale, 372 },

	{ propset_Document_IsDirty, 415 },
	{ propget_Document_IsDirty, 416 },

	{ propset_Document_CanRepaint, 429 },
	{ propget_Document_CanRepaint, 430 },

	{ propget_Document_ContextDataSource, 448 },
	{ propget_Document_Connections, 470 },

// Connections
	{ propget_Connections_NewEnum, 467 },
	{ propget_Connections_Next, 468 },

// Connection
	{ propget_Connection_Name, 469 },

// View
	{ propget_View_Value, 55 },
	{ propget_View_Name, 56 },
	{ propset_View_Name, 57 },
	{ propget_View_ClipObject, 322 },
	{ propset_View_ClipObject, 323 },
	{ propset_View_ResetClipObject, 396 },

	{ function_View_GetClasses, 58 },
	
	{ function_View_GetClass, 59 },
	{ function_View_AddClass, 60 },
	{ function_View_ReplaceClass, 61 },
	{ command_View_RemoveClass, 62 },
	
	{ function_View_GetObjects, 63 },

	{ function_View_GetObject, 64 },
	{ function_View_AddObject, 65 },
	{ function_View_ReplaceObject, 66 },
	{ command_View_RemoveObject, 67 },

	{ function_View_GetFeatures, 68 },

	{ function_View_GetFeature, 69 },
	{ function_View_AddFeature, 70 },
	{ function_View_ReplaceFeature, 71 },
	{ command_View_RemoveFeature, 72 },

	{ function_View_GetObjectsInWindow, 157 },

	{ propget_View_RefScale, 373 },
	{ propset_View_RefScale, 374 },
	{ propget_View_Scale, 375 },
	{ propset_View_Scale, 376 },

	{ propget_View_Desc, 377 },
	{ propset_View_Desc, 378 },

	{ command_View_GetActRect, 425 },
	{ command_View_SetActRect, 426 },
	{ command_View_GetConstraintRect, 427 },
	{ command_View_SetConstraintRect, 428 },

// GeoClass
	{ propget_GeoClass_Value, 73 },
	{ propset_GeoClass_Value, 458 },
	{ propget_GeoClass_Name, 74 },
	{ propset_GeoClass_Name, 75 },
	{ propget_GeoClass_FullName, 76 },
	{ propset_GeoClass_FullName, 77 },

	{ function_GeoClass_GetViews, 78 },

	{ function_GeoClass_GetObjects, 79 },

	{ function_GeoClass_GetObject, 80 },
	{ function_GeoClass_AddObject, 81 },
	{ function_GeoClass_ReplaceObject, 82 },
	{ command_GeoClass_RemoveObject, 83 },

	{ function_GeoClass_GetFeatures, 84 },

	{ function_GeoClass_GetFeature, 85 },
	{ function_GeoClass_AddFeature, 86 },
	{ function_GeoClass_ReplaceFeature, 87 },
	{ command_GeoClass_RemoveFeature, 88 },

	{ function_GeoClass_GetObjectFeatures, 451 },

	{ function_GeoClass_GetObjectFeature, 452 },
	{ function_GeoClass_AddObjectFeature, 453 },
	{ function_GeoClass_ReplaceObjectFeature, 454 },
	{ command_GeoClass_RemoveObjectFeature, 455 },

	{ function_GeoClass_GetObjectsInWindow, 158 },
	{ propget_GeoClass_Code, 353 },
	{ propget_GeoClass_Connection, 445 },

	{ propget_GeoClass_Updatable, 449 },
	{ propset_GeoClass_Updatable, 450 },

	{ propget_GeoClass_IsQueryDef, 456 },

	{ GetPointVisInfo_GeoClass_func, 241 },
	{ GetLineVisInfo_GeoClass_func, 242 },
	{ GetAreaVisInfo_GeoClass_func, 243 },
	{ GetTextVisInfo_GeoClass_func, 244 },
	{ SetVisInfo_GeoClass_cmd, 245 },
	{ ResetVisInfo_GeoClass_cmd, 398 },

// GeoObjects
	{ refcnt_GeoObjects, 246 },
	{ function_GeoObjects_CreateGeoObjectWin, 89 },
	{ function_GeoObjects_GeometryAND, 181 },
	{ function_GeoObjects_GeometryOR, 182 },
	{ function_GeoObjects_SetIntersection, 252 },
	{ function_GeoObjects_SetUnion, 253 },
	{ function_GeoObjects_SetDifference, 254 },
	{ function_GeoObjects_SetSymmetricDifference, 255 },
	{ GeometryLinesUnion_GeoObjects_function, 247 },
	{ function_GeoObjects_GetObjectsInWindow, 301 },
	{ function_GeoObjects_MakeGeoClass, 457 },

// GeoObject
	{ propget_GeoObject_Value, 90 },
	{ propget_GeoObject_Name, 91 },
	{ propset_GeoObject_Name, 92 },

	{ propget_GeoObject_ObjType, 93 },
	{ propget_GeoObject_ObjClass, 94 },

	{ function_GeoObject_ObjDistance, 95 },
	{ function_GeoObject_ClassDistance, 96 },

	{ function_GeoObject_GetGeometry1, 97 },
	{ function_GeoObject_GetGeometry2, 98 },
	{ function_GeoObject_GetGeometryRect, 300 },

	{ function_GeoObject_PutGeometry1, 99 },
	{ function_GeoObject_PutGeometry2, 100 },
	{ function_GeoObject_PutGeometry3, 465 },

	{ function_GeoObject_GetText, 101 },
	{ function_GeoObject_PutText, 102 },

	{ function_GeoObject_GetFeatures, 103 },

	{ function_GeoObject_GetFeature, 104 },
	{ function_GeoObject_AddFeature, 105 },
	{ function_GeoObject_ReplaceFeature, 106 },
	{ command_GeoObject_RemoveFeature, 107 },

	{ command_GeoObject_RePaint, 108 },

	{ function_GeoObject_TopRelation, 145 },
	{ function_GeoObject_GetTopRelationObjects, 163 },
	{ function_GeoObject_GetBufferObjects, 164 },
	{ function_GeoObject_GetBufferObjectsEx, 431 },
	{ function_GeoObject_GetCircleBufferObjects, 165 },
	{ function_GeoObject_GetIntersectObjects, 168 },
	{ function_GeoObject_GetIntersectObjectsColl, 169 },
	{ function_GeoObject_GetIntersectObjectsClass, 170 },
	{ function_GeoObject_GeometryAND, 183 },
	{ function_GeoObject_GeometryOR, 184 },
	{ function_GeoObject_GeometryXOR, 414 },

	{ GetPointVisInfo_GeoObject_func, 239 },
	{ GetLineVisInfo_GeoObject_func, 240 },
	{ GetAreaVisInfo_GeoObject_func, 249 },
	{ GetTextVisInfo_GeoObject_func, 250 },
	{ SetVisInfo_GeoObject_cmd, 251 },
	{ ResetVisInfo_GeoObject_cmd, 397 },

	{ GetCommonContourObjects_GeoObject_function, 248 },

	{ propget_GeoObject_Feature, 294 },
	{ propset_GeoObject_Feature, 295 },

	{ propget_GeoObject_Selected, 349 },
	{ propset_GeoObject_Selected, 350 },
	{ propget_GeoObject_Activated, 351 },
	{ propset_GeoObject_Activated, 352 },

	{ cmd_GeoObject_Hilight, 407 },
	{ cmd_GeoObject_UnHilight, 408 },

	{ function_GeoObject_ShiftGeometrySection, 411 },

	{ propget_GeoObject_Guid, 412 },
	{ propset_GeoObject_Guid, 413 },
	{ propget_GeoObject_UniqueID, 435 },
	{ propset_GeoObject_UniqueID, 436 },
	{ propget_GeoObject_OldUniqueID, 437 },
	{ propset_GeoObject_OldUniqueID, 438 },

	{ function_GeoObject_MakeRectangular, 419 },

	{ function_GeoObject_GetRelatedObject, 420 },
	{ cmd_GeoObject_CreateRelatedObject, 421 },
	{ function_GeoObject_RemoveRelatedObject, 422 },

	{ function_GeoObject_AnalyzeGeometry, 423 },
	{ function_GeoObject_AnalyzeGeometryObject, 424 },

	{ propget_GeoObject_Visible, 433 },
	{ propset_GeoObject_Visible, 434 },

	{ propget_GeoObject_Connection, 446 },

	{ function_GeoObject_CloneObject, 475 },		// #HK001022

// GeoFeature
	{ propget_GeoFeature_Value, 109 },
	{ propget_GeoFeature_Name, 110 },
	{ propset_GeoFeature_Name, 111 },
	{ propget_GeoFeature_FullName, 112 },
	{ propset_GeoFeature_FullName, 113 },
	{ propget_GeoFeature_Feature, 114 },
	{ propset_GeoFeature_Feature, 115 },
	{ propget_GeoFeature_Flags, 339 },
	{ propset_GeoFeature_Flags, 340 },
	{ function_GeoFeature_GetViews, 147 },
	{ function_GeoFeature_GetClasses, 148 },
	{ function_GeoFeature_GetObjects, 149 },
	{ propget_GeoFeature_ConfigData, 370}, 

// GeoObjectWins
	{ propget_GeoObjectWins_ActGeoObjectWin, 318 },

// GeoObjectWin
	{ propget_GeoObjectWin_Value, 116 },
	{ propget_GeoObjectWin_Name, 117 },
	{ propput_GeoObjectWin_Name, 118 },
	{ propget_GeoObjectWin_ActGeoObject, 119 },
	{ propput_GeoObjectWin_ActGeoObject, 120 },
	{ propget_GeoObjectWin_Visible, 161 },
	{ propset_GeoObjectWin_Visible, 162 },

	{ function_GeoObjectWin_GetClasses, 121 },
	{ function_GeoObjectWin_GetClass, 122 },
	{ function_GeoObjectWin_AddClass, 123 },
	{ command_GeoObjectWin_RemoveClass, 124 },

	{ function_GeoObjectWin_GetObjects, 125 },
	{ function_GeoObjectWin_GetObject, 126 },
	{ function_GeoObjectWin_AddObject, 127 },
	{ command_GeoObjectWin_RemoveObject, 128 },

	{ function_GeoObjectWin_AddMenuItem, 129 },
	{ GetSelectedObjects_GeoObjectWin_function, 256 },

	{ propget_GeoObjectWin_Left, 354 },
	{ propset_GeoObjectWin_Left, 355 },
	{ propget_GeoObjectWin_Top, 356 },
	{ propset_GeoObjectWin_Top, 357 },
	{ propget_GeoObjectWin_Width, 358 },
	{ propset_GeoObjectWin_Width, 359 },
	{ propget_GeoObjectWin_Height, 360 },
	{ propset_GeoObjectWin_Height, 361 },
	{ command_GeoObjectWin_SetActive, 417 },
	{ function_GeoObjectWin_IsActive, 418 },
	{ command_GeoObjectWin_SetShownFeature, 432 },

	{ propget_Documents_NewEnum, 166 },
	{ propget_Documents_Next, 167 },
	{ propget_GeoObjects_NewEnum, 175 },
	{ propget_GeoObjects_Next, 176 },
	{ propget_GeoClasses_NewEnum, 173 },
	{ propget_GeoClasses_Next, 174 },
	{ propget_GeoViews_NewEnum, 171 },
	{ propget_GeoViews_Next, 172 },
	{ propget_GeoFeatures_NewEnum, 177 },
	{ propget_GeoFeatures_Next, 178 },
	{ propget_GeoObjectWins_NewEnum, 179 },
	{ propget_GeoObjectWins_Next, 180 },

// Prototypes
	{ func_FDoc, 130 },
	{ func_FView, 131 },
	{ func_FObj, 132 },
	{ func_FCls, 133 },
	{ func_FFeat, 134 },

//	{ func_FBase, 135 },		// obsolete

//	Application Prototypes 
	{ cmd_Path, 136 },
	{ cmd_Visible, 137 },

	{ func_NewDocument, 138 },
	{ func_OpenDocument, 139 },

	{ func_GetDocument, 140 },
	{ func_AddDocument, 141 },
	{ func_MakeActive, 142 },
	{ cmd_CloseDocument, 143 },

// Debug
	{ help_SetDebug, 144 },

	{ func_FObjWin, 150 },

	{ func_FDocs, 151 },
	{ func_FViews, 152 },
	{ func_FObjs, 153 },
	{ func_FClss, 154 },
	{ func_FFeats, 155 },
	{ func_FObjWins, 156 },

// VisualisierungsInfo
	{ Style_VisInfo_propget, 185 }, 
	{ Style_VisInfo_propset, 186 }, 
	{ Priority_VisInfo_propget, 187 }, 
	{ Priority_VisInfo_propset, 188 }, 
	{ Name_VisInfo_propget, 189 }, 
	{ Name_VisInfo_propset, 190 }, 
	{ MainColor_VisInfo_propget, 191 }, 
	{ MainColor_VisInfo_propset, 192 }, 
	{ Changed_VisInfo_propget, 399 }, 
	{ Changed_VisInfo_propset, 400 }, 
	{ Visible_VisInfo_propget, 441 }, 
	{ Visible_VisInfo_propset, 442 }, 
	{ Locatable_VisInfo_propget, 443 }, 
	{ Locatable_VisInfo_propset, 444 }, 
	{ SizeX_PointVisInfo_propget, 193 }, 
	{ SizeX_PointVisInfo_propset, 194 }, 
	{ SizeY_PointVisInfo_propget, 195 }, 
	{ SizeY_PointVisInfo_propset, 196 }, 
	{ Rotate_PointVisInfo_propget, 197 }, 
	{ Rotate_PointVisInfo_propset, 198 }, 
	{ BkColor_PointVisInfo_propget, 199 }, 
	{ BkColor_PointVisInfo_propset, 200 }, 
	{ Width_LineVisInfo_propget, 201 }, 
	{ Width_LineVisInfo_propset, 202 }, 
	{ Width_AreaVisInfo_propget, 203 }, 
	{ Width_AreaVisInfo_propset, 204 }, 
	{ Opaque_AreaVisInfo_propget, 205 }, 
	{ Opaque_AreaVisInfo_propset, 206 }, 
	{ BkContour_AreaVisInfo_propget, 207 }, 
	{ BkContour_AreaVisInfo_propset, 208 }, 
	{ BkColor_AreaVisInfo_propget, 209 }, 
	{ BkColor_AreaVisInfo_propset, 210 }, 
	{ SizeX_TextVisInfo_propget, 211 }, 
	{ SizeX_TextVisInfo_propset, 212 }, 
	{ SizeY_TextVisInfo_propget, 213 }, 
	{ SizeY_TextVisInfo_propset, 214 }, 
	{ Bold_TextVisInfo_propget, 215 }, 
	{ Bold_TextVisInfo_propset, 216 }, 
	{ Italic_TextVisInfo_propget, 217 }, 
	{ Italic_TextVisInfo_propset, 218 }, 
	{ Underline_TextVisInfo_propget, 219 }, 
	{ Underline_TextVisInfo_propset, 220 }, 
	{ StrikeThrough_TextVisInfo_propget, 221 }, 
	{ StrikeThrough_TextVisInfo_propset, 222 }, 
	{ AlignStyle_TextVisInfo_propget, 223 }, 
	{ AlignStyle_TextVisInfo_propset, 224 }, 
	{ FrameStyle_TextVisInfo_propget, 225 }, 
	{ FrameStyle_TextVisInfo_propset, 226 }, 
	{ Rotate_TextVisInfo_propget, 227 }, 
	{ Rotate_TextVisInfo_propset, 228 }, 
	{ Slant_TextVisInfo_propget, 229 }, 
	{ Slant_TextVisInfo_propset, 230 }, 

	{ refcnt_PointVisInfo, 283 },
	{ refcnt_LineVisInfo, 284 },
	{ refcnt_AreaVisInfo, 285 },
	{ refcnt_TextVisInfo, 286 },

	{ RGB_protofunc, 231 }, 
	{ Red_protofunc, 232 }, 
	{ Green_protofunc, 233 }, 
	{ Blue_protofunc, 234 }, 
	{ HSB_protofunc, 235 }, 
	{ Hue_protofunc, 236 }, 
	{ Saturation_protofunc, 237 }, 
	{ Brightness_protofunc, 238 }, 

	{ Refresh_Documents_command, 257 },
	{ Refresh_GeoObjects_command, 260 },
	{ Refresh_GeoClasses_command, 259 },
	{ Refresh_GeoViews_command, 258 },
	{ Refresh_GeoObjectWins_command, 262 },
	{ Refresh_GeoFeatures_command, 261 },

// ToolBars support
	{ Refresh_ToolBars_command, 367 },
	{ propget_ToolBars_NewEnum, 368 },
	{ propget_ToolBars_Next, 369 },
	{ cmd_ToolBars_SaveState, 379 },
	{ cmd_ToolBars_LoadState, 380 },

// ToolBar support
	{ refcnt_ToolBar, 264 },
	{ Visible_ToolBar_propget, 266 },
	{ Visible_ToolBar_propset, 267 },
	{ Name_ToolBar_propget, 279 },
	{ Name_ToolBar_propset, 280 },
	{ DockState_ToolBar_propget, 281 },
	{ DockState_ToolBar_propset, 282 },
	{ Remove_ToolBar_command, 268 },
	{ InsertButton_ToolBar_command, 278 },
	{ propget_ToolBar_Left, 331 },
	{ propset_ToolBar_Left, 332 },
	{ propget_ToolBar_Top, 333 },
	{ propset_ToolBar_Top, 334 },
	{ propget_ToolBar_Width, 335 },
	{ propset_ToolBar_Width, 336 },
	{ propget_ToolBar_Height, 337 },
	{ propset_ToolBar_Height, 338 },
	{ propget_ToolBar_CtrlID, 381 },
	{ propset_ToolBar_CtrlID, 382 },
	{ propget_ToolBar_Style, 403 },
	{ propset_ToolBar_Style, 404 },
	{ propget_ToolBar_StyleEx, 405 },
	{ propset_ToolBar_StyleEx, 406 },

// ToolBarButton support
	{ refcnt_ToolBarButton, 265 },
	{ Name_ToolBarButton_propget, 269 },
	{ Name_ToolBarButton_propset, 270 },
	{ Helptext_ToolBarButton_propget, 271 },
	{ Helptext_ToolBarButton_propset, 272 },
	{ State_ToolBarButton_propget, 273 },
	{ State_ToolBarButton_propset, 274 },
	{ Style_ToolBarButton_propget, 275 },
	{ Style_ToolBarButton_propset, 276 },
	{ AttachImage_ToolBarButton_command, 277 },
	{ AttachImage_ToolBarButton_command2, 383 },
	{ AttachImage_ToolBarButton_command3, 384 },
	{ Value_ToolBarButton_propset, 324 },
	{ CmdID_ToolBarButton_propget, 409 },
	{ CmdID_ToolBarButton_propset, 410 },

// support for PropertyActions
	{ PropertySequence_refcnt, 287 },
	{ PropertySequence_propget_Description, 288 },
	{ PropertySequence_propset_Description, 289 },
	{ PropertySequence_cmd_AddAction, 290 },
	{ PropertySequence_cmd_AddActionSequence, 291 },
	{ PropertySequence_func_DoActions, 292 },
	{ PropertySequence_cmd_DoActions, 293 },
	{ PropertySequence_cmd_Save, 319 },
	{ PropertySequence_cmd_Load, 320 },
	{ PropertySequence_cmd_Init, 321 },
	{ PropertySequence_func_RedoActions, 401 },
	{ PropertySequence_cmd_RedoActions, 402 },

	{ PropertyChoice_refcnt, 327 },
	{ JoinPropertyActions_refcnt, 471 },
	{ SplitPropertyActions_refcnt, 472 },

// StatusIndicator
	{ StatusIndicator_propget_Caption, 345 },
	{ StatusIndicator_propset_Caption, 346 },
	{ StatusIndicator_propget_Field, 347 },
	{ StatusIndicator_propset_Field, 348 },
	{ StatusIndicator_cmd_Restart, 342 },
	{ StatusIndicator_func_SetPosition, 343 },
	{ StatusIndicator_func_WasCaceled, 344 },
	{ StatusIndicator_refcnt, 341 },
	{ StatusIndicator_func_InitNew, 459 },
	{ StatusIndicator_propset_Flags, 460 },
	{ StatusIndicator_propget_Flags, 461 },
	{ StatusIndicator_func_IncrementPosition, 462 },
	{ StatusIndicator_func_ChangeText, 463 },
	{ StatusIndicator_func_RetrieveText, 464 },

// #HK001017
	{ StatusIndicator_method_Show, 473 },
	{ StatusIndicator_method_Hide, 474 },

// ResourcenSupport
	{ LoadResPicture_protofunc,	393 },
	{ LoadResString_protofunc, 394 },
	{ LoadPicture_protofunc, 392 },

// IPicture support
	{ refcnt_Picture, 385 },
	{ Handle_Picture_propget, 386 },
	{ hPal_Picture_propget,	387 },
	{ hPal_Picture_propset,	388 },
	{ Type_Picture_propget,	389 },
	{ Width_Picture_propget, 390 },
	{ Height_Picture_propget, 391 },
};
#define NUMEXTPROCS (sizeof(s_StaticExtFcns)/sizeof(s_StaticExtFcns[0]))

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (dynamisch/laufzeitgeneriert)
ebEXTPROC *g_pExtFcns = NULL;
int g_iExtFcnsOffset = 0;		// Offset zum ersten Eintrag
int g_iExtFcnsLast = 0;			// erster nicht belegter FuncID

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung der SprungverteilerTabelle
inline int imin (int i1, int i2) { return (i1 < i2) ? i1 : i2; }
inline int imax (int i1, int i2) { return (i1 > i2) ? i1 : i2; }

ebEXTPROC *InitJumpTable (int &riMin, int &riMax)
{
	ASSERT(0 < NUMEXTPROCS);	// mindestens eine Funktion muß existieren

// kleinsten und größten Index finden
int iMin = INT_MAX;
int iMax = 0;
STATICEXTPROC *pTab = s_StaticExtFcns;

	for (int i = 0; i < NUMEXTPROCS; i++, pTab++) {
		iMin = imin (iMin, pTab -> m_iFcnNum);
		iMax = imax (iMax, pTab -> m_iFcnNum);
	}
	ASSERT(iMin != INT_MAX);
	ASSERT(iMax >= iMin);

// dynamische Sprungverteilertabelle anlegen
int iSize = iMax - iMin + 1;
ebEXTPROC *pFuncTab = NULL;
	
	ATLTRY(pFuncTab = new ebEXTPROC [iSize]);
	if (NULL == pFuncTab) return NULL;

	riMin = iMin;
	riMax = iMax + 1;

// Sprungverteilertabelle initialisieren
ebEXTPROC *pFcn = pFuncTab;
int j = 0;

	for (j = 0; j < iSize; j++, pFcn++) 
		*pFcn = TRiAS_not_supported;

	pTab = s_StaticExtFcns;
	for (j = 0; j < NUMEXTPROCS; j++, pTab++) {
	ebEXTPROC &rNewFcn = pFuncTab[pTab -> m_iFcnNum - iMin];
	
	// dieser Eintrag darf noch nicht belegt sein	
		ASSERT(rNewFcn == TRiAS_not_supported);
		
		rNewFcn = pTab -> m_pExtFcn;		// Funktion setzen
	}

return pFuncTab;
}

void FreeJumpTable (ebEXTPROC *&rpExtFcns)
{
	if (NULL != rpExtFcns) {
		delete[] rpExtFcns;
		rpExtFcns = NULL;
	}
}

