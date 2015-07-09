#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_hup(int signo)
{
	printf("SIGHUP recevied, pid = %d \n", getpid());
}

static void pr_ids(char *name)
{
	printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main()
{
	char c;
	pid_t pid;
	
	pr_ids("parent");
	if((pid = fork()) < 0)
		perror("fork error");
	else if(pid > 0)
	{
		sleep(5);	//sleep to let child stop itself 
		exit(0);
	}
	else{
		pr_ids("child");
		signal(SIGHUP,sig_hup);
		kill(getpid(),SIGTSTP); //before parent 5sec sleep stop childself
		//then parent is die ,and child is a orpham process, and the SIGHUP SIGCONT conming 
		pr_ids("child");	
		if(read(STDIN_FILENO, &c, 1) != 1)
			printf("read error from controlling TTY");
		exit(0);
	}
	
}
