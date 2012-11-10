# -*- makefile -*-
# Makefile for Generic Unix with GCC compiler

FAULT_TOLERANT=0

# Place where to copy GastDB header files
INCSPATH=/usr/local/include/fastdb

#Place where to copy Fastdb library
LIBSPATH=/usr/local/lib

#Place where to copy Fastdb subsql utility
BINSPATH=/usr/local/bin

OBJS = class.o compiler.o database.o hashtab.o file.o symtab.o ttree.o \
	cursor.o query.o wwwapi.o unisock.o sync.o localcli.o

CLI_OBJS = cli.o unisock.o 

INCS = fastdb.h stdtp.h class.h database.h cursor.h reference.h wwwapi.h \
	array.h file.h hashtab.h ttree.h sync.h query.h datetime.h 

#
# threads settings - please comment this lines for single-threaded libs
#
ifdef NO_PTHREADS
TFLAGS=-DNO_PTHREADS
THRLIBS=
SUFF=
else
ifneq (,$(findstring freebsd,$(OSTYPE)))
TFLAGS=-pthread
THRLIBS=
else 
TFLAGS=-D_REENTRANT -D_THREAD_SAFE
THRLIBS=-lpthread
endif
SUFF=_r
endif

STDLIBS =  -lm  $(THRLIBS)
ifneq (,$(findstring solaris,$(OSTYPE)))
SOCKLIBS = -lnsl -lsocket
TFLAGS += -fPIC
else
SOCKLIBS =
endif

VERSION=2
FASTDB_LIB = libfastdb$(SUFF).a 
FASTDB_SHARED = libfastdb$(SUFF).so.${VERSION}
CLI_LIB = libcli$(SUFF).a
CLI_SHARED = libcli$(SUFF).so.${VERSION}

EXES = subsql forcerecovery
#FASTDB_LIBS=-L. -lfastdb$(SUFF)
#CLI_LIBS=-L. -lcli$(SUFF)
FASTDB_LIBS=$(FASTDB_LIB)
CLI_LIBS=$(CLI_LIB)

EXAMPLES = guess testdb testleak testjoin testddl testperf testsync testiref testtrav testidx clitest testraw localclitest

WEB_EXAMPLES = cgistub bugdb clidb

CC = g++

# Possible FastDB compile time parameters (-Dxxx should be added to DEFS macro):
# 1. USE_LOCALE_SETTING - use C locale for string comparison operations
# 2. DEBUG - debug level
#    - DEBUG_NODE - disable any checking and tracing (except asserts)
#    - DEBUG_CHECK - disable trace message
#    - DEBUG_TRACE - enable trace messages 
# 3. SECURE_SERVER - enable authentication for remote logins: keep user/password table, 
#                    check password for remote logins
# 4. USE_QUEUE_MANAGER - use queue manager for internal HTTP server. This manager will manage pool
#    of threads assigned for client connections. Otherwise all requests will be executed sequnetially
#    in the main loop.
# 5. FASTDB_DLL - create gigabase.dll
# 6. THROW_EXCEPTION_ON_ERROR - throw C++ exception in case of database error 
#    instead of abort(). Do not forgot to specify -GX option if using exceptions.
# 7. IGNORE_CASE - perform all string comparisons as case insensitive
# 8. USE_STD_STRING - support of std:;string type for class fields
# 9. AUTOINCREMENT_SUPPORT support autoincrement fields (database built with this flag will be 
#    incompatible with database built without it)
# 10. CLONE_INDENTIFIERS - do not storef addresses of string constants in symbol table.
#     This option is needed if DLL library using GigaBASE can be unloaded.
# 11. DISKLESS_CONFIGURATION - only in-memory temporary database
#
# 12. USE_POSIX_API use POSIX sem_* sempahores and mmap 
#     instead of SysV semaphores and shared memory
# 13. USE_SYSV_SHARED_MEMORY - use SysV IPC shmem instead of mmap. 
# 14. INT8_IS_DEFINED - int8 type is defined at your system, in this case you should use db_int8 type instead
# 15. REPLICATION_SUPPORT - fault tolerant version of FastDB
#

#DEFS =-DTHROW_EXCEPTION_ON_ERROR -DUSE_QUEUE_MANAGER
#DEFS = -DUSE_QUEUE_MANAGER -DUSE_LOCALE_SETTINGS -DUSE_SYSV_SHARED_MEMORY
DEFS = -DUSE_QUEUE_MANAGER -DUSE_LOCALE_SETTINGS

