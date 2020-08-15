/**********************************************************************
 * File manager user interface part, implementation
 *********************************************************************/
#include "user_interface.h"

#define DEBUG

int user_interface_init(user_interface* ui) {
    /* Init main window */
    ui->main_wnd = initscr();
    
    /* Init the working mode */
    cbreak();
    noecho();
    keypad(ui->main_wnd, TRUE);
    
    /* Init the colors */
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_GREEN, COLOR_BLUE);
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
    
    /* Define sizes */
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);    
    
    /* Init view of main window */
    wbkgd(ui->main_wnd, COLOR_PAIR(1));
    box(ui->main_wnd, 0, 0);
    mvwaddstr(ui->main_wnd, 0,3, "main wnd");
    ui->main_panel = new_panel(ui->main_wnd);
    
    /* Init left window */
    ui->l_wnd = newwin(main_y-3, main_x/2, 0, 0);
    wbkgd(ui->l_wnd, COLOR_PAIR(2));
    box(ui->l_wnd, 0, 0);
    mvwaddstr(ui->l_wnd, 0,3, "left wnd");
    ui->l_wnd_active_flag = 0;
    ui->l_panel = new_panel(ui->l_wnd);
    
    /* Init right window */
    ui->r_wnd = newwin(main_y-3, main_x - main_x/2, 0, main_x/2);
    wbkgd(ui->r_wnd, A_BOLD|COLOR_PAIR(2));
    box(ui->r_wnd, 0, 0);
    mvwaddstr(ui->r_wnd, 0,3, "right wnd");
    ui->r_wnd_active_flag = 1;
    ui->r_panel = new_panel(ui->r_wnd);
    
    /* Init message window */
    
    /* It need up to 5 lines of main_wnd in center */
    /* Find limits for that */
    int message_y, message_x, start_y, start_x;
    if(main_y >= 5) {
        message_y = 5;
        start_y = main_y/2 - 2;
    } else {
        message_y = main_y;
        start_y = 0;
    }
    start_x = 0;
    message_x = main_x;
    
    ui->message = newwin(message_y, message_x, start_y, start_x);
    wbkgd(ui->message, A_BOLD|COLOR_PAIR(3));
    box(ui->message, 0, 0);
    mvwaddstr(ui->message, 0, 3, "message");
    ui->show_message_flag = 0;
    ui->message_panel = new_panel(ui->message);
    hide_panel(ui->message_panel);
    ui->message_text = "";
    
    /* Init command line window */
    ui->cmd = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->cmd, COLOR_PAIR(1));
    box(ui->cmd, 0, 0);
    mvwaddstr(ui->cmd, 0,3, "command line");
    ui->cmd_panel = new_panel(ui->cmd);
    
    /* Set flag ON */
    ui->on_off_flag = 1;
    
    /* Init place for menu items */
    /* It will be filled by converter module */
    /* After that will be created menues by this data */
    ui->l_menu_names = (dir_menu_names*)calloc(1, sizeof(dir_menu_names));
    ui->r_menu_names = (dir_menu_names*)calloc(1, sizeof(dir_menu_names));
    /* Set the cursors indexes as zeroes */
    ui->l_menu_cursor_pos = 0;
    ui->r_menu_cursor_pos = 0;
    return 0;
}

