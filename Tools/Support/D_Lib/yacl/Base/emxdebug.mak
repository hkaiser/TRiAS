
include ../control/emxdebug.ctl


LIBRARY    = $(YACLLIB)/$(BASE).a
MEMLIB     = $(YACLLIB)/$(MEMORY).a


OBJECTS =    \
bitset.o   \
bytarray.o \
bytestrm.o \
bytstrng.o \
clntset.o  \
date.o     \
error.o    \
gbtree.o   \
genseq.o   \
integer.o  \
intseq.o   \
intset.o   \
map.o      \
object.o   \
objseq.o   \
objset.o   \
regexpr.o  \
segseq.o   \
stream.o   \
strgseq.o  \
strgset.o  \
string.o   \
strsplit.o \
tbtree.o   \
timeofda.o \
tree.o     \
treewalk.o \
version.o






.SUFFIXES:
.SUFFIXES: .cxx .o

all: $(LIBRARY) $(MEMORY) $(STATICLIB)



$(LIBRARY): $(OBJECTS)
	$(AR) r $(LIBRARY) $(OBJECTS)
	-$(AR) d $(LIBRARY) __.SYMDEF
	$(AR) s $(LIBRARY)
	-rm -f $(YACLLIB)/$(BASE).bak

$(MEMORY): memory.o
	$(AR) r $(MEMLIB) memory.o
	-$(AR) d $(LIBRARY) __.SYMDEF
	$(AR) s $(MEMLIB)

        
memory.o: memory.cxx
	$(CC) $(CCOPTS) $*.cxx


.cxx.o:
	$(CC) $(CCOPTS)  $*.cxx

        


clean:
	-rm -f *.o  $(LIBRARY) $(MEMLIB)
