ACLOCAL_AMFLAGS = -I config

SUBDIRS = src exe

DIST_SUBDIRS = src exe

EXTRA_DIST = \
	autogen.sh

test: all
	cd tests ; $(MAKE) check