int user_interface_reinit(user_interface* ui) {
    /* Init main window */
    ui->main_wnd = initscr();
    
    /* Init the working mode */
    cbreak();
    noecho();
    keypad(ui->main_wnd, TRUE);
    
    /* Init the colors */
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_GREEN, COLOR_BLUE);
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
    
    /* Define sizes */
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);    
    
    /* Init view of main window */
    wbkgd(ui->main_wnd, COLOR_PAIR(1));
    box(ui->main_wnd, 0, 0);
    mvwaddstr(ui->main_wnd, 0,3, "main wnd");
    ui->main_panel = new_panel(ui->main_wnd);
    
    /* Init left window */
    ui->l_wnd = newwin(main_y-3, main_x/2, 0, 0);
    box(ui->l_wnd, 0, 0);
    mvwaddstr(ui->l_wnd, 0,3, "left wnd");
    ui->l_panel = new_panel(ui->l_wnd);
    
    /* Init right window */
    ui->r_wnd = newwin(main_y-3, main_x - main_x/2, 0, main_x/2);
    box(ui->r_wnd, 0, 0);
    mvwaddstr(ui->r_wnd, 0,3, "right wnd");
    ui->r_panel = new_panel(ui->r_wnd);
    
    /* Reactivate panels */
    user_interface_reactivate_panels(ui);
    
    /* Init message window */
    
    /* It need up to 5 lines of main_wnd in center */
    /* Find limits for that */
    int message_y, message_x, start_y, start_x;
    if(main_y >= 5) {
        message_y = 5;
        start_y = main_y/2 - 2;
    } else {
        message_y = main_y;
        start_y = 0;
    }
    start_x = 0;
    message_x = main_x;
    
    ui->message = newwin(message_y, message_x, start_y, start_x);
    wbkgd(ui->message, A_BOLD|COLOR_PAIR(3));
    box(ui->message, 0, 0);
    mvwaddstr(ui->message, 0, 3, "message");
    ui->show_message_flag = 0;
    ui->message_panel = new_panel(ui->message);
    hide_panel(ui->message_panel);
    
    /* Init command line window */
    ui->cmd = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->cmd, COLOR_PAIR(1));
    box(ui->cmd, 0, 0);
    mvwaddstr(ui->cmd, 0,3, "command line");
    ui->cmd_panel = new_panel(ui->cmd);
    
    /* Set flag ON */
    ui->on_off_flag = 1;
    
    /* Here difference with user_interface_init */
    /* memory won't be allocated for menu names */
    /* Will used that exist */
    /*
    ui->l_menu_names = (dir_menu_names*)calloc(1, sizeof(dir_menu_names));
    ui->r_menu_names = (dir_menu_names*)calloc(1, sizeof(dir_menu_names));
    */
    return 0;
}

int user_interface_what_user_did(user_interface* ui) {
    return wgetch(ui->main_wnd);
}

int user_interface_change_screen_size(user_interface* ui) {
    /* New main wnd parameters */
    //del_panel(ui->main_panel);
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);
    box(ui->main_wnd, 0, 0);
    mvwaddstr(ui->main_wnd, 0,3, "main wnd");
    ui->main_panel = new_panel(ui->main_wnd);
    
    /* New left wnd parameters */
    del_panel(ui->l_panel);
    delwin(ui->l_wnd);
    ui->l_wnd = newwin(main_y-3, main_x/2, 0, 0);
    wbkgd(ui->l_wnd, COLOR_PAIR(2));
    box(ui->l_wnd, 0, 0);
    mvwaddstr(ui->l_wnd, 0,3, "left wnd");
    ui->l_panel = new_panel(ui->l_wnd);
    
    /* New right wnd parameters */
    del_panel(ui->r_panel);
    delwin(ui->r_wnd);
    ui->r_wnd = newwin(main_y-3, main_x - main_x/2, 0, main_x/2);
    wbkgd(ui->r_wnd, A_BOLD|COLOR_PAIR(2));
    box(ui->r_wnd, 0, 0);
    mvwaddstr(ui->r_wnd, 0,3, "right wnd");
    ui->r_panel = new_panel(ui->r_wnd);
    
    /* New message window parameters */
    /* It need up to 5 lines of main_wnd in center */
    /* Find limits for that */
    int message_y, message_x, start_y, start_x;
    if(main_y >= 5) {
        message_y = 5;
        start_y = main_y/2 - 2;
    } else {
        message_y = main_y;
        start_y = 0;
    }
    start_x = 0;
    message_x = main_x;
    
    del_panel(ui->message_panel);
    delwin(ui->message);
    ui->message = newwin(message_y, message_x, start_y, start_x);
    wbkgd(ui->message, A_BOLD|COLOR_PAIR(3));
    box(ui->message, 0, 0);
    mvwaddstr(ui->message, 0, 3, "message");
    ui->show_message_flag = 0;
    ui->message_panel = new_panel(ui->message);
    hide_panel(ui->message_panel);
    
    /* New command line window parameters */
    del_panel(ui->cmd_panel);
    delwin(ui->cmd);
    ui->cmd = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->cmd, COLOR_PAIR(1));
    box(ui->cmd, 0, 0);
    mvwaddstr(ui->cmd, 0,3, "command line");
    ui->cmd_panel = new_panel(ui->cmd);
    
    /* Renew menues */
    user_interface_l_menu_unpost(ui);
    user_interface_l_menu_post(ui);
    return 0;
}

