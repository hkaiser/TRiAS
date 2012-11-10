
CvrtAscps.dll: dlldata.obj CvrtAsc_p.obj CvrtAsc_i.obj
	link /dll /out:CvrtAscps.dll /def:CvrtAscps.def /entry:DllMain dlldata.obj CvrtAsc_p.obj CvrtAsc_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CvrtAscps.dll
	@del CvrtAscps.lib
	@del CvrtAscps.exp
	@del dlldata.obj
	@del CvrtAsc_p.obj
	@del CvrtAsc_i.obj
