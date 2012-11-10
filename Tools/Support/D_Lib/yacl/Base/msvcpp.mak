


!include ..\control\msvcpp.ctl

LIBRARY  = $(BASE)
LIBRARYP = $(YACLLIB)\$(LIBRARY)


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

TARGET = $(LIBRARYP).lib


!ifdef BUILD_DLL
DLL_COMPILE  = /LD -DBUILD_DLL -DDLL
DLL_LINK     = /DLL
TARGET       = $(LIBRARYP).dll
!endif


.SUFFIXES:
.SUFFIXES: .cxx .obj


.cxx.obj:
    $(CC) $(DEBUG) $(CCOPTS) $(DLL_COMPILE) $<


	
all:  $(TARGET) $(MEMORY) $(STATIC_OBJS)



$(LIBRARYP).lib: $(OBJECTS) $(STATIC_OBJS)
    $(LIBR) /out:$(TARGET) $(OBJECTS) $(STATIC_OBJS)
    -$(DELETE) $(LIBRARYP).bak


$(LIBRARYP).dll: $(OBJECTS) $(STATIC_OBJS)
    $(LIBR) /out:$(LIBRARYP).lib /def:$(LIBRARY).def $(OBJECTS) $(STATIC_OBJS)
    $(LINK) /out:$(TARGET) /dll /implib:$(LIBRARYP).lib $(LIBRARYP).exp $(OBJECTS)
    

$(MEMORY): memory.obj
	$(LIBR) /out:$(YACLLIB)\$(MEMORY).lib memory.obj
	-$(DELETE) $(YACLLIB)\$(MEMORY).bak

memory.obj: memory.cxx
	$(CC) $(CCOPTS) memory.cxx

	
# ------------------ Other targets ---------------------------




clean:
    -del *.obj
    -del $(LIBRARYP).lib
    -del $(LIBRARYP).dll
    -del $(LIBRARYP).bak
    -del $(YACLLIB)\$(MEMORY).lib
    -del $(YACLLIB)\$(MEMORY).bak