int user_interface_change_active_panel(user_interface* ui) {
    if(1 == ui->l_wnd_active_flag) {
        user_interface_string_to_cmd(ui, "change to r");
        ui->l_wnd_active_flag = 0;
        wbkgd(ui->l_wnd, COLOR_PAIR(2));
        ui->r_wnd_active_flag = 1;
        wbkgd(ui->r_wnd, A_BOLD|COLOR_PAIR(2));
    } else {
        user_interface_string_to_cmd(ui, "change to l");
        ui->l_wnd_active_flag = 1;
        wbkgd(ui->l_wnd, A_BOLD|COLOR_PAIR(2));
        ui->r_wnd_active_flag = 0;
        wbkgd(ui->r_wnd, COLOR_PAIR(2));
    }
    return 0;
}

int user_interface_is_left_panel_active(user_interface* ui) {
    return ui->l_wnd_active_flag;
}

int user_interface_is_right_panel_active(user_interface* ui) {
    return ui->r_wnd_active_flag;
}

int user_interface_deactivate_panels(user_interface* ui) {
    wbkgd(ui->r_wnd, COLOR_PAIR(2));
    wbkgd(ui->l_wnd, COLOR_PAIR(2));
    return 0;
}

int user_interface_reactivate_panels(user_interface* ui) {
    if(1 == ui->l_wnd_active_flag) {
        wbkgd(ui->l_wnd, A_BOLD|COLOR_PAIR(2));
        wbkgd(ui->r_wnd, COLOR_PAIR(2));
    } else {
        wbkgd(ui->l_wnd, COLOR_PAIR(2));
        wbkgd(ui->r_wnd, A_BOLD|COLOR_PAIR(2));
    }
    return 0;
}

int user_interface_need_show_message(user_interface* ui, char* text) {
    ui->show_message_flag = 1;
    ui->message_text = text;
    return 0;
}

int user_interface_show_message(user_interface* ui) {
    if(ui->show_message_flag) {
        user_interface_deactivate_panels(ui);
        /* Add text to message */
        wmove(ui->message, 1, 1);
        waddstr(ui->message, ui->message_text);
        show_panel(ui->message_panel);
        ui->show_message_flag = 0;
    } else {
        user_interface_reactivate_panels(ui);
        hide_panel(ui->message_panel);
    }
    return 0;
}

int user_interface_show_on_screen(user_interface* ui) {
    update_panels();
    doupdate();
    return 0;
}

int user_interface_number_to_cmd(user_interface* ui, int number) {
    wmove(ui->cmd, 1,1);
    wprintw(ui->cmd, "%d", number);
    return 0;
}

int user_interface_string_to_cmd(user_interface* ui, char *str) {
    wmove(ui->cmd, 1,1);
    wprintw(ui->cmd, "%s", str);
    return 0;
}

int user_interface_final(user_interface* ui) {
    user_interface_l_menu_prepare_replace(ui);
    
    /* Free memory for structs */
    free(ui->l_menu_names);
    ui->l_menu_names = NULL;
    free(ui->r_menu_names);
    ui->r_menu_names = NULL;
    
    ui->l_menu_content = NULL;
    ui->r_menu_content = NULL;

    endwin();
/* Finalize if debug library was used */
#ifdef DEBUG    
    exit_curses(0);
#endif
    return 0;
}

