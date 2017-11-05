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
    MenuConfig("info", "Show information", NULL);
    MenuConfig("echo", "Repeat your input", NULL);
    MenuConfig("time", "Show time now", NULL);
    ExecuteMenu();
    return 0;
}
