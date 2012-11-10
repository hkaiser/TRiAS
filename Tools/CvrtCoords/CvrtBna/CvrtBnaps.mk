
CvrtBnaps.dll: dlldata.obj CvrtBna_p.obj CvrtBna_i.obj
	link /dll /out:CvrtBnaps.dll /def:CvrtBnaps.def /entry:DllMain dlldata.obj CvrtBna_p.obj CvrtBna_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CvrtBnaps.dll
	@del CvrtBnaps.lib
	@del CvrtBnaps.exp
	@del dlldata.obj
	@del CvrtBna_p.obj
	@del CvrtBna_i.obj
