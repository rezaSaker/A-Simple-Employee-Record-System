#include<stdio.h>
#include "ui_handle.h"

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
				if(user_confirmed_decision("exit"))
				{
					exitProgram = 1;
				}
				else
				{
					exitProgram = 0;
				}
				break;
			default:
				show_error_message("Invalid Input. Please try again.");
				break;			
		}//end of switch
		
	}//end of while 
	
	//show exit message
	show_success_message("The program has been successfully closed. Thank you for using this program.");
	
	return 0;
}