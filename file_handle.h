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
int save_to_file(struct employeeData employee, char fileName[]);
int read_and_show_from_file(char fileName[]);
int add_to_data_struct(struct employeeData employee);
int remove_from_data_struct(struct employeeData employee);
int lookup_employee(char searchStr[]);

#endif