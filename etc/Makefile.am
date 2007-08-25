schemasdir   = @GCONF_SCHEMA_FILE_DIR@
schemas_DATA = yast2-control-center-gnome.schemas

# hacks
menudir = $(sysconfdir)/xdg/menus
menu_DATA = YaST-gnome.menu

# built from yast2 groups/ desktop files
directorydir = $(datadir)/desktop-directories
directory_DATA = $(wildcard yast-gnome-*.directory)

$(schemas_DATA): $(schemas_DATA).in
	sed -e "s|\@DATADIR\@|$(datadir)|g" $< > $@

install-data-local:
	if test -z "$(DESTDIR)" ; then \
		for p in $(schemas_DATA) ; do \
			GCONF_CONFIG_SOURCE=$(GCONF_SCHEMA_CONFIG_SOURCE) $(GCONFTOOL) --makefile-install-rule $$p; \
		done \
	fi

EXTRA_DIST = $(schemas_DATA).in $(menu_DATA) $(directory_DATA)

CLEANFILES = $(schemas_DATA)
