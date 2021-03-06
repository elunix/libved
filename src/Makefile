#----------------------------------------------------------#
THIS_LIBNAME := ved
EDNAME       := veda

API := 0
REV := 3

# macOS doesn't have realpath by default (available through coreutils)
# THISDIR := $(shell realpath .)
THISDIR := $(shell (cd . && pwd))

THIS_LIBVERS  :=  $(API).$(REV)

THIS_HEADER     = lib$(THIS_LIBNAME).h
THIS_HEADER_EXT = lib$(THIS_LIBNAME)+.h
THIS_LIBSRC     = lib$(THIS_LIBNAME).c
LIBNAME         = $(THIS_LIBNAME)-$(THIS_LIBVERS)
THIS_LIB        = lib$(LIBNAME)

CC            := gcc
CC_STD        := -std=c11

SYSKERNEL     := $(shell uname -s)
SYSARCH       := $(shell uname -m)
SYS           := $(SYSKERNEL)-$(SYSARCH)

DATADIR    =  $(THISDIR)/data

SYSDIR    := $(THISDIR)/sys
SYSLIBDIR  = $(SYSDIR)/lib
SYSBINDIR  = $(SYSDIR)/bin
SYSINCDIR  = $(SYSDIR)/include
SYSDATADIR = $(SYSDIR)/data
SYSTMPDIR  = $(SYSDIR)/tmp

EXTNAME             = $(THIS_LIBNAME)+
LIB_EXTNAME         = lib$(EXTNAME)
LIB_EXT             = $(LIB_EXTNAME)-$(THIS_LIBVERS)
SYS_LIBEXT          = $(SYSLIBDIR)/$(LIB_EXT).so
SYS_LIBEXT_STATIC   = $(SYSLIBDIR)/$(LIB_EXTNAME).a
LIBEXT_FLAGS       := -L$(SYSLIBDIR) -l$(THIS_LIBNAME)
LIBEXT_SHARED_OBJS :=
LIBEXT_STATIC_OBJS :=

HEADERS = $(SYSINCDIR)/$(THIS_HEADER) $(SYSINCDIR)/$(THIS_HEADER_EXT)

PROGRAMMING_LANGUAGE_NAME = lai
PROGRAMMING_LANGUAGE_EXT_NAME = led
PROGRAMMING_LANGUAGE_DIR  = lib/$(PROGRAMMING_LANGUAGE_NAME)

THIS_PROGRAMMING_LANGUAGE_HEADER = $(PROGRAMMING_LANGUAGE_DIR)/$(PROGRAMMING_LANGUAGE_NAME).h
PROGRAMMING_LANGUAGE_EXT_HEADER = $(PROGRAMMING_LANGUAGE_DIR)/$(PROGRAMMING_LANGUAGE_EXT_NAME).h
SYS_PROGRAMMING_LANGUAGE_HEADER  = $(SYSINCDIR)/$(PROGRAMMING_LANGUAGE_NAME).h
SYS_PROGRAMMING_LANGUAGE_EXT_HEADER = $(SYSINCDIR)/$(PROGRAMMING_LANGUAGE_EXT_NAME).h

#----------------------------------------------------------#
THIS_SHAREDLIB := $(SYSLIBDIR)/$(THIS_LIB).so
THIS_STATICLIB := $(SYSLIBDIR)/lib$(THIS_LIBNAME).a

BASE_FLAGS  := -g -O2 -march=native -fvisibility=hidden -fdollars-in-identifiers

DEBUG_FLAGS := -Wextra -Wshadow -Wall -Wunused-function -Wunused-macros -Wno-override-init

# -Wno-override-init: is for designated initializers and both compilers complain.
# it is included in extra in gcc, but clang needs this unconditionally
ifneq ($(DEBUG), 1)
  ifeq (-$(CC), -clang)
    BASE_FLAGS  +=  -Wno-override-init
  endif
endif

ifneq (-$(CC), -tcc)
  DEBUG_FLAGS += -Werror
  # while compiling tinyexpr tcc warns with: assigment discards qualifiers
  # from pointer target type
  # -Wno-error=discarded-qualifiers doesn't have effect
