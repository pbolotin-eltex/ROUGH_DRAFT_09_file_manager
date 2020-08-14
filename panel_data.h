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
    dirent** dirs;
    dirent** reg;
    dirent** lnk;
    dirent** sock;
    dirent** fifo;
    dirent** blk;
    dirent** chr;
    dirent** unk_dirs;
    dirent** unk_entr;
    unsigned int dirs_count;
    unsigned int reg_count;
    unsigned int lnk_count;
    unsigned int sock_count;
    unsigned int fifo_count;
    unsigned int blk_count;
    unsigned int chr_count;
    unsigned int unk_dirs_count;
    unsigned int unk_entr_count;
    dirent** all_entr;
    unsigned int all_entr_count;
} panel_data;

int panel_data_init(panel_data* p_d);

int panel_data_check_if_entry_by_pos_is_dir(panel_data* p_d, int pos);

int panel_data_try_change_dir_to_entry_by_pos(panel_data* p_d, int pos);

int panel_data_final(panel_data* p_d);

#endif
