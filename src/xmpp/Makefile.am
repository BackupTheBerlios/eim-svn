noinst_PROGRAMS = test

test_SOURCES = \
	test.c
test_LDADD = \
	-L$(top_srcdir)/src/egxp -legxp \
	-lxmpp
test_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) -I$(top_srcdir)/src


noinst_LTLIBRARIES = libxmpp.la

pkgincludeinputdir = $(pkgincludedir)/xmpp
pkgincludeinput_HEADERS= \
	xmpp_opcode.h    \
	xmpp_callback.h  \
	xmpp_struct.h    \
	xmpp.h

libxmpp_la_SOURCES = \
	xmpp_opcode.c    \
	xmpp_callback.c  \
	xmpp.c

libxmpp_la_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) $(EXPAT_INCLUDE) -I$(top_srcdir)/src
