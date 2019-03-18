#ifndef FILE_HANDLE_H
#define FILE_HANDLE_H

//structure to deal with employee data in an organized wa
struct employeeData
{
	char name[1001];
	char id[1001];
	char position[1001];
	char joiningDate[1001];
	char resigningDate[1001];
	char status[1001];	
	char salary[1001];
};

//function prototypes
int add_to_file(struct employeeData employee, char fileName[]);
int read_from_file(char fileName[], char readType[]);
int update_file(char fileName[], char employeeId[], struct employeeData argEmployee);
int delete_employee(struct employeeData employee);
int found_employee(char searchStr[]);
int exist(char filenName[], char employeeId[]);
#endif