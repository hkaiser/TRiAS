# Makefile zur Erstellung von TRiAS3 - Bilder4

$(TRIASDIR_D)\bilderd.ext :
	CD OBJ32
	nmake /F BILDER16.MAK new formake
	CD ..
	SET T3PROJECT=Bilder4.dsp
	SET T3CONFIG="Bilder - Win32 Debug"
	SET T3LOGFILE=Bilder4.log
!INCLUDE C:\MAKE\MkMSDEV.mak	

$(TRIASDIR_R)\bilder.ext :
	CD OBJ32
	nmake /F BILDER16.MAK new formake
	CD ..
	SET T3PROJECT=Bilder4.dsp
	SET T3CONFIG="Bilder - Win32 Release"
	SET T3LOGFILE=Bilder4.log
!INCLUDE C:\MAKE\MkMSDEV.mak	
