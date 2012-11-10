# Microsoft Developer Studio Project File - Name="Ixtatl50" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Ixtatl50 - Win32 Debug WTL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ixtatl50.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ixtatl50.mak" CFG="Ixtatl50 - Win32 Debug WTL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ixtatl50 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Ixtatl50 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Ixtatl50 - Win32 Debug WTL" (based on "Win32 (x86) Static Library")
!MESSAGE "Ixtatl50 - Win32 Release WTL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Extension BaseClass (MFC)", EAEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Mfc50\Release"
# PROP Intermediate_Dir ".\Mfc50\Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /Yu"xtensnp.hxx" /Fd".\Mfc50\Release/Ixtmar50.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Mfc50\Release\Ixtmar50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Mfc50\Release
TargetPath=.\Mfc50\Release\Ixtmar50.lib
TargetName=Ixtmar50
InputPath=.\Mfc50\Release\Ixtmar50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Mfc50\Debug"
# PROP Intermediate_Dir ".\Mfc50\Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /FR /Yu"xtensnp.hxx" /Fd".\Mfc50\Debug/Ixtmad50.pdb" /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Mfc50\Debug\Ixtmad50.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Mfc50\Debug
TargetPath=.\Mfc50\Debug\Ixtmad50.lib
TargetName=Ixtmad50
InputPath=.\Mfc50\Debug\Ixtmad50.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Ixtatl50___Win32_Debug_WTL"
# PROP BASE Intermediate_Dir "Ixtatl50___Win32_Debug_WTL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Wtl\Debug"
# PROP Intermediate_Dir "Wtl\Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /FR /Yu"xtensnp.hxx" /Fd".\Mfc50\Debug/Ixtmad50.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "__WTL__" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /FR /Fp"Wtl/Debug/Ixtwtld.pch" /Yu"xtensnp.hxx" /Fd".\Wtl\Debug/Ixtwtld.pdb" /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Mfc50\Debug\Ixtmad50.lib"
# ADD LIB32 /nologo /out:".\Wtl\Debug\Ixtwtld.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Wtl\Debug
TargetPath=.\Wtl\Debug\Ixtwtld.lib
TargetName=Ixtwtld
InputPath=.\Wtl\Debug\Ixtwtld.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Ixtatl50___Win32_Release_WTL"
# PROP BASE Intermediate_Dir "Ixtatl50___Win32_Release_WTL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Wtl\Release"
# PROP Intermediate_Dir "Wtl\Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /Yu"xtensnp.hxx" /Fd".\Mfc50\Release/Ixtmar50.pdb" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "__WTL__" /D "_MBCS" /D "__ATL_XTENSION_BASE__" /Fp"Wtl/Release/Ixtwtlr.pch" /Yu"xtensnp.hxx" /Fd".\Wtl\Release/Ixtwtlr.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Mfc50\Release\Ixtmar50.lib"
# ADD LIB32 /nologo /out:".\Wtl\Release\Ixtwtlr.lib"
# Begin Custom Build - Copying created library ...
OutDir=.\Wtl\Release
TargetPath=.\Wtl\Release\Ixtwtlr.lib
TargetName=Ixtwtlr
InputPath=.\Wtl\Release\Ixtwtlr.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASLIB) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Ixtatl50 - Win32 Release"
# Name "Ixtatl50 - Win32 Debug"
# Name "Ixtatl50 - Win32 Debug WTL"
# Name "Ixtatl50 - Win32 Release WTL"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ctfxmfc.cpp
DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\STDAFX.H"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\atlbasex.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"Com\ClassFactoryCache.h"\
	{$(INCLUDE)}"Com\PropertyHelper.h"\
	{$(INCLUDE)}"com\VariantHelpers.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"CSPoint.h"\
	{$(INCLUDE)}"CSPointGeom.h"\
	{$(INCLUDE)}"CSRectGeom.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"geo_inl.hxx"\
	{$(INCLUDE)}"GMObjects\DefCoordSystem.tlh"\
	{$(INCLUDE)}"GMObjects\GeoMedia.tlh"\
	{$(INCLUDE)}"GMObjects\GMObjects.h"\
	{$(INCLUDE)}"GMObjects\Mapview.tlh"\
	{$(INCLUDE)}"GMObjects\PBasic.tlh"\
	{$(INCLUDE)}"GMObjects\PClient.tlh"\
	{$(INCLUDE)}"GMObjects\PCSS.tlh"\
	{$(INCLUDE)}"GMObjects\PDBPipe.tlh"\
	{$(INCLUDE)}"GMObjects\PService.tlh"\
	{$(INCLUDE)}"GMObjects\PView.tlh"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ictf.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"TrCatIds.h"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"TRiASBaseInterfaces.h"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"TRiASDB.h"\
	{$(INCLUDE)}"TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CtfxmfcObsolete.cpp
