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
   optind = 0;	//如果没有这句，循环不在有用。
   return 0;
}
int Echo(int argc, char** argv)\
{
    printf("Repeat your input.\n");
    return 0;
}
int Time(int argc, char** argv)
{
    printf("Show time now.\n");
    return 0;
}


int main(int argc, char** argv)
{
    /*char* cmd;
    char* desc;
    int (*handler)();*/
    MenuConfig("help", "This is help cmd", Help);
    MenuConfig("quit", "Quit the program", Quit);
    MenuConfig("info", "Show information", Info);
    MenuConfig("echo", "Repeat your input", Echo);
    MenuConfig("time", "Show time now", Time);
    ExecuteMenu();
    return 0;
}
