#include "file_handling.h"

#ifndef USER_DEF_FUNCS_H
#define USER_DEF_FUNCS_H

//function prototypes
char on_main_menu();
void view_employee_list();
void add_new_employee();
void edit_existing_employee();
void delete_existing_employee();
int confirm_user_decision(char confirmFor[]);
int show_employee_data(struct employeeData employee, int employeeNum);
void show_error_message(char message[]);
void set_text_color(char color[]);

#endif