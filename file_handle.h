#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

//employee data structure
struct EmployeeData
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
int File_Append(struct EmployeeData employee);
int File_ReadAll();
int File_ReadOne(char employeeId[]);
int File_Update(char employeeId[], struct EmployeeData argEmployee);
int File_Delete(char employeeId[]);
int File_ExistRecord(char employeeId[]);
int File_ExistFile(char fileName[]);
#endif