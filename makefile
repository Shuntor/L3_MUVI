
# définition des cibles particulières
.PHONY: clean, mrproper
 
# désactivation des règles implicites
#.SUFFIXES:

# définition des variables
CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
SOURCES=mainClient.c interfaceClient.c fonctions.c
SOURCES_SERV=mainServeur.c fonctions.c serveur.c
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_SERV=$(SOURCES_SERV:.c=.o)
EXECUTABLE=client serveur

# all
all: $(EXECUTABLE)
	
client: $(OBJECTS) 
	$(CC) -o $@ $^ $(LDFLAGS) 

serveur: $(OBJECTS_SERV)
	$(CC) -o $@ $^ $(LDFLAGS) 

.c.o:
	$(CC) -o $@ -c $< $(CFLAGS) 

# clean
clean:
		rm -rf *.bak rm -rf *.o
 
# mrproper
mrproper: clean
		rm -rf $(EXECUTABLE)