int user_interface_stop(user_interface* ui) {
    /* unpost menues */
    user_interface_l_menu_unpost(ui);
    
    /* del panels */
    del_panel(ui->r_panel);
    del_panel(ui->l_panel);
    del_panel(ui->message_panel);
    del_panel(ui->cmd_panel);
    del_panel(ui->main_panel);
    
    /* end windows */
    endwin();
    return 0;
}

int user_interface_on_off_switcher(user_interface* ui) {
    if(1 == ui->on_off_flag) {
        user_interface_off(ui);
    } else {
        user_interface_on(ui);
    }
    return 0;
}

int user_interface_on(user_interface* ui) {
    user_interface_reinit(ui);
    user_interface_l_menu_post(ui);
    ui->on_off_flag = 1;
    return 0;
}

int user_interface_off(user_interface* ui) {
    user_interface_stop(ui);
    ui->on_off_flag = 0;
    return 0;
}

int user_interface_format_filename_to_max_length_in_menu(user_interface* ui,\
                                                         const char* filename,\
                                                         char* be_formatted,\
                                                         int max_length) {
    int i;
    int base_len = strlen(filename);
    if(base_len < max_length) {
        for(i = 0; i < max_length; i++) {
            if(i < base_len) {
                be_formatted[i] = filename[i];
            } else {
                be_formatted[i] = (char)(' ');
            }
        }
    } else {
        if(max_length % 2) {
            for(i = 0; i < max_length/2; i++) {
                be_formatted[i] = filename[i];
            }
            be_formatted[i] = (char)('~');
            i++;
            for(i; i < max_length; i++) {
                be_formatted[i] = filename[base_len - max_length + i];
            }
        } else {
            for(i = 0; i < max_length/2; i++) {
                be_formatted[i] = filename[i];
            }
            be_formatted[i] = (char)('~');
            i++;
            for(; i < max_length; i++) {
                be_formatted[i] = filename[base_len - max_length + i];
            }
        }
    }
    be_formatted[i] = (char)('\0');
    return 0;
}

int user_interface_l_menu_prepare_replace(user_interface* ui) {
    ui->l_menu_cursor_pos = 0;
    
    /* Free menu infrastructures */
    user_interface_l_menu_unpost(ui);
    
    /* Free memory of strdup's allocations */
    int i;
    if(ui->l_menu_names->need_to_free_strings_flag) {
        int all = 0;
        for(i = 0; i < ui->l_menu_names->dirs_count; all++, i++) {
            free(ui->l_menu_names->dirs[i]);
        }
        for(i = 0; i < ui->l_menu_names->reg_count; all++, i++) {
            free(ui->l_menu_names->reg[i]);
        }
        for(i = 0; i < ui->l_menu_names->lnk_count; all++, i++) {
            free(ui->l_menu_names->lnk[i]);
        }
        for(i = 0; i < ui->l_menu_names->sock_count; all++, i++) {
            free(ui->l_menu_names->sock[i]);
        }
        for(i = 0; i < ui->l_menu_names->fifo_count; all++, i++) {
            free(ui->l_menu_names->fifo[i]);
        }
        for(i = 0; i < ui->l_menu_names->blk_count; all++, i++) {
            free(ui->l_menu_names->blk[i]);
        }
        for(i = 0; i < ui->l_menu_names->chr_count; all++, i++) {
            free(ui->l_menu_names->chr[i]);
        }
        for(i = 0; i < ui->l_menu_names->unk_dirs_count; all++, i++) {
            free(ui->l_menu_names->unk_dirs[i]);
        }
        for(i = 0; i < ui->l_menu_names->unk_entr_count; all++, i++) {
            free(ui->l_menu_names->unk_entr[i]);
        }
        ui->l_menu_names->need_to_free_strings_flag = 0;
    }
    /* Free memory of malloc's allocations */
    if(ui->l_menu_names->need_to_free_arrays_flag) {
        free(ui->l_menu_names->dirs);
        free(ui->l_menu_names->reg);
        free(ui->l_menu_names->lnk);
        free(ui->l_menu_names->sock);
        free(ui->l_menu_names->fifo);
        free(ui->l_menu_names->blk);
        free(ui->l_menu_names->chr);
        free(ui->l_menu_names->unk_dirs);
        free(ui->l_menu_names->unk_entr);
        ui->l_menu_names->need_to_free_arrays_flag = 0;
    }
    /* Free memory of cwd by strdup's allocation */
    if(ui->l_menu_names->need_to_free_cwd_flag) {
        free(ui->l_menu_names->cwd);
        ui->l_menu_names->cwd = NULL;
        ui->l_menu_names->need_to_free_cwd_flag = 0;
    }
    return 0;
}

