# Make

.PHONY = clean debug
KEYS :=
TMP  :=
TMPL :=
LIBS_G := -lmenu_g -lpanel_g -lncurses_g
LIBS := -lmenu -lpanel -lncurses
CC := gcc

file_manager : main.o file_manager.o user_interface.o panel_data.o converter.o
#		$(eval TMP:=-I./ncurses_debug/include/)
#		$(eval TMPL:=-L./ncurses_debug/lib/)
		$(CC) $(TMP) $(KEYS) main.o\
							 file_manager.o\
							 user_interface.o\
							 panel_data.o\
							 converter.o\
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
							 
panel_data.o : panel_data.c panel_data.h
		$(CC) $(TMP) $(KEYS) -c panel_data.c\
							 -o panel_data.o $(TMPL) $(LIBS)
							 
converter.o : converter.c converter.h
		$(CC) $(TMP) $(KEYS) -c converter.c\
							 -o converter.o $(TMPL) $(LIBS)


debug : main_g.o file_manager_g.o user_interface_g.o panel_data_g.o converter_g.o
		$(eval KEYS:=-g)
		$(eval TMP:=-I./ncurses_debug/include/)
		$(eval TMPL:=-L./ncurses_debug/lib/)
		$(CC) $(TMP) $(KEYS) main_g.o\
							 file_manager_g.o\
							 user_interface_g.o\
							 panel_data_g.o\
							 converter_g.o\
							 -o file_manager_g $(TMPL) $(LIBS_G)

main_g.o : main.c
		$(eval KEYS:=-g)
		$(CC) $(TMP) $(KEYS) -c main.c\
							 -o main_g.o $(TMPL) $(LIBS_G)

file_manager_g.o : file_manager.c file_manager.h
		$(eval KEYS:=-g)
		$(CC) $(TMP) $(KEYS) -c file_manager.c\
							 -o file_manager_g.o $(TMPL) $(LIBS_G)

user_interface_g.o : user_interface.c user_interface.h
		$(eval KEYS:=-g)
		$(CC) $(TMP) $(KEYS) -c user_interface.c\
							 -o user_interface_g.o $(TMPL) $(LIBS_G)
							 
panel_data_g.o : panel_data.c panel_data.h
		$(eval KEYS:=-g)
		$(CC) $(TMP) $(KEYS) -c panel_data.c\
							 -o panel_data_g.o $(TMPL) $(LIBS_G)
							 
converter_g.o : converter.c converter.h
		$(eval KEYS:=-g)
		$(CC) $(TMP) $(KEYS) -c converter.c\
							 -o converter_g.o $(TMPL) $(LIBS_G)


clean :
		rm -f *.o *.gch file_manager file_manager_g a.out
