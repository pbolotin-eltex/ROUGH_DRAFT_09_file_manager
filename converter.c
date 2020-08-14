#include "converter.h"

int converter_panel_data_to_dir_menu_items(panel_data* p_d, dir_menu_names* d_m_n) {
    int i;
    /* To copy the directories names */
    d_m_n->dirs = (char**)malloc(sizeof(char*)*p_d->dirs_count);
    if(!d_m_n->dirs) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->dirs_count; i++) {
        d_m_n->dirs[i] = strdup(p_d->dirs[i]->d_name);
        if(!d_m_n->dirs[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->dirs_count = p_d->dirs_count;
    
    /* To copy the reg names */
    d_m_n->reg = (char**)malloc(sizeof(char*)*p_d->reg_count);
    if(!d_m_n->reg) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->reg_count; i++) {
        d_m_n->reg[i] = strdup(p_d->reg[i]->d_name);
        if(!d_m_n->reg[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->reg_count = p_d->reg_count;
    
    /* To copy the lnk names */
    d_m_n->lnk = (char**)malloc(sizeof(char*)*p_d->lnk_count);
    if(!d_m_n->lnk) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->lnk_count; i++) {
        d_m_n->lnk[i] = strdup(p_d->lnk[i]->d_name);
        if(!d_m_n->lnk[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->lnk_count = p_d->lnk_count;
    
    /* To copy the sock names */
    d_m_n->sock = (char**)malloc(sizeof(char*)*p_d->sock_count);
    if(!d_m_n->sock) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->sock_count; i++) {
        d_m_n->sock[i] = strdup(p_d->sock[i]->d_name);
        if(!d_m_n->sock[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->sock_count = p_d->sock_count;
    
    /* To copy the fifo names */
    d_m_n->fifo = (char**)malloc(sizeof(char*)*p_d->fifo_count);
    if(!d_m_n->fifo) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->fifo_count; i++) {
        d_m_n->fifo[i] = strdup(p_d->fifo[i]->d_name);
        if(!d_m_n->fifo[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->fifo_count = p_d->fifo_count;
    
    /* To copy the blk names */
    d_m_n->blk = (char**)malloc(sizeof(char*)*p_d->blk_count);
    if(!d_m_n->blk) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->blk_count; i++) {
        d_m_n->blk[i] = strdup(p_d->blk[i]->d_name);
        if(!d_m_n->blk[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->blk_count = p_d->blk_count;
    
    /* To copy the chr names */
    d_m_n->chr = (char**)malloc(sizeof(char*)*p_d->chr_count);
    if(!d_m_n->chr) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->chr_count; i++) {
        d_m_n->chr[i] = strdup(p_d->chr[i]->d_name);
        if(!d_m_n->chr[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->chr_count = p_d->chr_count;
    
    /* To copy the unk_dirs names */
    d_m_n->unk_dirs = (char**)malloc(sizeof(char*)*p_d->unk_dirs_count);
    if(!d_m_n->unk_dirs) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->unk_dirs_count; i++) {
        d_m_n->unk_dirs[i] = strdup(p_d->unk_dirs[i]->d_name);
        if(!d_m_n->unk_dirs[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->unk_dirs_count = p_d->unk_dirs_count;
    
    /* To copy the unk_entr names */
    d_m_n->unk_entr = (char**)malloc(sizeof(char*)*p_d->unk_entr_count);
    if(!d_m_n->unk_entr) {
        perror("converter malloc\n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < p_d->unk_entr_count; i++) {
        d_m_n->unk_entr[i] = strdup(p_d->unk_entr[i]->d_name);
        if(!d_m_n->unk_entr[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
    }
    d_m_n->unk_entr_count = p_d->unk_entr_count;
    
    d_m_n->cwd = strdup(p_d->cwd);
    d_m_n->need_to_free_arrays_flag = 1;
    d_m_n->need_to_free_strings_flag = 1;
    d_m_n->need_to_free_cwd_flag = 1;
    return 0;
}
