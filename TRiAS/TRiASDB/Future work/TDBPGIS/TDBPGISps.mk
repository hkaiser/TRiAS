
TDBPGISps.dll: dlldata.obj TDBPGIS_p.obj TDBPGIS_i.obj
	link /dll /out:TDBPGISps.dll /def:TDBPGISps.def /entry:DllMain dlldata.obj TDBPGIS_p.obj TDBPGIS_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TDBPGISps.dll
	@del TDBPGISps.lib
	@del TDBPGISps.exp
	@del dlldata.obj
	@del TDBPGIS_p.obj
	@del TDBPGIS_i.obj
