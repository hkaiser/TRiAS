
RunCmdAsps.dll: dlldata.obj RunCmdAs_p.obj RunCmdAs_i.obj
	link /dll /out:RunCmdAsps.dll /def:RunCmdAsps.def /entry:DllMain dlldata.obj RunCmdAs_p.obj RunCmdAs_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RunCmdAsps.dll
	@del RunCmdAsps.lib
	@del RunCmdAsps.exp
	@del dlldata.obj
	@del RunCmdAs_p.obj
	@del RunCmdAs_i.obj
