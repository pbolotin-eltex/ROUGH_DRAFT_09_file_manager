/**********************************************************************
 * File manager module, header file
 * Common part of program, the other modules are used in here
 *********************************************************************/
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include "user_interface.h"
#include "panel_data.h"
#include "converter.h"
#include <unistd.h>

/* What can do user */
#define CHANGE_ACTIVE_PANEL '\t'
#define QUIT KEY_F(10)
#define CHANGE_SCREEN_SIZE KEY_RESIZE
#define TEST_SHOW_MESSAGE KEY_F(1)
#define ON_OFF_NCURSES KEY_F(2)
#define TEST_MENU KEY_F(3)
#define PAGE_DOWN_KEY 338
#define PAGE_UP_KEY 339
#define USER_KEY_ENTER 10

typedef struct file_manager_data {
    user_interface ui;
    panel_data l_panel_data;
    panel_data r_panel_data;
} file_manager_data;

int file_manager_init(file_manager_data* data);

int file_manager_work(file_manager_data* data);

int file_manager_final(file_manager_data* data);

#endif
