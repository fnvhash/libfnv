if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/fnv.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/fnv.sym
endif

lib_LTLIBRARIES = libfnv.la
libfnv_la_SOURCES = fnv.c
libfnv_la_CPPFLAGS = -I$(top_srcdir)/include -Wall
libfnv_la_LDFLAGS = $(VERSION_LDFLAGS)
include_HEADERS =   include/fnv.h

if HAVE_USABLE_ASM
libfnv_la_SOURCES += fnv64boost.s fnv64cboost.c
libfnv_la_CPPFLAGS += -DBOOSTED_ASM=1
else
libfnv_la_SOURCES += fnv64basic.c
libfnv_la_CPPFLAGS += -DBOOSTED_ASM=0
endif

pubincludedir = $(includedir)/fnv
pubinclude_HEADERS =                                    \
                       include/fnv/fnvtop.h             \
                       include/fnv/libfnv.h

EXTRA_DIST = fnv64boost.s fnv64cboost.c fnv64basic.c \
             asmtest/fastfnv64a.s asmtest/testasm.c
