dnl based on ideas from https://lists.gnu.org/archive/html/autoconf/2011-04/msg00006.html
dnl but not patching or original autoconf, so AC_CONFIG_SUBDIR does not
dnl check with VD_CONFIG_SUBDIR_CUSTOM subdirs and VD_OUTPUT must be added
dnl after AC_OUTPUT (and some code is duplicated...)

# VD_CONFIG_SUBDIR_CUSTOM(DIR, ARGUMENTS [, DISABLE_HELP_RECURSIVE])
# ------------------------------------------------------------------
# Build a list custom_subdirs of tuples (DIR, ARGUMENTS) where DIR is
# unique in _AC_LIST_CUSTOM_SUBDIRS and _AC_LIST_SUBDIRS. This list is used in
# _AC_OUTPUT_SUBDIRS to invoke nested configures in directory DIR with
# arguments ARGUMENTS. The arguments are modified as in the AC_CONFIG_SUBDIRS
# case, see _AC_SUB_CONFIGURE_ARGS. If the third argument
# DISABLE_HELP_RECURSIVE is given, configure --help=recursive will omit DIR.
AC_DEFUN([VD_CONFIG_SUBDIR_CUSTOM],
[AC_REQUIRE([AC_CONFIG_AUX_DIR_DEFAULT])]dnl
[AC_REQUIRE([AC_DISABLE_OPTION_CHECKING])]dnl
[m4_foreach_w([_AC_Sub], [$1],
	      [_AC_CONFIG_UNIQUE([SUBDIRS or CONFIG_SUBDIR_CUSTOM],
                                 m4_bpatsubst(m4_defn([_AC_Sub]), [:.*]))])]dnl

# build a list of (directory,arguments) tuples that will be processed in _AC_OUTPUT_SUBDIRS
[if test -z "$custom_subdirs"; then
  custom_subdirs="custom_sub_configure_dir=\"m4_normalize([$1])\";custom_sub_configure_args=\"m4_normalize([$2])\""
else
  custom_subdirs="$custom_subdirs|custom_sub_configure_dir=\"m4_normalize([$1])\";custom_sub_configure_args=\"m4_normalize([$2])\""
fi]

# per default, enable --help=recursive in directory $1.
[m4_ifval([$3], 
          [], 
          [m4_append([_AC_LIST_SUBDIRS], [$1], [
])dnl
])]dnl
[AS_LITERAL_IF([$1], [],
	       [AC_DIAGNOSE([syntax], [$0: you should use literals])])]dnl
[AC_SUBST([subdirs_custom], ["$subdirs_custom m4_normalize([$1])"])]dnl
)
# VD_CONFIG_SUBDIR_CUSTOM


# _VD_OUTPUT_SUBDIRS_CUSTOM
# -------------------------
# This is a subroutine of VD_OUTPUT, but it does not go into
# config.status, rather, it is called after running config.status.
AC_DEFUN([_VD_OUTPUT_SUBDIRS_CUSTOM],
[
#
# CONFIG_SUBDIRS_CUSTOM section.
#
if test "$no_recursion" != yes; then
  ac_popdir=`pwd`

  # call configures in list $custom_subdirs with directory-specific arguments.
  OIFS=$IFS
  IFS='|'
  list=$custom_subdirs
  for dir_and_args in $list; do
    IFS=$OIFS
    eval $dir_and_args
    if test "x$custom_sub_configure_dir" = x; then continue; fi
    ac_custom_sub_configure_args=
    _AC_SUB_CONFIGURE_ARGS([$custom_sub_configure_args], 
                           [ac_custom_sub_configure_args])
    _AC_SUB_CONFIGURE([$custom_sub_configure_dir], 
                      [$ac_custom_sub_configure_args])
    cd "$ac_popdir"
    IFS='|'
  done
  IFS=$OIFS  

dnl  # call configures in $subdirs with fixed arguments.
dnl  ac_sub_configure_args=
dnl  _AC_SUB_CONFIGURE_ARGS([$ac_configure_args], 
dnl                         [ac_sub_configure_args])
dnl  for ac_dir in : $subdirs; do test "x$ac_dir" = x: && continue
dnl     echo "ac_dir(inside): $ac_dir"
dnl    _AC_SUB_CONFIGURE([$ac_dir], 
dnl                      [$ac_sub_configure_args])
dnl    cd "$ac_popdir"
dnl  done
fi
])# _VD_OUTPUT_SUBDIRS_CUSTOM


