SUBDIRS=unit

EXTRA_DIST=compile-test

bin_PROGRAMS=arithtest

arithtest_SOURCES=arithtest.c
arithtest_CPPFLAGS=-I../libfnv/include -I../libfnv -Wall @CHECK_CFLAGS@ -I../libfnvutil -g
arithtest_LDADD =../libfnv/libfnv.la ../libfnvutil/libfnvutil.la @CHECK_LIBS@

