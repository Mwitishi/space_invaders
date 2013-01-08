CC=gcc
CFLAGS=-c -Wall
SDLFLAGS=-lSDL_main -lSDL -lSDL_image

SOURCEDIR=.
OBJDIR=../obj
BINDIR=../bin

CSOURCE=space_invaders.c
INDIR_CSOURCE=$(addprefix $(SOURCEDIR)/,$(CSOURCE))
COBJ=$(CSOURCE:.c=.o)
INDIR_COBJ=$(addprefix $(OBJDIR)/,$(COBJ))
BIN=space_invaders

all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(INDIR_COBJ)
	$(CC) $(INDIR_COBJ) -o $(BINDIR)/$(BIN)

$(INDIR_COBJ): $(INDIR_CSOURCE)
	$(CC) $(CFLAGS) $(SDLFLAGS) $(INDIR_CSOURCE)
	mv *.o $(OBJDIR)

clean:
	rm $(OBJDIR)/*.o $(BINDIR)/$(BIN)
