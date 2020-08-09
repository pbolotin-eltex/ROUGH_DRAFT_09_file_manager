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
    
    /* Define sizes */
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);    
    
    /* Init view of main window */
    wbkgd(ui->main_wnd, COLOR_PAIR(1));
    box(ui->main_wnd, 0, 0);
    mvwaddstr(ui->main_wnd, 0,3, "main wnd");
    
    /* Init left window */
    ui->l_wnd = newwin(main_y-3, main_x/2, 0, 0);
    wbkgd(ui->l_wnd, COLOR_PAIR(2));
    box(ui->l_wnd, 0, 0);
    mvwaddstr(ui->l_wnd, 0,3, "left wnd");
    ui->l_wnd_active_flag = 0;
    
    /* Init right window */
    ui->r_wnd = newwin(main_y-3, main_x/2, 0, main_x/2);
    wbkgd(ui->r_wnd, A_BOLD|COLOR_PAIR(2));
    box(ui->r_wnd, 0, 0);
    mvwaddstr(ui->r_wnd, 0,3, "right wnd");
    ui->r_wnd_active_flag = 1;
    
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
    wbkgd(ui->message, COLOR_PAIR(3));
    box(ui->message, 0, 0);
    mvwaddstr(ui->message, 0, 3, "message");
    
    /* Init command line window */
    ui->cmd = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->cmd, COLOR_PAIR(1));
    box(ui->cmd, 0, 0);
    mvwaddstr(ui->cmd, 0,3, "command line");
    
    /* Temporary show for the testing purpose */
    /*
    wnoutrefresh(ui->main_wnd);
    wnoutrefresh(ui->l_wnd);
    wnoutrefresh(ui->r_wnd);
    wnoutrefresh(ui->message);
    wnoutrefresh(ui->cmd);
    doupdate();
    */
    return 0;
}

int user_interface_what_user_did(user_interface* ui) {
    return wgetch(ui->main_wnd);
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

int user_interface_show_lpanel(user_interface* ui) {
    wnoutrefresh(ui->l_wnd);
    return 0;
}

int user_interface_show_rpanel(user_interface* ui) {
    wnoutrefresh(ui->r_wnd);
    return 0;
}

int user_interface_show_message(user_interface* ui) {
    wnoutrefresh(ui->message);
    return 0;
}

int user_interface_show_cmd(user_interface* ui) {
    wnoutrefresh(ui->cmd);
    return 0;
}

int user_interface_show_mainwnd(user_interface* ui) {
    wnoutrefresh(ui->main_wnd);
    return 0;
}

int user_interface_show_on_screen(user_interface* ui) {
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
    endwin();
#ifdef DEBUG
    exit_curses(0);
#endif
    return 0;
}

int user_interface_on(user_interface* ui) {
    return 0;
}

int user_interface_off(user_interface* ui) {
    return 0;
}
