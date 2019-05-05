#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#include "../include/ui_handle.h"
#include "../include/file_handle.h"

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

struct UI_EmployeeData ToUIEmployeeData(struct EmployeeData employee)
{
	struct UI_EmployeeData retEmployee;
	
	strcpy(retEmployee.name, employee.name);
	strcpy(retEmployee.id, employee.id);
	strcpy(retEmployee.position, employee.position);
	strcpy(retEmployee.joiningDate, employee.joiningDate);
	strcpy(retEmployee.status, employee.status);
	strcpy(retEmployee.resigningDate, employee.resigningDate);
	strcpy(retEmployee.salary, employee.salary);
	strcpy(retEmployee.address, employee.address);
	strcpy(retEmployee.phone, employee.phone);
	strcpy(retEmployee.email, employee.email);
	strcpy(retEmployee.description, employee.description);
	
	return retEmployee;
}

/*
	*public functions
	*used by any file that declares file_handle.h as header
*/

int File_Append(struct EmployeeData employee)
{
	FILE *file;
	
	if(file = fopen("records.bin", "ab"))
	{
		fwrite(&employee, sizeof(employee), 1, file);
		
		fclose(file);	
		return 1;
	}
	
	return 0;
}

int File_ReadAll()
{
	int employeeNum = 0;
	
	struct EmployeeData employee;
	
	FILE *file;
	
	if(file = fopen("records.bin", "rb"))
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(!UI_Display(ToUIEmployeeData(employee), ++employeeNum))
			{
				fclose(file);
				return 0;
			}
		}
		
		fclose(file);
		return 1;
	}
	
	return 0;
}

int File_ReadOne(char employeeId[])
{
	struct EmployeeData employee;
	
	FILE *file;
	
	if(file = fopen("records.bin", "rb"))
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(IsEqualStr(employee.id, employeeId))
			{
				fclose(file);
					
				if(UI_Display(ToUIEmployeeData(employee), -1))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		fclose(file);
	}
	
	return 0;
}

int File_ExistRecord(char employeeId[])
{
	struct EmployeeData employee;
	
	FILE *file;
	
	if(file = fopen("records.bin", "rb"))
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(IsEqualStr(employeeId, employee.id))
			{
				fclose(file);
				return 1;
			}
		}
		fclose(file);
	}
	
	return 0;
}

int File_Update(char employeeId[], struct EmployeeData argEmployee)
{
	struct EmployeeData employee;
	
	FILE *file;
	
	if(file = fopen("records.bin", "rb+"))
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
		fclose(file);
	}
	
	return 0;
}

int File_DeleteRecord(char employeeId[])
{
	FILE *file;
	FILE *temp_file;
	
	struct EmployeeData employee;
	
	file = fopen("records.bin", "rb");
	temp_file = fopen("temp_records.bin", "wb+");
	if(file != NULL && temp_file != NULL)
	{
		while(fread(&employee, sizeof(employee), 1, file))
		{
			if(!IsEqualStr(employee.id, employeeId))
			{
				fwrite(&employee, sizeof(employee), 1, temp_file);
			}
		}
		fclose(file);
		fclose(temp_file);
		remove("records.bin");
		rename("temp_records.bin", "records.bin");
		return 1;
	}
	
	return 0;
}

int File_ExistFile(char fileName[])
{
	FILE *file;
	
	if(file = fopen(fileName, "r"))
	{
		fclose(file);
		return 1;
	}
	
	return 0;
}