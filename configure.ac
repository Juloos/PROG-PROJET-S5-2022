#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.67)
AC_INIT(ELF_Linker, 1.0, Guillaume.Huard@imag.fr)
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([debug.c])
# AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_FUNC_ERROR_AT_LINE

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([alarm bzero dup2 gethostbyaddr gethostbyname munmap select socket strerror memset])

AC_ARG_WITH([arm-host], [AS_HELP_STRING([--with-arm-host@<:@=arch-prefix@:>@],
              [prefix for the cross compiler targeting the ARM platform @<:@default=check@:>@])],
  [], [with_arm_host=check])
AS_CASE(["$with_arm_host"],
 [no], [],
 [check|yes], [
    AC_CHECK_PROGS([GCC_CROSS],[arm-elf-gcc arm-linux-gnueabi-gcc arm-eabi-gcc arm-none-eabi-gcc], [none])
    AS_CASE(["$GCC_CROSS"],
      [*arm-elf-gcc], [with_arm_host=arm-elf],
      [*arm-linux-gnueabi-gcc], [with_arm_host=arm-linux-gnueabi],
      [*arm-eabi-gcc], [with_arm_host=arm-eabi],
      [*arm-none-eabi-gcc], [with_arm_host=arm-none-eabi],
      [none], [
	AC_MSG_WARN([Cannot find a cross compiler for the ARM plateform.])
	AS_IF([test -x /opt/gnu/arm/bin/arm-elf-gcc],
	  [AC_MSG_ERROR([Check your PATH, /opt/gnu/arm/bin/arm-elf-gcc seems to be here])])
	AS_IF([test -x /opt/gnu/arm/bin/arm-eabi-gcc],
	  [AC_MSG_ERROR([Check your PATH, /opt/gnu/arm/bin/arm-eabi-gcc seems to be here])])
	AS_IF([test x"$with_arm_host" = xcheck ],
	  [AC_MSG_WARN([Disabling rules to build ARM examples])
	   with_arm_host=no
	  ],
          [AC_MSG_ERROR([Check your installation and/or your PATH])])])])

if test x"$with_arm_host" != xno; then
  AC_MSG_NOTICE([enabling the Examples directory with $with_arm_host cross-compiler target])
  arm_subdir_args="--host=$with_arm_host --enable-arm-compiler"
else
  arm_subdir_args="--disable-arm-compiler"
fi
VD_CONFIG_SUBDIR_CUSTOM([Examples_loader], [$arm_subdir_args])
VD_CONFIG_SUBDIR_CUSTOM([Examples_fusion], [$arm_subdir_args])
AM_CONDITIONAL([HAVE_ARM_COMPILER],[test x"$with_arm_host" != xno])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
VD_OUTPUT
