## Process this file with automake to produce Makefile.in

INCLUDES = \
	$(GNOME_INCLUDEDIR)

bin_PROGRAMS = slim

slim_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	adlink.c adlink.h \
	elev.c config.c \
	program.c program.h \
	common.h proto.h vis.c

slim_LDADD = $(GNOME_LIBDIR) $(GNOMEUI_LIBS)

