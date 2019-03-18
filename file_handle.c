#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "ui_handle.h"//it declares file_handle.h as header in it

/*
	*function defintions for file_handle.h
*/

int add_to_file(struct employeeData employee, char fileName[])
{
	FILE *file;
	
	file = fopen(fileName, "ab");
	
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		//add data from the end of the file
		fwrite(&employee, sizeof(employee), 1, file);//write the data to the file
		fclose(file);
		
		return 1;
	}
}

int read_from_file(char fileName[], char readType[])
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
		if(!strcmp(readType, "READ_ALL"))
		{
			while(fread(&employee, sizeof(employee), 1, file))
			{
				//show_employee_data() prints data for the employee
				//return 0, if user doesn't want to continue
				if(!show_employee_data(employee, ++employeeNum))
				{
					fclose(file);
					return 3;//returning 3 will directly take the user to main menu
				}
			}
		}
		else
		{
			//this means only one particular employee info needs to be show..
			//the employee's id is sent as argument readType
			char employeeId[1001];			
			strcpy(employeeId, readType);
			
			while(fread(&employee, sizeof(employee), 1, file))
			{
				//show_employee_data() prints data for the employee
				//return 0, if user doesn't want to continue
				if(!strcmp(employee.id, employeeId))
				{
					fclose(file);//closes the file coz we no longer need to read the file
					
					if(show_employee_data(employee, -1))
					{
						break;
					}
					else
					{
						return 3;//returning 3 will take the user to main menu directly
					}
				}
			}
		}
		
		return 1;//returning 1 will print success message via ui_menu.c
	}
}

int exist(char fileName[], char employeeId[])
{
	struct employeeData employee;
	
	FILE *file;
	
	file = fopen(fileName, "rb");
	
	if(file != NULL)
	{
		//checks if the file contains the employee id sent as argument
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(!strcmp(employeeId, employee.id))
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int update_file(char fileName[] , char employeeId[], struct employeeData argEmployee)
{
	struct employeeData employee;
	
	FILE *file;
	
	file = fopen(fileName, "rb+");
	
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(!strcmp(employee.id, employeeId))
			{
				//found the employee data location in the file
				//now overwrites the current info with new info
				if(strcmp(argEmployee.name, "same") != 0)
				{
					strcpy(employee.name, argEmployee.name);
				}
				
				if(strcmp(argEmployee.id, "same") != 0)
				{
					strcpy(employee.id, argEmployee.id);
				}
				
				if(strcmp(argEmployee.position, "same") != 0)
				{
					strcpy(employee.position, argEmployee.position);
				}
				
				if(strcmp(argEmployee.joiningDate, "same") != 0)
				{
					strcpy(employee.joiningDate, argEmployee.joiningDate);
				}
				
				if(strcmp(argEmployee.status, "same") != 0)
				{
					strcpy(employee.status, argEmployee.status);
				}
				
				if(strcmp(argEmployee.resigningDate, "same") != 0)
				{
					strcpy(employee.resigningDate, argEmployee.resigningDate);
				}
				
				if(strcmp(argEmployee.salary, "same") != 0)
				{
					strcpy(employee.salary, argEmployee.salary);
				}
				
				//now write the new data in that location in the file
				fseek(file, -sizeof(employee), SEEK_CUR);
				fwrite(&employee, sizeof(employee), 1, file);
				fclose(file);
				return 1;
			}
		}
	}
}

int delete_employee(struct employeeData employee)
{
	
}

int found_employee(char searchStr[])
{
	
}