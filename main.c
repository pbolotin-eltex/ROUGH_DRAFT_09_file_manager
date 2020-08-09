#include "file_manager.h"

file_manager_data data;

int main(void) {
    file_manager_init(&data);
    file_manager_work(&data);
    file_manager_final(&data);
    return 0;
}
