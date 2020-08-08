/**********************************************************************
 * File manager user interface part, header
 *********************************************************************/
#ifndef _FILE_MANAGER_USER_INTERFACE_H_
#define _FILE_MANAGER_USER_INTERFACE_H_

#include <curses.h>
#include <panel.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct user_interface {
    WINDOW* main_wnd;
    WINDOW* l_wnd;
    WINDOW* r_wnd;
    WINDOW* message;
    WINDOW* string;
} user_interface;

int user_interface_init(user_interface* ui);

int user_interface_final(user_interface* ui);

int user_interface_on(user_interface* ui);

int user_interface_off(user_interface* ui);

#endif
