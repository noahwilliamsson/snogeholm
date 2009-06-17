# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/slim
pkglibdir = $(libdir)/slim
pkgincludedir = $(includedir)/slim

top_builddir = ..

ACLOCAL = aclocal -I macros
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
CC = gcc
GNOMEGNORBA_LIBS = -Wl,-E -lgnorba -lORBitCosNaming -lORBit -lIIOP -lORBitutil -lXpm -ljpeg -lgnomeui -lart_lgpl -lgdk_imlib -ltiff -lungif -lpng -lz -lSM -lICE -lgtk12 -lgdk12 -lgmodule12 -lxpg4 -lXext -lX11 -lgnome -lgnomesupport -lintl -lesd -laudiofile -lm -lglib12
GNOMEUI_LIBS = -Wl,-E -lXpm -ljpeg -lgnomeui -lart_lgpl -lgdk_imlib -ltiff -lungif -lpng -lz -lSM -lICE -lgtk12 -lgdk12 -lgmodule12 -lxpg4 -lXext -lX11 -lgnome -lgnomesupport -lintl -lesd -laudiofile -lm -lglib12
GNOME_APPLETS_LIBS = 
GNOME_CAPPLET_LIBS = 
GNOME_CONFIG = /usr/X11R6/bin/gnome-config
GNOME_DOCKLETS_LIBS = 
GNOME_INCLUDEDIR = -I/usr/X11R6/include -DNEED_GNOMESUPPORT_H -I/usr/local/include/glib12 -I/usr/local/include -I/usr/X11R6/include/gtk12
GNOME_LIBDIR = -Wl,-E -L/usr/X11R6/lib -L/usr/local/lib
GNOME_LIBS = -lgnome -lgnomesupport -lintl -lesd -laudiofile -lm -lglib12
GNORBA_CFLAGS = -I/usr/X11R6/include -DNEED_GNOMESUPPORT_H -I/usr/local/include/glib12 -I/usr/local/include -I/usr/X11R6/include/gtk12
GNORBA_LIBS = -Wl,-E -L/usr/X11R6/lib -L/usr/local/lib -lgnorba -lORBitCosNaming -lORBit -lIIOP -lORBitutil -lXpm -ljpeg -lgnomeui -lart_lgpl -lgdk_imlib -ltiff -lungif -lpng -lz -lSM -lICE -lgtk12 -lgdk12 -lgmodule12 -lxpg4 -lXext -lX11 -lgnome -lgnomesupport -lintl -lesd -laudiofile -lm -lglib12
GTKXMHTML_LIBS = -Wl,-E -lgtkxmhtml -lXpm -ljpeg -lpng -lz -lSM -lICE -lgtk12 -lgdk12 -lgmodule12 -lglib12 -lintl -lxpg4 -lXext -lX11 -lm
GTK_CFLAGS = -I/usr/X11R6/include/gtk12 -I/usr/local/include/glib12 -I/usr/local/include -I/usr/X11R6/include
GTK_CONFIG = /usr/X11R6/bin/gtk12-config
GTK_LIBS = -lSM -lICE -L/usr/X11R6/lib -L/usr/X11R6/lib -lgtk12 -lgdk12 -L/usr/local/lib -Wl,-E -lgmodule12 -lglib12 -lintl -lxpg4 -lXext -lX11 -lm
MAKEINFO = makeinfo
ORBIT_CFLAGS = -I/usr/local/include/glib12 -I/usr/local/include
ORBIT_CONFIG = /usr/local/bin/orbit-config
ORBIT_IDL = /usr/local/bin/orbit-idl
ORBIT_LIBS = -L/usr/local/lib -lORBitCosNaming -lORBit -lIIOP -lORBitutil -lglib12 -lm
PACKAGE = slim
PTHREAD_LIB = -lc_r
VERSION = 0.1
XPM_LIBS = -lXpm
ZVT_LIBS = -Wl,-E -lzvt -lutil -lSM -lICE -lgtk12 -lgdk12 -lgmodule12 -lglib12 -lintl -lxpg4 -lXext -lX11 -lm
cflags_set = yes
cxxflags_set = @cxxflags_set@

INCLUDES =  	$(GNOME_INCLUDEDIR)


bin_PROGRAMS = slim

slim_SOURCES =  	main.c 	support.c support.h 	interface.c interface.h 	callbacks.c callbacks.h 	adlink.c adlink.h 	elev.c config.c 	program.c program.h 	common.h proto.h vis.c


slim_LDADD = $(GNOME_LIBDIR) $(GNOMEUI_LIBS)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
PROGRAMS =  $(bin_PROGRAMS)


DEFS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I..
CPPFLAGS =  -I/usr/X11R6/include/gtk12 -I/usr/local/include/glib12 -I/usr/local/include -I/usr/X11R6/include
LDFLAGS = 
LIBS = 
slim_OBJECTS =  main.o support.o interface.o callbacks.o adlink.o elev.o \
config.o program.o vis.o
slim_DEPENDENCIES = 
slim_LDFLAGS = 
CFLAGS = -g -O2 -Wall -Wunused -Wmissing-prototypes -Wmissing-declarations 
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
DEP_FILES =  .deps/adlink.P .deps/callbacks.P .deps/config.P \
.deps/elev.P .deps/interface.P .deps/main.P .deps/program.P \
.deps/support.P .deps/vis.P
SOURCES = $(slim_SOURCES)
OBJECTS = $(slim_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu src/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status $(BUILT_SOURCES)
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

slim: $(slim_OBJECTS) $(slim_DEPENDENCIES)
	@rm -f slim
	$(LINK) $(slim_LDFLAGS) $(slim_OBJECTS) $(slim_LDADD) $(LIBS)

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = src

distdir: $(DISTFILES)
	here=`cd $(top_builddir) && pwd`; \
	top_distdir=`cd $(top_distdir) && pwd`; \
	distdir=`cd $(distdir) && pwd`; \
	cd $(top_srcdir) \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here --srcdir-name=$(top_srcdir) --output-dir=$$top_distdir --gnu src/Makefile
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done

DEPS_MAGIC := $(shell mkdir .deps > /dev/null 2>&1 || :)

-include $(DEP_FILES)

mostlyclean-depend:

clean-depend:

distclean-depend:
	-rm -rf .deps

maintainer-clean-depend:

%.o: %.c
	@echo '$(COMPILE) -c $<'; \
	$(COMPILE) -Wp,-MD,.deps/$(*F).pp -c $<
	@-cp .deps/$(*F).pp .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	  | sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	    >> .deps/$(*F).P; \
	rm .deps/$(*F).pp

%.lo: %.c
	@echo '$(LTCOMPILE) -c $<'; \
	$(LTCOMPILE) -Wp,-MD,.deps/$(*F).pp -c $<
	@-sed -e 's/^\([^:]*\)\.o[ 	]*:/\1.lo \1.o :/' \
	  < .deps/$(*F).pp > .deps/$(*F).P; \
	tr ' ' '\012' < .deps/$(*F).pp \
	  | sed -e 's/^\\$$//' -e '/^$$/ d' -e '/:$$/ d' -e 's/$$/ :/' \
	    >> .deps/$(*F).P; \
	rm -f .deps/$(*F).pp
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-compile \
		mostlyclean-tags mostlyclean-depend mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-compile clean-tags clean-depend \
		clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-compile distclean-tags \
		distclean-depend distclean-generic clean-am

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-depend maintainer-clean-generic \
		distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir mostlyclean-depend \
distclean-depend clean-depend maintainer-clean-depend info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
