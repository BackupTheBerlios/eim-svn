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
	xmpp.h           \
	xmpp_jid.h       \
	xmpp_message.h   \
	xmpp_auth.h      \
	sha1.h           \
	xmpp_presence.h

libxmpp_la_SOURCES = \
	xmpp_opcode.c    \
	xmpp_callback.c  \
	xmpp.c           \
	xmpp_jid.c       \
	xmpp_message.c   \
	xmpp_auth.c      \
	sha1.c           \
	xmpp_presence.c

libxmpp_la_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) $(EXPAT_INCLUDE) -I$(top_srcdir)/src
