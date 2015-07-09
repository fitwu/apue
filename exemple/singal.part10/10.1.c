#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static void sig_usr(int);

int main()
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("cat't catch SIGUSR2");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("cat't catch SIGUSR2");
	for(;;)
		pause();
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
		printf("SIGUSR1\n");
	if(signo == SIGUSR2)
		printf("SIGUSR2\n");
}
