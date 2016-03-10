CC=gcc
CFLAGS=
LDFLAGS=
EXEC=Graph

all: $(EXEC)

$(EXEC): bin/utils.o bin/listedble.o bin/graphes.o bin/main.o bin/parcours.o bin/acpm.o
	gcc -o $@ $^ $(LDFAGS)

%.o:	%.c
	gcc -o $@ -c $< $(CFLAGS)

bin/%.o: lib/%.c
	gcc -o $@ -c $< $(CFLAGS)

bin/%.o: src/%.c lib/utils.h lib/listedble.h lib/graphes.h
	gcc -o $@ -c $< $(CFLAGS)

clean :
	rm -rf bin/*.o && rm -rf $(EXEC)

#
# Help varaible interne
#
# $@ : nom de la cible
# $< : nom de la premiere dependance
# $^ : liste des dépendances
# $? : dépendance plus récentes que la cible
# $* : nom du fichier sans le suffixe
#
#
