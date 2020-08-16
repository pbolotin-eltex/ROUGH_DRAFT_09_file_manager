# file_manager

Simple two panel file manager ~ nightmare commander

## description

main.c - just the high level sequence of what program will do.

file_manager.h, file_manager.c - the application logic: init, work with user, end.

panel_data.h, panel_data.c - module to work with the system datatypes and requests.

user_interface.h, user_interface.c - module to give the user chance to understand what they can do.

converter.h, converter.c - module to do work between panel_data and user_interface (convert datatypes).

## compilation

make

make debug (if only you have right place for debug static versions of ncurses, panel, menu libs)

## usage

after work of make, exec:

./file_manager

or (if you compile debug version):

./file_manager_g

Now you can walk around your system directories like you do it in the midnight commander

Be careful! If you do something wrong, program will show you the red message!

You can also use F1 key, to view how it is, when this red message is showing to user.

Also F2 key, temporary shut down ncurses, and show you what was below at that time.

It will take just 5 seconds, and after that - ncurses will rise again!

What you can do, when you get full joy of work with the nightmare commander?

Quit to your system through the F10 key pressing.

Have joy!

## KNOWN BUGS

Many "Still reachable" leaks was found by valgrind, but I've read stackoverflow and think that's not so bad:

:-)

https://stackoverflow.com/questions/3840582/still-reachable-leak-detected-by-valgrind

Most of the leaks are associated with "scandir" system function and with the ncurses routines.