/**********************************************************************
 * File manager common part, app data is joined here
 *********************************************************************/
#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#include "user_interface.h"
#include <unistd.h>

/* What can do user */
#define CHANGE_ACTIVE_PANEL '\t'
#define QUIT KEY_F(10)
#define CHANGE_SCREEN_SIZE KEY_RESIZE

typedef struct file_manager_data {
    user_interface ui;
} file_manager_data;

int file_manager_init(file_manager_data* data);

int file_manager_work(file_manager_data* data);

int file_manager_final(file_manager_data* data);

#endif
