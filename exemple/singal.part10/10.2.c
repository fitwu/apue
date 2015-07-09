#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pwd.h>
#include<sys/types.h>


static void my_alarm(int signo)
{
	struct passed *rootptr;

	printf("in signal handler\n");
	if((rootptr = getpwnam("root")) == NULL)
		perror("getpwnam");
	alarm(1);
}

int main()
{
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);

	alarm(1);

	for(;;)
	{
		if((ptr = getpwnam("wu")) == NULL)
			perror("getpwanam main error");
		if(strcmp(ptr->pw_name, "wu") != 0)
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
	
}

