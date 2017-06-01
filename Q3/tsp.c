#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int m[17][17] ;

int path[17] ;
int used[17] ;
int length = 0 ;
int min = -1 ;
pid_t pid;
int k = 0;

void _travel(int idx) {
	int i ;
	char buf[32];
	sprintf(buf, "%d.sol", k);
	FILE* fp;

	if (idx == 17) {
		if (min == -1 || min > length) {
			fp = fopen(buf, "w");

			min = length ;
			fprintf(fp, "%d (", length) ;
			for (i = 0 ; i < 16 ; i++) 
				fprintf(fp, "%d ", path[i]) ;
			fprintf(fp, "%d)\n", path[16]) ;

			fclose(fp);
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
}

void travel(int start) {
	path[0] = start ;
	used[start] = 1 ;
	_travel(1) ;
	used[start] = 0 ;
}

void handler(int signum)
{
	if(signum == SIGINT){
		kill(getpid(), SIGKILL);
		exit(0);
	}
}

int main() {
	int i, j, t ;
	int s;
	int min = 10000;
	int len;
	char buf[32];
	char fileName[32];
	char result[32];

	FILE * fp = fopen("gr17.tsp", "r") ;
	FILE * fp2;
	FILE * fp3;

	for (i = 0 ; i < 17 ; i++) {
		for (j = 0 ; j < 17 ; j++) {
			fscanf(fp, "%d", &t) ;
			m[i][j] = t ;
		}
	}
	fclose(fp) ;

	signal(SIGINT, handler);

	for (i = 0  ; i < 17 ; i++) {
		if((pid = fork()) == 0)
			travel(i) ;
			k++;
	}
	
	waitpid(-1, &s, 0);

	for(i=0;i<17;i++)
	{
		sprintf(buf, "%d.sol", i);
		fp2 = fopen(buf, "r");
		fscanf(fp2, "%d", &len);
		fclose(fp2);
		
		if(min > len){
			min = len;
			strcpy(fileName, buf);
		}
	}

	fp3 = fopen(fileName, "r");
	fgets(result, 32, fp3);
	fclose(fp3);
	printf("%s\n", result);
	return 0;
}
