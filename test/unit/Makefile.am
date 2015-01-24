
if HAVE_CHECKMK

bin_PROGRAMS=fnvtest fnvutiltest benchmark

fnvtest_SOURCES=basic_full.c
fnvtest_CPPFLAGS=-I../../libfnv/include -I../../libfnv -Wall @CHECK_CFLAGS@ -I../../libfnvutil -g
fnvtest_LDADD =../../libfnv/libfnv.la ../../libfnvutil/libfnvutil.la @CHECK_LIBS@

benchmark_SOURCES=benchmark.c
benchmark_CPPFLAGS=-I../../libfnv/include -Wall @CHECK_CFLAGS@ -I../../libfnvutil -g
benchmark_LDADD =../../libfnv/libfnv.la ../../libfnvutil/libfnvutil.la @CHECK_LIBS@

fnvutiltest_SOURCES=basic_fnvutil.c
fnvutiltest_CPPFLAGS=-I../../libfnv/include -Wall @CHECK_CFLAGS@ -I../../libfnvutil -g
fnvutiltest_LDADD =../../libfnv/libfnv.la ../../libfnvutil/libfnvutil.la @CHECK_LIBS@

.ts.c:
	checkmk $< >$@

endif

EXTRA_DIST=basic_full.ts \
  basic_fnvutil.ts
