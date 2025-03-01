#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "Lib/string_utils/string_utils.h"
#include "Lib/input_control/input_control.h"
#include "Lib/Terminal_Size/terminal_size.h"
#include "Lib/file_reader/file_reader.h"
#include "Lib/LoadDirectory/LoadDirectory.h"


char* apply( char* CommandTyped){
    char* Direcotory = NULL;
    if(!strcmp(ToLowerChar(CommandTyped), ":q"))
    {
        //exit the code
        printf("\033[H\033[J");  //clear screen
        enable_input();
        exit(0);
    }else if(!strcmp(ToLowerChar(CommandTyped), ":dir"))
    {
        system("echo /home > /tmp/LastLocation");
        char *CurrentDirectory = read_file_as_string("/tmp/LastLocation");
        Direcotory = (LoadDirectory(CurrentDirectory));
        return Direcotory;
    }
    printf("%s",CommandTyped);
    printf("\n Apply was called\n");
    return Direcotory;
}



//main
int main() {
    char ch;
    char *CurrentWorkingDirectory;
    char CommandTyped[256];
    int CommandNumber = 0;
    printf("%s", CommandTyped);
    //TerminalSize Terminal_size; //Get it with Terminal_size.width and Terminal_size. height
    printf("\033[H\033[J"); 

    // Disable user input
    disable_input();
    while (1) {
        
        ch = getchar();
        
        if(ch == '\n'){
            //If pressed Enter
            
            CurrentWorkingDirectory = apply(CommandTyped);
            FreeFullString(CommandTyped);
            CommandNumber = 0;
            printf("%s", CurrentWorkingDirectory);

        }else if(ch == 27){
            //If presed Esc reset the command type for user to be able to write the next command
            FreeFullString(CommandTyped);
            CommandNumber = 0;
            printf("\033[H\033[J"); 
        }else{
            if(ch == 127){
                CommandTyped[CommandNumber - 1] = '\0';
                CommandNumber--;
                printf("%c",'\\');
            }else{
                CommandTyped[CommandNumber] = ch;            //If pressed Enter

                CommandNumber++;
                printf("%c",ch);
            }
        }
        
    }

    // Re-enable user input before exiting
    enable_input();

    printf("\nLeft The text Editor\n");
    return 0;
}
