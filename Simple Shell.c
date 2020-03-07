#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



void handler()
{
    FILE *fptr;
    fptr = fopen("log.txt","a");
    fprintf(fptr,"Child process was terminated\n");
    fclose(fptr);
}

int main()
{
    char input[100];
    char *string[100];
    char delimit[] = " ";
    pid_t ID;

   signal(SIGCHLD, handler);

    /// Get input and split
    while (1)
{
    int i=0;
    int thread = 0;
    if(fgets(input, sizeof input, stdin)) {
        /// removes new line from input
        int len = strlen(input);
        if( input[len-1] == '\n' )
        input[len-1] = 0;

        string[i]=strtok(input,delimit);
        while(string[i]!=NULL) {
            i++;
            string[i]=strtok(NULL,delimit);
        }
    }

    /// exit
    if(strcmp(string[0], "exit" )==0){
    exit(0);
    }

    /// Background execution
    if(strcmp(string[i-1], "&" )==0){
    thread=1;
    string[i-1] = NULL;
    }

    ID = fork();

    /// Child Process
    if (ID == 0){
    if ( execvp(string[0], string) == -1 ){ printf("Error \n"); }
    exit(0);
    }

    /// Parent Process
    else if (ID >0) {

    /// No Thread
    if(!thread){
    printf("\n"); 
    while (wait() > 0){} ///when there are no child processes to wait for it returns -1
    }

    else {
        printf("\n");
    }

    }

}
    return 0;
}
