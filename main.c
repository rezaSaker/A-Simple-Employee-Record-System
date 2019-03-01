#include<stdio.h>
#include "ui_menu.h"

int main()
{
	int exitProgram = 0;
	
	while(!exitProgram)//continue the program until user exits
	{
		char userChosenOption = on_main_menu();
		
		switch(userChosenOption)
		{
			case '1':
				view_employee_list();
				break;
			case '2':
				add_new_employee();
				break;
			case '3':
				edit_existing_employee();
				break;
			case '4':
				delete_existing_employee();
				break;
			case '5':
				exitProgram = confirm_user_decision("exit");
				break;
			default:
				show_error_message("Invalid Input!");
				break;			
		}//end of switch
		
	}//end of while 
	
	//show exit message
	printf("Thank you for using the program.");
	
	return 0;
}