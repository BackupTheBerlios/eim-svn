noinst_LTLIBRARIES = libcore.la

pkgincludeinputdir = $(pkgincludedir)/core
pkgincludeinput_HEADERS= \
	eim.h            \
	account_properties.h

libcore_la_SOURCES =      \
	eim.c             \
	account_properties.c

libcore_la_CFLAGS = \
	-I$(top_srcdir)/src                 \
	$(ecore_cflags)                     \
	$(IDN_CFLAGS) $(EXPAT_INCLUDE) 

libcore_la_LIBADD = \
	$(ecore_libs)                         \
	$(IDN_LIBS)                           \
	$(EXPAT_LIB)
