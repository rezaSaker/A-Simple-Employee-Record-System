#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include "ui_menu.h"

/*
	function definitions for ui_menu.h header filelength
*/

char on_main_menu()
{
	//clear the previous output on the screen first
	system("cls");
	
	//print the main menu
	printf("Enter the corresponding number to open that option:\n\n");
	printf("1 -> View Employee List\n");
	printf("2 -> Add New Employee\n");
	printf("3 -> Edit Existing Employee\n");
	printf("4 -> Delete Existing Employee\n");
	printf("5 -> Exit\n");
	
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
	//clear the previous output on the screen first
	system("cls");
	
	printf("feature coming soon. Press anykey to go back to main menu");
	getche();
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
	//clear the previous output on the screen first
	system("cls");
	
	if(strcmp(confirmFor, "exit") == 0)
	{
		//confirmation before exiting the program;
		while(1)
		{
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
				system("cls");//this will clear the screen
				printf("Invalid input. Please try again\n\n"); 
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