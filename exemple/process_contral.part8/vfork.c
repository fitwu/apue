#include "apue.h"

int 	glob = 6;				/* ecternal variable in initialiezed data */
	 
int main()
{
	int	var;				/* automatic variable on the stack */
	pid_t	pid;
	
	var = 8;
	printf(" before vfork\n");		/* we don't flush*/
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {			/* child */
		glob++;				/* modify parent's variables  */
		var++;	
		_exit(0);			/* child erminates */
	}	 	
	printf("now is parent's time:\n");
	printf("pid = %d, glob = %d, var = %d\n",getpid(), glob, var);
	exit(0);

}
