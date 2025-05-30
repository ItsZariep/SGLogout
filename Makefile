CC = cc

# Source files
SRC = events.c settings.c cfgmgr.c mainwindow.c sglogout.c

# Object files per backend
OBJ_X11 = $(SRC:.c=.x11.o)
OBJ_WAYLAND = $(SRC:.c=.wayland.o)

# Executable name
EXE = sglogout

# Backend-specific flags
CFLAGS_X11 = `pkg-config --cflags gtk+-3.0` -DX11 -fPIC
CFLAGS_WAYLAND = `pkg-config --cflags gtk+-3.0 gtk-layer-shell-0` -Dwayland

LIBS_X11 = `pkg-config --libs gtk+-3.0` -lX11 ./sgxpos/sgxpos.o
LIBS_WAYLAND = `pkg-config --libs gtk+-3.0 gtk-layer-shell-0`

# Build selection logic
ifeq ($(WAYLAND),1)
all: wayland
else ifeq ($(X11),1)
all: x11
else
all: wayland x11
endif

# Compile rules per target

x11: $(OBJ_X11)
	$(CC) $(CFLAGS_X11) -o $(EXE)-x11 $(OBJ_X11) $(LIBS_X11)

wayland: $(OBJ_WAYLAND)
	$(CC) $(CFLAGS_WAYLAND) -o $(EXE)-wayland $(OBJ_WAYLAND) $(LIBS_WAYLAND)

# Compile .c to .x11.o
%.x11.o: %.c
	$(CC) $(CFLAGS_X11) -c -o $@ $<

# Compile .c to .wayland.o
%.wayland.o: %.c
	$(CC) $(CFLAGS_WAYLAND) -c -o $@ $<

debug: $(SRC)
	$(CC) $(CFLAGS_X11) -g $(SRC) -o debug $(LIBS_X11)

clean:
	rm -f *.o *.x11.o *.wayland.o $(EXE)-x11 $(EXE)-wayland debug
