.DEFAULT_GOAL:= all

.PHONY: all test clean dependencies

CC?=gcc
CXX?=g++

CFLAGS?= -Wall -Werror -std=c++14
CXXFLAGS?=$(CFLAGS)

ifeq ($(shell uname -o),Cygwin)
# Building on Cygwin
IS_WINDOWS:=1
DOT_EXE:=.exe
else
# Building on *nix
IS_WINDOWS:=
DOT_EXE:=
endif

SOURCE_FILES:=$(wildcard *.cpp)
COMPILED_OBJECTS:=$(SOURCE_FILES:.cpp=.o)
DEPENDENCIES:=$(COMPILED_OBJECTS:.o=.d)
TARGET_EXECUTABLE:=bin/ArrayTransformExample$(DOT_EXE)

# Generate dependency information before trying to include it
MKDEPS=$(shell $(MAKE) -s dependencies)

-include $(DEPENDENCIES)

all: $(TARGET_EXECUTABLE)

$(TARGET_EXECUTABLE): $(COMPILED_OBJECTS)
	@mkdir -p bin
	$(CXX) -o $@ $(CXXFLAGS) $?

%.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(@:.o=.cpp)


clean:
	rm -f *.o
	rm -f *.d
	rm -f *~
	rm -f $(TARGET_EXECUTABLE)


define run-test
	@echo "Running $(notdir $(1))"
	@echo "-------------------------------------------"
	@$(MAKE) --no-print-directory -C $(1)
	@echo "-------------------------------------------"

endef
test: TEST_DIRS=$(sort $(wildcard test/test-*))
test: $(TARGET_EXECUTABLE)
	$(foreach dir,$(TEST_DIRS),$(call run-test,$(dir)))

dependencies: $(DEPENDENCIES)

%.d: %.cpp
	@$(CXX) -MM $? -MF $@
