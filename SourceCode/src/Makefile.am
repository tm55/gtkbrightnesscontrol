## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = gtkbrightnesscontrol.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GTKBRIGHTNESSCONTROL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gtkbrightnesscontrol

gtkbrightnesscontrol_SOURCES = \
	main.c


gtkbrightnesscontrol_LDFLAGS = \
	-Wl,--export-dynamic

gtkbrightnesscontrol_LDADD = $(GTKBRIGHTNESSCONTROL_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

