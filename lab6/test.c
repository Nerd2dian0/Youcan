#include"menu.h"
#include<string.h>
#include<stdio.h>
#include<unistd.h>

int Info(int argc, char** argv)
{
    opterr = 0;
    int oc;
    while((oc = getopt(argc, argv, "nv")) != -1)
      {
        switch(oc)
        {
            case 'n':
                printf("The author name is Nerd2dian0.\n");
                break;
            case 'v':
                printf("The version is 1.01.\n");
                break;
        }
    }
   return 0;
}
}

int main(int argc, char** argv)
{
    /*char* cmd;
    char* desc;
    int (*handler)();*/
    MenuConfig("help", "This is help cmd", Help);
    MenuConfig("quit", "Quit the program", Quit);
    MenuConfig("info", "Show information", Info);
    MenuConfig("echo", "Repeat your input", NULL);
    MenuConfig("time", "Show time now", NULL);
    ExecuteMenu();
    return 0;
}
