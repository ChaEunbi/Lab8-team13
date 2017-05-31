#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
        int i=1;
	int pid[argc];
	int s;
	
	for(i=1;i<argc;i++){
		if((pid[i]=fork())==0)
		{
			execl("/bin/gzip", "gzip", "-d", argv[i], NULL);
			exit(0);
		}
		else
		{
			waitpid(pid[i], &s, 0);
			if(!WIFEXITED(s))
				printf("error.\n");
		}
	}
	printf("end of program.\n");
	return 0;
}	
