dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
AC_INIT(configure.ac)
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE(eim, 0.0.1)
AM_CONFIG_HEADER(src/config.h)

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_C_CONST
AM_ENABLE_SHARED
AM_PROG_LIBTOOL
AC_FUNC_ALLOCA


dnl AC_EXPAND_DIR(PACKAGE_DATA_DIR, "$datadir/${PACKAGE}")
dnl AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "$PACKAGE_DATA_DIR")

dnl if test "x${prefix}" = "xNONE"; then
dnl 	AC_DEFINE_UNQUOTED(PREFIX, "/usr/local/")
dnl else
dnl 	AC_DEFINE_UNQUOTED(PREFIX, "${prefix}")
dnl fi

dnl AC_EXPAND_DIR(PACKAGE_CFG_DIR, "$sysconfdir")
dnl AC_DEFINE_UNQUOTED(PACKAGE_CFG_DIR, "$PACKAGE_CFG_DIR")

dnl Set PACKAGE_SOURCE_DIR in config.h.
dnl packagesrcdir=`cd $srcdir && pwd`
dnl AC_DEFINE_UNQUOTED(PACKAGE_SOURCE_DIR, "${packagesrcdir}")



# PKG_CHECK_MODULES(IDN, libidn >= 0.4.1)



dnl Check for ecore
AC_ARG_WITH(ecore-config, [  --with-ecore-config=ECORE_CONFIG  use ecore-config specified ],
[ ECORE_CONFIG=$withval;
  echo "using "$ECORE_CONFIG" for ecore-config"; ],
[ if test -z "$ECORE_CONFIG"; then
    AC_PATH_PROG(ECORE_CONFIG, "ecore-config", "", $PATH)
  fi
])
ecore_libs=`ecore-config --libs`
ecore_cflags=`ecore-config --cflags`
AC_SUBST(ecore_libs)
AC_SUBST(ecore_cflags)

dnl Check for edje
AC_PATH_GENERIC(edje, 0.5.0, [
  AC_SUBST(edje_libs)
	AC_SUBST(edje_cflags) ],
	AC_MSG_ERROR(Cannot find edje: Is edje-config in path?))
edje_libs=`edje-config --libs`
edje_cflags=`edje-config --cflags`
AC_SUBST(edje_libs)
AC_SUBST(edje_cflags)

dnl Check for esmart
AC_PATH_GENERIC(esmart, 0.9.0, [
  AC_SUBST(esmart_libs)
	AC_SUBST(esmart_cflags) ],
	AC_MSG_ERROR(Cannot find esmart: Is esmart-config in path?))
esmart_libs=`esmart-config --libs`
esmart_cflags=`esmart-config --cflags`
AC_SUBST(esmart_libs)
AC_SUBST(esmart_cflags)


dnl Check for evas
AC_PATH_GENERIC(evas, 0.9.0, [
  AC_SUBST(evas_libs)
	AC_SUBST(evas_cflags) ],
	AC_MSG_ERROR(Cannot find evas: Is evas-config in path?))
evas_libs=`evas-config --libs`
evas_cflags=`evas-config --cflags`
AC_SUBST(evas_libs)
AC_SUBST(evas_cflags)

dnl Check for expat
EXPAT_INCLUDE=""
EXPAT_LIB="-lexpat"
EXPAT_SUBDIR=""
LIBEXPAT="-lexpat"

have_expat_lib=no
have_expat_include=no

AC_CHECK_HEADER(expat.h, [have_expat_include=yes])

if test x$have_expat_include = xno; then
    AC_MSG_ERROR(
    [*** Unable to find expat header file! (http://expat.sourceforge.net)]
    [Please install the library and header files if you want to link to the shared library.]
    )
fi

AC_CHECK_LIB(expat, XML_ParserCreate, have_expat_lib=yes)

if test x$have_expat_lib = xno; then
   AC_MSG_ERROR(
    [*** Unable to find expat xml library! (http://expat.sourceforge.net)]
    [Please install the library and header files if you want to link to the shared library.]
    )
fi

AC_SUBST(EXPAT_INCLUDE)
AC_SUBST(EXPAT_LIB)
AC_SUBST(EXPAT_SUBDIR)
AC_SUBST(LIBEXPAT)


AC_OUTPUT([
Makefile
src/Makefile
src/egxp/Makefile
src/xmpp/Makefile
src/xmpp-im/Makefile
src/gui/Makefile
doc/Makefile
])
