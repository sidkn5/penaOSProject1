#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
#include<getopt.h>
#include<unistd.h>
/*
 *sources:
 *gnu.org for example of getopt
 *tutorialspoint.com for example of strtok

 * *****************************/

void printEnv(char **envp){
	char *j;
	char **i;
	char cpy[10000];
	for (i = envp; *i != NULL; i++){
		strcpy(cpy, *i);
		j = strtok(cpy, "=");
		printf("%s=%s\n", j, getenv(j));
	}
}

void printEnv2(){
	char *j;
	char **i;
	char cpy[10000];
	for (i = environ; *i != NULL; i++){
		strcpy(cpy, *i);
		j = strtok(cpy, "=");
		printf("%s=%s\n", j, getenv(j));
	}
}


int iOption(int argc, char **argv){
	int noOfChars = 0;
	int i = 0;
	for (i=2; i < argc; i++){
		char *str1 = argv[i];
		char *utility = "utility";
		int ret = strcmp(str1, utility);
		if (ret == 0){
			printf("found utility\n");
			//do something when utility is used
		} else {
			noOfChars++;
		}
	}

	
	char **newEnvironment = malloc(sizeof(char *) * (noOfChars + 1));

	char *arg = optarg;

	if(optind < argc){
		for(i=0;i < noOfChars; i++){
			int size = strlen(argv[i]);
			char *currentArg = argv[i+2];
			newEnvironment[i] = (char*)malloc(sizeof(char *) * (size + 1));			
			newEnvironment[i] = argv[optind];
			optind++;
			
		}

		newEnvironment[noOfChars] = NULL;
		environ = newEnvironment;
	
		printf("The new environment: \n");
		printEnv2();
	} else {
		//use perror?
		printf("An error occured.");
	}
	

}

//not done
void help(){
}

int main(int argc, char *argv[], char *envp[]){
	int c = 0;
	//1. if no options used
	if (argc == 1){
		printEnv(envp);
		
	}

	//
	while ((c = getopt(argc, argv,"ih:")) != -1){
		switch (c){
			//-i option used
			case 'i':
			iOption(argc, argv);
			break;
			
			case 'h':
			help();
			break;
		}
	}
	return 0;
}
