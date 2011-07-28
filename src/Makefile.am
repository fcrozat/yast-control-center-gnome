SUBDIRS = cut-n-paste

INCLUDES = 						\
	$(CONTROL_CFLAGS)				\
	-I$(srcdir)/cut-n-paste				\
	-I$(srcdir)/cut-n-paste/libgnome-control-center	\
	-I$(srcdir)/cut-n-paste/shell			\
	-I$(top_builddir)/src/cut-n-paste/shell

AM_CPPFLAGS =							\
	-DGETTEXT_PACKAGE="\"gnome-control-center-2.0\""	\
	-DGNOMELOCALEDIR="\"$(datadir)/locale\""		\
	-DYAST_CC_PACKAGE="\"control-center\""			\
	-DYASTLOCALEDIR="\"$(datadir)/YaST2/locale\""		\
	-DUIDIR="\"$(uidir)\""

ybin_PROGRAMS = y2controlcenter-gnome

y2controlcenter_gnome_SOURCES = 	\
	control-center.c                \
	gnome-control-center.c

y2controlcenter_gnome_LDADD = 	\
	$(top_builddir)/src/cut-n-paste/libgnome-control-center/libgnome-control-center.la	\
	$(top_builddir)/src/cut-n-paste/shell/libshell-unpatched.la				\
	$(CONTROL_LIBS)

uidir = $(pkgdatadir)/ui
ui_DATA = shell.ui

EXTRA_DIST = 			\
	$(ui_DATA)
