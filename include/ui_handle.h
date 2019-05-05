#ifndef UI_HANDLE_H
#define UI_HANDLE_H

//employee data structure
struct UI_EmployeeData
{
	char name[1001];
	char id[1001];
	char position[1001];
	char joiningDate[1001];
	char resigningDate[1001];
	char status[1001];	
	char salary[1001];
	char address[1001];
	char phone[1001];
	char email[1001];
	char description[1001];
};

//function prototypes
char UI_OnMainMenu();
void UI_ShowRecord();
void UI_AddRecord();
void UI_EditRecord();
void UI_DeleteRecord();
int UI_UserConfirmed(char confirmFor[]);
int UI_Display(struct UI_EmployeeData employee, int employeeNum);
void UI_ShowSuccessMsg(char message[]);
void UI_ShowErrorMsg(char message[]);

#endif