# file_manager

Simple two panel file manager ~ nightmare commander

## compilation

make

make debug (only if you have debug static versions of ncurses, panel, menu libs)

## usage

now need to use command like this

./file_manager 2> some_file.txt

because of ncurses will be corrupted if stderr won't be redirected

## KNOWN BUGS

many memory leaks

no correct finalization of ncurses
