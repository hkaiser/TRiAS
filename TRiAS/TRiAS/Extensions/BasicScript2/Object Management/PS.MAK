
ObjManps.dll: dlldata.obj ObjMan_p.obj ObjMan_i.obj
	link /dll /out:ObjManps.dll /def:ObjManps.def /entry:DllMain dlldata.obj ObjMan_p.obj ObjMan_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /DREGISTER_PROXY_DLL $<

clean:
	@del ObjManps.dll
	@del ObjManps.lib
	@del ObjManps.exp
	@del dlldata.obj
	@del ObjMan_p.obj
	@del ObjMan_i.obj
