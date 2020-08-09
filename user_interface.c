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
    
    /* Init right window */
    ui->r_wnd = newwin(main_y-3, main_x/2, 0, main_x/2);
    wbkgd(ui->r_wnd, COLOR_PAIR(2));
    box(ui->r_wnd, 0, 0);
    mvwaddstr(ui->r_wnd, 0,3, "right wnd");
    
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
    ui->string = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->string, COLOR_PAIR(1));
    box(ui->string, 0, 0);
    mvwaddstr(ui->string, 0,3, "command line");
    
    /* Temporary show */
    wnoutrefresh(ui->main_wnd);
    wnoutrefresh(ui->l_wnd);
    wnoutrefresh(ui->r_wnd);
    wnoutrefresh(ui->message);
    wnoutrefresh(ui->string);
    doupdate();
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
