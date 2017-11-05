//增添命令函数
int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]));
//将具体的命令加入链表
int ExecuteMenu();
int Help(int argc, char **argv);
int Quit(int argc, char **argv);