int user_interface_l_menu_post(user_interface* ui) {
    /* Get size of window where will be placed menu */
    int wnd_size_y, wnd_size_x;
    getmaxyx(ui->l_wnd, wnd_size_y, wnd_size_x);
    
    int how_many_elements = ui->l_menu_names->dirs_count+\
                            ui->l_menu_names->reg_count+\
                            ui->l_menu_names->lnk_count+\
                            ui->l_menu_names->sock_count+\
                            ui->l_menu_names->fifo_count+\
                            ui->l_menu_names->blk_count+\
                            ui->l_menu_names->chr_count+\
                            ui->l_menu_names->unk_dirs_count+\
                            ui->l_menu_names->unk_entr_count;
    ui->l_menu_size = how_many_elements;
    /* Place for (ITEM*) array */
    ui->l_menu_content = (ITEM**)calloc((how_many_elements + 1), sizeof(ITEM*));
    
    /* Place for formatted filenames (near panel width) */
    ui->l_menu_names->format = (char**)calloc(how_many_elements, sizeof(char*));
    if(NULL == ui->l_menu_names->format) {
        perror("can't calloc for formatted_filenames");
        exit(EXIT_FAILURE);
    }
    int i;
    for(i = 0; i < how_many_elements; i++) {
        ui->l_menu_names->format[i] = (char*)calloc(1, sizeof(char)*(wnd_size_x));
        if(NULL == ui->l_menu_names->format[i]) {
            perror("can't calloc for formatted_filenames[]");
            exit(EXIT_FAILURE);
        }
    }
    ui->l_menu_names->need_to_free_format_flag = 1;
    ui->l_menu_names->format_size = how_many_elements;
    
    /* Format filenames and fill menu items by them */
    int format_len = wnd_size_x - 6;
    int all = 0;
    for(i = 0; i < ui->l_menu_names->dirs_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->dirs[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "/D");
    }
    for(i = 0; i < ui->l_menu_names->reg_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->reg[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "rg");
    }
    for(i = 0; i < ui->l_menu_names->lnk_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->lnk[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "lk");
    }
    for(i = 0; i < ui->l_menu_names->sock_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->sock[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "sk");
    }
    for(i = 0; i < ui->l_menu_names->fifo_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->fifo[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "io");
    }
    for(i = 0; i < ui->l_menu_names->blk_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->blk[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "bl");
    }
    for(i = 0; i < ui->l_menu_names->chr_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->chr[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "ch");
    }
    for(i = 0; i < ui->l_menu_names->unk_dirs_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->unk_dirs[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "UD");
    }
    for(i = 0; i < ui->l_menu_names->unk_entr_count; all++, i++) {
        user_interface_format_filename_to_max_length_in_menu(ui,\
                                             ui->l_menu_names->unk_entr[i],\
                                             ui->l_menu_names->format[all],\
                                             format_len);
        ui->l_menu_content[all] = new_item(ui->l_menu_names->format[all], "UE");
    }
    /* Final NULL */
    ui->l_menu_content[all] = new_item("", "");
    /* Create new menu */
    ui->l_menu = new_menu(ui->l_menu_content);
    /* Bind to window */
    set_menu_win(ui->l_menu, ui->l_wnd);
    /* Create derived window with menu (same memory as parent) */
    set_menu_sub(ui->l_menu, derwin(ui->l_wnd, wnd_size_y-2, wnd_size_x-2, 1, 1));
    /* set menu format */
    set_menu_format(ui->l_menu, wnd_size_y-2, 1);
    /* post menu */
    int ret = post_menu(ui->l_menu);
    /* set cursor position */
    set_current_item(ui->l_menu, ui->l_menu_content[ui->l_menu_cursor_pos]);
    return 0;
}

