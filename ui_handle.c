#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>

#include "ui_handle.h"//it also declares file_handle.h as header in itself

/*
	*local functions
	*used by this file ui_menu.c only 
*/

int take_string_input(char *input)
{
	int i = 0;//only used for looping
	
	//the highest accepted length for input string would be 1000
	//we will take input character by character beacuse it will prevent...
	//error that may occur if user enters a string of length greater than the array size
	for(i = 0; i < 1000; i++)
	{
		scanf("%c", &input[i]);
		
		//if user hits enter, break the loop
		if(input[i] == 10)
		{
			break;
		}
	}
	input[i] = '\0'; //null char at the end will make it a full string
	
	//if user types --mm it takes the user to main menu instatntly  
	if(strcmp(input, "--mm") == 0)
	{
		return 0;
	}
	
	return 1;
}

int take_char_input(char *ch)
{
	*ch = getch();
	
	//if user press ctrl+Z, it will take the user to main menu instantly
	if(*ch == 26)
	{
		return 0;
	}
	
	return 1;
}

int to_int(char digitChar)
{
	//we know the argument passed to the funnction is always a digit.....
	//because we check it before passing it to this function
	//deleting '0' from any character that is digit.....
	//gives the int value equal to that digit char
	
	return digitChar - '0';
}

int is_double(char str[])
{
	//the string is convertible to double...
	//if it contains only digits...
	//and if it contains only one decimal point
	
	int i = 0; //this is only used for loop
	int numberOfDecimalPoints = 0;
	
	if(strlen(str) < 1) 
	{
		return 0;
	}
	else
	{
		for(i = 0; i < strlen(str); i++)
		{
			if(!isdigit(str[i]) && str[i] != '.')
			{
				return 0;
			}
			else if(str[i] == '.')
			{
				if(++numberOfDecimalPoints > 1)
				{
					return 0;
				}		
			}
		}
	}
	
	//if all conditions are passed, the string value is valid double value
	return 1;
}