endif

# DEBUG_FLAGS += -fsanitize=undefined
# if turn on -Wpedantic gcc gives: ISO C forbids braced-groups within expressions
# (this is for statement expressions)

SHARED_CFLAGS := -shared -fPIC
STATIC_CFLAGS := -static

FLAGS         := $(BASE_FLAGS)

CHECK_PTR_BOUNDS_FLAGS := -mmpx -fcheck-pointer-bounds

CHECK_PTR_BOUNDS := 0

ifneq ($(CHECK_PTR_BOUNDS), 0)
  FLAGS += $(CHECK_PTR_BOUNDS_FLAGS)
endif

ifeq (-$(CC), -gcc)
  FLAGS += -Wno-implicit-fallthrough
  # for gcc < 7 version
  #  FLAGS += -Wimplicit-fallthrough=0
endif

DEBUG := 0
ifneq ($(DEBUG), 0)
  FLAGS += $(DEBUG_FLAGS)
endif

#----------------------------------------------------------#
HAS_PROGRAMMING_LANGUAGE := 0
HAS_TCC  := 0
HAS_CURL := 0
HAS_JSON := 0

LIBOPTS :=

TABWIDTH := 8
UNDO_NUM_ENTRIES := 40
RLINE_HISTORY_NUM_ENTRIES := 20
CLEAR_BLANKLINES := 1
TAB_ON_INSERT_MODE_INDENTS := 0
CARRIAGE_RETURN_ON_NORMAL_IS_LIKE_INSERT_MODE := 0
SPACE_ON_NORMAL_IS_LIKE_INSERT_MODE := 0
SMALL_E_ON_NORMAL_GOES_INSERT_MODE := 0
BACKSPACE_ON_FIRST_IDX_REMOVE_TRAILING_SPACES := 1
BACKSPACE_ON_NORMAL_IS_LIKE_INSERT_MODE := 0
BACKSPACE_ON_NORMAL_GOES_UP := 1
BACKSPACE_ON_INSERT_GOES_UP_AND_JOIN := 1

LIBOPTS += -DLIBVED_DIR='"$(SYSDIR)"'
LIBOPTS += -DLIBVED_DATADIR='"$(SYSDATADIR)"'
LIBOPTS += -DLIBVED_TMPDIR='"$(SYSTMPDIR)"'

LIBOPTS += -DTABWIDTH=$(TABWIDTH)
LIBOPTS += -DUNDO_NUM_ENTRIES=$(UNDO_NUM_ENTRIES)
LIBOPTS += -DRLINE_HISTORY_NUM_ENTRIES=$(RLINE_HISTORY_NUM_ENTRIES)
LIBOPTS += -DCLEAR_BLANKLINES=$(CLEAR_BLANKLINES)
LIBOPTS += -DTAB_ON_INSERT_MODE_INDENTS=$(TAB_ON_INSERT_MODE_INDENTS)
LIBOPTS += -DCARRIAGE_RETURN_ON_NORMAL_IS_LIKE_INSERT_MODE=$(CARRIAGE_RETURN_ON_NORMAL_IS_LIKE_INSERT_MODE)
LIBOPTS += -DSPACE_ON_NORMAL_IS_LIKE_INSERT_MODE=$(SPACE_ON_NORMAL_IS_LIKE_INSERT_MODE)
LIBOPTS += -DSMALL_E_ON_NORMAL_GOES_INSERT_MODE=$(SMALL_E_ON_NORMAL_GOES_INSERT_MODE)
LIBOPTS += -DBACKSPACE_ON_FIRST_IDX_REMOVE_TRAILING_SPACES=$(BACKSPACE_ON_FIRST_IDX_REMOVE_TRAILING_SPACES)
LIBOPTS += -DBACKSPACE_ON_NORMAL_IS_LIKE_INSERT_MODE=$(BACKSPACE_ON_NORMAL_IS_LIKE_INSERT_MODE)
LIBOPTS += -DBACKSPACE_ON_NORMAL_GOES_UP=$(BACKSPACE_ON_NORMAL_GOES_UP)
LIBOPTS += -DBACKSPACE_ON_INSERT_GOES_UP_AND_JOIN=$(BACKSPACE_ON_INSERT_GOES_UP_AND_JOIN)

