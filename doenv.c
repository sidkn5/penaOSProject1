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
//no option given, updates the environment by copying the oldenv
//if the the name exists, replace the pointer
//otherwise, add it as a new entry
void noOptionUpdate(int argc, char **argv){
	printf("Im on no option \n");

	/*char *j;
	char **i;
	char cpy[10000];
	char **newEnv = malloc(sizeof(char *) * (noOfChars + 1));

	for (i = environ; i !=NULL; i++){
		**newEnv = (char *)malloc(sizeof(char *) * (size + 1));

	}*/

	char **i;
	char noOfChars = 0;
	char noOfCharsAdded = 0;
	for (i = environ; *i != NULL; i++){
		noOfChars++;
	}
/*
	int x = 0;
	for(x=1; x < argc; x++){

		noOfCharsAdded++;
	}
	printf("Old: %d\n", noOfCharsAdded);
	*/
	/////////////////////////////////////
	int x = 0;
	for (x=1; x < argc; x++){
		char *str1 = argv[x];
		int sizeOfStr1 = strlen(argv[x]);
		char buffer[1];
		strcpy(buffer, str1);
		char *ptr;
		int ch = '=';

		ptr = strchr(buffer, ch);
		if ( ptr == NULL){
			//left for testing
			//printf("i'm a system call\n");
			//system(argv[i]);
			
		}else {
			noOfCharsAdded++;
		}
	}

	/////////////////////////////////////
	int totalChars = 0;
	totalChars = noOfChars + noOfCharsAdded;

	char **updatedEnvironment;
	updatedEnvironment = malloc(sizeof(char *) * (totalChars + 1));
	if(optind < argc){
		//copies the current environment
		for(x=0; x < noOfChars; x++){
			int len = strlen(environ[x]);
			updatedEnvironment[x] = (char *)malloc(sizeof(char *)*(len + 1));
			updatedEnvironment[x] = environ[x];
		}
		
		for(x=noOfChars; x < totalChars; x++){
			int len = strlen(argv[optind]);
			updatedEnvironment[x] = (char *)malloc(sizeof(char *)*(len + 1));
			updatedEnvironment[x] = argv[optind];
			optind++;
		}

	} else {
		printf("Please refer to ./doenv -h for proper use of program\n");
	}
	
	environ = updatedEnvironment;
	printf("Updated Environment: ");
	printEnv2();	

	
	for (x=1; x < argc; x++){
		char *str1 = argv[x];
		int sizeOfStr1 = strlen(argv[x]);
		char buffer[1];
		strcpy(buffer, str1);
		char *ptr;
		int ch = '=';

		ptr = strchr(buffer, ch);
		if ( ptr == NULL){
			printf("i'm a system call\n");
				//int systemptr = system(argv[x-1]);
				if((system(argv[x])) == 0){
				}else{
					perror("Unknown Command: No such process");
				}
		}
	}
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
			//printf("i'm a system call\n");
			//system(argv[i]);
			
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
		printf("An error occured. Please refer to help menu for proper use of the program.");
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
				//int systemptr = system(argv[i]);
				if((system(argv[i])) == 0){
				}else{
					perror("Unknown Command: No such process");
				}
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

		noOptionUpdate(argc, argv);
	return 0;
}
