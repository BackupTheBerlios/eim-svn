noinst_PROGRAMS = test

test_SOURCES = \
	test.c
test_LDADD = \
	-L$(top_srcdir)/src/egxp -legxp \
	-L$(top_srcdir)/src/xmpp -lxmpp \
	-lxmppim

test_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) -I$(top_srcdir)/src


noinst_LTLIBRARIES = libxmppim.la

pkgincludeinputdir = $(pkgincludedir)/xmppim
pkgincludeinput_HEADERS= \
	xmpp_im_contact.h   \
	xmpp_im_roster.h    \
	xmpp_im_struct.h    \
	xmpp_im.h

libxmppim_la_SOURCES = \
	xmpp_im_contact.c  \
	xmpp_im_roster.c   \
	xmpp_im.c

libxmppim_la_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) $(EXPAT_INCLUDE) -I$(top_srcdir)/src
