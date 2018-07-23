CC = gcc
CXX = g++
AR = ar
CFLAGS += -g -Wall\
 -Wextra\
 -Wconversion\
 -Wshadow\
 -Wno-unused-parameter\
 -Wno-unused-function\
 -Wno-missing-field-initializers\
 -Wno-ignored-qualifiers\
 -Werror -Wno-conversion\
 -O0\
 -Wnon-virtual-dtor\
 -Woverloaded-virtual\
 -Wno-aggressive-loop-optimizations\
 -std=gnu++11

# -s for release
#  # -g for debug

CFLAGS += -D__STDC_LIMIT_MACROS
CFLAGS += -DPLATFORM_LINUX


LIBS += -lpthread
LIBS += -lxml2

BUILDTYPE = debug

TARGETNAME = $(LIBNAME)

LIBDIR = $(abspath $(ROOT)/lib/$(BUILDTYPE))
BINDIR = $(abspath $(ROOT)/bin/$(BUILDTYPE))
OBJDIR = $(abspath $(ROOT)/obj/$(BUILDTYPE)/$(TARGETNAME))

LINK_FLAGS += -L$(LIBDIR)

