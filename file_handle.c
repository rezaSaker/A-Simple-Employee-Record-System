#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "ui_handle.h"
#include "file_handle.h"

/*
	*function defintions for file_handling.harderr
*/

int save_to_file(struct employeeData employee, char fileName[])
{
	FILE *file;
	
	file = fopen(fileName, "ab");
	
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		fseek(file, 0, SEEK_END);//find the end of file and start adding data from there
		fwrite(&employee, sizeof(employee), 1, file);//write the data to the file
		fclose(file);
		
		return 1;
	}
}

int read_and_show_from_file(char fileName[])
{
	int employeeNum = 0;//used to count number of employees
	
	struct employeeData employee;
	
	FILE *file;
	
	file = fopen(fileName, "rb");
	
	if(file == NULL)
	{
		return 2;//returning 2 will show error message via ui_menu.c 
	}
	else
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			//show_employee_data() prints data for the employee
			//return 0, if user doesn't want to continue
			if(!show_employee_data(employee, ++employeeNum))
			{
				return 3;//returning 3 will directly take the user to main menu
			}
		}
		fclose(file);
		
		return 1;//returning 1 will print success message via ui_menu.c
	}
}

int add_to_data_struct(struct employeeData employee)
{
	
}

int remove_from_data_struct(struct employeeData employee)
{
	
}

int lookup_employee(char searchStr[])
{
	
}