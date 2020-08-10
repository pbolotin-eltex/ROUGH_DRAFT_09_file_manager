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
    WINDOW* cmd;
    PANEL*  l_panel;
    PANEL*  r_panel;
    PANEL*  message_panel;
    PANEL*  cmd_panel;
    PANEL*  main_panel;
    int l_wnd_active_flag;
    int r_wnd_active_flag;
    int show_message_flag;
    int on_off_flag;
} user_interface;

int user_interface_what_user_did(user_interface* ui);

int user_interface_init(user_interface* ui);

int user_interface_change_screen_size(user_interface* ui);

int user_interface_change_active_panel(user_interface* ui);
int user_interface_deactivate_panels(user_interface* ui);
int user_interface_reactivate_panels(user_interface* ui);

int user_interface_need_show_message(user_interface* ui);
int user_interface_show_message(user_interface* ui);

int user_interface_show_on_screen(user_interface* ui);

int user_interface_number_to_cmd(user_interface* ui, int number);

int user_interface_string_to_cmd(user_interface* ui, char* str);

int user_interface_final(user_interface* ui);

int user_interface_on(user_interface* ui);

int user_interface_off(user_interface* ui);

int user_interface_on_off_switcher(user_interface* ui);

#endif