#----------------------------------------------------------#
LIBFLAGS := -I. -I$(SYSINCDIR) $(FLAGS)
# clang complains about unused command line arguments
#LIBFLAGS := -I. -I$(SYSINCDIR) -L$(SYSLIBDIR) $(FLAGS)

all: shared static veda-all

prereq: Env

shared: prereq $(THIS_SHAREDLIB) header
$(THIS_SHAREDLIB):
	$(CC) -x c $(THIS_LIBSRC) $(LIBOPTS) $(LIBFLAGS) $(SHARED_CFLAGS) -o $(THIS_SHAREDLIB)
	@$(LN_S) -vf $(THIS_SHAREDLIB) $(SYSLIBDIR)/lib$(THIS_LIBNAME).so

static: prereq $(THIS_STATICLIB) header
$(THIS_STATICLIB):
	$(CC) -x c $(THIS_LIBSRC) $(LIBOPTS) $(LIBFLAGS) $(STATIC_CFLAGS) -c -o $(THIS_LIB).o
	@$(AR) $(THIS_STATICLIB) $(THIS_LIB).o
	@$(RM) $(THIS_LIB).o

ifneq ($(HAS_PROGRAMMING_LANGUAGE), 0)
  HEADERS += $(SYS_PROGRAMMING_LANGUAGE_HEADER) $(SYS_PROGRAMMING_LANGUAGE_EXT_HEADER)
  LIBEXT_SHARED_OBJS += $(PROGRAMMING_LANGUAGE_NAME)-shared
  LIBEXT_STATIC_OBJS += $(PROGRAMMING_LANGUAGE_NAME)-static
endif

shared-libext: shared $(LIBEXT_SHARED_OBJS) $(SYS_LIBEXT) $(SYSINCDIR)/$(THIS_HEADER_EXT)
$(SYS_LIBEXT):
	$(CC) -x c $(LIB_EXTNAME).c $(LIBFLAGS) $(LIBEXT_FLAGS) $(SHARED_CFLAGS) -o $(SYS_LIBEXT)
	@$(LN_S) -vf $(SYS_LIBEXT) $(SYSLIBDIR)/$(LIB_EXTNAME).so

static-libext: static $(LIBEXT_STATIC_OBJS) $(SYS_LIBEXT_STATIC) $(SYSINCDIR)/$(THIS_HEADER_EXT)
$(SYS_LIBEXT_STATIC):
	$(CC) -x c $(LIB_EXTNAME).c $(LIBFLAGS) $(LIBEXT_FLAGS) $(STATIC_CFLAGS) -c -o $(LIB_EXTNAME).o
	@$(AR) $(SYS_LIBEXT_STATIC) $(LIB_EXTNAME).o
	@$(RM) $(LIB_EXTNAME).o

#################################################

header: $(HEADERS)

$(SYSINCDIR)/$(THIS_HEADER):
	@$(CP) $(THIS_HEADER) $(SYSINCDIR)
$(SYSINCDIR)/$(THIS_HEADER_EXT):
	@$(CP) $(THIS_HEADER_EXT) $(SYSINCDIR)
$(SYS_PROGRAMMING_LANGUAGE_HEADER):
	@$(CP) $(THIS_PROGRAMMING_LANGUAGE_HEADER) $(SYSINCDIR)
$(SYS_PROGRAMMING_LANGUAGE_EXT_HEADER):
	@$(CP) $(PROGRAMMING_LANGUAGE_EXT_HEADER) $(SYSINCDIR)

preproc:
	$(CC) -x c $(THIS_LIBSRC) $(LIBFLAGS) $(SHARED_CFLAGS) -E

clean: clean_shared clean_static clean_header clean_veda clean_libext_shared clean_libext_static

