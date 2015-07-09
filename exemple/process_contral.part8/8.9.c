#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
void read_file()
{
	printf("uid:%d  euid:%d  \n",getuid(), geteuid());
}



int main()
{
	read_file();
	setuid(1000);
	read_file();
	setuid(1);
	read_file();
	return 0;
}

