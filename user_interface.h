/**********************************************************************
 * File manager user interface part, header
 *********************************************************************/
#ifndef _FILE_MANAGER_USER_INTERFACE_H_
#define _FILE_MANAGER_USER_INTERFACE_H_

#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct dir_menu_names {
    char **dirs;
    unsigned int dirs_count;
    char **reg;
    unsigned int reg_count;
    char **lnk;
    unsigned int lnk_count;
    char **sock;
    unsigned int sock_count;
    char **fifo;
    unsigned int fifo_count;
    char **blk;
    unsigned int blk_count;
    char **chr;
    unsigned int chr_count;
    char **unk_dirs;
    unsigned int unk_dirs_count;
    char **unk_entr;
    unsigned int unk_entr_count;
    
    char *cwd;
    int need_to_free_strings_flag;
    int need_to_free_arrays_flag;
    int need_to_free_cwd_flag;
} dir_menu_names;

typedef struct user_interface {
    WINDOW* main_wnd;
    WINDOW* l_wnd;
    WINDOW* r_wnd;
    char* message_text;
    WINDOW* message;
    WINDOW* cmd;
    PANEL*  l_panel;
    PANEL*  r_panel;
    PANEL*  message_panel;
    PANEL*  cmd_panel;
    PANEL*  main_panel;
    dir_menu_names* l_menu_names;
    dir_menu_names* r_menu_names;
    ITEM** l_menu_content;
    ITEM** r_menu_content;
    unsigned int l_menu_cursor_pos;
    unsigned int r_menu_cursor_pos;
    unsigned int l_menu_size;
    unsigned int r_menu_size;
    MENU* l_menu;
    MENU* r_menu;
    WINDOW* l_der_menu_win;
    WINDOW* r_der_menu_win;
    int l_wnd_active_flag;
    int r_wnd_active_flag;
    int show_message_flag;
    int on_off_flag;
} user_interface;

int user_interface_what_user_did(user_interface* ui);

int user_interface_init(user_interface* ui);

int user_interface_change_screen_size(user_interface* ui);

int user_interface_is_left_panel_active(user_interface* ui);
int user_interface_is_right_panel_active(user_interface* ui);
int user_interface_change_active_panel(user_interface* ui);
int user_interface_deactivate_panels(user_interface* ui);
int user_interface_reactivate_panels(user_interface* ui);

int user_interface_need_show_message(user_interface* ui, char* message_text);
int user_interface_show_message(user_interface* ui);

int user_interface_show_on_screen(user_interface* ui);

int user_interface_number_to_cmd(user_interface* ui, int number);

int user_interface_string_to_cmd(user_interface* ui, char* str);

int user_interface_final(user_interface* ui);

int user_interface_on(user_interface* ui);

int user_interface_off(user_interface* ui);

int user_interface_on_off_switcher(user_interface* ui);

int user_interface_l_menu_prepare_replace(user_interface* ui);
int user_interface_l_menu_post(user_interface* ui);
int user_interface_l_menu_unpost(user_interface* ui);

int user_interface_active_menu_cursor_down(user_interface* ui);
int user_interface_active_menu_cursor_up(user_interface* ui);
int user_interface_active_menu_cursor_page_down(user_interface* ui);
int user_interface_active_menu_cursor_page_up(user_interface* ui);
int user_interface_active_menu_cursor_to_last_pos(user_interface* ui);
int user_interface_active_menu_cursor_to_first_pos(user_interface* ui);

int user_interface_active_menu_get_cursor_position(user_interface* ui);

/*Menu experiment*/
/*
int user_interface_menu(user_interface* ui);
*/
#endif
