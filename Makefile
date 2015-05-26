#Compiler Directives
CXX=g++
CPPFLAGS=
LDFLAGS=
LIBS=#-lsomething
#Directories
IDIR=include
LDIR=lib
ODIR=obj
#Files
BINFILE= slide-solve
SRC= board.cpp \
	 solve.cpp
_OBJ=$(SRC:.cpp=.o)
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
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
help:
	$(E)
	$(E)Helpful Comments
	$(E)

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) -I$(IDIR)

$(BINFILE):	$(OBJ) $(DEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(BINFILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi

