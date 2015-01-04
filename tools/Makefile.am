bin_PROGRAMS=fnv32sum fnv64sum fnv128sum fnv256sum

bin_SCRIPTS=fnv512sum fnv1024sum

EXTRA_DIST=fnv512sum fnv1024sum

fnv256sum_SOURCES=fnv256sum.c
fnv256sum_CPPFLAGS=-I../libfnv/include -Wall -I../libfnvutil
fnv256sum_LDADD =../libfnv/libfnv.la ../libfnvutil/libfnvutil.la -lm

fnv128sum_SOURCES=fnv128sum.c
fnv128sum_CPPFLAGS=-I../libfnv/include -Wall -I../libfnvutil
fnv128sum_LDADD =../libfnv/libfnv.la ../libfnvutil/libfnvutil.la -lm

fnv64sum_SOURCES=fnv64sum.c
fnv64sum_CPPFLAGS=-I../libfnv/include -Wall -I../libfnvutil
fnv64sum_LDADD =../libfnv/libfnv.la ../libfnvutil/libfnvutil.la -lm

fnv32sum_SOURCES=fnv32sum.c
fnv32sum_CPPFLAGS=-I../libfnv/include -Wall -I../libfnvutil
fnv32sum_LDADD =../libfnv/libfnv.la ../libfnvutil/libfnvutil.la -lm
