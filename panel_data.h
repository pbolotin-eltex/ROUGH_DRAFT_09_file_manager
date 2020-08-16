/**********************************************************************
 * Panel_data module, header
 * this module need to work with data from filesystem
 **********************************************************************/

#ifndef _FILE_MANAGER_PANELS_H_
#define _FILE_MANAGER_PANELS_H_

#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* If defined - directory with name "." will be removed from list */
#define FILTER_DOT_DIR

typedef struct dirent dirent;

typedef struct panel_data {
    char* cwd;
    dirent** all_entr;
    int* description_code;
    unsigned int all_entr_count;
} panel_data;

int panel_data_init(panel_data* p_d);

int panel_data_check_if_entry_by_pos_is_dir(panel_data* p_d, int pos);

int panel_data_try_change_dir_to_entry_by_pos(panel_data* p_d, int pos);

int panel_data_final(panel_data* p_d);

#endif
