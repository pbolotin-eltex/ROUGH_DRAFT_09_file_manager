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
    //ui->main_panel = new_panel(ui->main_wnd);
    
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
    
    /* Init command line window */
    ui->cmd = newwin(3, main_x, main_y - 3, 0);
    wbkgd(ui->cmd, COLOR_PAIR(1));
    box(ui->cmd, 0, 0);
    mvwaddstr(ui->cmd, 0,3, "command line");
    ui->cmd_panel = new_panel(ui->cmd);
    
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

int user_interface_change_screen_size(user_interface* ui) {
    /* New main wnd parameters */
    //del_panel(ui->main_panel);
    int main_y, main_x;
    getmaxyx(ui->main_wnd, main_y, main_x);
    box(ui->main_wnd, 0, 0);
    mvwaddstr(ui->main_wnd, 0,3, "main wnd");
    //ui->main_panel = new_panel(ui->main_wnd);
    
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
    
    //wnoutrefresh(ui->main_wnd);
    //wnoutrefresh(ui->l_wnd);
    //wnoutrefresh(ui->r_wnd);
    if(ui->show_message_flag) {
        //wnoutrefresh(ui->message);
    }
    //wnoutrefresh(ui->cmd);
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

int user_interface_show_lpanel(user_interface* ui) {
    //wnoutrefresh(ui->l_wnd);
    return 0;
}

int user_interface_show_rpanel(user_interface* ui) {
    //wnoutrefresh(ui->r_wnd);
    return 0;
}

int user_interface_need_show_message(user_interface* ui) {
    ui->show_message_flag = 1;
    return 0;
}

int user_interface_show_message(user_interface* ui) {
    if(ui->show_message_flag) {
        //wbkgd(ui->message, COLOR_PAIR(3));
        //box(ui->message, 0, 0);
        //mvwaddstr(ui->message, 0, 3, "message");
        //wnoutrefresh(ui->message);
        user_interface_deactivate_panels(ui);
        show_panel(ui->message_panel);
        ui->show_message_flag = 0;
    } else {
        user_interface_reactivate_panels(ui);
        hide_panel(ui->message_panel);
    }
    return 0;
}

int user_interface_show_cmd(user_interface* ui) {
    //wnoutrefresh(ui->cmd);
    return 0;
}

int user_interface_show_mainwnd(user_interface* ui) {
    //wnoutrefresh(ui->main_wnd);
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
    //wnoutrefresh(ui->cmd);
    return 0;
}

int user_interface_string_to_cmd(user_interface* ui, char *str) {
    wmove(ui->cmd, 1,1);
    wprintw(ui->cmd, "%s", str);
    //wnoutrefresh(ui->cmd);
    return 0;
}

int user_interface_final(user_interface* ui) {
    //del_panel(ui->main_panel);
    del_panel(ui->r_panel);
    del_panel(ui->l_panel);
    del_panel(ui->message_panel);
    del_panel(ui->cmd_panel);
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
