#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
sig_atomic_t quitflag;

static void
sig_int(int signo)
{
	if(signo== SIGINT)
	{
		printf("\ninterrupt\n");
	}
	else if(signo == SIGQUIT)
		quitflag = 1;
}

void pr_mask(char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	
	if(sigprocmask(0, NULL, &sigset) < 0)
		perror("sigprocmask error");
	printf("%s", str);

	if(sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM)) printf("SIGARLM ");
	printf("\n");
	
	errno = errno_save;
}

int main()
{
	sigset_t newmask, oldmask, zeromask;
	
	if(signal(SIGINT, sig_int) == SIG_ERR)
		perror("signal(SIGINT) error");
	if(signal(SIGQUIT, sig_int) == SIG_ERR)
		perror("signal(SIGQUIT) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
		
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		perror("SIG_BOLOC error");
	while(quitflag == 0)
		sigsuspend(&zeromask);

	quitflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");

	exit(0);
		


}
