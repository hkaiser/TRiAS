
DefaultCTFps.dll: dlldata.obj DefaultCTF_p.obj DefaultCTF_i.obj
	link /dll /out:DefaultCTFps.dll /def:DefaultCTFps.def /entry:DllMain dlldata.obj DefaultCTF_p.obj DefaultCTF_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del DefaultCTFps.dll
	@del DefaultCTFps.lib
	@del DefaultCTFps.exp
	@del dlldata.obj
	@del DefaultCTF_p.obj
	@del DefaultCTF_i.obj
