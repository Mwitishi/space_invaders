CC=gcc
WIN_CC=i586-mingw32msvc-gcc
CFLAGS=-Wall
WIN_CFLAGS=-Wall -lmingw32
SDLFLAGS=-lSDLmain -lSDL -lSDL_image

SOURCEDIR=.
BINDIR=../bin

CSOURCE=space_invaders.c
INDIR_CSOURCE=$(addprefix $(SOURCEDIR)/,$(CSOURCE))
CHEADER=space_invaders.h
INDIR_CHEADER=$(addprefix $(SOURCEDIR)/,$(CHEADER))
BIN=space_invaders
EXE=space_invaders.exe

all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(INDIR_CSOURCE) $(INDIR_CHEADER)
	$(CC) $(CFLAGS) $(INDIR_CSOURCE) -o $(BINDIR)/$(BIN) $(SDLFLAGS)

win: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(INDIR_CSOURCE) $(INDIR_CHEADER)
	$(WIN_CC) $(WIN_CFLAGS) $(INDIR_CSOURCE) -o $(BINDIR)/$(EXE) $(SDLFLAGS)

clean:
	rm -f $(BINDIR)/$(BIN) $(BINDIR)/$(EXE)
