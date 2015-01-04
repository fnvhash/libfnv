if HAVE_LD_VERSION_SCRIPT
    VERSION_LDFLAGS = -Wl,--version-script=$(top_srcdir)/lib/fnvutil.map
else
    VERSION_LDFLAGS = -export-symbols $(top_srcdir)/lib/fnvutil.sym
endif

lib_LTLIBRARIES = libfnvutil.la
libfnvutil_la_SOURCES = fnvutil.c

libfnvutil_la_CPPFLAGS = -I$(top_srcdir)/libfnv/include -Wall
libfnvutil_la_LDFLAGS = $(VERSION_LDFLAGS)

EXTRA_DIST = fnvutil.h
