SUBDIRS= \
	egxp    \
	xmpp	\
	xmpp-im \
	gui


bin_PROGRAMS = eim

eim_SOURCES = \
	eim.c

eim_CFLAGS = \
	$(ecore_cflags) $(IDN_CFLAGS) \
	-I$(top_srcdir)/src

eim_LDADD = \
	-Legxp/ -legxp        \
	-Lxmpp/ -lxmpp        \
	-Lxmpp-im/ -lxmppim   \
	-Lgui/ -lgui

