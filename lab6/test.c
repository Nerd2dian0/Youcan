#include"menu.h"
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char** argv)
{
    /*char* cmd;
    char* desc;
    int (*handler)();*/
    MenuConfig("help", "This is help cmd", Help);
    MenuConfig("quit", "Quit the program", Quit);
    MenuConfig("hello", "This is a test cmd", Hello);
    ExecuteMenu();
    return 0;
}
