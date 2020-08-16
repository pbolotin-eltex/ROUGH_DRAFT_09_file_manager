/**********************************************************************
 * File manager module, implementation
 * Common part of program, the other modules are used in here
 *********************************************************************/
#include "file_manager.h"

int file_manager_init(file_manager_data* data) {
    /* Init panel_data for left and right panels */
    if(panel_data_init(&data->l_panel_data)) {
        perror("Can't init l_panel_data\n");
        exit(EXIT_FAILURE);
    }
    if(panel_data_init(&data->r_panel_data)) {
        perror("Can't init r_panel_data\n");
        exit(EXIT_FAILURE);
    }
    /* Init user interface */
    if(user_interface_init(&data->ui) != 0) {
        perror("Can't initialize user interface\n");
        exit(EXIT_FAILURE);
    }
    /* To init menues using panel_data */
    converter_panel_data_to_dir_menu_names(&data->l_panel_data,\
                                           (&data->ui)->l_menu_names);
    /*converter_panel_data_to_dir_menu_names(&data->r_panel_data,\
                                           (&data->ui)->r_menu_names);*/
    user_interface_l_menu_post(&data->ui);
    return 0;
}

int file_manager_work(file_manager_data* data) {
    /* It do main file_manager cycle */
    int what_user_did;
    int end_work_flag = 0;
    while(!end_work_flag) {
        what_user_did = user_interface_what_user_did(&data->ui);
        switch(what_user_did) {
            case CHANGE_SCREEN_SIZE:
                user_interface_change_screen_size(&data->ui);
                break;
            case CHANGE_ACTIVE_PANEL:
                user_interface_change_active_panel(&data->ui);
                break;
            case TEST_SHOW_MESSAGE:
                user_interface_need_show_message(&data->ui, "test message");
                break;
            case KEY_DOWN:
                user_interface_active_menu_cursor_down(&data->ui);
                break;
            case KEY_UP:
                user_interface_active_menu_cursor_up(&data->ui);
                break;
            case PAGE_UP_KEY:
                user_interface_active_menu_cursor_page_up(&data->ui);
                break;
            case PAGE_DOWN_KEY:
                user_interface_active_menu_cursor_page_down(&data->ui);
                break;
            case KEY_HOME:
                user_interface_active_menu_cursor_to_first_pos(&data->ui);
                break;
            case KEY_END:
                user_interface_active_menu_cursor_to_last_pos(&data->ui);
                break;
            case USER_KEY_ENTER:
                if(user_interface_is_left_panel_active(&data->ui)) {
                    int pos;
                    pos = user_interface_active_menu_get_cursor_position(&data->ui);
                    if(panel_data_check_if_entry_by_pos_is_dir(&data->l_panel_data, pos)) {
                        int ret = panel_data_try_change_dir_to_entry_by_pos(&data->l_panel_data, pos);
                        if(ret != 0) {
                            switch(ret) {
                            case EACCES:/*Search permission is denied for one of the components of path.*/
                                user_interface_need_show_message(&data->ui, "Permission denied");
                                break;
                            case EIO:/*An I/O error occurred.*/
                                user_interface_need_show_message(&data->ui, "I/O error");
                                break;
                            case ELOOP:/*Too many symbolic links were encountered in resolving path.*/
                                user_interface_need_show_message(&data->ui, "Too many symbolic links were encountered in resolving path");
                                break;
                            case ENAMETOOLONG:/*path is too long.*/
                                user_interface_need_show_message(&data->ui, "Path is too long");
                                break;
                            case ENOENT:/*The directory specified in path does not exist.*/
                                user_interface_need_show_message(&data->ui, "The directory specified in path does not exist");
                                break;
                            case ENOMEM:/*Insufficient kernel memory was available*/
                                user_interface_need_show_message(&data->ui, "Insufficient kernel memory was available");
                                break;
                            case ENOTDIR:/*A component of path is not a directory*/
                                user_interface_need_show_message(&data->ui, "A component of path is not a directory");
                                break;
                            default:
                                user_interface_need_show_message(&data->ui, "Unknown error");
                                break;
                            }
                        } else {/* change dir was successful */
                            user_interface_l_menu_prepare_replace(&data->ui);
                            converter_panel_data_to_dir_menu_names(&data->l_panel_data,\
                                                                  (&data->ui)->l_menu_names);
                            user_interface_l_menu_post(&data->ui);
                        }
                    }
                }
                break;
            case ON_OFF_NCURSES:
                user_interface_on_off_switcher(&data->ui);
                sleep(5);
                user_interface_on_off_switcher(&data->ui);
                break;
            case QUIT:
                end_work_flag = 1;
                break;
        }
        user_interface_number_to_cmd(&data->ui, what_user_did);
        user_interface_show_message(&data->ui);
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
    /* End panel_data */
    if(panel_data_final(&data->l_panel_data) != 0) {
        perror("Can't finilize panel data\n");
        exit(1);
    }
    if(panel_data_final(&data->r_panel_data) != 0) {
        perror("Can't finilize panel data\n");
        exit(1);
    }
    return 0;
}
