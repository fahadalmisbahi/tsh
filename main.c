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
#include <string.h> //include header for strtok()

void print (struct rusage *usage) {
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

    //code idea source: http://www.unix.com/hp-ux/38937-getrusage.html

    printf("\t Number of times the process was preempted involuntarily: %lu .\n",
            usage->ru_nivcsw);    //c
    printf("\t Number of times the process gave up the CPU voluntarily: %lu .\n",
        usage->ru_nvcsw);     //d
    printf("\t Number of page faults: %lu .\n",
        usage->ru_majflt);    //e
    printf("\t Number of page faults that could be satisfied from the kernel’s internal cache: %lu .\n",
        usage->ru_minflt);    //f
}

void getstats (void) {
    int who = RUSAGE_SELF;
    //struct timeval tim;
    struct rusage usage;
    getrusage(who, &usage);
    print (&usage);
}

int main(void) {



    extern int errno;
    //memcpy (inputbuffer, args, strlen(args)+1);

    while (1) {
        int length;
        int i = 0;
        char inputbuffer[80];// the string the user inputs

        char *strings[32];// srting after divding each word ot token
        char *cmd;
        length = read (STDIN_FILENO, inputbuffer,100);

        if (length == 0) {// no text was entered
            exit(0);
        }

        if (length<0)
        {
            exit(-1); // somthing went wrong
        }

        cmd = inputbuffer;
        strings[i] = (strtok (cmd," \t\n"));

        while (strings[i] != NULL)
        {
            i++;
            strings[i] = strtok (NULL," \t\n");
        }

        if (strcmp(strings[0],"cd") == 0) {
            //If the command is cd, call chdir(): see man page for calling parameters
            //http://linux.die.net/man/3/chdir
            chdir(strings[1]);

            if (errno != 0) {
                //fprintf(stderr, "Change directory failed.\n");
            }
        }

        else if (strcmp(strings[0],"exit") == 0) {
                //If exit, then exit
                return (EXIT_SUCCESS);
            }

        else {
                pid_t pid;
                int i;
                pid = fork();
                if (pid < 0) {                     /* error occurred */
                    fprintf(stderr, "execUS: Fork Failed");
                    exit (1);
                }

                else if (pid > 0) {
                    wait(NULL);
                }

                else {
                    execvp (strings[0],strings);
                }
                getstats();
            }

        //getstats();
	}
}