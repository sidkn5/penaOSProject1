#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *sources:
 *gnu.org for example of getopt
 *tutorialspoint.com for example of strtok
 * *****************************/

void printEnv(char **envp){
	char *j;
	char **i;
	char cpy[10000];
	char separateEqual[2] = "=";
	for (i = envp; *i != NULL; i++){
		strcpy(cpy, *i);
		j = strtok(cpy, separateEqual);
		printf("%s=%ss\n", j, getenv(j));
	}
}

int main(int argc, char *argv[], char *envp[]){
	//1
	if (argc == 1){
		printEnv(envp);
	}

	return 0;
}
