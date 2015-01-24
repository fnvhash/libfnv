if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/fnv.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/fnv.sym
endif

lib_LTLIBRARIES = libfnv.la
libfnv_la_SOURCES = fnv.c arith128.c fnv128mp.c arith256.c fnv256mp.c arith512.c arith1024.c fnv512mp.c fnv1024mp.c mgmp.c
libfnv_la_CPPFLAGS = -I$(top_srcdir)/include
libfnv_la_LDFLAGS = $(VERSION_LDFLAGS)

include_HEADERS =   include/fnv.h

pubincludedir = $(includedir)/fnv
pubinclude_HEADERS =                                    \
                       include/fnv/fnvtop.h             \
                       include/fnv/libfnv.h

EXTRA_DIST = arith128.h arith256.h arith512.h arith1024.h mgmp.h ifnv.h
