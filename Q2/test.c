#include "csapp.h"

int  main(int argc, char** argv)
{
	int i, status;
	pid_t pid[argc], retpid;
	//char *data[];
	//char *data2[];

	for(i=1;i<argc;i++)
	{
		if((pid[i]=Fork()) == 0){
			char* data[] = { "./gzip", argv[i], NULL};
			char* data2[] = {"-d", NULL};
			execve("./gunzip", data, data2);
			exit(0);
		}
	}


	i = 0;

	while((retpid = waitpid(pid[i++], &status, 0))>0){
		if(WIFEXITED(status))
			printf("success ");
		else
			printf("Failed ");
	}

	return 0;
}
