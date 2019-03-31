#include<stdio.h>
#include "ui_handle.h"

int main()
{
	int exitProgram = 0;
	
	while(!exitProgram)//continue the program until user exits
	{
		char userChosenOption = UI_OnMainMenu();
		
		switch(userChosenOption)
		{
			case '1':
				UI_ShowRecord();
				break;
			case '2':
				UI_AddRecord();
				break;
			case '3':
				UI_EditRecord();
				break;
			case '4':
				UI_DeleteRecord();
				break;
			case '5':
				if(UI_UserConfirmed("exit")) exitProgram = 1;
				break;
			default:
				UI_ShowErrorMsg("Invalid Input. Please try again.");
				break;			
		}		
	}
	
	UI_ShowSuccessMsg("The program has been successfully closed. Thank you for using this program.");
	
	return 0;
}