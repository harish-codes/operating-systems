#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/*
Harish Nagallapati,250922183
*/


int main (int argc, char * argv[]){

	pid_t pid1, pid2;
	
	int fd[2],readY;
	if (pipe(fd) < 0){	//Create pipe and check if error
		perror("Pipe Error.\n");
		exit(0);
	}

	pid1 = fork();	//Child ID
	if (pid1 < 0){	//If child creation was not successful, exit
		printf("Fork Error.\n");
		exit(0);
	}


	//ONLY Parent will run this code.
	else if (pid1 > 0){
		pid2 = getpid();	//Parent ID
		printf("A pipe is created for communication between parent PID# %d and child PID# %d.\n",pid2,pid1);
		printf("Parent PID# %d created a Child PID# %d.\n",pid2,pid1);

		//Convert first command line argument to intger.
		char *a = argv[1];
 		int X = atoi(a);

		printf("Parent PID# %d reading X = %d from the user.\n",pid2,X);
		//printf("X = %d\n",X);
		wait(NULL);	//Wait for Child process to finish.

		//Reading Y from Pipe
		read(fd[0],&readY,sizeof(readY));
		printf("Parent PID# %d reading Y from the pipe. (Y = %d)\n",pid1,readY);

		//Add X + Y = 30.
		printf("Parent PID# %d adding X + Y = %d.\n",pid1,X+readY);


	}

	//ONLY Child will run this code.
	else if (pid1 == 0){
		pid1 = getpid();
		char *b = argv[2];
  		int Y = atoi(b);

		printf("Child PID# %d reading Y = %d from the user.\n",pid1,Y);

		//Write Y into pipe.
		printf("Child PID# %d writing Y into the pipe.\n",pid1);
		write(fd[1],&Y, sizeof(Y));

	}

	return 0;
}