int is_leap_year(int year)
{
	if(year % 4 == 0)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

int is_valid_date(char dateStr[])
{	
	int i = 0;//only used for loop
	int day, month, year, currentYear;
	
	//first check if the date is in dd/mm/yyyy for
	if(dateStr[2] != '/' || dateStr[5] != '/' || strlen(dateStr) != 10)
	{
		return 0;
	}
	
	//now check if the argument passed conatins any char other than digit
	for(i = 0; i < 10; i++)
	{
		if(i != 2 && i != 5)//char in index 3 and 5 is '/'
		{
			if(!isdigit(dateStr[i]))
			{
				return 0;
			}
		}
	}
	//split the argument dateStr into day, month and year and convert to equivalent integer
	day = (to_int(dateStr[0]) * 10) + to_int(dateStr[1]);
	month = (to_int(dateStr[3]) * 10) + to_int(dateStr[4]);
	year = (to_int(dateStr[6]) * 1000) + (to_int(dateStr[7]) * 100)
			+ (to_int(dateStr[8]) * 10) + to_int(dateStr[9]);
			
	//get current year
	char currentYearStr[5];
	time_t timer;
	struct tm* time_info;
	time(&timer);
	time_info = localtime(&timer);
	strftime(currentYearStr, 5, "%Y", time_info);
	currentYear = (to_int(currentYearStr[0]) * 1000) + (to_int(currentYearStr[1]) * 100)
			+ (to_int(currentYearStr[2]) * 10) + to_int(currentYearStr[3]);

	//check if the date is invalid
	if(year > currentYear || month > 12 || month < 1 || day > 31 || day < 1)
	{
		return 0;
	}
	else if(month == 2)
	{
		if(is_leap_year(year) && day > 29)
		{
			return 0;
		}
		else if(!is_leap_year(year) && day > 28)
		{
			return 0;
		}
	}
	else if(month % 2 == 0 && month != 8 && day > 30)
	{
		return 0;
	}
	
	//if all conditions are passed successfully, the date is valid
	return 1;
}

int take_employee_info(struct employeeData *employee)
{	
	//prompt user to enter employee info
	printf("Enter the employee information below:\n(Hint: type [same] for the fields that you don't want to change)\n\n");
	printf("\tEmployee name: ");	
	if(!take_string_input(employee->name)) 
	{
		return 0;// takes user to main menu
	}
		
	while(1)//loops until user enters valid employee id
	{
		printf("\tEmployee ID: ");
		if(take_string_input(employee->id))
		{
			if(strcmp(employee->id, "same") != 0 && exist("records.bin", employee->id))
			{
				show_error_message("The ID already belongs to another employee. Please provide an unique ID.");
			}
			else
			{
				//the id is valid , so breaks the loop and takes next input
				break;
			}
		}
		else
		{
			//user entered --mm, so terminates the current process..
			//..and takes the user to main menu directly
			return 0;
		}
	}
		
	printf("\tEmployee position: ");
	if(!take_string_input(employee->position))
	{
		return 0;//takes user to main menu
	}
		
	while(1)//loops until user enters valid date
	{
		printf("\tEmployee joining date(dd/mm/yyyy): ");
		if(!take_string_input(employee->joiningDate))
		{
			//takes the user directly to the main menu
			return 0;
		}
		else
		{
			if(strcmp(employee->joiningDate, "same") == 0 || is_valid_date(employee->joiningDate))
			{
				//breaks current loop and continue to take next input
				break;
			}
			else
			{
				//requires the user to enter date again
				show_error_message("The date is not valid. Please try again");
			}
		}
	}
		
	printf("\tChoose employee status:\n");
	printf("\t\t1 -> Current Employee\n");
	printf("\t\t2 -> Previous Employee\n");
			
	while(1)//loops until user enter valid input
	{
		char input;
				
		if(!take_char_input(&input))
		{
			return 0;//takes the user to main menu
		}
		else
		{
			if(input == '1')
			{
				strcpy(employee->status, "Current employee");
				printf("\tEmployee status: Current employee\n");
						
				//resigning date is not applicable since this is a current employee
				strcpy(employee->resigningDate, "N/A");
						
				break;
			}
			else if(input == '2')
			{
				strcpy(employee->status, "Previous employee");
				printf("\tEmployee status: Previous employee\n");
						
				//if status is prevoius employee, prompts user to enter resigning date
				while(1)//loops until user enters valid date
				{
					printf("\tEmployee resgining date(dd/mm/yyyy): ");
					if(!take_string_input(employee->resigningDate))
					{
						//breaks the loop and takes the user directly to the main menu
						return 0;
					}
					else
					{
						if(strcmp(employee->resigningDate, "same") == 0 || is_valid_date(employee->resigningDate))
						{
							//breaks the loop and continues to take next input
							break;
						}
						else
						{
							//requires the user to enter date again
							show_error_message("The date is not valid. Please try again.");
						}
					}
				}
						
				break;
			}
			else
			{
				show_error_message("Inavalid input. please try again.");
			}
		}			
	}
	
	while(1)//loops until user enters valid input 
	{
		printf("\tEmployee's salary ($): ");
		if(!take_string_input(employee->salary)) 
		{
			//breaks the loop and directly takes the user to the main menu
			return 0;
		}
		else
		{
			if(strcmp(employee->salary, "same") == 0 || is_double(employee->salary))
			{
				break;
			}
			else
			{
				show_error_message("Invalid salary. Please try again.");
			}
		}
	}
		
	return 1;
}


/*
	function definitions for ui_handle.h
*/

char on_main_menu()
{
	system("cls");//clears the screen
	
	//print the main menu
	printf("Enter the corresponding number to open that option:\n\n");
	printf("\t1 -> View Employee List\n");
	printf("\t2 -> Add New Employee\n");
	printf("\t3 -> Edit Existing Employee\n");
	printf("\t4 -> Delete Existing Employee\n");
	printf("\t5 -> Exit\n");
	
	char userInput = getch();//let user choose an option
	
	return userInput;
}

void view_employee_list()
{
	system("cls");//clears the screen
	
	int result = read_from_file("records.bin","READ_ALL");
	
	if(result == 1)
	{
		//user saw all data until end of file
		printf("\nYou have reached the  end of data. Press any key to go back to main menu.");
		
		getch();
	}
	else if(result == 2)
	{
		//no file was found 
		show_error_message("No data available.");
	}
	//else if result = 3, 
	//then, user wants to return to the main menu directly
	//and no action needs to be taken
}

void add_new_employee()
{	
	//declare identifiers
	struct employeeData employee;
	int continueAddingEmployee = 1;
	
	while(continueAddingEmployee)
	{
		system("cls");//clears the screen
		
		//prompt user to enter employee info
		printf("Enter the employee information below:\n\n");
		printf("\tEmployee name: ");
		if(!take_string_input(employee.name)) 
		{
			break;//breaks current loop and takes user to main menu
		}
		
		while(continueAddingEmployee)
		{
			printf("\tEmployee ID: ");
			if(take_string_input(employee.id))
			{
				if(exist("records.bin", employee.id))
				{
					show_error_message("The ID already belongs to another employee. Please provide an unique ID.");
				}
				else
				{
					//the id is valid becuase it doesn't belong to any other employees
					break;
				}
			}
			else
			{
				//user entered --mm, so terminates the current process..
				//..and takes the user to main menu directly
				continueAddingEmployee = 0;
				break;
			}
		}
		
		if(continueAddingEmployee)
		{
			printf("\tEmployee position: ");
			if(!take_string_input(employee.position))
			{
				break;//breaks current loop and takes user to main menu
			}
		}
		
		while(continueAddingEmployee)//loops until user enters valid date
		{
			printf("\tEmployee joining date(dd/mm/yyyy): ");
			if(!take_string_input(employee.joiningDate))
			{
				//breaks current loop and take the user directly to the main menu
				continueAddingEmployee = 0;
				break;
			}
			else
			{
				if(is_valid_date(employee.joiningDate))
				{
					//breaks current loop and continue to take next input
					break;
				}
				else
				{
					//requires the user to enter date again
					show_error_message("The date is not valid. Please try again");
				}
			}
		}
				
		while(continueAddingEmployee)//loops until user enter valid input
		{
			char input;
				
			printf("\tChoose employee status:\n");
			printf("\t\t1 -> Current Employee\n");
			printf("\t\t2 -> Previous Employee\n");
				
			if(!take_char_input(&input))
			{
				continueAddingEmployee = 0;
			}
			else
			{
				if(input == '1')
				{
					strcpy(employee.status, "Current employee");
					printf("\tEmployee status: Current employee\n");
						
					//resigning date is not applicable since this is a current employee
					strcpy(employee.resigningDate, "N/A");
						
					break;
				}
				else if(input == '2')
				{
					strcpy(employee.status, "Previous employee");
					printf("\tEmployee status: Previous employee\n");
						
					//if status is prevoius employee, prompts user to enter resigning date
					while(continueAddingEmployee)//loops until user enters valid input
					{
						printf("\tEmployee resgining date(dd/mm/yyyy): ");
						if(!take_string_input(employee.resigningDate))
						{
							//breaks the loop and takes the user directly to the main menu
							continueAddingEmployee = 0;
						}
						else
						{
							if(is_valid_date(employee.resigningDate))
							{
								//breaks the loop and continues to take next input
								break;
							}
							else
							{
								//requires the user to enter date again
								show_error_message("The date is not valid. Please try again.");
							}
						}
					}					
					break;
				}
				else
				{
					show_error_message("Invalid input. Please try again.");
				}
			}			
		}
		
		while(continueAddingEmployee)//loops until user enters valid input 
		{
			printf("\tEmployee's salary ($): ");
			if(!take_string_input(employee.salary)) 
			{
				//breaks the loop and directly takes the user to the main menu
				continueAddingEmployee = 0;
			}
			else
			{
				if(is_double(employee.salary))
				{
					break;
				}
				else
				{
					show_error_message("Invalid salary. Please try again.");
				}
			}
		}
		
		//confirm before saving the employee information
		if(continueAddingEmployee)
		{
			if(user_confirmed_decision("save_employee"))
			{
				if(add_to_file(employee, "records.bin"))
				{
					show_success_message("Employee information is successfully saved.");
				}
				else
				{
					show_error_message("Something went wrong. The employee information could not be saved.");
				}
			}
			else if(!user_confirmed_decision("save_employee"))
			{
				printf("Attention: The employee data was not saved.");
			}
			else
			{
				//user pressed ctrl+z, so the loop needs to break...
				//and take the user to main menu
				continueAddingEmployee = 0;
			}
		}

		//prompts user to choose if the user wants to add another employee data
		while(continueAddingEmployee)//loops until user enters valid input
		{
			if(user_confirmed_decision("add_another_employee"))
			{
				break;
			}
			else
			{
				continueAddingEmployee = 0;
			}
		}
	}
}

void edit_existing_employee()
{
	struct employeeData employee;
	
	char employeeId[1001];
	
	while(1)//loops until user wants to go back to main menu
	{
		system("cls");//clears the screen
		
		//prompt user to enter employee id to find and edit the employee information
		printf("Enter the employee Id: ");
		if(take_string_input(employeeId))
		{
			if(exist("records.bin", employeeId))
			{
				int result = read_from_file("records.bin", employeeId);
				
				if(result == 1)//employee found
				{
					if(user_confirmed_decision("edit_employee"))
					{
						if(take_employee_info(&employee))
						{
							if(update_file("records.bin", employeeId, employee))
							{
								show_success_message("The employee information has been successfully updated.");
							}
							else
							{
								show_error_message("Sorry, could not updated the information");
							}
						}
						else
						{
							//user entered --mm or ctrl+z..
							//so breaks the loop and takes the user directly to main menu
							break;
						}
					}
					else
					{
						printf("The employee information was not changed\n\n");
					}
					
					//prompts to check if user wants to edit another employee info
					//if not, breaks the loop and takes the user to main menu
					if(!user_confirmed_decision("edit_another_employee")) break;
				}
				else if(result == 2)//file opeing error occurred
				{
					show_error_message("Sorry, could not find the file.");
				}
				else
				{
					break;//breaks and takes the user to main menu
				}
			}
			else
			{
				char message[1001] = "No employee found with ID ";
				strcat(message, employeeId);
				show_error_message(message);
			}
		}
		else
		{
			break;//breaks the loop and takes the user to main menu
		}
	}
}

void delete_existing_employee()
{
	system("cls");//clear the screen
	
	show_error_message("Feature is currently not available. press any key to go back");
	
	getch();
}

int user_confirmed_decision(char confirmFor[])
{	
	if(!strcmp(confirmFor, "exit"))
	{	//confirmation before exiting the program			
		while(1)
		{	
			printf("Are you sure you want to exit?\n");
			printf("\t1 -> Yes\n");
			printf("\t2 -> No\n");
			
			char userInput = getch();
			
			if(userInput == '1')
			{				
				return 1;
			}
			else if(userInput == '2')
			{
				return 0;
			}
			else
			{
				show_error_message("Invalid input. Please try again.");
			}			
		}		
	}
	else if(!strcmp(confirmFor, "save_employee"))
	{
		//confirmation before saving employee data
		
		char userInput;
		
		while(1)//loops until user enters a valid value which is 1 or 2
		{	
			printf("\tDo you want to save the employee information?\n");
			printf("\t\t1 -> Yes\n");
			printf("\t\t2 -> No\n");
		
			if(!take_char_input(&userInput))
			{
				return 2;//returning 2 will take the user to main menu directly
			}
			else 
			{
				if(userInput == '1')
				{				
					return 1;
				}
				else if(userInput == '2')
				{
					return 0;
				}
				else
				{
					show_error_message("Invalid input. Please try again.");
				}	
			}	
		}	
	}
	else if(!strcmp(confirmFor, "add_another_employee"))
	{
		//confirmation before adding another employee
		
		char userInput;
		
		while(1)//loops until user enters a valid input
		{	
			printf("\tDo you want to add another employee?\n");
			printf("\t\t1 -> Yes\n");
			printf("\t\t2 -> No\n");
		
			if(take_char_input(&userInput))
			{
				if(userInput == '1')
				{				
					return 1;
				}
				else if(userInput == '2')
				{
					return 0;
				}
				else
				{
					show_error_message("Invalid input. Please try again.");
				}
			}
			else 
			{
				return 0;	
			}	
		}	
	}
	else if(!strcmp(confirmFor, "edit_employee"))
	{
		//confirmation before editing employee info
		
		char userInput;
		
		while(1)//loops until user enters a valid input
		{	
			printf("\tDo you want to edit this employee information?\n");
			printf("\t\t1 -> Yes\n");
			printf("\t\t2 -> No\n");
		
			if(take_char_input(&userInput))
			{
				if(userInput == '1')
				{				
					return 1;
				}
				else if(userInput == '2')
				{
					return 0;
				}
				else
				{
					show_error_message("Invalid input. Please try again.");
				}
			}
			else 
			{
				return 0;	
			}	
		}	
	}
	else if(!strcmp(confirmFor, "edit_another_employee"))
	{
		//confirmation before editing another employee info
		
		char userInput;
		
		while(1)//loops until user enters a valid input
		{	
			printf("\tDo you want to edit another employee information?\n");
			printf("\t\t1 -> Yes\n");
			printf("\t\t2 -> No\n");
		
			if(take_char_input(&userInput))
			{
				if(userInput == '1')
				{				
					return 1;
				}
				else if(userInput == '2')
				{
					return 0;
				}
				else
				{
					show_error_message("Invalid input. Please try again.");
				}
			}
			else 
			{
				return 0;	
			}	
		}	
	}
	else
	{	
		show_error_message("Unrecognized argument received in confirm_user_decision");
		getch();
		
		return 0;
	}	
}

int show_employee_data(struct employeeData employee, int employeeNum)
{
	//we want to show no more than 3 employee data at a time
	//so we will clear the screen after every 3 employee data is shown
	if(employeeNum % 3 == 1)
	{
		system("cls");//clears the screen 
	}
	
	if(employeeNum > -1) printf("Employee Number: %d\n", employeeNum);
	printf("\tName          : %s\n", employee.name);
	printf("\tID            : %s\n", employee.id);
	printf("\tPosition      : %s\n", employee.position);
	printf("\tJoining Date  : %s\n", employee.joiningDate);
	printf("\tStatus        : %s\n", employee.status);
	printf("\tResigning Date: %s\n", employee.resigningDate);
	printf("\tSalary        : %s\n", employee.salary);
	printf("________________________________________________\n\n");

	
	if(employeeNum % 3 == 0)
	{
		char input;
		
		printf("press any key to load more or [ctrl]+[z} to go back to main manu.");		
		if(!take_char_input(&input))
		{
			return 0;
		}
	}
	
	return 1;
}

void show_success_message(char message[])
{
	printf("\033[0;32m");//set text color to green
	printf("%s\n\n", message);
	printf("\033[0m");//set text color to default
}

void show_error_message(char message[])
{
	printf("\033[0;31m");//set text color to red
	printf("Alert: %s\n\n", message);	
	printf("\033[0m");//set text color to default
}
