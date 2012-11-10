
Helperps.dll: dlldata.obj Helper_p.obj Helper_i.obj
	link /dll /out:Helperps.dll /def:Helperps.def /entry:DllMain dlldata.obj Helper_p.obj Helper_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Helperps.dll
	@del Helperps.lib
	@del Helperps.exp
	@del dlldata.obj
	@del Helper_p.obj
	@del Helper_i.obj
