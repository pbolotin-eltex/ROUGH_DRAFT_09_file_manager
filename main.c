#include "file_manager.h"

file_manager_data data;

int main(void) {
    file_manager_init(&data);
    sleep(5);
    file_manager_final(&data);
    return 0;
}
