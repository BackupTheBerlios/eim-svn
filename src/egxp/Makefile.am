noinst_PROGRAMS= test

test_SOURCES = \
	test.c
test_LDADD = libegxp.la
test_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS)

lib_LTLIBRARIES = libegxp.la

pkgincludeinputdir = $(pkgincludedir)/egxp

pkgincludeinput_HEADERS= \
	egxp_condition.h     \
	egxp_message.h       \
	egxp_node_struct.h   \
	egxp_node.h          \
	egxp_opcode.h        \
	egxp.h               \
	egxp_protocol_handler.h


libegxp_la_SOURCES = \
	egxp_condition.c    \
	egxp_message.c      \
	egxp_node.c         \
	egxp_opcode.c       \
	egxp.c              \
	egxp_protocol_handler.c

libegxp_la_LIBADD = $(ecore_libs) $(IDN_LIBS) $(EXPAT_LIB)
libegxp_la_CFLAGS = $(ecore_cflags) $(IDN_CFLAGS) $(EXPAT_INCLUDE)
