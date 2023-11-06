#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

//man grep | grep -A 3 -e "-A" > output_first_pipe.txt

#define READ_END 0                             // INPUT_END means where the pipe takes input
#define WRITE_END 1 

int main()
{
    printf("I'm SHELL process, with PID: %d - Main command is: <man grep | grep -A 3 -e \"-A\" > output_first_pipe.txt>\n", (int) getpid());
    int p[2];
    int childMan, childGrep;
    //pipe creation failed
    if (pipe(p) < 0)
        exit(1);


    if ((childMan = fork()) == 0)
    {
        
        printf("I'm MAN process, with PID: %d - Main command is: <man grep>\n", (int) getpid());
        dup2(p[WRITE_END], STDOUT_FILENO);
        //close the file descriptors
        close(p[READ_END]);
        close(p[WRITE_END]);
        char * myargs[3];
        myargs[0] = strdup("man");
        myargs[1] = "grep";
        myargs[2] = NULL;
        execvp("man", myargs);
        printf("this no no");
        
        _exit(0);
    }
    if ((childGrep = fork()) == 0)
    {
        // second child stuff goes here
        printf("I'm GREP process, with PID: %d - Main command is: <grep -A 3 -e \"-A\">\n", (int) getpid());
        
	    int fd = open("output5.txt", O_CREAT | O_APPEND | O_WRONLY,  0644);
        dup2(fd, 1);
        dup2(p[READ_END], STDIN_FILENO);
        
        close(p[WRITE_END]);
        close(p[READ_END]); 
        close(fd);
        //char * myargs[] = {"grep",,"-e","-A", NULL};
        char * myargs[] = {"grep", "-A", "3" , "-e", "a", NULL};
        execvp("grep", myargs);
        _exit(0);
    }
        // parent goes down this path (original process)
    close(p[READ_END]);
    close(p[WRITE_END]);
    int man = wait(NULL);    
    int grep = wait(NULL);
    printf("hello, I am parent of %d (pid:%d)\n", childMan, (int) getpid());     

    
    
    return 0;
}

/*
    char command[100];

    // Replace "man ls" with the desired man page command
    sprintf(command, "man ls");

    // Execute the command using system()
    system(command);
*/
