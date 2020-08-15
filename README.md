# file_manager

Simple two panel file manager ~ nightmare commander

## compilation

make

make debug (if only you have right place for debug static versions of ncurses, panel, menu libs)

## usage

after work of make, exec:

./file_manager

or (if you compile debug version):

./file_manager_g

## KNOWN BUGS

Many "Still reachable" leaks was found by valgrind, but I've read stackoverflow and think that's not so bad:

:-)

https://stackoverflow.com/questions/3840582/still-reachable-leak-detected-by-valgrind

Most of the leaks are associated with "scandir" system function

It used more many times than it need for learning purposes and it can be replaced in the future.

Also: now it just one panel commander, because of no need to do two panel when the one panel version has errors.