# _AC_SUB_CONFIGURE_ARGS(ARGUMENTS_IN, ARGUMENTS_OUT)
# ---------------------------------------------------
# Create ARGUMENTS_OUT from ARGUMENTS_IN for use in nested configure calls.
m4_define([_AC_SUB_CONFIGURE_ARGS],
[
  # Remove --cache-file, --srcdir, and --disable-option-checking arguments
  # so they do not pile up.
  ac_sub_configure_args=
  ac_prev=
  eval "set x $1"
  shift
  for ac_arg
  do
    if test -n "$ac_prev"; then
      ac_prev=
      continue
    fi
    case $ac_arg in
    -cache-file | --cache-file | --cache-fil | --cache-fi \
    | --cache-f | --cache- | --cache | --cach | --cac | --ca | --c)
      ac_prev=cache_file ;;
    -cache-file=* | --cache-file=* | --cache-fil=* | --cache-fi=* \
    | --cache-f=* | --cache-=* | --cache=* | --cach=* | --cac=* | --ca=* \
    | --c=*)
      ;;
    --config-cache | -C)
      ;;
    -srcdir | --srcdir | --srcdi | --srcd | --src | --sr)
      ac_prev=srcdir ;;
    -srcdir=* | --srcdir=* | --srcdi=* | --srcd=* | --src=* | --sr=*)
      ;;
    -prefix | --prefix | --prefi | --pref | --pre | --pr | --p)
      ac_prev=prefix ;;
    -prefix=* | --prefix=* | --prefi=* | --pref=* | --pre=* | --pr=* | --p=*)
      ;;
    --disable-option-checking)
      ;;
    *)
      case $ac_arg in
      *\'*) ac_arg=`AS_ECHO(["$ac_arg"]) | sed "s/'/'\\\\\\\\''/g"` ;;
      esac
      AS_VAR_APPEND([$2], [" '$ac_arg'"]) ;;
    esac
  done

  # Always prepend --prefix to ensure using the same prefix
  # in subdir configurations.
  ac_arg="--prefix=$prefix"
  case $ac_arg in
  *\'*) ac_arg=`AS_ECHO(["$ac_arg"]) | sed "s/'/'\\\\\\\\''/g"` ;;
  esac
  $2="'$ac_arg' $$2"

  # Pass --silent
  if test "$silent" = yes; then
    $2="--silent $$2"
  fi

  # Always prepend --disable-option-checking to silence warnings, since
  # different subdirs can have different --enable and --with options.
  $2="--disable-option-checking $$2"
])# _AC_SUB_CONFIGURE_ARGS


# _AC_SUB_CONFIGURE(DIR, ARGUMENTS)
# ---------------------------------
# Call nested configure in DIR with arguments ARGUMENTS.
m4_define([_AC_SUB_CONFIGURE],
[
  sub_configure_dir=$1
  sub_configure_args=$2

  # Do not complain, so a configure script can configure whichever
  # parts of a large source tree are present.
  test -d "$srcdir/$sub_configure_dir" || continue

  ac_msg="=== configuring in $sub_configure_dir (`pwd`/$sub_configure_dir)"
  _AS_ECHO_LOG([$ac_msg])
  _AS_ECHO([$ac_msg])
  AS_MKDIR_P(["$sub_configure_dir"])
  _AC_SRCDIRS(["$sub_configure_dir"])

  cd "$sub_configure_dir"

  # Check for guested configure; otherwise get Cygnus style configure.
  if test -f "$ac_srcdir/configure.gnu"; then
    ac_sub_configure=$ac_srcdir/configure.gnu
  elif test -f "$ac_srcdir/configure"; then
    ac_sub_configure=$ac_srcdir/configure
  elif test -f "$ac_srcdir/configure.in"; then
    # This should be Cygnus configure.
    ac_sub_configure=$ac_aux_dir/configure
  else
    AC_MSG_WARN([no configuration information is in $sub_configure_dir])
    ac_sub_configure=
  fi

  # The recursion is here.
  if test -n "$ac_sub_configure"; then
    # Make the cache file name correct relative to the subdirectory.
    case $cache_file in
    [[\\/]]* | ?:[[\\/]]* ) ac_sub_cache_file=$cache_file ;;
    *) # Relative name.
      ac_sub_cache_file=$ac_top_build_prefix$cache_file ;;
    esac

    AC_MSG_NOTICE([running $SHELL $ac_sub_configure $sub_configure_args --cache-file=$ac_sub_cache_file --srcdir=$ac_srcdir])
    # The eval makes quoting arguments work.
    eval "\$SHELL \"\$ac_sub_configure\" $sub_configure_args \
	 --cache-file=\"\$ac_sub_cache_file\" --srcdir=\"\$ac_srcdir\"" ||
      AC_MSG_ERROR([$ac_sub_configure failed for $sub_configure_dir])
  fi
])# _AC_SUB_CONFIGURE

AC_DEFUN([VD_OUTPUT],
[AC_PROVIDE_IFELSE([VD_CONFIG_SUBDIR_CUSTOM],
                  [_VD_OUTPUT_SUBDIRS_CUSTOM()])dnl
])
