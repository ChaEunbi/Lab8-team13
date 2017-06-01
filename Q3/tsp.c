#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int m[17][17] ;

int path[17] ;
int used[17] ;
int length = 0 ;
int min = -1 ;
pid_t pid[17];

void _travel(int idx) {
	int i ;
	FILE* fp=fopen("text","w");

	if (idx == 17) {
		if (min == -1 || min > length) {
			min = length ;
			printf("%d (", length) ;
			for (i = 0 ; i < 16 ; i++) 
				printf("%d ", path[i]) ;
			printf("%d)\n", path[16]) ;
		}
	}
	else {
		for (i = 0 ; i < 17 ; i++) {
			if (used[i] == 0) {
				path[idx] = i ;
				used[i] = 1 ;
				length += m[path[idx-1]][i] ;
				_travel(idx+1) ;
				length -= m[path[idx-1]][i] ;
				used[i] = 0 ;
			}
		}
	}
	fclose(fp);
}

void travel(int start) {
	path[0] = start ;
	used[start] = 1 ;
	_travel(1) ;
	used[start] = 0 ;
}

void handler(int signum)
{      
        int i;
        int s ;
        for(i=0;i<17;i++)
                kill(pid[i], SIGKILL);

	for(i=0;i<17;i++)
		waitpid(pid[i],&s,0);
        printf("Bye.\n");
}

int main() {

	int i, j, t ;
	int s;
	FILE * fp = fopen("gr17.tsp", "r") ;

	for (i = 0 ; i < 17 ; i++) {
		for (j = 0 ; j < 17 ; j++) {
			fscanf(fp, "%d", &t) ;
			m[i][j] = t ;
		}
	}
	fclose(fp) ;
	
	signal(SIGINT,handler);

	for (i = 0  ; i < 17 ; i++) 
		if((pid[i]=fork())==0)	
		{
			travel(i);
			exit(0);
		}

	for(i=0;i<17;i++)
		waitpid(pid[i],&s,0);
}
