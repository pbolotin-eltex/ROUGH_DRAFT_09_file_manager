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

int file_manager_final(file_manager_data* data) {
    /* End user interface */
    if(user_interface_final(&data->ui) != 0) {
        perror("Can't initialize user interface\n");
        exit(1);
    }
    return 0;
}
