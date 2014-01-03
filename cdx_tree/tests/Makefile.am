AM_CPPFLAGS = -I$(top_srcdir)/src -I/opt/local/include

noinst_PROGRAMS = test

test_LDFLAGS = -L/opt/local/lib -lcheck
test_SOURCES = ../src/tree_thing.cpp \
               ../src/tree_thing.h \
               main.cpp

TESTS = test
