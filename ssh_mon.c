#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#define RUNNING_DIR 	"/"
#define LOG_FILE	"test.log"
#define LOCK_FILE	"test.lock"

int main(void) {
	/*Our process ID and Session ID */
	pid_t pid, sid;
	/*Declare our file pointer*/
	FILE *fp;
	//Fork off parent process
	pid = fork();

	if(pid < 0) {
		exit(EXIT_FAILURE);
	}

	/*If we got a good PID, then
	  we can exit the parent process*/
	if(pid > 0) {
		//Great success!!
		exit(EXIT_SUCCESS);
	}

	/*Change the file mode mask*/
	umask(0);
	
	
	/*Create the new SID for th child process*/
	sid = setsid();
	if(sid < 0) {
		exit(EXIT_FAILURE);
	}

	/*Change the current working directory*/
	if(chdir(RUNNING_DIR) < 0) {
		exit(EXIT_FAILURE);
	}
	
	fp = fopen("test.log","w+");
	fprintf(fp,"PID: ");
	fprintf(fp,"%ld",(long)pid);
	fprintf(fp,"\n");
	
	/*Daemon specific initialization goes here*/

	/*The Big Loop*/
	while(1) {
		fprintf(fp,"Testing");
		sleep(5);
	}

	exit(EXIT_SUCCESS);

}

