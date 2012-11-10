


!include ..\control\borlandc.ctl

LIBRARY  = $(BASE)
LIBRARYP = $(YACLLIB)\$(LIBRARY)
MEMLIB   = $(YACLLIB)\$(MEMORY).lib

# ------------------------ Names of files --------------------------


OBJECTS  =   \
bitset.obj   \
bytarray.obj \
bytestrm.obj \
bytstrng.obj \
clntset.obj  \
date.obj     \
error.obj    \
gbtree.obj   \
genseq.obj   \
integer.obj  \
intseq.obj   \
intset.obj   \
map.obj      \
object.obj   \
objseq.obj   \
objset.obj   \
regexpr.obj  \
segseq.obj   \
stream.obj   \
strgseq.obj  \
strgset.obj  \
string.obj   \
strsplit.obj \
tbtree.obj   \
timeofda.obj \
tree.obj     \
treewalk.obj \
version.obj

# STATIC_OBJS = statbase.obj



# ---------------------- Compilation rules -----------------------


.SUFFIXES:
.SUFFIXES: .cxx .obj


CCOPTS    = $(CCOPTS) $(OPTIMIZE)


TARGET = $(LIBRARYP).lib


!if $d(BUILD_DLL)
!if $(YACLPLATFORM) == WINDOWS
CCOPTS   = $(CCOPTS) -DBUILD_DLL -WDE -tWDE -p-
TARGET   = $(LIBRARYP).dll
LINK_DLL = -Twd -C -c -A:16
C0OBJD   = c0dl
COBJD    = crtldll cwl 
IMPORT   = import
MATH     = mathwl
DLLMAIN  = dllmain.obj
!elif $(YACLPLATFORM) == WIN32
CCOPTS   = -WDE -tWDE $(CCOPTS) -DBUILD_DLL 
TARGET   = $(LIBRARYP).dll
LINK_DLL = -Tpd 
C0OBJD   = c0d32
COBJD    = cw32
IMPORT   = import32
CPP_IMP  = cl.lib
MATH     = 
DLLMAIN  = dllmain.obj
!elif $(YACLPLATFORM) == OS2
CCOPTS   = $(CCOPTS) -sd  -DBUILD_DLL
TARGET   = $(LIBRARYP).dll
LINK_DLL = -Tod
C0OBJD   = c02d
COBJD    = c2 os2
DLLDEF   = base.def
DLLMAIN  =
!else
!error Cannot build dll for $(YACLPLATFORM).
!ENDIF
!ENDIF




.cxx.obj:
    $(CC) $(DEBUG) -Jgd +$(LIBRARY).cfg  { $<}


	
all: $(LIBRARY).cfg $(TARGET) $(MEMLIB) $(STATIC_OBJS)
    -$(DELETE) $(LIBRARY).cfg
    
	
$(LIBRARY).cfg: borlandc.mak $(YACLPATH)\control\borlandc.ctl
    copy &&|
$(WARNINGS) $(CCOPTS)
| $(LIBRARY).cfg


$(LIBRARYP).lib: $(OBJECTS) $(STATIC_OBJS)
    $(LIBR) $(LIBRARYP) /E /P64 @&&!
-+$(OBJECTS: = -+) -+$(STATIC_OBJS)
!
    -$(DELETE) $(LIBRARYP).BAK



$(LIBRARYP).dll: $(OBJECTS) $(STATIC_OBJS) $(DLLMAIN) basedll.def
    $(LINK) $(DEBUG) $(LINK_DLL) -L$(BCPATH)\LIB @&&|
    $(BCPATH)\LIB\$(C0OBJD).OBJ $(OBJECTS) $(STATIC_OBJS) $(DLLMAIN)
    $(LIBRARYP).dll
    NUL
    $(COBJD) $(IMPORT) $(MATH)
|, basedll.def
    $(BCPATH)\bin\implib $(LIBRARYP).lib $(LIBRARYP).dll
    -del basedll.def



!if $(YACLPLATFORM) == WINDOWS
basedll.def:
    copy &&|
    LIBRARY base;dll
    EXETYPE WINDOWS
    CODE PRELOAD MOVEABLE DISCARDABLE
    DATA PRELOAD MOVEABLE MULTIPLE
    HEAPSIZE 32000
| basedll.def
!elif $(YACLPLATFORM) == WIN32
basedll.def:
    copy &&|
    LIBRARY base;dll
    EXETYPE WINDOWS
    CODE PRELOAD MOVEABLE DISCARDABLE
    DATA PRELOAD MOVEABLE MULTIPLE
    HEAPSIZE 32000
| basedll.def
!elif $(YACLPLATFORM) == OS2
basedll.def:
    copy &&|
    LIBRARY base INITINSTANCE
    DESCRIPTION 'YACL base library'
    PROTMODE
    DATA  NONSHARED
| basedll.def
!endif


    
    
$(MEMLIB): memory.obj
	$(LIBR) $(YACLLIB)\$(MEMORY) -+memory.obj
	-$(DELETE) $(YACLLIB)\$(MEMORY).bak


memory.obj: memory.cxx
	$(CC) @&&|
$(CCOPTS)
| memory.cxx

	
# ------------------ Other targets ---------------------------




clean:
    -del *.obj
    -del *.cfg
    -del $(LIBRARYP).lib
    -del $(LIBRARYP).dll
    -del $(LIBRARYP).bak
    -del $(YACLLIB)\$(MEMORY).lib
    -del $(YACLLIB)\$(MEMORY).bak