DEP_CPP_CTFXMF=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"Com\ClassFactoryCache.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"CSPoint.h"\
	{$(INCLUDE)}"CSPointGeom.h"\
	{$(INCLUDE)}"CSRectGeom.h"\
	{$(INCLUDE)}"ctf.h"\
	{$(INCLUDE)}"ctfm.hxx"\
	{$(INCLUDE)}"ctfx.hxx"\
	{$(INCLUDE)}"ctfxmfc.h"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dblpair.hxx"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"geo_inl.hxx"\
	{$(INCLUDE)}"GMObjects\DefCoordSystem.tlh"\
	{$(INCLUDE)}"GMObjects\GeoMedia.tlh"\
	{$(INCLUDE)}"GMObjects\GMObjects.h"\
	{$(INCLUDE)}"GMObjects\Mapview.tlh"\
	{$(INCLUDE)}"GMObjects\PBasic.tlh"\
	{$(INCLUDE)}"GMObjects\PClient.tlh"\
	{$(INCLUDE)}"GMObjects\PCSS.tlh"\
	{$(INCLUDE)}"GMObjects\PDBPipe.tlh"\
	{$(INCLUDE)}"GMObjects\PService.tlh"\
	{$(INCLUDE)}"GMObjects\PView.tlh"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ictf.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"resstrg.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"TRiASBaseInterfaces.h"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"TRiASDB.h"\
	{$(INCLUDE)}"TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dllbindx.cxx
DEP_CPP_DLLBI=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"dllbindx.hxx"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy1.cxx
DEP_CPP_DUMMY=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy2.cxx
DEP_CPP_DUMMY2=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy3.cxx
DEP_CPP_DUMMY3=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dummy4.cxx
DEP_CPP_DUMMY4=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy6.cpp
DEP_CPP_DUMMY6=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy7.cpp
DEP_CPP_DUMMY7=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy8.cpp
DEP_CPP_DUMMY8=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dummy9.cpp
DEP_CPP_DUMMY9=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\enmcprop.cxx
DEP_CPP_ENMCP=\
	".\cimpxtsn.hxx"\
	".\enmcprop.hxx"\
	".\synccook.h"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\enumprop.cxx
DEP_CPP_ENUMP=\
	".\cimpxtsn.hxx"\
	".\enumprop.hxx"\
	".\synccook.h"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Extreg.cxx
DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"resstrg.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"TrCatIds.h"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"WrongTrCatIds.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hdrentrx.cxx
DEP_CPP_HDREN=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"hdrentrx.hxx"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ienumonr.cxx
DEP_CPP_IENUM=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"ienumonr.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Objcontx.cxx
DEP_CPP_OBJCO=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"Com\ClassFactoryCache.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"CSPoint.h"\
	{$(INCLUDE)}"CSPointGeom.h"\
	{$(INCLUDE)}"CSRectGeom.h"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"geo_inl.hxx"\
	{$(INCLUDE)}"GMObjects\DefCoordSystem.tlh"\
	{$(INCLUDE)}"GMObjects\GeoMedia.tlh"\
	{$(INCLUDE)}"GMObjects\GMObjects.h"\
	{$(INCLUDE)}"GMObjects\Mapview.tlh"\
	{$(INCLUDE)}"GMObjects\PBasic.tlh"\
	{$(INCLUDE)}"GMObjects\PClient.tlh"\
	{$(INCLUDE)}"GMObjects\PCSS.tlh"\
	{$(INCLUDE)}"GMObjects\PDBPipe.tlh"\
	{$(INCLUDE)}"GMObjects\PService.tlh"\
	{$(INCLUDE)}"GMObjects\PView.tlh"\
	{$(INCLUDE)}"ictf.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"objcontx.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\objpropf.cxx
