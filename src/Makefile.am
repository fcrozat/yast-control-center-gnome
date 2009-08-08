INCLUDES = $(CONTROL_CFLAGS)

AM_CPPFLAGS =							\
	-DYASTLOCALEDIR="\"$(datadir)/YaST2/locale\""		\
	-DGNOMELOCALEDIR="\"$(datadir)/locale\""		\
	-DENABLE_NLS=1

ybin_PROGRAMS = y2controlcenter-gnome

y2controlcenter_gnome_SOURCES = control-center.c
y2controlcenter_gnome_LDADD = $(CONTROL_LIBS)
