
include ../control/emxos2.ctl


LIBRARY    = $(YACLLIB)/$(BASE).lib
MEMLIB     = $(YACLLIB)/$(MEMORY).lib


OBJECTS =    \
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






.SUFFIXES:
.SUFFIXES: .cxx .obj

all: $(LIBRARY) $(MEMORY) $(STATICLIB)



$(LIBRARY): $(OBJECTS)
	$(OMFAR) r $(LIBRARY) $(OBJECTS)
	-$(OMFAR) d $(LIBRARY) __.SYMDEF
	$(OMFAR) s $(LIBRARY)
	-rm -f $(YACLLIB)/$(BASE).bak

$(MEMORY): memory.obj
	$(OMFAR) r $(MEMLIB) memory.obj
	-$(OMFAR) d $(LIBRARY) __.SYMDEF
	$(OMFAR) s $(MEMLIB)

        
memory.obj: memory.cxx
	$(CC) $(CCOPTS) $*.cxx


.cxx.obj:
	$(CC) $(CCOPTS)  $*.cxx

        


clean:
	-rm -f *.obj  $(LIBRARY) $(MEMLIB)