DEP_CPP_OBJPR=\
	".\cimpxtsn.hxx"\
	".\objpropf.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropNamex.cpp
DEP_CPP_PROPN=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"propnamex.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
DEP_CPP_REGIS=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strutil.cxx
DEP_CPP_STRUT=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XtencAtl.cxx
DEP_CPP_XTENC=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"fnamestr.h"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"registrx.hxx"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"TrCatIds.h"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"WrongTrCatIds.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Xtensnp.cxx
DEP_CPP_XTENS=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

# ADD CPP /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

# ADD CPP /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xtsnatl.cpp
DEP_CPP_XTSNA=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XtsnImpAtl.cpp
DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"XtsnImpAtl.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XtsnPropAtl.cpp
DEP_CPP_XTSNP=\
	".\cimpxtsn.hxx"\
	".\enmcprop.hxx"\
	".\enumprop.hxx"\
	".\objpropf.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"eonrguid.h"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"TRiASHelper.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"xtsnguid.h"\
	{$(INCLUDE)}"XtsnPropAtl.h"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=C:\MSDEV5\VC\atl\include\ATL20.H
# End Source File
# Begin Source File

SOURCE=C:\MSDEV5\VC\atl\include\AtlImpl20.h
# End Source File
# Begin Source File

SOURCE=.\enmcprop.hxx
# End Source File
# Begin Source File

SOURCE=.\enumprop.hxx
# End Source File
# Begin Source File

SOURCE=.\objpropf.hxx
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\synccook.h
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\xtencatl.hxx
# End Source File
# Begin Source File

SOURCE=.\Xtensnp.hxx
# End Source File
# Begin Source File

