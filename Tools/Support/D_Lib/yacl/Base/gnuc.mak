

LIBRARY = $(YACLLIB)/lib$(BASE).a
BASE_SO = $(YACLPATH)/lib/$(YACLPLATFORM)/lib$(BASE).so
MEMLIB  = $(YACLLIB)/lib$(MEMORY).a

include $(YACLPATH)/control/gnuc.ctl

LIBRARY_SO = $(BASE_SO)

#
# Comment out the following if you don't want the object code
# optimized:
#
OPTIMIZE = -O3


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

all: $(LIBRARY) $(MEMLIB) $(BUILD_SHARED_BASE)



$(LIBRARY): $(OBJECTS) $(STATIC_OBJS)
	ar r $(LIBRARY) $(OBJECTS) $(STATIC_OBJS)
	$(RANLIB) $(LIBRARY)

build_shared_base: $(OBJECTS) $(STATIC_OBJS)
	rm -rf $(BASE_SO)
	$(BUILD_SO_CMD) -o $(BASE_SO) $(OBJECTS) $(STATIC_OBJS)


$(MEMLIB): memory.o
	ar r $(MEMLIB) memory.o
	$(RANLIB) $(MEMLIB)

        
memory.o: memory.cxx
	$(CC) $(CCOPTS) $(OPTIMIZE) $*.cxx

                
# $(STATIC_OBJS): statbase.cxx
        


.SUFFIXES:

.SUFFIXES: .cxx .o .a


.cxx.o:
	$(CC) $(CCOPTS) $(PIC)  $*.cxx
        


clean:
	-rm -f *.o  $(LIBRARY) $(MEMLIB) $(BASE_SO)
