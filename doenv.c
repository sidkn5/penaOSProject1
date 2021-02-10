/*
 *Student: Sean Dela Pena
 *Professor:Dr. Sanjiv Bhatia
 *email:sidkn5@umsystem.edu
 *Assignment1: Linux System Calls and Library Functions
 *		Duplicates the env utility
 *
 *github: github.com/sidkn5
 *Date: 2/9/2021
 *
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<getopt.h>
#include<unistd.h>
#include<errno.h>
extern char **environ;
/*
 *Some sources:
 *gnu.org for example of getopt
 *tutorialspoint.com for example of strtok
 *makefile: cs.colby.edu/maxwell/courses/tutorials/maketutor/
 *geeksforgeeks.com for strchr example
 *Stackoverflow.com for errorno explanation
 * *****************************/

//prints the current environment
//this is called for ./doenv
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

//This function is not called in this program. It is ONLY
//used for testing
//the same as above but uses the environ external variable
//this was called by the other functions for testing
//if you want to view the environment please use the env command
/*void printEnv2(){
	char *j;
	char **i;
	char cpy[10000];
	for (i = environ; *i != NULL; i++){
		strcpy(cpy, *i);
		j = strtok(cpy, "=");
		printf("%s=%s\n", j, getenv(j));
	}
}*/

//no option given, updates the environment by copying the oldenv
//if the the name exists, update/modify the name=var pair
//otherwise, add it as a new entry
void noOptionUpdate(int argc, char **argv){
	int x = 0;
	char **i;
	char noOfChars = 0;		//no. of lines of the old environment
	char noOfCharsAdded = 0;	//no. of lines that will be added to the old environment

	//counts the lines that will be copied
	for (i=environ; *i !=NULL;i++){
		noOfChars++;
	}

	//If the name exists then modify the environment
	//otherwise increment noOfCharsAdded, for later use when adding to the environment
	//strchr used to check whether the argument contains "="
	//if it isn't then it is not treated as a name value pair
	for (x=1; x < argc; x++){
		char *str1 = argv[x];
		int sizeOfStr1 = strlen(argv[x]);
		int size = strlen(argv[x]);
		char *argString = (char *)malloc(sizeof(char) * (size + 1));
		strcpy(argString, argv[x]);
		char *token = strtok(argString, "=");
		if(getenv(token) != NULL){
			putenv(argv[x]);
		}else{
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
			//if the argument contained = then it is 
			//a name value pair so increment
			noOfCharsAdded++;
		}
		}
	}

	
	int totalChars = 0;		//holds the total for the updated environment
	totalChars = noOfChars + noOfCharsAdded +1;

	char **updatedEnvironment;
	updatedEnvironment = malloc(sizeof(char *) * (totalChars + 1));
	if(optind < (argc)){
		//copies the current environment
		for(x=0; x < noOfChars; x++){
			int len = strlen(environ[x]);
			updatedEnvironment[x] = (char *)malloc(sizeof(char *)*(len + 1));
			updatedEnvironment[x] = environ[x];
		}
		//adds to the new environment
		for(x=noOfChars; x < totalChars; x++){
			int len = strlen(argv[optind]);
			updatedEnvironment[x] = (char *)malloc(sizeof(char *)*(len + 1));
			updatedEnvironment[x] = argv[optind];
			optind++;;
			
		}
		
		
	} else {
		printf("Please refer to ./doenv -h for proper use of program\n");
	}

	updatedEnvironment[totalChars]= NULL;
	environ = updatedEnvironment;

	//printed out the updated environment for testing
	//printf("Updated Environment: \n");
	//printEnv2();	

	//checks whether the argument is a call or a name value pair 
	//by checking if the '=' sign is present
	//otherwise attempt the call using system(3),
	//if that fails then perror is displayed
	for (x=1; x < argc; x++){
		char *str1 = argv[x];
		int sizeOfStr1 = strlen(argv[x]);
		char buffer[1];
		strcpy(buffer, str1);
		char *ptr;
		int ch = '=';

		ptr = strchr(buffer, ch);
		if ( ptr == NULL){
			if((system(argv[x])) == 0){
			}else{
					//if the call fails, then errno is set and perror is displayed.
					errno = 3;
					perror("doenv: Error: Unknown Process");
			}
		}
	}

	free(updatedEnvironment);
}

//ignores the current environment and replaces it with the new one
void iOption(int argc, char **argv){
	int noOfChars = 0;	
	int i = 0;		

	//find shell command
	//checks whether the argument is a call or a name value pair 
	//by checking if the '=' sign is present
	//otherwise attempt the call using system(3),
	//if that fails then perror is displayed
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

	//opind < argc ensures that -i option is used properly
	if(optind < argc){
		//overwrites the environment with the new one
		for(i=0;i < noOfChars; i++){
			int size = strlen(argv[i]);
			newEnvironment[i] = (char*)malloc(sizeof(char *) * (size + 1));			
			newEnvironment[i] = argv[optind - 1];
			optind++;
			
		}

		newEnvironment[noOfChars] = NULL;
		environ = newEnvironment;

		//printed the new environment for testing
		//printf("The new environment: \n");
		//printEnv2();
	} else {
		printf("Please refer to help menu for proper use of the program.\n");
		printf("This is not an error but NOTE that the -i option can be used with name=variable arguments to change the environment.\n");
	}


	//checks whether the argument is a call or a name value pair 
	//by checking if the '=' sign is present
	//otherwise attempt the call using system(3),
	//if that fails then perror is displayed
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
				if((system(argv[i])) == 0){
				}else{		
					//if the call fails, then errno is set and perror is displayed.
					errno = 3;
					perror("doenv: Error: Unknown Process");
				}
		}
	}
	free(newEnvironment);
	
}

//displays the help menu
void help(){
	printf("Help: \n");
	printf("Usage: ./doenv [option] [name1=val1] ... [namen=valn] command1 ... commandn \n");
	printf("This program behaves in the same way as the env utility when executing another program. \n");
	printf("Example: ./doenv -i TZ=EST date\n");
	printf("Options: \n");
	printf("-h \t\t displays help information on how this program is to be called or executed\n\n");
	printf("-i \t\t ignores the current environment and replaces it with the name=value pair entered by the user.\n\n");
	printf("A call without arguments or options will simply print the current evironment. \n");
	printf("A call without an option but with name=value arguments modifies/updates the current environment. \n");
	printf("If the name already exists in the current environment then it is modified. \n");
	printf("If the name does not exists then it will be added to the current environment \n");

}

int main(int argc, char *argv[], char *envp[]){
	int c = 0;
	int noOptionGiven;
	// if no options used
	if (argc == 1){
		printEnv(envp);
		return 0;
	}else{
		noOptionGiven=1;
		
	}

	//options are used
	while ((c = getopt(argc, argv,"hi:")) != -1){
		switch (c){
			case 'i':
			iOption(argc, argv);
			break;
			
			case 'h':
			help();
			break;

			default:
			printf("Please refer to the help menu for proper use of the program.\n");
			break;
		}
		return 0;

	}

	//if no option is given it calls noOptionUpdate function
	if(noOptionGiven=1){
		noOptionUpdate(argc, argv);
	}
	return 0;
}
