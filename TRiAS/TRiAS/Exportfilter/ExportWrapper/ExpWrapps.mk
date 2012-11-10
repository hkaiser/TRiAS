
ExpWrapps.dll: dlldata.obj ExpWrap_p.obj ExpWrap_i.obj
	link /dll /out:ExpWrapps.dll /def:ExpWrapps.def /entry:DllMain dlldata.obj ExpWrap_p.obj ExpWrap_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ExpWrapps.dll
	@del ExpWrapps.lib
	@del ExpWrapps.exp
	@del dlldata.obj
	@del ExpWrap_p.obj
	@del ExpWrap_i.obj
