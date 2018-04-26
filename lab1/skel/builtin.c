#include "builtin.h"

// returns true if the 'exit' call
// should be performed
int exit_shell(char* cmd) {

	if (strncmp(cmd, "exit", 4) == 0) {
		exit(EXIT_SUCCESS);
		return true;
	}
	return false;
}

// returns true if "chdir" was performed
// this means that if 'cmd' contains:
// 	$ cd directory (change to 'directory')
// 	$ cd (change to HOME)
// it has to be executed and then return true
int cd(char* cmd) {
	if (strncmp(cmd, "cd", 2) == 0) {
		if ((strlen(cmd) > 2) && (cmd[3] != ' ')) {
			char buf[256];
			chdir(cmd + 3);
			getcwd(buf,256);
			snprintf(promt, sizeof promt, "(%s)", buf);
		} else {
			chdir(getenv("HOME"));
			snprintf(promt, sizeof promt, "(%s)", getenv("HOME"));
		}
		return true;
	}
	return false;
}

// returns true if 'pwd' was invoked
// in the command line
int pwd(char* cmd) {
	if (strncmp(cmd, "pwd", 3) == 0) {
		char buf[256];
		getcwd(buf, 256);
		printf("%s\n", buf);
		return true;
	}
	return false;
}
