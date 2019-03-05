#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>
#include "ui_menu.h"
#include "file_handling.h"

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
	
	//if user types --out it takes him to main menu instatntly  
	if(strcmp(input, "--mm") == 0)
	{
		return 0;
	}
	
	return 1;
}

int take_char_input(char *ch)
{
	*ch = getch();
	
	//if user pressed ctrl + z, it will take the user to main menu instantly
	if(*ch == 26)
	{
		return 0;
	}
	
	return 1;
}

int to_int(char digitChar)
{
	//we know the argument passed to the funnction is always a digit
	//because we check it before passing it to this function
	//deleting '0' from any character that is digit 
	//gives the int value equal to that digit char
	
	return digitChar - '0';
}

int is_leap_year(int year)
{
	if(year % 4 == 0 && year % 100 != 0)
	{
		return 1;
	}
	else if(year % 100 == 0 && year % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_valid_date(char dateStr[])
{	
	int i = 0;//this is only used for loop
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
	
	//if all condition passed successfully, the date is valid
	return 1;
}

int is_convertable_to_double(char str[])
{
	//the string is convertible to double
	//if it contains only digits
	//f it contains only one decimal point
	
	int i = 0; //this is only used for loop
	int numberOfDecimalPoints = 0;
	
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
	
	return 1;
}

/*
	function definitions for ui_menu.h header file
*/

char on_main_menu()
{
	//clear the previous output on the screen first
	system("cls");
	
	//print the main menu
	printf("Enter the corresponding number to open that option:\n\n");
	printf("\t1 -> View Employee List\n");
	printf("\t2 -> Add New Employee\n");
	printf("\t3 -> Edit Existing Employee\n");
	printf("\t4 -> Delete Existing Employee\n");
	printf("\t5 -> Exit\n");
	
	//let user choose option
	char userInput = getch();
	
	return userInput;
}

void view_employee_list()
{
	//clear the previous output on the screen first
	system("cls");
	
	int userViewResult = read_and_show_from_file("records.bin");
	
	if(userViewResult == 1)
	{
		//user saw all data until end of file
		printf("\nYou have reached end of file. Press any key to go back to main menu.");
		getch();
	}
	else if(userViewResult == 2)
	{
		//no file was found 
		show_error_message("No data available.");
	}
	//else if userViewResult = 3, 
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
		//clear the previous output on the screen first
		system("cls");
		
		//prompt user for input employee info
		printf("Enter the employee information:\n\n");
		printf("\tEmployee name: ");
		if(!take_string_input(employee.name)) break;
		
		printf("\tEmployee ID: ");
		if(!take_string_input(employee.id)) break;
		
		printf("\tEmployee position: ");
		if(!take_string_input(employee.position)) break;
		
		while(continueAddingEmployee)//loops until user enter valid date
		{
			printf("\tEmployee joining date(dd/mm/yyyy): ");
			if(!take_string_input(employee.joiningDate))
			{
				//will break current loop and take the user directly to the main menu
				continueAddingEmployee = 0;
				break;
			}
			else
			{
				if(is_valid_date(employee.joiningDate))
				{
					//will break this loop and continue to take next input
					break;
				}
				else
				{
					//will require the user to enter date again
					printf("Alert: The date is not valid! Please try again\n");
				}
			}
		}
		
		if(continueAddingEmployee)
		{
			printf("\tChoose employee status:\n");
			printf("\t\t1 -> Current Employee\n");
			printf("\t\t2 -> Previous Employee\n");
			while(continueAddingEmployee)//loops until user enter valid input
			{
				char input;
				
				if(!take_char_input(&input))
				{
					continueAddingEmployee = 0;
					break;
				}
				
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
					
					//if status is prevoius employee, prompt user for resigning date
					while(continueAddingEmployee)//loops until user enters valid input
					{
						printf("\tEmployee resgining date(dd/mm/yyyy): ");
						if(!take_string_input(employee.resigningDate))
						{
							//will break the loop and take the user directly to the main menu
							continueAddingEmployee = 0;
							break;
						}
						else
						{
							if(is_valid_date(employee.resigningDate))
							{
								//break the loop and continue to take next input
								break;
							}
							else
							{
								//will require the user to enter date again
								printf("Alert: The date is not valid! Please try again\n");
							}
						}
					}
					
					break;
				}
				//else the loop continues until user enters valid input (1 or 2 or ctrl+z)
			}
		}
		
		while(continueAddingEmployee)//loops until user enters valid input 
		{
			printf("\tEmployee salary ($): ");
			if(!take_string_input(employee.salary)) 
			{
				//will break the loop and directly take the user to the main menu
				continueAddingEmployee = 0;
				break;
			}
			else
			{
				if(is_convertable_to_double(employee.salary))
				{
					break;
				}
				else
				{
					printf("Alert: Invalid input for salary. Please try again.\n");
				}
			}
		}
		
		//confirm before saving the employee information
		if(continueAddingEmployee && confirm_user_decision("add_employee"))
		{
			if(save_to_file(employee, "records.bin"))
			{
				printf("\tEmployee information is successfully saved.\n\n");
			}
			else
			{
				show_error_message("The employee data could not be saved.");
			}
		}

		//prompt user to choose if the user wants to add another employee data
		while(continueAddingEmployee)//loops until user enters valid input
		{
			char input;
			
			printf("Press [y] to add another employee or press [n] to go back to main menu.\n");
			
			if(!take_char_input(&input) || input == 'n' || input == 'N')
			{
				//break and take user to to main menu
				continueAddingEmployee = 0;
				break;			
			}
			else if(input == 'y' || input == 'Y')
			{
				//break and continue taking input for another employee
				break;
			}
			else
			{
				//continue the loop until a valid input is given
				printf("\a");//it gives an alert due to invalid input
			}
		}
	}
}

