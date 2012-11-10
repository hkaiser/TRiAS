
include ../control/cfr_sgi.ctl


LIBRARY    = $(YACLLIB)/lib$(BASE).a
LIBRARY_SO = $(YACLLIB)/lib$(BASE).so
MEMLIB     = $(YACLLIB)/lib$(MEMORY).a


OBJECTS =    \
bitset.o   \
bytarray.o \
bytestrm.o \
bytstrng.o \
clntset.o  \
date.o     \
error.o    \
genseq.o   \
gbtree.o   \
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


# STATIC_OBJS = statbase.o



.SUFFIXES:
.SUFFIXES: .cxx .o

#
# For now, I don't build shared objects

all: $(LIBRARY) $(MEMLIB) 




$(LIBRARY): $(OBJECTS) $(STATIC_OBJS) 
	ar r $(LIBRARY) $(OBJECTS) $(STATIC_OBJS)
	$(RANLIB) $(LIBRARY)


$(LIBRARY_SO): $(OBJECTS)
	ld -shared -o $(YACLLIB)/lib$(BASE).so $(OBJECTS)


$(MEMLIB): memory.o
	ar r $(MEMLIB) memory.o
	$(RANLIB) $(MEMLIB)

        
memory.o: memory.cxx
	$(CC) $(CCOPTS) $(OPTIMIZE) $*.cxx
        
# $(STATIC_OBJS): statbase.cxx



.SUFFIXES:

.SUFFIXES: .cxx .o .a


.cxx.o:
	$(CC) -ptall -ptv $(CCOPTS) $(OPTIMIZE)  $*.cxx
        


clean:
	-rm -f *.o  $(LIBRARY) $(MEMLIB)
