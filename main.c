/* 
 * File:   main.c
 * Author: melstrom
 *
 * Created on June 8, 2012, 3:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //include header for chdir()
#include <sys/resource.h> //include header for getrusage()


int main(int argc, char** argv) {

	extern int errno;
	
	while (1) {

int length;
int i=0;
char inputbuffer[];// the string the user inputs
char *strings[];// srting after divding each word ot token
char * cmd;
length = read (STDIN_FILENO, inputbuffer,MAX_LINE);
 if (lenght == 0)// no text was entered
{
exit(0);
}
if (lenght<0)
{
exit(-1); // somthing went wrong
}
cmd= inputbuffer;
strings[i] = strtok cmd," \t\n");
while (strings[i]!= NULL)
{
i++;
strings[i] = strtok (NULL," \t\n");
}
            char *test[];
            test[0] = "cd";
		if (test[0]=="cd") {
			//If the command is cd, call chdir(): see man page for calling parameters @Cary
			//http://linux.die.net/man/3/chdir
			chdir(test[1]);
			
			if (errno==-1) {
				fprintf(stderr, "Change directory failed");
			}
		}
		
		if (test[0]=="exit") {
			//If exit, then exit
			return (EXIT_SUCCESS);
		}
		
		else {
			//Else Fork, exec, and run processes (using arguments from buffer)
			//call print function @Cary
		}
        //return to the beginning
	}
}

//Print function
void print () {
	/*
	 a)	The amount of CPU time used (both user and system time) (in milliseconds), 
	 b)	The elapsed “wall-clock” time for the command to execute (in milliseconds), 
	 c)	The number of times the process was preempted involuntarily (e.g. time slice expired,
	 preemption by higher priority process, etc.), 
	 d)	the number of times the process gave up the CPU voluntarily (e.g. waiting for a resource), 
	 e)	The number of page faults, and 
	 f)	The number of page faults that could be satisfied from the kernel’s internal cache (e.g. did not
	 require any input/output operations).
	 */
	
	/*
	a) timeval ru_utime, timeval ru_stime
	b) 
	 */
	int who = RUSAGE_SELF;
	struct timeval tim; 
	struct rusage usage;
	getrusage(who, &usage);
	
	int involuntarily = usage.ru_nivcsw;
	printf("\t Preempted involuntary: %d .\n", involuntarily);
	int voluntarily = usage.ru_nvcsw;
	printf("\t Preempted involuntary: %d .\n", voluntarily);
	int pagefault = usage.ru_majflt;
	printf("\t Preempted involuntary: %d .\n", pagefault);
	int pagefaultkernel = usage.ru_minflt;
	printf("\t Preempted involuntary: %d .\n", pagefaultkernel);
}