void edit_existing_employee()
{
	//clear the previous output on the screen first
	system("cls");
	
	printf("feature coming soon. Press anykey to go back to main menu");
	getche();
}

void delete_existing_employee()
{
	//clear the previous output on the screen first
	system("cls");
	
	printf("feature coming soon. Press anykey to go back to main menu");
	getche();
}

int confirm_user_decision(char confirmFor[])
{	
	if(strcmp(confirmFor, "exit") == 0)
	{
		//confirmation before exiting the program;
		while(1)
		{
			//clear the previous output on the screen first
			system("cls");
			
			//print the confirm message
			printf("Are you sure you want to exit?\n");
			printf("\t1 -> Yes\n");
			printf("\t2 -> No\n");
			
			//let the user confirm by entering 1 or 2
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
				printf("Invalid input. Please try again\n\n"); 
			}			
		}		
	}
	else if(strcmp(confirmFor, "add_employee") == 0)
	{
		//confirmation before saving employee
		printf("\tDo you want to save the employee information?\n");
		printf("\t\t1 -> Yes\n");
		printf("\t\t2 -> No\n");
		
		while(1)
		{	
			//let the user confirm by entering 1 or 2
			char userInput = getch();
			
			if(userInput == '1')
			{				
				return 1;
			}
			else if(userInput == '2')
			{
				return 0;
			}			
		}	
	}
	else
	{
		printf("unrecognized argument error\n");
		printf("press any key to go back");
		getche();
		return 0;
	}	
}

int show_employee_data(struct employeeData employee, int employeeNum)
{
	//we want to show no more than five employee data at a time
	//so we will clear the screen after every five employee data is shown
	if(employeeNum % 5 == 1)
	{
		system("cls");//this will clear the screen 
	}
	
	printf("Employee Number : %d\n", employeeNum);
	printf("\tName          : %s\n", employee.name);
	printf("\tID            : %s\n", employee.id);
	printf("\tPosition      : %s\n", employee.position);
	printf("\tJoining Date  : %s\n", employee.joiningDate);
	printf("\tStatus        : %s\n", employee.status);
	printf("\tResigning Date: %s\n", employee.resigningDate);
	printf("\tSalary        : %s\n", employee.salary);
	printf("\n");
	
	if(employeeNum % 5 == 0)
	{
		char input;
		
		printf("press any key to load more or [ctrl] + [z] to go back to main manu.");
		if(!take_char_input(&input))
		{
			return 0;
		}
	}
	
	return 1;
}

void show_error_message(char message[])
{
	//clear the previous output on the screen first
	system("cls");
	
	printf("\a");//gives a lttle alert
	printf("%s\n\n", message);
	
	printf("Press any key to go back");
	getche();
}

/*
	*functions that are used only by the members of this file
*/

