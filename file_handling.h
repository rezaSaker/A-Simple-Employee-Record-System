#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

//structure to deal with employee data in an organized wa
struct employeeData
{
	char name[1000];
	char id[100];
	char position[1000];
	char joiningDate[1000];
	char resigningDate[1000];
	char status[100];	
	char salary[100];
};

//function prototypes
int save_to_file(struct employeeData employee, char fileName[]);
int read_and_show_from_file(char fileName[]);
int add_to_data_struct(struct employeeData employee);
int remove_from_data_struct(struct employeeData employee);
int lookup_employee(char searchStr[]);

#endif