schemasdir   = @GCONF_SCHEMA_FILE_DIR@
schemas_DATA = yast2-control-center-gnome.schemas

# hacks
menudir = $(sysconfdir)/xdg/menus
menu_DATA = YaST-gnome.menu

# built from yast2 groups/ desktop files
directorydir = $(datadir)/desktop-directories
directory_DATA = $(wildcard yast-gnome-*.directory)

NLD_YAST_THEME_DIR = /usr/share/YaST2/theme/NLD
SL_YAST_THEME_DIR = /usr/share/YaST2/theme/SuSELinux

$(schemas_DATA): $(schemas_DATA).in
	sed -e "s|\@DATADIR\@|$(datadir)|g" $< > $@

# -----------------------------------------------------
# clobber the NLD yast2 theme to make it an icon theme
# this hack should be in the themes themselves.
# -----------------------------------------------------
indexdir = $(NLD_YAST_THEME_DIR)/icons
index_DATA = index.theme
index2dir = $(SL_YAST_THEME_DIR)/icons
index2_DATA = index.theme
# we also require a symlink to make it look like a theme
link-hicolor:
	mkdir -p $(DESTDIR)$(NLD_YAST_THEME_DIR) ; ln -sf icons $(DESTDIR)$(NLD_YAST_THEME_DIR)/hicolor
	mkdir -p $(DESTDIR)$(SL_YAST_THEME_DIR) ; ln -sf icons $(DESTDIR)$(SL_YAST_THEME_DIR)/hicolor
# -----------------------------------------------------

install-data-local: link-hicolor
	if test -z "$(DESTDIR)" ; then \
		for p in $(schemas_DATA) ; do \
			GCONF_CONFIG_SOURCE=$(GCONF_SCHEMA_CONFIG_SOURCE) $(GCONFTOOL) --makefile-install-rule $$p; \
		done \
	fi

EXTRA_DIST = $(schemas_DATA).in $(menu_DATA) $(directory_DATA) $(index_DATA)

CLEANFILES = $(schemas_DATA)
