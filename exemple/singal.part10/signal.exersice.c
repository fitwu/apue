#include <apue.h>

static void sig_alrm(int);

int main(void)
{
	int a;
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys (" signal (SIGALRM ) error");
	printf(" before alarm\n");
	alarm(1);

	
	printf("oo%d\n",a);	
	printf("oo\n");
	printf(" after alarm\n");
	pause();

	printf("wa");
	exit(0);
}

static void sig_alrm ( int signo )
{
	printf(" haha ");
}
