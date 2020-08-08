/**********************************************************************
 * File manager user interface part, implementation
 *********************************************************************/
#include "user_interface.h"

#define DEBUG

int user_interface_init(user_interface* ui) {
    /* Init main window */
    ui->main_wnd = initscr();
    box(ui->main_wnd, 0, 0);
    start_color();
    cbreak();
    noecho();
    keypad(ui->main_wnd, TRUE);
    /* Init the colors */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    /* Define sizes */
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);
    /* Init left window */
    ui->l_wnd = newwin(main_y-2, main_x/2, 0, 0);
    box(ui->l_wnd, 0, 0);
    /* Init right window */
    ui->r_wnd = newwin(main_y-2, main_x/2, 0, main_x/2);
    box(ui->r_wnd, 0, 0);
    /* Init message window */
    // It need up to 5 lines of main_wnd in center
    int message_y, message_x, start_y, start_x;
    if(main_y >= 5) {
        message_y = 5;
        start_y = main_y/2 - 2;
    } else {
        message_y = main_y;
        start_y = 0;
    }
    start_x = 0;
    ui->message = newwin(message_y, message_x, start_y, start_x);
    box(ui->message, 0, 0);
    /* Init command line window */
    ui->string = newwin(2, main_x, main_y - 2, 0);
    box(ui->string, 0, 0);
    /* Temporary show */
    wrefresh(ui->main_wnd);
    wrefresh(ui->l_wnd);
    wrefresh(ui->r_wnd);
    wrefresh(ui->message);
    wrefresh(ui->string);
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
