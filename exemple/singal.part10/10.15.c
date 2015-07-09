#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<signal.h>

#include<errno.h>


void pr_mask(const char*str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0 ,NULL, &sigset) < 0)
		perror("sigprocmask error");

	printf("%s", str);
	if(sigismember(&sigset, SIGINT))	printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT))	printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1))	printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM))	printf("SIGALRM ");

	printf("\n");
	errno = errno_save;
}

static void sig_int(int);

int main()
{
	sigset_t newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if(signal(SIGINT, sig_int) == SIG_ERR)
		perror("signal(SIGINT) error");

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		perror("SIG_BLOCK error");


	pr_mask("in critical region: ");

	if(sigsuspend(&waitmask) != -1)
		perror("sigsuspend error");
	pr_mask("after return from sigsuspend: ");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("SIG_SETMASK error");
	
	pr_mask("program exit: ");
	exit(0);



}

static void sig_int(int signo)
{
	pr_mask("\nint sig_int: ");
}