clean_shared: clean_header
	@$(TEST) ! -f $(THIS_SHAREDLIB) || $(RM) $(THIS_SHAREDLIB)

clean_static: clean_header
	@$(TEST) ! -f $(THIS_STATICLIB) || $(RM)  $(THIS_STATICLIB)

clean_header:
	@$(TEST) ! -f $(SYSINCDIR)/$(THIS_HEADER)     || $(RM) $(SYSINCDIR)/$(THIS_HEADER)
	@$(TEST) ! -f $(SYSINCDIR)/$(THIS_HEADER_EXT) || $(RM) $(SYSINCDIR)/$(THIS_HEADER_EXT)
	@$(TEST) ! -f $(SYS_PROGRAMMING_LANGUAGE_HEADER) || $(RM) $(SYSINCDIR)/$(SYS_PROGRAMMING_LANGUAGE_HEADER)
	@$(TEST) ! -f $(SYS_PROGRAMMING_LANGUAGE_EXT_HEADER) || $(RM) $(SYS_PROGRAMMING_LANGUAGE_EXT_HEADER)

clean_libext_shared: clean_libext_header
	@$(TEST) ! -f $(SYS_LIBEXT) || $(RM) $(SYS_LIBEXT)

clean_libext_static: clean_libext_header
	@$(TEST) ! -f $(SYS_LIBEXT_STATIC) || $(RM) $(SYS_LIBEXT_STATIC)

clean_libext_header:
	@$(TEST) ! -f $(SYSINCDIR)/$(THIS_HEADER_EXT) || $(RM) $(SYSINCDIR)/$(THIS_HEADER_EXT)

#----------------------------------------------------------#

THIS_APPSRC  := $(EDNAME).c
THIS_APPVERS := $(API)$(REV)

EDSHARED    := $(EDNAME)-$(THIS_APPVERS)_shared
EDSTATIC    := $(EDNAME)-$(THIS_APPVERS)_static
SYSEDSHARED := $(SYSBINDIR)/$(EDSHARED)
SYSEDSTATIC := $(SYSBINDIR)/$(EDSTATIC)
SYSEDSHAREDSH := $(SYSBINDIR)/$(EDNAME)s
SYSEDSTATICLNK := $(SYSBINDIR)/$(EDNAME)

#----------------------------------------------------------#
APPFLAGS  :=

REQOBJS   :=

PROGRAMMING_LANGUAGE_SHARED_FLAGS :=
PROGRAMMING_LANGUAGE_STATIC_FLAGS := "ENABLE_HTTP=0"

ifneq ($(HAS_PROGRAMMING_LANGUAGE), 0)
  APPFLAGS += -DHAS_PROGRAMMING_LANGUAGE
  LIBEXT_FLAGS += -DHAS_PROGRAMMING_LANGUAGE

  REQ_SHARED_LIBS = $(PROGRAMMING_LANGUAGE_NAME)-shared
  REQ_STATIC_LIBS = $(PROGRAMMING_LANGUAGE_NAME)-static

  ifeq ($(HAS_CURL), 0)
    PROGRAMMING_LANGUAGE_SHARED_FLAGS += "ENABLE_HTTP=0"
  else
    PROGRAMMING_LANGUAGE_SHARED_FLAGS += "ENABLE_HTTP=1"
  endif

endif

APPFLAGS += $(REQOBJS)
APPFLAGS += -I$(SYSINCDIR) -L$(SYSLIBDIR) -l$(EXTNAME) -l$(THIS_LIBNAME)

# This is to set specific order, needed by the linker in the static target
# as it has to be after the required objects but before -lm (if present)
ifneq ($(HAS_PROGRAMMING_LANGUAGE), 0)
  APPFLAGS += -l$(PROGRAMMING_LANGUAGE_NAME)
  LIBEXT_FLAGS += -l$(PROGRAMMING_LANGUAGE_NAME)
endif

APPFLAGS += -lm
LIBEXT_FLAGS += -lm

