VERSION := $(shell cat VERSION)

CC = cc
SRC = events.c settings.c cfgmgr.c mainwindow.c sglogout.c
OBJ_X11 = $(SRC:.c=.x11.o)
OBJ_WAYLAND = $(SRC:.c=.wayland.o)
EXE = sglogout

CFLAGS_X11 = `pkg-config --cflags gtk+-3.0` -DX11 -fPIC -Dpver=\"$(VERSION)\"
CFLAGS_WAYLAND = `pkg-config --cflags gtk+-3.0 gtk-layer-shell-0` -Dwayland -Dpver=\"$(VERSION)\"
LIBS_X11 = `pkg-config --libs gtk+-3.0` -lX11 ./sgxpos/sgxpos.o
LIBS_WAYLAND = `pkg-config --libs gtk+-3.0 gtk-layer-shell-0`

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
DESKTOPDIR = $(PREFIX)/share/applications



ifeq ($(WAYLAND),1)
all: wayland
else ifeq ($(X11),1)
all: x11
else
all: wayland x11
endif


x11: $(OBJ_X11)
	$(CC) $(CFLAGS_X11) -o $(EXE)-x11 $(OBJ_X11) $(LIBS_X11)

wayland: $(OBJ_WAYLAND)
	$(CC) $(CFLAGS_WAYLAND) -o $(EXE)-wayland $(OBJ_WAYLAND) $(LIBS_WAYLAND)

%.x11.o: %.c
	$(CC) $(CFLAGS_X11) -c -o $@ $<

%.wayland.o: %.c
	$(CC) $(CFLAGS_WAYLAND) -c -o $@ $<

debug: $(SRC)
	$(CC) $(CFLAGS_X11) -g $(SRC) -o debug $(LIBS_X11)

test:
	./$(EXE)

clean:
	rm -f *.o *.x11.o *.wayland.o $(EXE)-x11 $(EXE)-wayland debug

install:
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(EXE) $(DESTDIR)$(BINDIR)/$(EXE) || true
	[ -f $(EXE)-x11 ] && install -m 755 $(EXE)-x11 $(DESTDIR)$(BINDIR)/$(EXE)-x11 || true
	[ -f $(EXE)-wayland ] && install -m 755 $(EXE)-wayland $(DESTDIR)$(BINDIR)/$(EXE)-wayland || true
	install -d $(DESTDIR)$(DESKTOPDIR)
	install -m 644 $(EXE).desktop $(DESTDIR)$(DESKTOPDIR)/$(EXE).desktop