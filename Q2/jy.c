#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
        int i=1;
	int pid[argc];
	
	if((pid[i++]=fork())==0)
	{
		execve("/bin/gzip",argv,NULL);
		exit(0);
	}
}