#CFLAGS = $(TFLAGS) -c -Wall -O5 -g $(DEFS) 
CFLAGS = -c -Wall -O0 -g $(DEFS) $(TFLAGS)
#CFLAGS = -c -Wall -O0 -DDEBUG=DEBUG_TRACE -g $(DEFS) $(TFLAGS)
SHFLAGS=-shared


LD = $(CC)
LDFLAGS = -g $(TFLAGS)

AR = ar
ARFLAGS = -cru

ifneq (,$(findstring freebsd,$(OSTYPE)))
RANLIB = ranlib
else
RANLIB = true
endif

ifneq (0,$(FAULT_TOLERANT))
STDLIBS +=  $(SOCKLIBS)
DEFS += -DREPLICATION_SUPPORT
endif


all: static shared bins

static: $(FASTDB_LIB) $(CLI_LIB) 

shared: $(FASTDB_SHARED) $(CLI_SHARED) 

bins: $(EXES) $(EXAMPLES) 

www: $(FASTDB_SHARED) $(WEB_EXAMPLES)


class.o: class.cpp compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) class.cpp

compiler.o: compiler.cpp compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) compiler.cpp

query.o: query.cpp compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) query.cpp

database.o: database.cpp compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) database.cpp

localcli.o: localcli.cpp compiler.h compiler.d symtab.h localcli.h $(INCS)
	$(CC) $(CFLAGS) localcli.cpp

cursor.o: cursor.cpp compiler.h compiler.d $(INCS)
	$(CC) $(CFLAGS) cursor.cpp

hashtab.o: hashtab.cpp $(INCS)
	$(CC) $(CFLAGS) hashtab.cpp

file.o: file.cpp $(INCS)
	$(CC) $(CFLAGS) file.cpp

sync.o: sync.cpp $(INCS)
	$(CC) $(CFLAGS) sync.cpp

symtab.o: symtab.cpp symtab.h $(INCS)
	$(CC) $(CFLAGS) symtab.cpp

ttree.o: ttree.cpp $(INCS)
	$(CC) $(CFLAGS) ttree.cpp

wwwapi.o: wwwapi.cpp wwwapi.h sockio.h stdtp.h
	$(CC) $(CFLAGS) wwwapi.cpp

unisock.o: unisock.cpp unisock.h sockio.h stdtp.h
	$(CC) $(CFLAGS) unisock.cpp

cli.o: cli.cpp cli.h cliproto.h
	$(CC) $(CFLAGS) cli.cpp

$(FASTDB_LIB): $(OBJS)
	rm -f $(FASTDB_LIB)
	$(AR) $(ARFLAGS) $(FASTDB_LIB) $(OBJS)
	$(RANLIB) $(FASTDB_LIB)

$(FASTDB_SHARED): $(OBJS)
	rm -f $(FASTDB_SHARED)
	$(CC) $(SHFLAGS) -o $(FASTDB_SHARED) $(OBJS)
	ln -f -s $(FASTDB_SHARED) libfastdb$(SUFF).so

$(CLI_LIB): $(CLI_OBJS)
	rm -f $(CLI_LIB)
	$(AR) $(ARFLAGS) $(CLI_LIB) $(CLI_OBJS)
	$(RANLIB) $(CLI_LIB)

$(CLI_SHARED): $(CLI_OBJS)
	rm -f $(CLI_SHARED)
	$(CC) $(SHFLAGS) -o  $(CLI_SHARED) $(CLI_OBJS)
	ln -f -s $(CLI_SHARED) libcli$(SUFF).so


clitest.o: clitest.c cli.h
	$(CC) $(CFLAGS) clitest.c

clitest: clitest.o $(CLI_LIB)
	$(LD) $(LDFLAGS) -o clitest clitest.o $(CLI_LIBS) $(STDLIBS) $(SOCKLIBS)

localclitest: clitest.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o localclitest clitest.o $(FASTDB_LIB) $(STDLIBS)

subsql.o: subsql.cpp subsql.h compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) subsql.cpp

ifdef NO_PTHREADS
subsql: subsql.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o subsql subsql.o $(FASTDB_LIBS) $(STDLIBS) $(SOCKLIBS)
else
server.o: server.cpp server.h cli.h cliproto.h subsql.h compiler.h compiler.d symtab.h $(INCS)
	$(CC) $(CFLAGS) server.cpp

subsql: subsql.o server.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o subsql subsql.o server.o $(FASTDB_LIBS) $(STDLIBS) $(SOCKLIBS)
endif

bugdb.o: bugdb.cpp bugdb.h $(INCS)
	$(CC) $(CFLAGS) bugdb.cpp

bugdb: bugdb.o  $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o bugdb bugdb.o $(FASTDB_LIBS) $(STDLIBS) $(SOCKLIBS)

