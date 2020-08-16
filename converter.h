/**********************************************************************
 * Converter module, header file
 * This module need to translate data from one kind of data to another.
 * For example: from system datatypes that are presenting 
 * the struct of directory to the user-interface datatype.
 * That is good for user to work with it
 *********************************************************************/
#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <string.h>
#include "panel_data.h"
#include "user_interface.h"

int converter_panel_data_to_dir_menu_names(panel_data* p_d, dir_menu_names* d_m_n);

#endif
