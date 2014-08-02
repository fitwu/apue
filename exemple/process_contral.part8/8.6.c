
#include <apue.h>

#define PSCMD "ps -o pid,ppid,state,tty,command"


int main()
{
	pid_t	pid;
	
	if ((pid = fork() ) < 0) 
		err_sys(" fork error");
	else if (pid == 0)
		exit(0);			/* CHILD */
	
	/* PARENT */
	sleep(5);
	system(PSCMD);
	
}
