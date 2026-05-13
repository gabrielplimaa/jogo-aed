

CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

SRCDIR = src
BINDIR = build

SRCS = $(SRCDIR)/main.c      \
       $(SRCDIR)/jogo.c      \
       $(SRCDIR)/lista.c     \
       $(SRCDIR)/objeto.c    \
       $(SRCDIR)/jogador.c   \
       $(SRCDIR)/ranking.c   \
       $(SRCDIR)/ordenacao.c \
       $(SRCDIR)/interface.c \
       $(SRCDIR)/menu.c

UNAME := $(shell uname 2>/dev/null || echo Windows)

ifeq ($(UNAME), Darwin)
	TARGET  = $(BINDIR)/pega-o-frevo
	LDFLAGS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit \
	          -framework CoreAudio -framework CoreVideo
else ifeq ($(UNAME), Windows)
	TARGET  = $(BINDIR)/pega-o-frevo.exe
	LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
	TARGET  = $(BINDIR)/pega-o-frevo
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

.PHONY: all clean run dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(BINDIR) data

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -rf $(BINDIR)
