
# définition des cibles particulières
.PHONY: clean, mrproper
 
# désactivation des règles implicites
#.SUFFIXES:

# définition des variables
CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
SOURCES=mainClient.c interfaceClient.c fonctions.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=client

# all
all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $^ $(LDFLAGS) 

.c.o:
	$(CC) -o $@ -c $< $(CFLAGS) 

# clean
clean:
		rm -rf *.bak rm -rf *.o
 
# mrproper
mrproper: clean
		rm -rf $(EXEC)

