/**********************************************************************
 * Converter module, implementation
 * This module need to translate data from one kind of data to another.
 * For example: from system datatypes that are presenting 
 * the struct of directory to the user-interface datatype.
 * That is good for user to work with it
 *********************************************************************/
#include "converter.h"

int converter_panel_data_to_dir_menu_names(panel_data* p_d, dir_menu_names* d_m_n) {
    int i;
    /* To copy the all_entr names */
    d_m_n->all_entr = (char**)malloc(sizeof(char*)*p_d->all_entr_count);
    if(!d_m_n->all_entr) {
        perror("converter malloc all_entr\n");
        exit(EXIT_FAILURE);
    }
    /* To set the all_entr_descr */
    d_m_n->all_entr_descr = (int*)malloc(sizeof(int)*p_d->all_entr_count);
    if(!d_m_n->all_entr_descr) {
        perror("converter malloc all_entr_descr\n");
        exit(EXIT_FAILURE);
    }
    /* Set up arrays by names and the description codes */
    int descr_code;
    for(i = 0; i < p_d->all_entr_count; i++) {
        d_m_n->all_entr[i] = strdup(p_d->all_entr[i]->d_name);
        if(!d_m_n->all_entr[i]) {
            perror("converter strdup\n");
            exit(EXIT_FAILURE);
        }
        d_m_n->all_entr_descr[i] = p_d->description_code[i];
    }
    d_m_n->all_entr_count = p_d->all_entr_count;
    
    d_m_n->cwd = strdup(p_d->cwd);
    d_m_n->need_to_free_all_entr_flag = 1;
    d_m_n->need_to_free_all_entr_descr_flag = 1;
    d_m_n->need_to_free_strings_flag = 1;
    d_m_n->need_to_free_cwd_flag = 1;
    return 0;
}
