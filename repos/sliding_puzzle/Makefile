#Compiler Directives
CXX=g++
CPPFLAGS=-std=c++11
LDFLAGS=
LIBS=#-lsomething
#Directories
IDIR=include
LDIR=lib
ODIR=obj
#Files
BINFILE= slide-solve
TESTFILE= tester
MAIN_SRC= solve.cpp
TEST_SRC= test.cpp
SRC= board.cpp \

_OBJ=$(SRC:.cpp=.o)
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
_MAIN_OBJ=$(MAIN_SRC:.cpp=.o)
MAIN_OBJ=$(patsubst %,$(ODIR)/%,$(_MAIN_OBJ))
_TEST_OBJ=$(TEST_SRC:.cpp=.o)
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))
_DEPS= board.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

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

.PHONY: all help clean

all: $(BINFILE)
test: $(TESTFILE)
help:
	$(E)
	$(E)Helpful Comments
	$(E)

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) -I$(IDIR)

$(BINFILE):	$(OBJ) $(MAIN_OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

$(TESTFILE): $(OBJ) $(TEST_OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(BINFILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi

