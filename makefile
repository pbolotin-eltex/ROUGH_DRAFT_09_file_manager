# Make

.PHONY = clean debug
KEYS :=
TMP  :=
TMPL :=
LIBS := -lpanel_g -lncurses_g
CC := gcc

file_manager : main.o file_manager.o user_interface.o
		$(eval TMP:=-I./ncurses_debug/include/)
		$(eval TMPL:=-L./ncurses_debug/lib/)
		$(CC) $(TMP) $(KEYS) main.o\
							 file_manager.o\
							 user_interface.o\
							 -o file_manager $(TMPL) $(LIBS)

debug : main.o file_manager.o user_interface.o
		$(eval KEYS:=-g)
		$(eval TMP:=-I./ncurses_debug/include/)
		$(eval TMPL:=-L./ncurses_debug/lib/)
		$(CC) $(TMP) $(KEYS) main.o\
							 file_manager.o\
							 user_interface.o\
							 -o file_manager $(TMPL) $(LIBS)

main.o : main.c
		$(CC) $(TMP) $(KEYS) -c main.c\
							 -o main.o $(TMPL) $(LIBS)

file_manager.o : file_manager.c file_manager.h
		$(CC) $(TMP) $(KEYS) -c file_manager.c\
							 -o file_manager.o $(TMPL) $(LIBS)

user_interface.o : user_interface.c user_interface.h
		$(CC) $(TMP) $(KEYS) -c user_interface.c\
							 -o user_interface.o $(TMPL) $(LIBS)

clean :
		rm -f *.o *.gch file_manager a.out
