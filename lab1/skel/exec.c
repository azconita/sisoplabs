#include "exec.h"

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {

	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {

	int i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {

}

// opens the file in which the stdin/stdout or
// stderr flow will be redirected, and returns
// the file descriptor
//
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int open_redir_fd(char* file) {

	// CHEQUEAR ERRORES
	int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	return fd;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
void exec_cmd(struct cmd* cmd) {

	switch (cmd->type) {

		case EXEC: {
			// spawns a command
			struct execcmd *excmd = (struct execcmd*) cmd;
			for (int i = 0; i < excmd->eargc; i++) {
				char key[256];
				char *f = strchr(excmd->eargv[i], '=');
				strncpy(key,excmd->eargv[i], strcspn(excmd->eargv[i], "=") );
				setenv(excmd->eargv[i], f+1, 0);
			}
			execvp(excmd->argv[0], excmd->argv);
			//execvpe(excmd->argv[0], excmd->argv, excmd->eargv);
			break;
		}

		// runs a command in background
		case BACK: {
			/*pid_t p;
			int nstatus = 0;
			struct backcmd *bkcmd = (struct backcmd*) cmd;
			struct execcmd *excmd = (struct execcmd*) bkcmd->c;
			if ((p = fork()) == 0) {
				for (int i = 0; i < excmd->eargc; i++) {
					char key[256];
					char *f = strchr(excmd->eargv[i], '=');
					strncpy(key,excmd->eargv[i], strcspn(excmd->eargv[i], "=") );
					setenv(excmd->eargv[i], f+1, 0);
				}
				execvp(excmd->argv[0], excmd->argv);
				//execvpe(excmd->argv[0], excmd->argv, excmd->eargv);
			}
			waitpid(p, &nstatus, 0);
			free_command(cmd);*/
			struct backcmd *bkcmd = (struct backcmd*) cmd;
			//struct execcmd *excmd = (struct execcmd*) bkcmd->c;
			exec_cmd(bkcmd->c);

			break;
		}

		case REDIR: {
			// changes the input/output/stderr flow
			struct execcmd *rdcmd = (struct execcmd*) cmd;
			if (rdcmd->in_file != NULL) {
				int infd = open_redir_fd(rdcmd->in_file);
				dup2(infd, 0);
				close(infd);
			}
			if (rdcmd->out_file != NULL) {
				int outfd = open_redir_fd(rdcmd->out_file);
				dup2(outfd, 1);
				close(outfd);
			}
			if (rdcmd->err_file != NULL) {
				if(strncmp(rdcmd->err_file, "&1", 2) == 0) {
					dup2(1, 2);
				} else {
					int errfd = open_redir_fd(rdcmd->err_file);
					dup2(errfd, 2);
					close(errfd);
				}
			}
			execvpe(rdcmd->argv[0], rdcmd->argv, rdcmd->eargv);
			break;
		}

		case PIPE: {
			// pipes two commands
			struct pipecmd *ppcmd = (struct pipecmd*) cmd;
			int pipefd[2];
			pipe(pipefd);
			int pid, status = 0;
			if ((pid = fork()) == 0) {
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				dup2(pipefd[1], 2);
				close(pipefd[1]);
				exec_cmd(ppcmd->leftcmd);
			} else {
				waitpid(pid, &status, 0);
				close(pipefd[1]);
				dup2(pipefd[0],0);
				close(pipefd[0]);
				exec_cmd(ppcmd->rightcmd);
				// free the memory allocated
				// for the pipe tree structure
			}
			free_command(parsed_pipe);

			break;
		}
	}
}
