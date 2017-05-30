#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
        int i=0;
	int status,pid[argc],retpid;
	
//	for(i=0;i<argc;i++)
		if((pid[i++]=fork())==0)
		{
			if((pid[i++]=fork())==0)
			{
				execve("/bin/gunzip",argv,NULL);
			}
			else{
				execve("/bin/gunzip",argv,NULL);
			}
		}
		else
		{
				execve("/bin/gunzip",argv,NULL);
		}
		
	
	i=0;
        while((retpid = waitpid(pid[i++], &status, 0))> 0){
                if(WIFEXITED(status))  
                        printf("child %d terminated normally with exit status=%d\n",retpid,WEXITSTATUS(status));
                else
                        printf("child %d terminated abnormally\n", retpid);
        }
}
