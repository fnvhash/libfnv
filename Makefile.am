ACLOCAL_AMFLAGS = -I m4
SUBDIRS = libfnv libfnvutil tools test

EXTRA_DIST = lib/fnv.map lib/fnv.sym lib/fnvutil.map lib/fnvutil.sym \
             lib/libfnv.pc.in

dist_man_MANS = man/fnv32sum.1 man/fnv64sum.1 man/fnv128sum.1 man/fnv256sum.1 \
                man/fnv512sum.1 man/fnv1024sum.1

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = lib/libfnv.pc

lib/libfnv.pc: $(srcdir)/lib/libfnv.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
			-e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
			-e 's![@]includedir[@]!$(includedir)!g' \
			-e 's![@]libdir[@]!$(libdir)!g' \
			-e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
			-e 's![@]FNV1_LDFLAGS[@]!$(FNV1_LDFLAGS)!g' \
			-e 's![@]FNV1_LIBS[@]!$(FNV1_LIBS)!g' \
			$(srcdir)/lib/libfnv.pc.in > $@

