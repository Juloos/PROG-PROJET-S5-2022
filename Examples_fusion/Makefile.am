ACLOCAL_AMFLAGS = -I ../m4

# no code transformations to work with thumb
AM_CFLAGS= @VD_CROSS_NOPIE_CFLAGS@ -mno-thumb-interwork

if HAVE_ARM_COMPILER

noinst_PROGRAMS=fusion_result

if HAVE_NO_STDLIB
# avec arm-none-eabi-, on a besoin de "puts" pour générer le programme
fusion_result_SOURCES=eabi-none-lib.c
AM_LDFLAGS = @VD_CROSS_NOSTDLIB_LDFLAGS@
endif

# il faudra linker avec fusion_result.o
fusion_result_LDADD=fusion_result.o

# mais il faut aussi construire explicitement fusion_result.o
# (cf la règle suivante)
nodist_EXTRA_fusion_result_SOURCES=fusion_result.o

# Appel du linker avec -no-stdlib et -r car on ne fait qu'un link partiel
fusion_result.o: file1.o file2.o
	$(AM_V_CCLD)$(LINK) -nostdlib -Wl,-r $^

endif # HAVE_ARM_COMPILER

clean-local:
	rm -f *.o fusion_result .deps/*.Po

EXTRA_DIST=file1.c file2.c
