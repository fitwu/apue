#include <apue.h>
#define PSCMD	"ps -o pid,ppid,session,comm"

int main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_sys (" fork error");
	else if (pid == 0) {
		printf(" before setsid() ,the child process group is %d,and the child process is %d \n",getpgrp(),getpid());

		setsid();			/* child */
		printf(" after  setsid() ,the child process group is %d,and the child process is %d \n",getpgrp(),getpid());
		_exit(0);
	}
	printf(" the  parent process group is %d,and the process is %d \n",getpgrp(),getpid());
	sleep(4);						/* parent */
	exit(0);
}
