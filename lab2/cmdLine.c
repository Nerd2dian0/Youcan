#include<stdio.h>
#include<stdlib.h>

int main()
{
    char cmd[128];
    while(1)
    {
    	scanf("%s",cmd);
	if(strcmp(cmd,"help")==0)
       	{
	    printf("This is help cmd!\n");
	}
        else if(strcmp(cmd,"quit")==0)
	    {
		exit(0);
	    }
	else if(strcmp(cmd,"open")==0)
	    {
		printf("You will open a file!\n");
	    } 
	else if(strcmp(cmd,"read")==0)
	    {
		printf("You will read the  file!\n");
	    }		
	else if(strcmp(cmd,"write")==0)
            {
	        printf("You can write!\n");
	    }
	else if(strcmp(cmd,"back")==0)
	    {
		printf("revocation?(Y/N)\n");
	    }	
	else if(strcmp(cmd,"boss")==0)
	    {
	        printf("Yeap,it's you!\n");
	    }
	else 
	    {
	    printf("Wrong cmd!\n");
	    }
    }
}

