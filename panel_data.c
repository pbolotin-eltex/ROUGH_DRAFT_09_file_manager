/**********************************************************************
 * Panel_data module, implementation
 * this module need to work with data from filesystem
 **********************************************************************/
#include "panel_data.h"

int dot_dir_filter(const dirent* ent) {
    #ifdef FILTER_DOT_DIR
    if(0 == strcmp(ent->d_name, ".")) return 0;
    #endif
    return 1;
}

int filter_unk_dirs_by_opendir(const dirent* ent) {
    DIR* is_dir;
    switch(ent->d_type) {
        case DT_UNKNOWN:
        /* Try to check dir for opening */
        is_dir = opendir(ent->d_name);
        if(NULL != is_dir) {
            int success = closedir(is_dir);
            if(!success) {
                perror("Error when try to closedir()\n");
                exit(EXIT_FAILURE);
            }
            return 1;
        } else {
            switch(errno) {
                case ENOTDIR: /* name is not a directory. */
                    return 0;
                break;
                case EACCES:
                    return 1;
                break;
                case EBADF:  /*fd is not a valid file descriptor opened for reading.*/
                    return 0;
                break;
                case EMFILE: /*The per-process limit on the number of open file descriptors has been reached.*/
                    perror("Error in filter by_opendir,  limit open fd\n");
                    exit(EXIT_FAILURE);
                    return 0;
                break;
                case ENFILE: /*The system-wide limit on the total number of open files has been reached.*/
                    perror("Error in filter by_opendir, limit open files\n");
                    exit(EXIT_FAILURE);
                    return 0;
                break;
                case ENOENT: /*Directory does not exist, or name is an empty string.*/
                    return 0;
                break;
                case ENOMEM: /*Insufficient memory to complete the operation.*/
                    perror("Error in filter by_opendir\n");
                    exit(EXIT_FAILURE);
                    return 0;
                break;
            }
        }
    }
    return 0;
}

int category_alphasort(const dirent** a, const dirent** b) {
    /* Define first parameter */
    int d_type = (*a)->d_type;
    int a_prior = 0;
    switch(d_type) {
        case DT_DIR:
            a_prior = 1;
            if(0 == strcmp((*a)->d_name, "..")) {
                a_prior = 0;
            }
            break;
        case DT_REG:
            a_prior = 2;
            break;
        case DT_LNK:
            a_prior = 3;
            break;
        case DT_SOCK:
            a_prior = 4;
            break;
        case DT_FIFO:
            a_prior = 5;
            break;
        case DT_BLK:
            a_prior = 6;
            break;
        case DT_CHR:
            a_prior = 7;
            break;            
        case DT_UNKNOWN:
            if(filter_unk_dirs_by_opendir(*a)) {
                a_prior = 8;
                if(0 == strcmp((*a)->d_name, "..")) {
                    a_prior = 0;
                }
            } else {
                a_prior = 9;
            }
            break;
    }
    /* Define second parameter */
    d_type = (*b)->d_type;
    int b_prior = 0;
    switch(d_type) {
        case DT_DIR:
            b_prior = 1;
            if(0 == strcmp((*b)->d_name, "..")) {
                b_prior = 0;
            }
            break;
        case DT_REG:
            b_prior = 2;
            break;
        case DT_LNK:
            b_prior = 3;
            break;
        case DT_SOCK:
            b_prior = 4;
            break;
        case DT_FIFO:
            b_prior = 5;
            break;
        case DT_BLK:
            b_prior = 6;
            break;
        case DT_CHR:
            b_prior = 7;
            break;            
        case DT_UNKNOWN:
            if(filter_unk_dirs_by_opendir(*b)) {
                b_prior = 8;
                if(0 == strcmp((*b)->d_name, "..")) {
                    b_prior = 0;
                }
            } else {
                b_prior = 9;
            }
            break;
    }
    if(a_prior != b_prior) return a_prior - b_prior;
    return alphasort(a, b);
}

