/**********************************************************************
 * File manager common part, implementation
 *********************************************************************/
#include "file_manager.h"

int file_manager_init(file_manager_data* data) {
    /* Init user interface */
    if(user_interface_init(&data->ui) != 0) {
        perror("Can't initialize user interface\n");
        exit(1);
    }
    return 0;
}

int file_manager_work(file_manager_data* data) {
    /* It do main file_manager cycle */
    int what_user_did;
    int end_work_flag = 0;
    while(!end_work_flag) {
        what_user_did = user_interface_what_user_did(&data->ui);
        switch(what_user_did) {
            case CHANGE_ACTIVE_PANEL:
                user_interface_change_active_panel(&data->ui);
                break;
            case QUIT:
                end_work_flag = 1;
                break;
        }
        user_interface_show_lpanel(&data->ui);
        user_interface_show_rpanel(&data->ui);
        user_interface_number_to_cmd(&data->ui, what_user_did);
        user_interface_show_cmd(&data->ui);
        user_interface_show_on_screen(&data->ui);
    }
    return 0;
}

int file_manager_final(file_manager_data* data) {
    /* End user interface */
    if(user_interface_final(&data->ui) != 0) {
        perror("Can't finilize user interface\n");
        exit(1);
    }
    return 0;
}
