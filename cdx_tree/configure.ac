AC_PREREQ([2.65])
AC_INIT([tree_thing], [0.1.0], [mellery451@gmail.com])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR(config)
AM_INIT_AUTOMAKE(-Wall tar-ustar dist-zip foreign subdir-objects)

# This lets us use PACKAGE_VERSION in Makefiles
AC_SUBST(PACKAGE_VERSION)

# Initialize libtool so we could build shared objects.
LT_INIT

# Checks for programs.
AC_PROG_CXX
AM_PROG_AR

AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile exe/Makefile])
AC_OUTPUT
