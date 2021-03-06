#!/bin/sh

# This is a convenience file to compile the shared targets with the default
# options. See convenience.sh for the opposite (compile with all the options
# enabled)

# You may need first to `chmod' this unit to make it executable.

if [ -z $LIBVED_SYSDIR ]; then
  SYSDIR=$PWD/sys
else
  SYSDIR=$LIBVED_SYSDIR
fi

if [ -z $LIBVED_DATADIR ]; then
  SYSDATADIR=$SYSDIR/data
else
  SYSDATADIR=$LIBVED_DATADIR
fi

if [ -z $LIBVED_TMPDIR ]; then
  SYSTMPDIR=$SYSDIR/tmp
else
  SYSTMPDIR=$LIBVED_TMPDIR
fi

if [ 0 = $# ]; then
  make SYSDIR=$SYSDIR clean_shared
fi

make SYSDIR=$SYSDIR clean_veda_shared

if [ -z $CC ]; then
  CC=gcc
fi

make                                                \
    CC=$CC                                          \
    SYSDIR=$SYSDIR                                  \
    SYSDATADIR=$SYSDATADIR                          \
    SYSTMPDIR=$SYSTMPDIR                            \
    DEBUG=0                                         \
    HAS_PROGRAMMING_LANGUAGE=0                      \
    HAS_USER_EXTENSIONS=0                           \
    HAS_JSON=0                                      \
    HAS_TCC=0                                       \
    HAS_LOCAL_EXTENSIONS=0                          \
    CLEAR_BLANKLINES=1                              \
    TAB_ON_INSERT_MODE_INDENTS=0                    \
    TABWIDTH=8                                      \
    CARRIAGE_RETURN_ON_NORMAL_IS_LIKE_INSERT_MODE=0 \
    SPACE_ON_NORMAL_IS_LIKE_INSERT_MODE=0           \
    SMALL_E_ON_NORMAL_GOES_INSERT_MODE=0            \
    BACKSPACE_ON_FIRST_IDX_REMOVE_TRAILING_SPACES=1 \
    BACKSPACE_ON_NORMAL_IS_LIKE_INSERT_MODE=0       \
    BACKSPACE_ON_NORMAL_GOES_UP=1                   \
    BACKSPACE_ON_INSERT_GOES_UP_AND_JOIN=1          \
    veda-shared
