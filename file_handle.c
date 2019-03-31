#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "ui_handle.h"//also declares file_handle.h as header in itself

/*
	*private functions
	*only used by this file, file_handle.c
*/

static int IsEqualStr(char str1[], char str2[])
{
	if(strlen(str1) != strlen(str2))
	{
		return 0;
	}
	
	int i;
	for(i = 0; i < str1[i] != '\0'; ++i)
	{
		if(str1[i] != str2[i])
		{
			return 0;
		}	
	}
	
	return 1;
}

/*
	*public functions
	*used by any file that declares file_handle.h as header
*/

int File_Append(struct EmployeeData employee)
{
	FILE *file;
	
	file = fopen("records.bin", "ab");
	
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		fwrite(&employee, sizeof(employee), 1, file);
		fclose(file);
		
		return 1;
	}
}

int File_ReadAll()
{
	int employeeNum = 0;//used to count number of employees
	
	struct EmployeeData employee;
	
	FILE *file;
	
	file = fopen("records.bin", "rb");
	
	if(file == NULL)
	{
		return 2;
	}
	else
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(!UI_Display(employee, ++employeeNum))
			{
				fclose(file);
				return 3;
			}
		}
		
		return 1;
	}
}

int File_ReadOne(char employeeId[])
{
	struct EmployeeData employee;
	
	FILE *file;
	
	file = fopen("records.bin", "rb");
	
	if(file == NULL)
	{
		return 2; 
	}
	else
	{			
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(IsEqualStr(employee.id, employeeId))
			{
				fclose(file);
					
				if(UI_Display(employee, -1))
				{
					break;
				}
				else
				{
					return 3;
				}
			}
		}
		
		return 1;
	}
}

int File_ExistRecord(char employeeId[])
{
	struct EmployeeData employee;
	
	FILE *file;
	
	file = fopen("records.bin", "rb");
	
	if(file != NULL)
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(IsEqualStr(employeeId, employee.id))
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int File_Update(char employeeId[], struct EmployeeData argEmployee)
{
	struct EmployeeData employee;
	
	FILE *file;
	
	file = fopen("records.bin", "rb+");
	
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(IsEqualStr(employee.id, employeeId))
			{
				if(!IsEqualStr(argEmployee.name, "same"))
				{
					strcpy(employee.name, argEmployee.name);
				}
				
				if(!IsEqualStr(argEmployee.id, "same"))
				{
					strcpy(employee.id, argEmployee.id);
				}
				
				if(!IsEqualStr(argEmployee.position, "same"))
				{
					strcpy(employee.position, argEmployee.position);
				}
				
				if(!IsEqualStr(argEmployee.joiningDate, "same"))
				{
					strcpy(employee.joiningDate, argEmployee.joiningDate);
				}		
				
				strcpy(employee.status, argEmployee.status);
				
				if(!IsEqualStr(argEmployee.resigningDate, "same"))
				{
					strcpy(employee.resigningDate, argEmployee.resigningDate);
				}
				
				if(!IsEqualStr(argEmployee.salary, "same"))
				{
					strcpy(employee.salary, argEmployee.salary);
				}
				
				fseek(file, -sizeof(employee), SEEK_CUR);
				fwrite(&employee, sizeof(employee), 1, file);
				fclose(file);
				return 1;
			}
		}
	}
}

int File_delete(struct EmployeeData employee)
{
	
}