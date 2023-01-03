ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS=-Wall -Werror -g
AM_CFLAGS+=-D DEBUG
AM_CFLAGS+=-D WARNING
# Uncomment if performance when running with -DDEBUG is an issue
# Warning, if uncommented, issuing calls to debug functions during options
# parsing might result in debug flag incorrectly set to 0 for some files
#AM_CFLAGS+=-D CACHE_DEBUG_FLAG



SUBDIRS=
SUBDIRS+=. Examples_fusion

bin_PROGRAMS=
bin_PROGRAMS+=Options_and_debug_example
bin_PROGRAMS+=readELF
bin_PROGRAMS+=oracle

COMMON=utils.h utils.c

EXTRA_DIST=filtre.pl
Options_and_debug_example_SOURCES=Options_and_debug_example.c debug.c debug.h
readELF_SOURCES=readELF.c ELF.c ELF.h $(COMMON)
oracle_SOURCES=oracle.c oracle.h ELF.c ELF.h $(COMMON)

EXTRA_DIST+=