ifeq ($(SYSKERNEL), "Darwin")
  APPFLAGS += -lutil
endif

HAS_LOCAL_EXTENSIONS := 0
LOCAL_EXTENSIONS_FLAGS :=

ifneq ($(HAS_LOCAL_EXTENSIONS), 0)
  ifdef LOCAL_EXTENSIONS_FLAGS
    APPFLAGS += $(LOCAL_EXTENSIONS_FLAGS)
    LIBEXT_FLAGS  += $(LOCAL_EXTENSIONS_FLAGS)
  endif
  APPFLAGS += -DHAS_LOCAL_EXTENSIONS
  LIBEXT_FLAGS += -DHAS_LOCAL_EXTENSIONS
endif

VED_APPLICATION_FLAGS :=

ifdef VED_APPLICATION_FLAGS
  APPFLAGS += $(VED_APPLICATION_FLAGS)
endif

HAS_USER_EXTENSIONS := 0
USER_EXTENSIONS_FLAGS :=

ifneq ($(HAS_JSON), 0)
  HAS_USER_EXTENSIONS = 1
endif

ifneq ($(HAS_TCC), 0)
  HAS_USER_EXTENSIONS = 1
endif

ifneq ($(HAS_PROGRAMMING_LANGUAGE), 0)
  HAS_USER_EXTENSIONS = 1
endif

SHARED_APP_FLAGS :=

ifneq ($(HAS_USER_EXTENSIONS), 0)
  APPFLAGS += -DHAS_USER_EXTENSIONS
  LIBEXT_FLAGS += -DHAS_USER_EXTENSIONS

  ifdef USER_EXTENSIONS_FLAGS
    APPFLAGS += $(USER_EXTENSIONS_FLAGS)
    LIBEXT_FLAGS += $(USER_EXTENSIONS_FLAGS)
  endif

  ifneq ($(HAS_JSON), 0)
    APPFLAGS += -DHAS_JSON
    LIBEXT_FLAGS += -DHAS_JSON
  endif

  ifneq ($(HAS_TCC), 0)
    SHARED_APP_FLAGS += -DHAS_TCC -ltcc -ldl
    LIBEXT_FLAGS +=     -DHAS_TCC -ltcc -ldl
  endif

endif

APPFLAGS += $(FLAGS)

veda-all: veda-static veda-shared

clean_veda: clean_veda_static clean_veda_shared
clean_veda_shared:
	@$(TEST) ! -f $(SYSEDSHARED) || $(RM) $(SYSEDSHARED)
clean_veda_static:
	@$(TEST) ! -f $(SYSEDSTATIC) || $(RM) $(SYSEDSTATIC)

spell-dictionary:
	@$(TEST) -d $(SYSDATADIR)/spell || $(MKDIR) $(SYSDATADIR)/spell
	@$(CP) $(DATADIR)/spell/spell.txt $(SYSDATADIR)/spell
	@$(CP) $(DATADIR)/spell/Readme    $(SYSDATADIR)/spell

veda-shared: shared shared-libext $(REQ_SHARED_LIBS) $(SYSEDSHARED) spell-dictionary

$(SYSEDSHARED):
	$(CC) -x c $(THIS_APPSRC) $(APPFLAGS) $(SHARED_APP_FLAGS) -o $(EDSHARED)
	@$(INSTALL) -v $(EDSHARED) $(SYSBINDIR)
	@$(RM) $(EDSHARED)
	@$(PRINTF) "#!/bin/sh\n" > $(SYSEDSHAREDSH)
	@$(PRINTF) "LD_LIBRARY_PATH=$(SYSLIBDIR) $(SYSEDSHARED) \"\$$@\"\n" >> $(SYSEDSHAREDSH)
	@$(CHMOD_X) $(SYSEDSHAREDSH)

veda-static: static static-libext $(REQ_STATIC_LIBS) $(SYSEDSTATIC) spell-dictionary
$(SYSEDSTATIC):
	$(CC) -x c $(THIS_APPSRC) $(APPFLAGS) $(STATIC_CFLAGS) -o $(EDSTATIC)
	@$(INSTALL) -v $(EDSTATIC) $(SYSBINDIR)
	@$(RM) $(EDSTATIC)
	@$(LN_S) -f $(SYSEDSTATIC) $(SYSEDSTATICLNK)