int user_interface_l_menu_unpost(user_interface* ui) {
    unpost_menu(ui->l_menu);
    delwin(menu_sub(ui->l_menu));
    free_menu(ui->l_menu);
    ui->l_menu = NULL;
    int i;
    for(i = 0; i < ui->l_menu_size; i++) {
        free_item(ui->l_menu_content[i]);
    }
    ui->l_menu_size = 0;
    free(ui->l_menu_content);
    
    /* Free memory of formated names for menu */
    for(i = 0; i < ui->l_menu_names->format_size; i++) {
        free(ui->l_menu_names->format[i]);
    }
    free(ui->l_menu_names->format);
    ui->l_menu_names->format_size = 0;
    return 0;
}

int user_interface_active_menu_cursor_down(user_interface* ui) {
    if(ui->l_wnd_active_flag) {
        menu_driver(ui->l_menu, REQ_DOWN_ITEM);
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        menu_driver(ui->r_menu, REQ_DOWN_ITEM);
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_cursor_up(user_interface* ui) {
    if(ui->l_wnd_active_flag) {
        menu_driver(ui->l_menu, REQ_UP_ITEM);
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        menu_driver(ui->r_menu, REQ_UP_ITEM);
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_cursor_page_down(user_interface* ui) {
    int ret = 0;
    if(ui->l_wnd_active_flag) {
        ret = menu_driver(ui->l_menu, REQ_SCR_DPAGE);
        switch(ret) {
        case E_REQUEST_DENIED:
            menu_driver(ui->l_menu, REQ_LAST_ITEM);
            break;
        }
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        ret = menu_driver(ui->r_menu, REQ_SCR_DPAGE);
        switch(ret) {
        case E_REQUEST_DENIED:
            menu_driver(ui->r_menu, REQ_LAST_ITEM);
            break;
        }
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_cursor_page_up(user_interface* ui) {
    int ret = 0;
    if(ui->l_wnd_active_flag) {
        ret = menu_driver(ui->l_menu, REQ_SCR_UPAGE);
        switch(ret) {
        case E_REQUEST_DENIED:
            menu_driver(ui->l_menu, REQ_FIRST_ITEM);
            break;
        }
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        ret = menu_driver(ui->r_menu, REQ_SCR_UPAGE);
        switch(ret) {
        case E_REQUEST_DENIED:
            menu_driver(ui->r_menu, REQ_FIRST_ITEM);
            break;
        }
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_cursor_to_last_pos(user_interface* ui) {
    if(ui->l_wnd_active_flag) {
        menu_driver(ui->l_menu, REQ_LAST_ITEM);
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        menu_driver(ui->r_menu, REQ_LAST_ITEM);
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_cursor_to_first_pos(user_interface* ui) {
    if(ui->l_wnd_active_flag) {
        menu_driver(ui->l_menu, REQ_FIRST_ITEM);
        ui->l_menu_cursor_pos = item_index(current_item(ui->l_menu));
    }
    if(ui->r_wnd_active_flag) {
        menu_driver(ui->r_menu, REQ_FIRST_ITEM);
        ui->r_menu_cursor_pos = item_index(current_item(ui->r_menu));
    }
    return 0;
}

int user_interface_active_menu_get_cursor_position(user_interface* ui) {
    if(ui->l_wnd_active_flag) {
        return ui->l_menu_cursor_pos;
    }
    if(ui->r_wnd_active_flag) {
        return ui->r_menu_cursor_pos;
    }
    return 0;
}
