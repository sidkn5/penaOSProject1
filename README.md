Student: Sean Dela Pena 
Professor: Dr. Sanjiv Bhatia
Assignment 1:
	The purpose of the assignment is be familiar with the environment in hoare while
	practising system calls. Another purpose was to show our proficiency with the use
	of perror and getopt. In this assignment we recread the env utility in a smaller
	scale. ./doenv can be use with -i,-h, and no options. The -i option ignores the
	current environment and replaces it with the name=value pairs that the user inputed.
	The -h option displays a help menu about the program. If called without an option and
	without arguments then the current environment is displayed. If called without an
	option but given name=value pairs, allows the user to modify the environment. If 
	the name already exists then it will be modified. If the name does not exists then it
	will be added to the environment.

USAGE: ./doenv [option] [name1=val1] ... [nameN=valN] command1 ... commandN

NOTES:
	Please note that using the -i option does not automatically print out
	the new environment with out the env or ./doenv call.

	./doenv -i TZ=EST	does not print anything.
	./doenv -i TZ=EST env 	prints the new environment.

	The same goes if it is not given an option. If name=value pairs are entered
	the updated environment will not be printed unless env is called.

	./doenv TZ=EST new=pair	TERM=example		does not print anything.
	./doenv TZ=EST new=pair	TERM=example env	prints the updated environment.


Functions:
	printEnv():
		This function prints out the environment. Passed with envp.
		Called in main when user calls ./doenv

	printEnv2();
		This is the same as the printEnv function with the difference that it uses
		the environ external variable. So passing envp was not necessary. Not 
		really used for this program but it was called by the other functions
		for testing.

	noOptionUpdate():
		This function  handles the call when the user does not use an option.
		In this function the copies the entire environment, modifies it and 
		adds to it if it does not already exist. This function also check wheter
		the arguments is a name=val pair or a call. If it is a call it calls it 
		using system(3), and if it is an invalid call perror is displayed.

	iOption():
		This function handles the call when the user uses -i option. This function
		completely overwrites the environment. This function also check wheter
		the arguments is a name=val pair or a call. If it is a call it calls it 
		using system(3), and if it is an invalid call perror is displayed.

	help():
		This function displays the help menu.

	main(): 
		Main driver whre getopt() is used.


PROBLEMS:

	When the -i option is used and the user decides to overwrite the environment and
	print it, there are will be additional ones. This was also mentioned on microsoft
	teams. I believe the reason to this is that the shell needs those environment 
	that's why they are there by default. 

	./doenv -i TZ=EST new=pair env	//env call ads a few lines to the print
	./doenv -i TZ=EST new=pair 	//only prints the two pairs without the additional lines
	NOTE: The second call only works if the printEnv2() function and call is commented out on 
	the iOption function.

	Another problem is with using system(3) with perror. This was also brought up in teams.
	If the user inputs an invalid command then the perror is displayed but also the shell
	displays it's own error. So there will be two errors shows.

	This isn't really a problem but it is abnormal, when env is called:

	./doenv new=pair test=check HISTSIZE=50 env

	This prints the environment but the arrangement is off. The environment is modified properly
	and new ones are added properly. It's just the arrangement is off.


	Something that I had trouble with is the allocation of memory to double pointers. Teams 
	really helped me with this one. I was stuck in this a long time because I didn't know
	how to allocate memory properly. Thankfully this was answered in teams.
	Also I've only written a makefile once in the past and even then it was probably provided by 
	the teacher. I had trouble with that so I had to look up templates online and Jacob,a tutor, 
	was more than happy to help me with the makefile.
	Jacob also helped me understand what the project is really asking. In hindsight, I probably just
	wasn't paying much attention to the project description. This project was really difficult
	for me not because of what the project is but because of the language we had to use. 
	I probably only made a project using C once or twice in the past. So this was a good 
	learning experience for me as well. After a while you realize the usefulness of man pages
	as well. Also i probably could've made my code shorter and much cleaner had I made more
	functions but I was hesistant because of my unfamiliarity with the language. 





