noinst_LTLIBRARIES = libgui.la

pkgincludeinputdir = $(pkgincludedir)/gui
pkgincludeinput_HEADERS= \
	gui_main.h

libgui_la_SOURCES = \
	gui_main.c

libgui_la_CFLAGS = \
	-I$(top_srcdir)/src                 \
	$(ecore_cflags)                     \
	$(evas_cflags)                      \
	$(esmart_cflags)                    \
	$(IDN_CFLAGS) $(EXPAT_INCLUDE) 

libgui_la_LIBADD = \
	$(ecore_libs)                         \
	$(evas_libs)                          \
	$(esmart_libs)  -lesmart_trans_x11 -lesmart_container   \
	$(IDN_LIBS)                           \
	$(EXPAT_LIB)
