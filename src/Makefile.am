INCLUDES = $(CONTROL_CFLAGS)

AM_CPPFLAGS =							\
	-DGETTEXT_PACKAGE="\"gnome-control-center-2.0\""	\
	-DGNOMELOCALEDIR="\"$(datadir)/locale\""		\
	-DYAST_CC_PACKAGE="\"control-center\""			\
	-DYASTLOCALEDIR="\"$(datadir)/YaST2/locale\""		\
	-DUIDIR="\"$(uidir)\""

ybin_PROGRAMS = y2controlcenter-gnome

MARSHAL_FILES = cc-shell-marshal.c cc-shell-marshal.h
BUILT_SOURCES = $(MARSHAL_FILES)

cc-shell-marshal.h: cc-shell-marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=cc_shell_marshal $< --header > $@

cc-shell-marshal.c: cc-shell-marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=cc_shell_marshal $< --body --header > $@

y2controlcenter_gnome_SOURCES = 		\
	control-center.c                        \
	cc-shell-log.c                          \
	cc-shell-log.h                          \
	gnome-control-center.c                  \
	gnome-control-center.h                  \
	shell-search-renderer.c                 \
	shell-search-renderer.h                 \
	cc-shell-category-view.c                \
	cc-shell-category-view.h                \
	cc-shell-item-view.c                    \
	cc-shell-item-view.h                    \
	cc-shell-model.c                        \
	cc-shell-model.h                        \
	$(MARSHAL_FILES)

y2controlcenter_gnome_LDADD = $(CONTROL_LIBS)

uidir = $(pkgdatadir)/ui
ui_DATA = shell.ui

EXTRA_DIST = 			\
	$(ui_DATA)		\
	cc-shell-marshal.list