clidb.o: clidb.cpp clidb.h $(INCS)
	$(CC) $(CFLAGS) clidb.cpp

clidb: clidb.o  $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o clidb clidb.o $(FASTDB_LIBS) $(STDLIBS) $(SOCKLIBS)

cgistub.o: cgistub.cpp stdtp.h sockio.h
	$(CC) $(CFLAGS) cgistub.cpp 

cgistub: cgistub.o
	$(LD) $(LDFLAGS) -o cgistub cgistub.o $(FASTDB_LIBS) $(STDLIBS) $(SOCKLIBS)


forcerecovery.o: forcerecovery.cpp database.h
	$(CC) $(CFLAGS) forcerecovery.cpp 

forcerecovery: forcerecovery.o
	$(LD) $(LDFLAGS)  -o forcerecovery forcerecovery.o


guess.o: guess.cpp $(INCS)
	$(CC) $(CFLAGS) guess.cpp 

guess: guess.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o guess guess.o $(FASTDB_LIBS) $(STDLIBS)

testdb.o: testdb.cpp $(INCS)
	$(CC) $(CFLAGS) testdb.cpp 

testdb: testdb.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testdb testdb.o $(FASTDB_LIBS) $(STDLIBS)

testraw.o: testraw.cpp $(INCS)
	$(CC) $(CFLAGS) testraw.cpp 

testraw: testraw.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testraw testraw.o $(FASTDB_LIBS) $(STDLIBS)

testleak.o: testleak.cpp $(INCS)
	$(CC) $(CFLAGS) testleak.cpp 

testleak: testleak.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testleak testleak.o $(FASTDB_LIBS) $(STDLIBS)

testjoin.o: testjoin.cpp $(INCS)
	$(CC) $(CFLAGS) testjoin.cpp 

testjoin: testjoin.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testjoin testjoin.o $(FASTDB_LIBS) $(STDLIBS)

testddl.o: testddl.cpp $(INCS)
	$(CC) $(CFLAGS) testddl.cpp 

testddl: testddl.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testddl testddl.o $(FASTDB_LIBS) $(STDLIBS)

testperf.o: testperf.cpp $(INCS)
	$(CC) $(CFLAGS) testperf.cpp 

testperf: testperf.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testperf testperf.o $(FASTDB_LIBS) $(STDLIBS)

testidx.o: testidx.cpp $(INCS)
	$(CC) $(CFLAGS) testidx.cpp 

testidx: testidx.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testidx testidx.o $(FASTDB_LIBS) $(STDLIBS)

testsync.o: testsync.cpp $(INCS)
	$(CC) $(CFLAGS) testsync.cpp 

testsync: testsync.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testsync testsync.o $(FASTDB_LIBS) $(STDLIBS)

testiref.o: testiref.cpp $(INCS)
	$(CC) $(CFLAGS) testiref.cpp 

testiref: testiref.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testiref testiref.o $(FASTDB_LIBS) $(STDLIBS)

testtrav.o: testtrav.cpp $(INCS)
	$(CC) $(CFLAGS) testtrav.cpp 

testtrav: testtrav.o $(FASTDB_LIB)
	$(LD) $(LDFLAGS) -o testtrav testtrav.o $(FASTDB_LIBS) $(STDLIBS)



install: subsql installlib
	mkdir -p $(BINSPATH)
	cp subsql $(BINSPATH)
	strip $(BINSPATH)/subsql

installlib: $(FASTDB_LIB) $(CLI_LIB) $(FASTDB_SHARED) $(CLI_SHARED)
	mkdir -p $(INCSPATH)
	cp $(INCS) $(INCSPATH)
	mkdir -p $(LIBSPATH)
	cp $(FASTDB_LIB) $(CLI_LIB) $(FASTDB_SHARED) $(CLI_SHARED) $(LIBSPATH)
	cp -P libcli.so $(LIBSPATH)
	ln -f -s $(LIBSPATH)/$(FASTDB_SHARED) $(LIBSPATH)/libfastdb$(SUFF).so
	ln -f -s $(LIBSPATH)/$(CLI_SHARED) $(LIBSPATH)/libcli$(SUFF).so
	mkdir -p $(BINSPATH)
	cp subsql $(BINSPATH)



cleanobj:
	rm -fr *.o *.tgz core *~ cxx_repository

cleandbs:
	rm -f *.fdb


clean: cleanobj cleandbs
	rm -f *.a *.so *.so.* $(EXAMPLES) $(WEB_EXAMPLES) $(EXES)

tgz:	clean
	cd ..; tar cvzf fastdb.tgz fastdb

copytgz: tgz
	mcopy -o ../fastdb.tgz a:
