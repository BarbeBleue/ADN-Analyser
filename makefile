# options de compilation
CC =gcc
CCFLAGS = -g -Wall 

# fichiers du projet
SRC = main.c utile.c methode1.c methode2.c
OBJ = $(SRC:.c=.o)
EXEC = ADN


# règle initiale
all: $(EXEC) 

# dépendance des .h
main.o: struct.h utile.h methode1.h methode2.h
utile.o: struct.h
methode1.o: struct.h utile.h
methode2.o: struct.h utile.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ 

# règles supplémentaires
clean:
	@rm -rf *.o