veda-shared-preproc:
	$(CC) -x c $(THIS_APPSRC) $(APPFLAGS) -E

pl-shared-library: clean_pl_shared $(PROGRAMMING_LANGUAGE_NAME)-shared

$(PROGRAMMING_LANGUAGE_NAME)-shared:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) $(PROGRAMMING_LANGUAGE_SHARED_FLAGS) shared-library

pl-static-library: clean_pl_static $(PROGRAMMING_LANGUAGE_NAME)-static

$(PROGRAMMING_LANGUAGE_NAME)-static:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) $(PROGRAMMING_LANGUAGE_STATIC_FLAGS) static-library

clean_pl:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) clean

clean_pl_shared:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) clean_shared

clean_pl_static:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) clean_static

pl-interpr:
	@cd $(PROGRAMMING_LANGUAGE_DIR) && make SYSDIR=$(SYSDIR) ENABLE_REPL=1 interpr

#----------------------------------------------------------#
LD_LIBRARY_PATH := $(SYSLIBDIR)
#----------------------------------------------------------#
AR = ar rs
TEST = test
STAT = stat
GREP = grep
RM = rm -f
RM_R = rm -r -f
RMDIR = rmdir
MKDIR = mkdir
MKDIR_P = $(MKDIR) -p
CP = cp
CP_R = $(CP) -r
LN_S = ln -s
CHMOD = chmod
CHMOD_X = $(CHMOD) 0755
PRINTF = printf
INSTALL = install
MAKE = make
VALGRIND = valgrind
VALGRIND_ARGS = --leak-check=full --show-leak-kinds=all -v --track-origins=yes
GDB = gdb
GDB_ARGS = --quiet -ex "set logging file /tmp/gdb.txt" -ex "set logging on" -ex run --args
#----------------------------------------------------------#

Env: makeenv checkenv
makeenv:
	@$(TEST) -d $(SYSDIR)     || $(MKDIR_P) $(SYSDIR)
	@$(TEST) -d $(SYSLIBDIR)  || $(MKDIR)   $(SYSLIBDIR)
	@$(TEST) -d $(SYSINCDIR)  || $(MKDIR)   $(SYSINCDIR)
	@$(TEST) -d $(SYSBINDIR)  || $(MKDIR)   $(SYSBINDIR)
	@$(TEST) -d $(SYSDATADIR) || $(MKDIR_P) -m 0700 $(SYSDATADIR)
	@$(TEST) -d $(SYSTMPDIR)  || $(MKDIR_P) -m 0700 $(SYSTMPDIR)
#           macOS mkdir doesn't understand --mode=

checkenv:
	@$(TEST) -w $(SYSDIR)     || exit 1
	@$(TEST) -w $(SYSLIBDIR)  || exit 1
	@$(TEST) -w $(SYSINCDIR)  || exit 1
	@$(TEST) -w $(SYSBINDIR)  || exit 1
	@$(TEST) -w $(SYSDATADIR) || exit 1
	@$(TEST) -w $(SYSTMPDIR)  || exit 1

#----------------------------------------------------------#
FILE := libved.c libved.h

VERBOSE := 0
VALGRIND_V :=
ifneq ($(VERBOSE), 0)
  VALGRIND_V = -v
endif

run_shared:
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(SYSEDSHARED) $(FILE)

run_static:
	@$(SYSEDSTATIC) $(FILE)

check_veda_memory_leaks:
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(VALGRIND) $(VALGRIND_ARGS) $(VALGRIND_V) $(SYSEDSHARED) $(FILE)

debug_veda_static:
	@$(GDB) $(GDB_ARGS) $(SYSEDSTATIC) $(FILE)

debug_veda_shared:
	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(GDB) $(GDB_ARGS) $(SYSEDSHARED) $(FILE)
