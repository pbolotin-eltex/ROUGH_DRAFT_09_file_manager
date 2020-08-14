#include "panel_data.h"

/*
case DT_REG:
case DT_LNK:
case DT_SOCK:
case DT_FIFO:
case DT_BLK:
case DT_CHR:
case DT_UNKNOWN:
*/
int filter_dir_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_DIR:
            #ifdef FILTER_DOT_DIR
            if(0 == strcmp(ent->d_name, ".")) return 0;
            #endif
            return 1;
    }
    return 0;
}

int filter_reg_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_REG:
            return 1;
    }
    return 0;
}

int filter_lnk_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_LNK:
            return 1;
    }
    return 0;
}

int filter_sock_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_SOCK:
            return 1;
    }
    return 0;
}

int filter_fifo_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_FIFO:
            return 1;
    }
    return 0;
}

int filter_blk_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_FIFO:
            return 1;
    }
    return 0;
}

int filter_chr_by_d_type(const dirent* ent) {
    switch(ent->d_type) {
        case DT_CHR:
            return 1;
    }
    return 0;
}

int filter_unk_dirs_by_opendir(const dirent* ent) {
    #ifdef FILTER_DOT_DIR
    if(0 == strcmp(ent->d_name, ".")) return 0;
    #endif
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

int filter_unk_entr_by_opendir(const dirent* ent) {
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
            return 0;
        } else {
            switch(errno) {
                case ENOTDIR: /* name is not a directory. */
                    return 1;
                break;
                case EACCES:
                    return 0;
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

int panel_data_init(panel_data* p_d) {
    /* get cwd (after using it need to free)*/
    p_d->cwd = getcwd(NULL, 0);
    if(NULL == p_d->cwd) {
        perror("Can't getcwd()\n");
        exit(EXIT_FAILURE);
    }
    /* scandir for directories */
    int ret = scandir(p_d->cwd, &p_d->dirs, filter_dir_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for directories \n");
        exit(EXIT_FAILURE);
    }
    p_d->dirs_count = ret;
    /* scandir for reg files*/
    ret = scandir(p_d->cwd, &p_d->reg, filter_reg_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for regfiles \n");
        exit(EXIT_FAILURE);
    }
    p_d->reg_count = ret;
    /* scandir for lnk files*/
    ret = scandir(p_d->cwd, &p_d->lnk, filter_lnk_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for lnk \n");
        exit(EXIT_FAILURE);
    }
    p_d->lnk_count = ret;
    /* scandir for socket */
    ret = scandir(p_d->cwd, &p_d->sock, filter_sock_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for sockets \n");
        exit(EXIT_FAILURE);
    }
    p_d->sock_count = ret;
    /* scandir for fifo */
    ret = scandir(p_d->cwd, &p_d->fifo, filter_fifo_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for fifo \n");
        exit(EXIT_FAILURE);
    }
    p_d->fifo_count = ret;
    /* scandir for blk */
    ret = scandir(p_d->cwd, &p_d->blk, filter_blk_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for blk \n");
        exit(EXIT_FAILURE);
    }
    p_d->blk_count = ret;
    /* scandir for chr */
    ret = scandir(p_d->cwd, &p_d->chr, filter_chr_by_d_type, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for chr \n");
        exit(EXIT_FAILURE);
    }
    p_d->chr_count = ret;
    /* scandir for unk_dirs */
    ret = scandir(p_d->cwd, &p_d->unk_dirs, filter_unk_dirs_by_opendir, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for unk_dirs \n");
        exit(EXIT_FAILURE);
    }
    p_d->unk_dirs_count = ret;
    /* scandir for unk_entr */
    ret = scandir(p_d->cwd, &p_d->unk_entr, filter_unk_entr_by_opendir, alphasort);
    if(-1 == ret) {
        perror("Can't scandir for unk_entr \n");
        exit(EXIT_FAILURE);
    }
    p_d->unk_entr_count = ret;
    
    p_d->all_entr_count = p_d->dirs_count +\
                          p_d->reg_count +\
                          p_d->lnk_count +\
                          p_d->sock_count +\
                          p_d->fifo_count +\
                          p_d->blk_count +\
                          p_d->chr_count +\
                          p_d->unk_dirs_count +\
                          p_d->unk_entr_count;
    p_d->all_entr = (dirent**)calloc(p_d->all_entr_count, sizeof(dirent*));
    if(NULL == p_d->all_entr) {
        perror("calloc in panel_data_init\n");
        exit(EXIT_FAILURE);
    }
    /* fill all_entr sequentally */
    {
    int a = 0;
    for(int i = 0; i < p_d->dirs_count; i++, a++) {
        p_d->all_entr[a] = p_d->dirs[i];
    }
    for(int i = 0; i < p_d->reg_count; i++, a++) {
        p_d->all_entr[a] = p_d->reg[i];
    }
    for(int i = 0; i < p_d->lnk_count; i++, a++) {
        p_d->all_entr[a] = p_d->lnk[i];
    }
    for(int i = 0; i < p_d->sock_count; i++, a++) {
        p_d->all_entr[a] = p_d->sock[i];
    }
    for(int i = 0; i < p_d->fifo_count; i++, a++) {
        p_d->all_entr[a] = p_d->fifo[i];
    }
    for(int i = 0; i < p_d->blk_count; i++, a++) {
        p_d->all_entr[a] = p_d->blk[i];
    }
    for(int i = 0; i < p_d->chr_count; i++, a++) {
        p_d->all_entr[a] = p_d->chr[i];
    }
    for(int i = 0; i < p_d->unk_dirs_count; i++, a++) {
        p_d->all_entr[a] = p_d->unk_dirs[i];
    }
    for(int i = 0; i < p_d->unk_entr_count; i++, a++) {
        p_d->all_entr[a] = p_d->unk_entr[i];
    }
    }
    
    /*Test output block*/
    {
    fprintf(stderr, "***DIRS***\n");
    for(int i = 0; i < p_d->dirs_count; i++) {
        if(p_d->dirs[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->dirs[i]->d_name);
        }
    }
    fprintf(stderr, "***REG***\n");
    for(int i = 0; i < p_d->reg_count; i++) {
        if(p_d->reg[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->reg[i]->d_name);
        }
    }
    fprintf(stderr, "***LNK***\n");
    for(int i = 0; i < p_d->lnk_count; i++) {
        if(p_d->lnk[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->lnk[i]->d_name);
        }
    }
    fprintf(stderr, "***SOCK***\n");
    for(int i = 0; i < p_d->sock_count; i++) {
        if(p_d->sock[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->sock[i]->d_name);
        }
    }
    fprintf(stderr, "***FIFO***\n");
    for(int i = 0; i < p_d->fifo_count; i++) {
        if(p_d->fifo[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->fifo[i]->d_name);
        }
    }
    fprintf(stderr, "***BLK***\n");
    for(int i = 0; i < p_d->blk_count; i++) {
        if(p_d->blk[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->blk[i]->d_name);
        }
    }
    fprintf(stderr, "***CHR***\n");
    for(int i = 0; i < p_d->chr_count; i++) {
        if(p_d->chr[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->chr[i]->d_name);
        }
    }
    fprintf(stderr, "***UNK_DIRS***\n");
    for(int i = 0; i < p_d->unk_dirs_count; i++) {
        if(p_d->unk_dirs[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->unk_dirs[i]->d_name);
        }
    }
    fprintf(stderr, "***UNK_ENTR***\n");
    for(int i = 0; i < p_d->unk_entr_count; i++) {
        if(p_d->unk_entr[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->unk_entr[i]->d_name);
        }
    }
    }
    
    /*Test output block*/
    {
    fprintf(stderr, "***DIRS***\n");
    for(int i = 0; i < p_d->dirs_count; i++) {
        if(p_d->dirs[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->dirs[i]->d_name);
        }
    }
    fprintf(stderr, "***REG***\n");
    for(int i = 0; i < p_d->reg_count; i++) {
        if(p_d->reg[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->reg[i]->d_name);
        }
    }
    fprintf(stderr, "***LNK***\n");
    for(int i = 0; i < p_d->lnk_count; i++) {
        if(p_d->lnk[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->lnk[i]->d_name);
        }
    }
    fprintf(stderr, "***SOCK***\n");
    for(int i = 0; i < p_d->sock_count; i++) {
        if(p_d->sock[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->sock[i]->d_name);
        }
    }
    fprintf(stderr, "***FIFO***\n");
    for(int i = 0; i < p_d->fifo_count; i++) {
        if(p_d->fifo[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->fifo[i]->d_name);
        }
    }
    fprintf(stderr, "***BLK***\n");
    for(int i = 0; i < p_d->blk_count; i++) {
        if(p_d->blk[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->blk[i]->d_name);
        }
    }
    fprintf(stderr, "***CHR***\n");
    for(int i = 0; i < p_d->chr_count; i++) {
        if(p_d->chr[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->chr[i]->d_name);
        }
    }
    fprintf(stderr, "***UNK_DIRS***\n");
    for(int i = 0; i < p_d->unk_dirs_count; i++) {
        if(p_d->unk_dirs[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->unk_dirs[i]->d_name);
        }
    }
    fprintf(stderr, "***UNK_ENTR***\n");
    for(int i = 0; i < p_d->unk_entr_count; i++) {
        if(p_d->unk_entr[i] != NULL) {
            fprintf(stderr, "%s\n", p_d->unk_entr[i]->d_name);
        }
    }
    }
    /*struct entries output*/
    {
    fprintf(stderr, "cwd:\t%s\n", p_d->cwd);
    fprintf(stderr, "dirs:\t%p\n", p_d->dirs);
    fprintf(stderr, "reg:\t%p\n", p_d->reg);
    fprintf(stderr, "lnk:\t%p\n", p_d->lnk);
    fprintf(stderr, "sock:\t%p\n", p_d->sock);
    fprintf(stderr, "fifo:\t%p\n", p_d->fifo);
    fprintf(stderr, "blk:\t%p\n", p_d->blk);
    fprintf(stderr, "chr:\t%p\n", p_d->chr);
    fprintf(stderr, "unk_dirs:\t%p\n", p_d->unk_dirs);
    fprintf(stderr, "unk_entr:\t%p\n", p_d->unk_entr);
    fprintf(stderr, "dirs_count:\t%d\n", p_d->dirs_count);
    fprintf(stderr, "reg_count:\t%d\n", p_d->reg_count);
    fprintf(stderr, "lnk_count:\t%d\n", p_d->lnk_count);
    fprintf(stderr, "sock_count:\t%d\n", p_d->sock_count);
    fprintf(stderr, "fifo_count:\t%d\n", p_d->fifo_count);
    fprintf(stderr, "blk_count:\t%d\n", p_d->blk_count);
    fprintf(stderr, "chr_count:\t%d\n", p_d->chr_count);
    fprintf(stderr, "unk_dirs_count:\t%d\n", p_d->unk_dirs_count);
    fprintf(stderr, "unk_entr_count:\t%d\n", p_d->unk_entr_count);
    }
    return 0;
}

int panel_data_check_if_entry_by_pos_is_dir(panel_data* p_d, int pos) {
    if(pos >= 0 && pos < p_d->dirs_count) {
        return 1;
    }
    int l_lim = p_d->dirs_count +\
                p_d->reg_count +\
                p_d->lnk_count +\
                p_d->sock_count +\
                p_d->fifo_count +\
                p_d->blk_count +\
                p_d->chr_count +\
                p_d->chr_count;
    if(pos >= l_lim && pos < l_lim + p_d->unk_dirs_count) {
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
    fprintf(stderr, "old_path: %s\n new_path %s\n", p_d->cwd, new_path);
    
    int ret = chdir(new_path);
    if(-1 == ret) {
        perror("chdir in panel_data_check fail");
        int my_errno = errno;
        switch(my_errno) {
        case EACCES:/*Search permission is denied for one of the components of path.*/
            return EACCES;
            break;
        case EFAULT:/*path points outside your accessible address space.*/
            exit(EXIT_FAILURE);
            break;
        case EIO:/*An I/O error occurred.*/
            return EIO;
            break;
        case ELOOP:/*Too many symbolic links were encountered in resolving path.*/
            return ELOOP;
            break;
        case ENAMETOOLONG:/*path is too long.*/
            return ENAMETOOLONG;
            break;
        case ENOENT:/*ENOENT The directory specified in path does not exist.*/
            return ENOENT;
            break;
        case ENOMEM:/*ENOMEM Insufficient kernel memory was available.*/
            exit(EXIT_FAILURE);
            break;
        case ENOTDIR:/*A component of path is not a directory*/
            return(ENOTDIR);
            break;
        }
    }
    /* chdir success! do new panel_data */
    panel_data *new_p_d = (panel_data*)calloc(1, sizeof(panel_data));
    if(NULL == new_p_d) {
        perror("calloc in panel_data_try_to_change for new_p_d\n");
        exit(EXIT_FAILURE);
    }
    /* Set new_p_d */
    panel_data_init(new_p_d);
    /* Final old p_d */
    panel_data_final(p_d);
    /* reenter fields of static p_d by new_p_d fields */
    p_d->cwd = new_p_d->cwd;
    p_d->dirs = new_p_d->dirs;
    p_d->reg = new_p_d->reg;
    p_d->lnk = new_p_d->lnk;
    p_d->sock = new_p_d->sock;
    p_d->fifo = new_p_d->fifo;
    p_d->blk = new_p_d->blk;
    p_d->chr = new_p_d->chr;
    p_d->unk_dirs = new_p_d->unk_dirs;
    p_d->unk_entr = new_p_d->unk_entr;
    p_d->dirs_count = new_p_d->dirs_count;
    p_d->reg_count = new_p_d->reg_count;
    p_d->lnk_count = new_p_d->lnk_count;
    p_d->sock_count = new_p_d->sock_count;
    p_d->fifo_count = new_p_d->fifo_count;
    p_d->blk_count = new_p_d->blk_count;
    p_d->chr_count = new_p_d->chr_count;
    p_d->unk_dirs_count = new_p_d->unk_dirs_count;
    p_d->unk_entr_count = new_p_d->unk_entr_count;
    p_d->all_entr = new_p_d->all_entr;
    p_d->all_entr_count = new_p_d->all_entr_count;
    return 0;
}

/* There is trouble with memory freeing! */
/* I think because of scandir and maybe ~readdir under it */
/* Also maybe because of the filter functions */
/* MB there is a way to correct it. Using of readdir instead of scandir */
/* And read directory's content manually */
int panel_data_final(panel_data* p_d) {
    free(p_d->cwd);
    if(NULL != p_d->dirs) {
        for(int i = 0; i < p_d->dirs_count; i++) {
            //free(p_d->dirs[i]->d_name);
            free(p_d->dirs[i]);
        }
        free(p_d->dirs);
    }
    if(NULL != p_d->reg) {
        for(int i = 0; i < p_d->reg_count; i++) {
            //free(p_d->reg[i]->d_name);
            free(p_d->reg[i]);
        }
        free(p_d->reg);
    }
    if(NULL != p_d->lnk) {
        for(int i = 0; i < p_d->lnk_count; i++) {
            //free(p_d->lnk[i]->d_name);
            free(p_d->lnk[i]);
        }
        free(p_d->lnk);
    }
    if(NULL != p_d->sock) {
        for(int i = 0; i < p_d->sock_count; i++) {
            //free(p_d->sock[i]->d_name);
            free(p_d->sock[i]);
        }
        free(p_d->sock);
    }
    if(NULL != p_d->fifo) {
        for(int i = 0; i < p_d->fifo_count; i++) {
            //free(p_d->fifo[i]->d_name);
            free(p_d->fifo[i]);
        }
        free(p_d->fifo);
    }
    if(NULL != p_d->blk) {
        for(int i = 0; i < p_d->blk_count; i++) {
            //free(p_d->blk[i]->d_name);
            free(p_d->blk[i]);
        }
        free(p_d->blk);
    }
    if(NULL != p_d->chr) {
        for(int i = 0; i < p_d->chr_count; i++) {
            //free(p_d->chr[i]->d_name);
            free(p_d->chr[i]);
        }
        free(p_d->chr);
    }
    if(NULL != p_d->unk_dirs) {
        for(int i = 0; i < p_d->unk_dirs_count; i++) {
            //free(p_d->unk_dirs[i]->d_name);
            free(p_d->unk_dirs[i]);
        }
        free(p_d->unk_dirs);
    }
    if(NULL != p_d->unk_entr) {
        for(int i = 0; i < p_d->unk_entr_count; i++) {
            //free(p_d->unk_entr[i]->d_name);
            free(p_d->unk_entr[i]);
        }
        free(p_d->unk_entr);
    }
    free(p_d->all_entr);
    return 0;
}
