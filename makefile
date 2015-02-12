SRCDIR=src
BINDIR=bin
OBJDIR=obj

SOURCES_CLIENT=transport.c fonctions.c test_client.c
SOURCES_SERVEUR=transport.c fonctions.c test_serveur.c
OBJECTSPRE_C=$(SOURCES_CLIENT:%.c=%.o)
OBJECTSPRE_S=$(SOURCES_SERVEUR:%.c=%.o)
OBJECTSLINKER_C=$(OBJECTSPRE_C:%=$(OBJDIR)/%)
OBJECTSLINKER_S=$(OBJECTSPRE_S:%=$(OBJDIR)/%)
EXECUTABLE=client serveur

CC=gcc
CFLAGS=-c -W -Wall -I$(SRCDIR)
LDFLAGS=

all: $(EXECUTABLE)

client: $(OBJECTSPRE_C)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTSLINKER_C) -o $(BINDIR)/$@

serveur: $(OBJECTSPRE_S)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTSLINKER_S) -o $(BINDIR)/$@

%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

.PHONY=clean

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*