int panel_data_init(panel_data* p_d) {
    p_d->cwd = getcwd(NULL, 0);

    dirent** scan;
    int ret = scandir(p_d->cwd, &p_d->all_entr, dot_dir_filter, category_alphasort);
    if(0 > ret) {
        perror("panel_data_init scandir\n");
        exit(EXIT_FAILURE);
    }
    p_d->all_entr_count = ret;
    
    /* Define array of the description codes */
    p_d->description_code = calloc(p_d->all_entr_count, sizeof(int));
    if(NULL == p_d->description_code) {
        perror("panel_data_init calloc\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for(i = 0; i < p_d->all_entr_count; i++) {
        switch(p_d->all_entr[i]->d_type) {
            case DT_DIR:
                p_d->description_code[i] = 1;
                break;
            case DT_REG:
                p_d->description_code[i] = 2;
                break;
            case DT_LNK:
                p_d->description_code[i] = 3;
                break;
            case DT_SOCK:
                p_d->description_code[i] = 4;
                break;
            case DT_FIFO:
                p_d->description_code[i] = 5;
                break;
            case DT_BLK:
                p_d->description_code[i] = 6;
                break;
            case DT_CHR:
                p_d->description_code[i] = 7;
                break;            
            case DT_UNKNOWN:
                if(filter_unk_dirs_by_opendir(p_d->all_entr[i])) {
                    p_d->description_code[i] = 8;
                } else {
                    p_d->description_code[i] = 9;
                }
                break;
        }
    }
    return 0;
}

int panel_data_check_if_entry_by_pos_is_dir(panel_data* p_d, int pos) {
    if(1 == p_d->description_code[pos]) {
        return 1;
    }
    if(8 == p_d->description_code[pos]) {
        return 1;
    }
    return 0;
}

int panel_data_try_change_dir_to_entry_by_pos(panel_data* p_d, int pos) {
    char* entry_name = p_d->all_entr[pos]->d_name;
    char* new_path = (char*)calloc(1, sizeof(char) * (strlen(p_d->cwd) + strlen(entry_name) + 2));
    if(!new_path) {
        perror("panel_data_try_change_dir calloc\n");
        exit(EXIT_FAILURE);
    }
    /* manually form new path to directory */
    int rel;
    int abs = 0;
    int cwd_len = strlen(p_d->cwd);
    int entry_len = strlen(entry_name);
    for(rel = 0; rel < cwd_len; rel++, abs++) {
        new_path[abs] = p_d->cwd[rel];
    }
    new_path[abs] = '/';
    abs++;
    for(rel = 0; rel < entry_len; rel++, abs++) {
        new_path[abs] = entry_name[rel];
    }
    new_path[abs] = '\0';
    /* Try chdir to the formed new_path */
    int ret = chdir(new_path);
    if(-1 == ret) {
        int my_errno = errno;
        free(new_path);
        switch(my_errno) {
        case EACCES:/*Search permission is denied for one of the components of path.*/
            return EACCES;
        case EFAULT:/*path points outside your accessible address space.*/
            perror("chdir in panel_data_check fail\n");
            exit(EXIT_FAILURE);
        case EIO:/*An I/O error occurred.*/
            return EIO;
        case ELOOP:/*Too many symbolic links were encountered in resolving path.*/
            return ELOOP;
        case ENAMETOOLONG:/*path is too long.*/
            return ENAMETOOLONG;
        case ENOENT:/*ENOENT The directory specified in path does not exist.*/
            return ENOENT;
        case ENOMEM:/*ENOMEM Insufficient kernel memory was available.*/
            perror("chdir in panel_data_check fail\n");
            exit(EXIT_FAILURE);
        case ENOTDIR:/*A component of path is not a directory*/
            return(ENOTDIR);
        }
    }
    /* chdir success! */
    /* Now new_path can be freed because of getcwd now can get it back */
    free(new_path);
    /* do new panel_data (temporary) */
    panel_data  temp_p_d;
    panel_data* new_p_d = &temp_p_d;
    memset(new_p_d, 0, sizeof(panel_data));
    /* Set new_p_d */
    panel_data_init(new_p_d);
    /* Final old p_d */
    panel_data_final(p_d);
    /* reenter fields of static p_d by new_p_d fields */
    p_d->cwd = new_p_d->cwd;
    p_d->all_entr = new_p_d->all_entr;
    p_d->description_code = new_p_d->description_code;
    p_d->all_entr_count = new_p_d->all_entr_count;
    return 0;
}

int panel_data_final(panel_data* p_d) {
    free(p_d->cwd);
    p_d->cwd = NULL;
    int i;
    if(NULL != p_d->all_entr) {
        for(int i = 0; i < p_d->all_entr_count; i++) {
            //free(p_d->all_entr[i]->d_name);
            free(p_d->all_entr[i]);
        }
        free(p_d->all_entr);
    }
    p_d->all_entr = NULL;
    p_d->all_entr_count = 0;
    free(p_d->description_code);
    p_d->description_code = NULL;
    return 0;
}
