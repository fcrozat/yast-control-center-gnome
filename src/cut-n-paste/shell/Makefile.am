noinst_LTLIBRARIES = libshell-unpatched.la

INCLUDES = 							\
	$(CONTROL_CFLAGS)					\
	-I$(top_srcdir)/src					\
	-I$(top_srcdir)/src/cut-n-paste/libgnome-control-center

MARSHAL_FILES = cc-shell-marshal.c cc-shell-marshal.h
BUILT_SOURCES = $(MARSHAL_FILES)

cc-shell-marshal.h: cc-shell-marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=cc_shell_marshal $< --header > $@

cc-shell-marshal.c: cc-shell-marshal.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=cc_shell_marshal $< --body --header > $@

libshell_unpatched_la_SOURCES =			\
	cc-shell-log.c				\
	cc-shell-log.h				\
	gnome-control-center.h			\
	shell-search-renderer.h			\
	cc-shell-category-view.c		\
	cc-shell-category-view.h		\
	cc-shell-item-view.c			\
	cc-shell-item-view.h			\
	cc-shell-model.c			\
	cc-shell-model.h			\
	$(MARSHAL_FILES)

EXTRA_DIST =					\
	cc-shell-marshal.list
