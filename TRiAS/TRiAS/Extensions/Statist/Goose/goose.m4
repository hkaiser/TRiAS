# m4 file for the Goose statistical library
# Ripped off of glib's glib.m4 by Owen Taylor

dnl AM_PATH_GOOSE([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for GOOSE, and define GOOSE_CFLAGS and GOOSE_LIBS
dnl If any sub-libraries are specified in modules, pass them to goose-config
dnl
AC_DEFUN(AM_PATH_GOOSE,
[dnl 
dnl Get the cflags and libraries from the glib-config script
dnl
AC_ARG_WITH(goose-prefix,[  --with-goose-prefix=PFX   Prefix where GOOSE is installed (optional)],
            goose_config_prefix="$withval", goose_config_prefix="")
AC_ARG_WITH(goose-exec-prefix,[  --with-goose-exec-prefix=PFX Exec prefix where GOOSE is installed (optional)],
            goose_config_exec_prefix="$withval", goose_config_exec_prefix="")
AC_ARG_ENABLE(goosetest, [  --disable-goosetest       Do not try to compile and run a test GOOSE program],
		    , enable_goosetest=yes)

  if test x$goose_config_exec_prefix != x ; then
     goose_config_args="$goose_config_args --exec-prefix=$goose_config_exec_prefix"
     if test x${GOOSE_CONFIG+set} != xset ; then
        GOOSE_CONFIG=$goose_config_exec_prefix/bin/goose-config
     fi
  fi
  if test x$goose_config_prefix != x ; then
     goose_config_args="$goose_config_args --prefix=$goose_config_prefix"
     if test x${GOOSE_CONFIG+set} != xset ; then
        GOOSE_CONFIG=$goose_config_prefix/bin/goose-config
     fi
  fi

  for module in . $4
  do
      case "$module" in
         scm) 
             goose_config_args="$goose_config_args scm"
         ;;
      esac
  done

  AC_PATH_PROG(GOOSE_CONFIG, goose-config, no)
  min_goose_version=ifelse([$1], ,0.0.5,$1)
  AC_MSG_CHECKING(for GOOSE - version >= $min_goose_version)
  no_goose=""
  if test "$GOOSE_CONFIG" = "no" ; then
    no_goose=yes
  else
    GOOSE_CFLAGS=`$GOOSE_CONFIG $goose_config_args --cflags`
    GOOSE_LIBS=`$GOOSE_CONFIG $goose_config_args --libs`
    goose_config_major_version=`$GOOSE_CONFIG $goose_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    goose_config_minor_version=`$GOOSE_CONFIG $goose_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    goose_config_micro_version=`$GOOSE_CONFIG $goose_config_args --version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_goosetest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $GOOSE_CFLAGS"
      LIBS="$GOOSE_LIBS $LIBS"
dnl
dnl Now check if the installed GOOSE is sufficiently new. (Also sanity
dnl checks the results of goose-config to some extent
dnl
      rm -f conf.goosetest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>

char* check_goose_version(int major, int minor, int micro);

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;
  char *check;

  system ("touch conf.goosetest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = malloc(sizeof(char)*1024);
  strcpy(tmp_version, "$min_goose_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_goose_version");
     exit(1);
   }

  check = check_goose_version(major, minor, micro);

  if (check == 0) return 0;
  else {
   printf(check);
   return 1;
  }
}
],, no_goose=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_goose" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$GOOSE_CONFIG" = "no" ; then
       echo "*** The goose-config script installed by GOOSE could not be found"
       echo "*** If GOOSE was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the GOOSE_CONFIG environment variable to the"
       echo "*** full path to goose-config."
     else
       if test -f conf.goosetest ; then
        :
       else
          echo "*** Could not run GOOSE test program, checking why..."
          CFLAGS="$CFLAGS $GOOSE_CFLAGS"
          LIBS="$LIBS $GOOSE_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
],      [ return check_goose_version(0,0,5) != 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding GOOSE or finding the wrong"
          echo "*** version of GOOSE. If it is not finding GOOSE, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     GOOSE_CFLAGS=""
     GOOSE_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(GOOSE_CFLAGS)
  AC_SUBST(GOOSE_LIBS)
  rm -f conf.goosetest
])
