noinst_PROGRAMS = test

test_SOURCES = \
	test.c
test_LDADD = \
	-L$(top_builddir)/src/egxp -legxp \
	-L$(top_builddir)/src/xmpp -lxmpp \
	-lxmppim

test_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) -I$(top_srcdir)/src


noinst_LTLIBRARIES = libxmppim.la

pkgincludeinputdir = $(pkgincludedir)/xmppim
pkgincludeinput_HEADERS = xmpp_im_contact.h 	xmpp_im_roster.h 	xmpp_im_struct.h \
		xmpp_im.h 	xmpp_im_callback.h xmpp_im_opcode.h

libxmppim_la_SOURCES = xmpp_im_contact.c 	xmpp_im_roster.c 	xmpp_im.c \
		xmpp_im_callback.c xmpp_im_opcode.c

libxmppim_la_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) $(EXPAT_INCLUDE) -I$(top_srcdir)/src
noinst_HEADERS = xmpp_im_callback.h
