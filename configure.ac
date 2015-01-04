AC_PREREQ([2.69])
AC_INIT([libfnv], [0.8.1], [fnvhash@fnvhash.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_LIBOBJ_DIR([portable])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE()
LT_INIT()
LT_PREREQ([2.2])
AM_PROG_AS()
AC_PROG_CC()
AC_CONFIG_SRCDIR([tools/fnv64.c])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
RRA_LD_VERSION_SCRIPT
AC_CONFIG_FILES([Makefile
                 libfnv/Makefile
                 libfnvutil/Makefile
                 tools/Makefile
                 test/Makefile
                 test/unit/Makefile
                ])

AC_PATH_PROG([HAVE_CHECKMK_PATH], [checkmk], [notfound])

HAVE_USABLE_ASM=no
if $CC libfnv/asmtest/fastfnv64a.s libfnv/asmtest/testasm.c ; then
  if ./a.out ; then
    HAVE_USABLE_ASM=yes
    rm -f a.out
  fi
fi

AM_CONDITIONAL([HAVE_USABLE_ASM], [ test "x$HAVE_USABLE_ASM" = "xyes" ])

AM_CONDITIONAL([HAVE_CHECKMK], [ test ! "x$HAVE_CHECKMK_PATH" = "xnotfound" ])

if test "x$HAVE_CHECKMK_PATH" = "xnotfound" ; then
  AC_WARN([checkmk not found please install "check" package for unit tests])
else
  CHECK_CFLAGS=$(pkg-config check --cflags)
  CHECK_LIBS=$(pkg-config check --libs)
fi

AC_SUBST([CHECK_CFLAGS])
AC_SUBST([CHECK_LIBS])

AC_OUTPUT
