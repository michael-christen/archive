#Compiler Directives
CXX=g++
CPPFLAGS= -std=c++11
LDFLAGS= -L/usr/local/lib
LIBS= -lthrift
#Directories
IDIR=backend/include
LDIR=backend/lib
ODIR=backend/obj

IDL_DIR=idl
GEN_CPP_DIR=backend/gen-cpp
GEN_JS_DIR=frontend/gen-js
#Paths
INCLUDE_PATHS= -I$(IDIR) \
			   -I$(GEN_CPP_DIR)
#Files
# Call thrift with the MAIN_IDL
# TODO: Change these to your own thrift files 
_MAIN_IDL= PID_Simulator.thrift
MAIN_IDL=$(patsubst %,$(IDL_DIR)/%,$(_MAIN_IDL))
_IDL= types.thrift \
	  $(_MAIN_IDL)
IDL=$(patsubst %,$(IDL_DIR)/%,$(_IDL))
_GEN_SRC_CONST=$(_IDL:.thrift=_constants.cpp)
_GEN_SRC_TYPES=$(_IDL:.thrift=_types.cpp)
_GEN_SRC_MAIN=$(_MAIN_IDL:.thrift=.cpp)
_GEN_SRC=$(_GEN_SRC_CONST) $(_GEN_SRC_TYPES) $(_GEN_SRC_MAIN)
GEN_SRC=$(patsubst %,$(GEN_CPP_DIR)/%,$(_GEN_SRC))
_GEN_OBJ=$(_GEN_SRC:.cpp=.o)
GEN_OBJ=$(patsubst %,$(ODIR)/%,$(_GEN_OBJ))
_GEN_DEPS=$(_GEN_SRC:.cpp=.h)
GEN_DEPS=$(patsubst %,$(GEN_CPP_DIR)/%,$(_GEN_DEPS))

_GEN_JS_TYPES=$(_IDL:.thrift=_types.js)
_GEN_JS_MAIN=$(_MAIN_IDL:.thrift=.js)
_GEN_JS=$(_GEN_JS_TYPES) $(_GEN_JS_MAIN)
GEN_JS=$(patsubst %,$(GEN_JS_DIR)/%,$(_GEN_JS))

MAIN_BINFILE= run
TEST_BINFILE= test-run
SRC= utils.cpp \
	 simulator.cpp
MAIN_SRC= main.cpp
TEST_SRC= test.cpp
_OBJ=$(SRC:.cpp=.o)
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ)) $(GEN_OBJ)
_MAIN_OBJ=$(MAIN_SRC:.cpp=.o)
MAIN_OBJ=$(patsubst %,$(ODIR)/%,$(_MAIN_OBJ)) $(GEN_OBJ)
_TEST_OBJ=$(TEST_SRC:.cpp=.o)
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ)) $(GEN_OBJ)

_DEPS= easylogging++.h \
	   utils.h \
	   simulator.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS)) $(GEN_DEPS)

#Flag Handling
ifdef DEBUG
CPPFLAGS := $(CPPFLAGS) -g
endif
ifdef VERBOSE
        Q =
        E = @true 
else
        Q = @
        E = @echo 
endif

.PHONY: all help clean nuke generate test

all: $(MAIN_BINFILE)
test: $(TEST_BINFILE)
	./$(TEST_BINFILE)
generate: $(GEN_DEPS) $(GEN_SRC) $(GEN_JS)
help:
	$(E)
	$(E)all			create executable server and generate necessary files
	$(E)test		generate & run a test script
	$(E)generate	generate js & cpp code from idl/thrift files
	$(E)clean		remove object files and executables
	$(E)nuke		clean & remove any generated files
	$(E)help		show this display
	$(E)

$(GEN_CPP_DIR):
	mkdir -p $(GEN_CPP_DIR)
# Do command in either case
$(GEN_DEPS): $(IDL) $(GEN_CPP_DIR)
	thrift -r -out $(GEN_CPP_DIR) --gen cpp $(MAIN_IDL)
$(GEN_SRC): $(IDL) $(GEN_CPP_DIR)
	thrift -r -out $(GEN_CPP_DIR) --gen cpp $(MAIN_IDL)

$(GEN_JS_DIR):
	mkdir -p $(GEN_JS_DIR)
$(GEN_JS): $(IDL) $(GEN_JS_DIR)
	thrift -r -out $(GEN_JS_DIR) --gen js $(MAIN_IDL)

$(ODIR)/%.o: $(GEN_CPP_DIR)/%.cpp $(GEN_DEPS)
	$(E)C++-compiling generated: $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) $(INCLUDE_PATHS)

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) $(INCLUDE_PATHS)

$(MAIN_BINFILE):	$(OBJ) $(MAIN_OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $(INCLUDE_PATHS) $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

$(TEST_BINFILE):	$(OBJ) $(TEST_OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $(INCLUDE_PATHS) $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(MAIN_BINFILE) $(TEST_BINFILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi

nuke: clean
	$(E)Nuking
	$(Q)rm -rf $(GEN_CPP_DIR) $(GEN_JS_DIR)
