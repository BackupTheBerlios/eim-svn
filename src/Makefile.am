SUBDIRS= \
	egxp    \
	xmpp	\
	xmpp-im \
	gui


bin_PROGRAMS = eim

eim_SOURCES = \
	eim.c

eim_CFLAGS = \
	-I$(top_srcdir)/src           \
	$(ewl_cflags)                 \
	$(ecore_cflags) $(IDN_CFLAGS)


eim_LDADD = \
	-Legxp/ -legxp        \
	-Lxmpp/ -lxmpp        \
	-Lxmpp-im/ -lxmppim   \
	-Lgui/ -lgui

