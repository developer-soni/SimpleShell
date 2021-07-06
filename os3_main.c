/**************************************************************
* Project: Assignment 3 – Simple Shell
*
* File: os3_main.c
*
* Description: In this program, I create my own shell that that runs
*               on top of the regular command-line interpreter for Linux.
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFERSIZE 512

int parse_buffer(char *input, char **arg) //parsing input buffer
{
    int count = 0;
    char *token = " \n\t";

    arg[count] = strtok(input, token); //initializing string token

    //separating input buffer into substrings
    while ((arg[count] != NULL) && ((count + 1) < BUFFERSIZE))
    {
        arg[++count] = strtok((char *)0, token);
    }
    return count;
}

int main(int argc, char *argv[])
{
    char *buffer;
    char *myargv[BUFFERSIZE];

    int myargc, status;

    buffer = malloc(BUFFERSIZE); //allocating size of buffer

    while (1) //loop until exit
    {
        printf("%s", argv[1]); //prints first argument from RUNOPTIONS i.e. command line arg.

        fgets(buffer, BUFFERSIZE, stdin); //stdin upto BUFFERSIZE in buffer

        if (!strchr(buffer, '\n')) //clear buffer if > BUFFERSIZE
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        if (feof(stdin)) //EOF, exit
        {
            printf("\n");
            break;
            exit(EXIT_SUCCESS);
        }

        if (ferror(stdin)) //error reading input
        {
            printf("*** Can't read input ***\n ");
            break;
            exit(EXIT_FAILURE);
        }

        myargc = parse_buffer(buffer, myargv); //storing 'count'

        if (myargc == 0) //no input
        {
            printf("*** No arguments in command line ***\n");
            continue;
        }

        if (strcmp(myargv[0], "exit") == 0) //exit
        {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        pid_t pid = fork(); //forking a process
        int myexec;

        if (pid < 0) //forking error
        {
            printf("*** Fork process failed ***\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) //child process
        {
            myexec = execvp(myargv[0], myargv); //calling execvp to execute the command

            if (myexec == -1) //execvp error
            {
                printf("*** Exec failed ***\n");
                exit(EXIT_FAILURE);
            }
        }
        else //parent process waiting for completion
        {
            if (wait(&status) == -1) //wait error
            {
                printf("*** Parent error ***\n");
                exit(EXIT_FAILURE);
            }
            else //child PID and exit code
            {
                printf("Child %d, exited with %d\n", pid, WEXITSTATUS(status));
            }
        }
    }
    return 0;
}
