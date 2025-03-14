#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
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
    return Direcotory;
}

void PrintLine(char* ToPrint, int* TextColor, int* BackGroundColor) {
    TerminalSize Terminal_size;
    get_terminal_size(&Terminal_size);
    int width = Terminal_size.width;
    int ToPrintLength = strlen(ToPrint);
    for (int i = 0; i < width; i++) {
        if (ToPrintLength < i) {
            printf("\x1b[38;2;%i;%i;%im\x1b[48;2;%i;%i;%im ",TextColor[0], TextColor[1], TextColor[2],BackGroundColor[0], BackGroundColor[1], BackGroundColor[2]);}
        else{
            printf("\x1b[38;2;%i;%i;%im\x1b[48;2;%i;%i;%im%c", TextColor[0], TextColor[1], TextColor[2], BackGroundColor[0], BackGroundColor[1], BackGroundColor[2], ToPrint[i]);
        }
    }

    // Reset the colors to default at the end of the line
    printf("\x1b[0m");
}

void PrintScreen(char* TextToPrint,int CurrentLineNumber,int* LocationOfCursor, char* TheCommandBellow){
    printf("\033[H\033[J");

    int TextToPrintLength = strlen(TextToPrint);
    TerminalSize Terminal_size;
    get_terminal_size(&Terminal_size);
    int height = Terminal_size.height;
    char* Line[height];
    int CurrentLine = 0;
    for (int i = 0; i < TextToPrintLength; i++) {
        if(TextToPrint[i] == '\n'){
            CurrentLine++;
        }
        if (height + CurrentLineNumber - 2 > CurrentLine && CurrentLine > CurrentLineNumber  ) {
            printf("%c",TextToPrint[i]);
        }
    }
    int TextColor[3]; TextColor[0] = 255; TextColor[1] = 255; TextColor[2] = 255;
    int BackGroundColor[3]; BackGroundColor[0] = 0; BackGroundColor[1] = 0; BackGroundColor[2] = 0;

    PrintLine(TheCommandBellow,BackGroundColor ,TextColor);
}
char* CatDirectory(){
    char* Awnser;
    return Awnser;
}
//main
int main() {
    char ch;
    char *CurrentWorkingDirectory;
    char CommandTyped[256];
    int CommandNumber = 0;
    //printf("%s", CommandTyped);
    //TerminalSize Terminal_size; //Get it with Terminal_size.width and Terminal_size. height
    printf("\033[H\033[J");
        printf("\033[?7l");
        int *LocationOfCursor = 0;

    // Disable user input
    disable_input();
    while (1) {
        char *CurrentFile = read_file_as_string("/tmp/LastLocation");
        PrintScreen(CurrentFile, 0 ,LocationOfCursor , CommandTyped);
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
            }
        }

    }

    // Re-enable user input before exiting
    enable_input();

    printf("\nLeft The text Editor\n");
    return 0;
}
