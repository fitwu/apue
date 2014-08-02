#include<apue.h>
#include<sys/wait.h>

int main()
{
	pid_t	pid;
	
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {					/* first child*/
		if ((pid = fork()) < 0)				
			err_sys("fork error");
		else if (pid > 0)				/* parent form second child == first child*/
			exit(0);
		/*
 		*/
		sleep(2);
		printf("second child, parent pid = %d\n",getppid());	 
		exit(0); 
	}
	if (waitpid(pid, NULL, 0) != pid)
		err_sys("waitpid error");
	
	exit(0);
	
}
