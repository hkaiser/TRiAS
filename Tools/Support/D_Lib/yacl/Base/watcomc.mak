
!include ../control/watcomc.ctl

LIBRARY = $(BASE)

# ------------------------ Names of files --------------------------


OBJ1 = bitset.obj    bytarray.obj  bytestrm.obj  bytstrng.obj  clntset.obj 
OBJ2 = date.obj      error.obj     gbtree.obj    genseq.obj    integer.obj
OBJ3 = intseq.obj    intset.obj    map.obj       object.obj    objseq.obj
OBJ4 = objset.obj    regexpr.obj   stream.obj    strgseq.obj   strgset.obj 
OBJ5 = string.obj    strsplit.obj  segseq.obj    tbtree.obj  
OBJ6 = timeofda.obj  tree.obj      treewalk.obj  version.obj

OBJECTS = $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6)




!ifdef BUILD_DLL
DLLOPTS = -DBUILD_DLL -bd
TARGET  = $(LIBRARY).dll
!else
TARGET  = $(LIBRARY).lib
!endif


all: $(YACLLIB)\$(TARGET) memory.obj .SYMBOLIC




$(YACLLIB)\$(LIBRARY).lib:   $(OBJECTS)  libfile.tmp 
	$(LIBR) /b /p=64 $(YACLLIB)\$(LIBRARY) @libfile.tmp
        -del libfile.tmp


!ifeq YACLPLATFORM WIN32	
$(YACLLIB)\$(LIBRARY).dll:  $(OBJECTS) dllfile.tmp 
	wlink @dllfile.tmp
        %create $(YACLLIB)\base.rex
        wbind $(YACLLIB)\$(LIBRARY).dll -d -n
        wlib $(YACLLIB)\$(LIBRARY).lib +$(YACLLIB)\$(LIBRARY).dll
        -del dllfile.tmp
        -del $(YACLLIB)\base.rex
dllfile.tmp: .SYMBOLIC
  %create dllfile.tmp
  @for %i in ($(OBJECTS)) do @%append dllfile.tmp libfile %i
  @%append dllfile.tmp system nt dll initinstance terminstance
  @%append dllfile.tmp option stack=64K
  @%append dllfile.tmp option caseexact
  @%append dllfile.tmp name $(YACLLIB)\$(LIBRARY).dll


!else ifeq YACLPLATFORM OS2
$(YACLLIB)\$(LIBRARY).dll:  $(OBJECTS) dllfile.tmp 
	wlink @dllfile.tmp
        %create $(YACLLIB)\base.rex
        wbind $(YACLLIB)\$(LIBRARY).dll -d -n
        wlib $(YACLLIB)\$(LIBRARY).lib +$(YACLLIB)\$(LIBRARY).dll
        -del dllfile.tmp
        -del $(YACLLIB)\base.rex
dllfile.tmp: .SYMBOLIC
  %create dllfile.tmp
  @for %i in ($(OBJECTS)) do @%append dllfile.tmp libfile %i
  @%append dllfile.tmp system os2v2 dll initglobal
  @%append dllfile.tmp option stack=64K
  @%append dllfile.tmp option caseexact
  @%append dllfile.tmp name $(YACLLIB)\$(LIBRARY).dll


!endif





libfile.tmp: .SYMBOLIC
  %create libfile.tmp
  @for %i in ($(OBJECTS)) do @%append libfile.tmp -+%i
  


# ---------------------- Compilation rules -----------------------


memory.obj:  memory.cxx
	$(CC) $(CCOPTS) $*.cxx
	$(LIBR) -b $(YACLLIB)\$(MEMORY) -+$*.obj
        
.cxx.obj:
	$(CC) $(CCOPTS) $(DLLOPTS) $*.cxx
        


# ------------------ Other targets ---------------------------




clean: .SYMBOLIC
	-del *.obj
	-del $(YACLLIB)\$(LIBRARY).lib
	-del $(YACLLIB)\$(LIBRARY).bak


