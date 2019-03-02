#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include "ui_menu.h"

//structure to deal with employee data in an organized way
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

/*
	*local functions
	*used by this file ui_menu.c only 
*/
int take_string_input(char *input)
{
	scanf(" %[^\n]s", input);
	
	//if user types --out it takes him to main menu instatntly  
	if(strcmp(input, "--out") == 0)
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
	//we know the argument passed to this function
	//is in dd/mm/yyyy format 
	//and each character is a digit except '/' char
	//because we check it before passing it to this function
	
	int i = 0;//this is only used for loop
	int day, month, year;
	
	//parse the argument dateStr into day, month and year
	day = (to_int(dateStr[0]) * 10) + to_int(dateStr[1]);
	month = (to_int(dateStr[3]) * 10) + to_int(dateStr[4]);
	year = (to_int(dateStr[6]) * 1000) + (to_int(dateStr[7]) * 100)
			+ (to_int(dateStr[8]) * 10) + to_int(dateStr[9]);
	
	//check if the date is invalid
	if(month > 12 || month < 1 || day > 31 || day < 1)
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
	
	//if passes all condiiton successfully, the date is valid
	return 1;
}

int take_date_input(char *date)
{
	int i;//used only for loop
	int j = 0;//used as index of date char array
	char input;
	
	for(i = 0; i < 8; i++)
	{
		if(!take_char_input(&input))
		{
			return 0;
		}
		
		//check if the value is digit, only digit is valid input
		if(isdigit(input))
		{
			printf("%c", input);
			date[j++] = input;
			
			//print '/' sign after every two digits to show format like dd/mm/yyyy
			if(i % 2 == 1 && i < 5)
			{
				printf("/");
				date[j++] = '/';
			}
		}
		else
		{
			//decrease i by 1 so that it loops one more time
			i--;
		}
	}
	
	//null char at the end of date array will make it a full string
	date[j] = '\0';
	
	printf("\n");
	
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
	function definitions for ui_menu.h header filelength
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
	
	printf("feature coming soon. Press anykey to go back to main menu");
	getche();	
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
		
		while(continueAddingEmployee)
		{
			printf("\tEmployee joining date(dd/mm/yyyy): ");
			if(!take_date_input(employee.joiningDate))
			{
				continueAddingEmployee = 0;
				break;
			}
			
			if(is_valid_date(employee.joiningDate))
			{
				break;
			}
			else
			{
				printf("Alert: The date is not valid! Please try again\n");
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
						if(!take_date_input(employee.resigningDate))
						{
							continueAddingEmployee = 0;
							break;
						}
						
						if(is_valid_date(employee.resigningDate))
						{
							break;
						}
						else
						{
							printf("Alert: The date is not valid! Please try again\n");
						}
					}
					break;
				}
			}
		}
		
		while(continueAddingEmployee)//loops until user enters valid input 
		{
			printf("\tEmployee salary ($): ");
			if(!take_string_input(employee.salary)) break;
			
			if(is_convertable_to_double(employee.salary))
			{
				break;
			}
			else
			{
				printf("Alert: Invalid input for salary. Please try again.\n");
			}
		}
		
		//confirm before saving the employee information
		if(continueAddingEmployee && confirm_user_decision("add_employee"))
		{
			//save_employee_data(&employee)
			printf("\tEmployee information is successfully saved.\n\n");
		}

		//prompt user to choose if the user wants to add another employee data
		while(continueAddingEmployee)//loops until user enters valid input
		{
			char input;
			
			printf("Press [y] to add another employee or press [n] to go back to main menu.\n");
			
			if(!take_char_input(&input))
			{
				continueAddingEmployee = 0;
				break;
				
			}
			
			if(input == 'n' || input == 'N')
			{
				continueAddingEmployee = 0;
				break;
			}
			else if(input == 'y' || input == 'Y')
			{
				break;
			}
			else
			{
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

