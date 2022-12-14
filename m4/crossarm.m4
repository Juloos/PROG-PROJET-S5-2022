dnl Using two macros, so that AC_PROG_CC is not invoked by dependency
dnl before we set LDFLAGS...
AC_DEFUN([VD_CONFIG_CROSS_ARM_COMPILER],[dnl
  AC_ARG_ENABLE([arm-compiler], [AS_HELP_STRING([--enable-arm-compiler],
              [use an ARM cross compiler to compile examples @<:@default=check@:>@])],
    [], [enable_arm_compiler=check])

  _have_no_stdlib=
  AS_CASE(["$enable_arm_compiler"],
  [no], [ have_arm_compiler=no ],
  [check|yes], [
    _save_LDFLAGS="$LDFLAGS"
    LDFLAGS="-nostdlib -Wl,--entry=0"
    AC_PROG_CC
    LDFLAGS="$_save_LDFLAGS"
    AS_CASE(["$CC"],
      [*-none-eabi-*], [
         VD_CROSS_NOSTDLIB_LDFLAGS="-nostdlib -Wl,--entry=0"
         _have_no_stdlib=1
      ])

    AC_MSG_CHECKING([whether the compiler is targeting ARM])
    if $CC -dumpmachine | grep arm > /dev/null ; then
      AC_MSG_RESULT([yes])
      have_arm_compiler=yes
    else
      AC_MSG_RESULT([no])
      have_arm_compiler=no
      AS_IF([test x"$enable_arm_compiler" = xyes ],
        [AC_MSG_ERROR([Cannot found an ARM cross-compiler whereas required])],
        [AC_MSG_WARN([An ARM cross-compiler is required to compile the examples])])
    fi

  ],
  [AC_MSG_ERROR([Invalid value `$enable_arm_compiler' for --enable-arm-compiler])])
  
  AM_CONDITIONAL([HAVE_ARM_COMPILER],[test $have_arm_compiler = yes])
  AC_SUBST([VD_CROSS_NOSTDLIB_LDFLAGS])
])
AC_DEFUN([VD_CONFIG_CROSS_ARM],[dnl
  AC_REQUIRE([VD_CONFIG_CROSS_ARM_COMPILER])
  AS_CASE(["$have_arm_compiler"],
  [no], [
    AC_MSG_NOTICE([Still looking for a (host) compiler, so that the Makefile is correctly generated])
    AC_PROG_CC
    AM_PROG_AS
  ],
  [yes], [
    AM_PROG_AS
    AM_PROG_CC_C_O
    AX_CHECK_COMPILE_FLAG([-no-pie], [VD_CROSS_NOPIE_CFLAGS="-no-pie"], [], [-Werror])
  ],
  [AC_MSG_ERROR([Intenal error: invalid value `$have_arm_compiler'])])

  AM_CONDITIONAL([HAVE_NO_STDLIB], [test x"$_have_no_stdlib" = x1])
  AC_SUBST([VD_CROSS_NOPIE_CFLAGS])
])
