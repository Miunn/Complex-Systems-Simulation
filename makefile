CC = gcc
CFLAGS = -Wall
LIB =
SDIR = src
HDIR = includes
BUILDDIR = bin
BINARY = main
CUSTOMLIBDIR = lib


# ==========================================================================

# listing all .c file inside SDIR and his child folder
SOURCES := $(foreach dir, $(wildcard $(SDIR)/*),$(wildcard $(dir)/*.c)) $(wildcard $(SDIR)/*.c)

# listing all .o file from all .c file from SDIR
OBJECTS := $(patsubst $(SDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

CUSTOMLIBS := $(wildcard $(CUSTOMLIBDIR)/*)

INCLUDELIB := $(foreach lib, $(CUSTOMLIBS), -I$(lib)/$(HDIR))

# ==========================================================================

all: $(BINARY) 

$(BINARY): $(OBJECTS) $(CUSTOMLIBS)/%.o
	$(CC) $(CFLAGS) $(OBJECTS) $(foreach lib, $(CUSTOMLIBS), $(wildcard $(lib)/*.o)) -o $@ $(LIB) -lm

$(BUILDDIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(HDIR) $(INCLUDELIB) -c $< -o $@ -lm

$(CUSTOMLIBS)/%.o:
	$(foreach lib, $(CUSTOMLIBS),  (cd $(lib) && make))

full-clean: clean
	$(foreach lib, $(CUSTOMLIBS),  (cd $(lib) && make clean))

clean:
	rm -rf $(foreach dir,$(wildcard $(BUILDDIR)/*), $(dir)) $(BINARY)

# ==========================================================================