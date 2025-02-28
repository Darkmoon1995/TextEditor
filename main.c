#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "string_utils/string_utils.h"
#include "input_control/input_control.h"
#include "Terminal_Size/terminal_size.h"
#include "file_reader/file_reader.h"

char* LoadDirectory(char *CurrentDirectory){
    printf("\033[H\033[J"); 
    char DirecotryForLsHelper[1024]; 
    
    sprintf(DirecotryForLsHelper, "ls -p %s > /tmp/FileLocationForCodeEditor", CurrentDirectory);
    

    system(DirecotryForLsHelper);
    
    char *FullDirectoryContext = read_file_as_string("/tmp/FileLocationForCodeEditor");
    //Gets the start And helps witht the last one
    int startOfText[1025];
    int LineNumber = 0;
    int HowManyChoises = 0;

    for(int Length = 0;Length < (int)strlen(FullDirectoryContext);Length++ ){
        if(FullDirectoryContext[Length] == '\n'){
            if(startOfText[LineNumber] != 1){
                startOfText[LineNumber] = 0;
            }
            LineNumber++;
        }
        if(FullDirectoryContext[Length] == '/' ){
            startOfText[LineNumber] = 1;
        }
    }
    HowManyChoises = LineNumber;
    int CurrentChoise = 0;
    int DirecotryForLsHelperValueNumber = 1;
    while (1) {
        LineNumber = 0;
        printf("\033[0m\n");
        printf("\033[H\033[J"); 

    for(int Length = 0;Length < (int)strlen(FullDirectoryContext);Length++ ){
            if(CurrentChoise != LineNumber ){
                if(startOfText[LineNumber] == 1){
                    printf("\033[1;34m%c\033[0m",FullDirectoryContext[Length]);
                }else{
                    printf("\033[0m%c\033[0m",FullDirectoryContext[Length]);
                }
            }else{
                printf("\033[30;47m%c\033[0m",FullDirectoryContext[Length]);
            }
            if(FullDirectoryContext[Length] == '\n'){
                LineNumber++;
                printf("\n");
            }
        }
        printf("\n\033[31;47m Q = Quit\033[0m");
        printf("\n%i\n", CurrentChoise);
        char ch = getchar();
        if(ch == 'q'){
            break;
        }else if(ch == 65){
            //Down Key
            CurrentChoise = (CurrentChoise + HowManyChoises)% (HowManyChoises + 1);
        }else if(ch == 66){
            CurrentChoise = (CurrentChoise + 1)% (HowManyChoises + 1);
        }else if(ch == '\n'){
            FreeFullString(DirecotryForLsHelper);
            LineNumber = 0;
            for(int i = 0;i < (int)strlen(FullDirectoryContext);i++){
                if(LineNumber == CurrentChoise && FullDirectoryContext[i] != '\n' ){
                    DirecotryForLsHelper[0] = '/';

                    DirecotryForLsHelper[DirecotryForLsHelperValueNumber] = FullDirectoryContext[i];
                    DirecotryForLsHelperValueNumber++;
                    continue;
                }
                
                if(FullDirectoryContext[i] == '\n'){
                    LineNumber++;
                }
            }
            
            char combined[10000]; 
            
            if(DirecotryForLsHelper[DirecotryForLsHelperValueNumber - 1] == '/'){
                snprintf(combined, sizeof(combined),"%s%s",CurrentDirectory,DirecotryForLsHelper);
                return LoadDirectory(combined);
            }else{
                //Call The txt Editor 
                snprintf(combined, sizeof(combined),"%s%s",CurrentDirectory,DirecotryForLsHelper);
                char *returnAwenser = combined;
                return returnAwenser;
            }
        }
    }
    return NULL;
}
    



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
                CommandTyped[CommandNumber] = ch;
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
