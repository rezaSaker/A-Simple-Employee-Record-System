#include "file_handle.h"

#ifndef UI_HANDLE_H
#define UI_HANDLE_H

//function prototypes
char UI_OnMainMenu();
void UI_ShowRecord();
void UI_AddRecord();
void UI_EditRecord();
void UI_DeleteRecord();
int UI_UserConfirmed(char confirmFor[]);
int UI_Display(struct EmployeeData employee, int employeeNum);
void UI_ShowSuccessMsg(char message[]);
void UI_ShowErrorMsg(char message[]);

#endif