SOURCE=..\..\INCLUDE\XtsnPropAtl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\DUMPOUT.CXX
DEP_CPP_DUMPO=\
	".\cimpxtsn.hxx"\
	".\XtensionConfig.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"aggressiveoptimize.h"\
	{$(INCLUDE)}"atl20.h"\
	{$(INCLUDE)}"Atl\AtlDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"Atl\PE_Debug.h"\
	{$(INCLUDE)}"atlapp.h"\
	{$(INCLUDE)}"atlgdi.h"\
	{$(INCLUDE)}"atlmisc.h"\
	{$(INCLUDE)}"atlres.h"\
	{$(INCLUDE)}"atluser.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bool.h"\
	{$(INCLUDE)}"commonvu.hxx"\
	{$(INCLUDE)}"config\_compile.h"\
	{$(INCLUDE)}"config\_platfrm.h"\
	{$(INCLUDE)}"config\compiler.h"\
	{$(INCLUDE)}"config\local.h"\
	{$(INCLUDE)}"config\platform.h"\
	{$(INCLUDE)}"containr.hxx"\
	{$(INCLUDE)}"ctrlines.hxx"\
	{$(INCLUDE)}"ctrtypes.hxx"\
	{$(INCLUDE)}"cv_defs.h"\
	{$(INCLUDE)}"cv_types.hxx"\
	{$(INCLUDE)}"cvInline.hxx"\
	{$(INCLUDE)}"cxxtypes.hxx"\
	{$(INCLUDE)}"DateTime.h"\
	{$(INCLUDE)}"dbconfig.h"\
	{$(INCLUDE)}"dbtypes.h"\
	{$(INCLUDE)}"declarehandles.h"\
	{$(INCLUDE)}"defines.hpp"\
	{$(INCLUDE)}"errcodes.hxx"\
	{$(INCLUDE)}"exceptio.hpp"\
	{$(INCLUDE)}"Foundation\APIStructs\GCUtil.h"\
	{$(INCLUDE)}"Foundation\Apps\ClientWnd.h"\
	{$(INCLUDE)}"Foundation\Controls\AtlControls.h"\
	{$(INCLUDE)}"foundation\CppIface.h"\
	{$(INCLUDE)}"Foundation\Debug.h"\
	{$(INCLUDE)}"Foundation\Events\CommandListener.h"\
	{$(INCLUDE)}"foundation\Events\Event.h"\
	{$(INCLUDE)}"Foundation\Events\EventFactory.h"\
	{$(INCLUDE)}"foundation\Events\EventListener.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouter.h"\
	{$(INCLUDE)}"Foundation\Events\EventRouterMap.h"\
	{$(INCLUDE)}"Foundation\Events\KeyboardListener.h"\
	{$(INCLUDE)}"Foundation\Events\MouseEvent.h"\
	{$(INCLUDE)}"Foundation\Events\ScrollListener.h"\
	{$(INCLUDE)}"Foundation\Events\WindowListener.h"\
	{$(INCLUDE)}"foundation\Events\WinEvent.h"\
	{$(INCLUDE)}"foundation\graphics\gccore.h"\
	{$(INCLUDE)}"Foundation\Graphics\GDIObjects.h"\
	{$(INCLUDE)}"Foundation\Graphics\GraphicContext.h"\
	{$(INCLUDE)}"Foundation\GuidCast.h"\
	{$(INCLUDE)}"Foundation\Layout\BorderClient.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutBase.h"\
	{$(INCLUDE)}"foundation\Layout\LayoutNode.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcClientViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcCommand.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcController.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcLogicalPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcModel.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcScrollWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcViewport.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcVisualComponent.h"\
	{$(INCLUDE)}"Foundation\Mvc\MvcVisualPart.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcWrapper.h"\
	{$(INCLUDE)}"Foundation\MVC\MvcZoomCommand.h"\
	{$(INCLUDE)}"foundation\Patterns\Composite.h"\
	{$(INCLUDE)}"foundation\Patterns\Factory.h"\
	{$(INCLUDE)}"foundation\Patterns\Iterator.h"\
	{$(INCLUDE)}"Foundation\Patterns\SubjectObserver.h"\
	{$(INCLUDE)}"Foundation\Print\PageSettings.h"\
	{$(INCLUDE)}"Foundation\Print\Printable.h"\
	{$(INCLUDE)}"Foundation\Print\PrintDoc.h"\
	{$(INCLUDE)}"Foundation\Print\Printer.h"\
	{$(INCLUDE)}"Foundation\Print\PrinterConfig.h"\
	{$(INCLUDE)}"Foundation\Print\PrintJob.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewController.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewModel.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewViewport.h"\
	{$(INCLUDE)}"Foundation\Print\PrintPreviewWnd.h"\
	{$(INCLUDE)}"Foundation\RefCount.h"\
	{$(INCLUDE)}"Foundation\SflCommon.h"\
	{$(INCLUDE)}"foundation\SflDef.h"\
	{$(INCLUDE)}"Foundation\SflDll.h"\
	{$(INCLUDE)}"foundation\SflGuids.h"\
	{$(INCLUDE)}"Foundation\sflres.h"\
	{$(INCLUDE)}"Foundation\SflVersion.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinates.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\LogCoordinatesImpl.h"\
	{$(INCLUDE)}"foundation\StructuredGraphics\Visual.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualHost.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\VisualWindow.h"\
	{$(INCLUDE)}"Foundation\StructuredGraphics\Zoom.h"\
	{$(INCLUDE)}"Foundation\Util\Convert.h"\
	{$(INCLUDE)}"freestor.hxx"\
	{$(INCLUDE)}"gc.h"\
	{$(INCLUDE)}"gc_cpp.h"\
	{$(INCLUDE)}"ienumobj.hxx"\
	{$(INCLUDE)}"istatus.h"\
	{$(INCLUDE)}"ixtensn.hxx"\
	{$(INCLUDE)}"ospace\com\comerrormacros.h"\
	{$(INCLUDE)}"ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"ospace\com\smartif.h"\
	{$(INCLUDE)}"ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"ospace\config.h"\
	{$(INCLUDE)}"ospace\except\config.h"\
	{$(INCLUDE)}"ospace\except\except.h"\
	{$(INCLUDE)}"ospace\except\stdex.h"\
	{$(INCLUDE)}"ospace\internal\fmacros.h"\
	{$(INCLUDE)}"ospace\std\iosfwd"\
	{$(INCLUDE)}"ospace\std\istream"\
	{$(INCLUDE)}"ospace\std\list"\
	{$(INCLUDE)}"ospace\std\map"\
	{$(INCLUDE)}"ospace\std\ostream"\
	{$(INCLUDE)}"ospace\std\string"\
	{$(INCLUDE)}"ospace\std\vector"\
	{$(INCLUDE)}"ospace\stl\allocate.cc"\
	{$(INCLUDE)}"ospace\stl\allocate.h"\
	{$(INCLUDE)}"ospace\stl\allocimp.h"\
	{$(INCLUDE)}"ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"ospace\stl\basalgo.h"\
	{$(INCLUDE)}"ospace\stl\common.h"\
	{$(INCLUDE)}"ospace\stl\config.h"\
	{$(INCLUDE)}"ospace\stl\function.h"\
	{$(INCLUDE)}"ospace\stl\internal.h"\
	{$(INCLUDE)}"ospace\stl\iterator.cc"\
	{$(INCLUDE)}"ospace\stl\iterator.h"\
	{$(INCLUDE)}"ospace\stl\list.cc"\
	{$(INCLUDE)}"ospace\stl\list.h"\
	{$(INCLUDE)}"ospace\stl\map.cc"\
	{$(INCLUDE)}"ospace\stl\map.h"\
	{$(INCLUDE)}"ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"ospace\stl\ops.h"\
	{$(INCLUDE)}"ospace\stl\pair.h"\
	{$(INCLUDE)}"ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"ospace\stl\rbtree.h"\
	{$(INCLUDE)}"ospace\stl\stlerror.h"\
	{$(INCLUDE)}"ospace\stl\treeaux.h"\
	{$(INCLUDE)}"ospace\stl\vector.cc"\
	{$(INCLUDE)}"ospace\stl\vector.h"\
	{$(INCLUDE)}"ospace\string\basic.cc"\
	{$(INCLUDE)}"ospace\string\basic.h"\
	{$(INCLUDE)}"ospace\string\basic.ipp"\
	{$(INCLUDE)}"ospace\string\config.h"\
	{$(INCLUDE)}"ospace\string\search.cc"\
	{$(INCLUDE)}"ospace\string\search.h"\
	{$(INCLUDE)}"ospace\string\string.h"\
	{$(INCLUDE)}"ospace\string\traits.cc"\
	{$(INCLUDE)}"ospace\string\traits.h"\
	{$(INCLUDE)}"ospace\type\prim.h"\
	{$(INCLUDE)}"ospace\utility\memory.h"\
	{$(INCLUDE)}"print.h"\
	{$(INCLUDE)}"protos.h"\
	{$(INCLUDE)}"risdb.h"\
	{$(INCLUDE)}"syncthrd.hxx"\
	{$(INCLUDE)}"syncthrdcs.hxx"\
	{$(INCLUDE)}"tassert.hxx"\
	{$(INCLUDE)}"trias01m.hxx"\
	{$(INCLUDE)}"triasconfig.h"\
	{$(INCLUDE)}"tstring"\
	{$(INCLUDE)}"tstring.hpp"\
	{$(INCLUDE)}"versions.h"\
	{$(INCLUDE)}"xtencatl.hxx"\
	{$(INCLUDE)}"xtencunk.hxx"\
	{$(INCLUDE)}"xtension.h"\
	{$(INCLUDE)}"xtensnm.hxx"\
	{$(INCLUDE)}"xtensnn.h"\
	{$(INCLUDE)}"xtensnx.h"\
	{$(INCLUDE)}"xtensnxx.h"\
	{$(INCLUDE)}"xtsnaux.hxx"\
	{$(INCLUDE)}"yxvals.h"\
	

!IF  "$(CFG)" == "Ixtatl50 - Win32 Release"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Debug WTL"

!ELSEIF  "$(CFG)" == "Ixtatl50 - Win32 Release WTL"

!ENDIF 

# End Source File
# End Target
# End Project
