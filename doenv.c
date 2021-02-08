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
//no option given, updates the environment
void noOptionUpdate(int argc, char **argv){
	int noOfChars = 0;
	int i = 0;
}

//ignores the current environment and replaces it with the new one
void iOption(int argc, char **argv){
	int noOfChars = 0;
	int i = 0;

	//find shell command

	for (i=2; i < argc; i++){
		char *str1 = argv[i];
		int x;
		int sizeOfStr1 = strlen(argv[i]);
		char buffer[1];
		strcpy(buffer, str1);
		char *ptr;
		int ch = '=';

		ptr = strchr(buffer, ch);
		if ( ptr == NULL){
			//left for testing
			printf("i'm a system call\n");
			system(argv[i]);
			
		}else {
			noOfChars++;
		}
	}
	
	char **newEnvironment = malloc(sizeof(char *) * (noOfChars + 1));


	if(optind < argc){
		for(i=0;i < noOfChars; i++){
			int size = strlen(argv[i]);
			newEnvironment[i] = (char*)malloc(sizeof(char *) * (size + 1));			
			newEnvironment[i] = argv[optind-1];
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
	
	for (i=2; i < argc; i++){
		char *str1 = argv[i];
		int x;
		int sizeOfStr1 = strlen(argv[i]);
		char buffer[1];
		strcpy(buffer, str1);
		char *ptr;
		int ch = '=';

		ptr = strchr(buffer, ch);
		if ( ptr == NULL){
			printf("i'm a system call\n");
			system(argv[i]);	
		}
	}
}

//not done
void help(){
	printf("Help: \n");
	printf("Usage: ./doenv [option] [name1=val1] ... [namen=valn] command1 ... commandn \n");
	printf("This program behaves in the same way as the env utility when executing another program. \n");
	printf("Example: ./doenv -i TZ=EST date\n");
	printf("Options: \n");
	printf("-h \t displays help information on how this program is to be called or executed\n");
	printf("-i \t ignores the current environment and replaces it with the name=value pair entered by the user.\n");
	printf("A call without arguments or an option will simply print the current evironment. \n");
	printf("A call without an option but with name=value arguments modifies/updates the current environment. \n");

}

int main(int argc, char *argv[], char *envp[]){
	int c = 0;
	//1. if no options used
	if (argc == 1){
		printEnv(envp);
		
	}

	//
	while ((c = getopt(argc, argv,"hi:")) != -1){
		switch (c){
			//-i option used
			case 'i':
			iOption(argc, argv);
			break;
			
			case 'h':
			help();
			break;

			default:
			printEnv(envp);
			break;
		}
	}

	return 0;
}
