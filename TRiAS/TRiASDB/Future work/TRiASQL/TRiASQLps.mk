
TRiASQLps.dll: dlldata.obj TRiASQL_p.obj TRiASQL_i.obj
	link /dll /out:TRiASQLps.dll /def:TRiASQLps.def /entry:DllMain dlldata.obj TRiASQL_p.obj TRiASQL_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASQLps.dll
	@del TRiASQLps.lib
	@del TRiASQLps.exp
	@del dlldata.obj
	@del TRiASQL_p.obj
	@del TRiASQL_i.obj
