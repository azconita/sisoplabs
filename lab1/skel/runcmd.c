#include "runcmd.h"

int status = 0;
struct cmd* parsed_pipe;
struct cmd back_cmds[10];
int back_cmds_idx = 0;

void check_backcmds() {
	int bkstatus, pid, i;
	if ((pid=waitpid(-1,&bkstatus,WNOHANG)) > 0) {
		for (i = 0; i < 10; i++) {
			if (back_cmds[i].pid == pid)
				break;
		}
		if (i < 10)
			print_back_finish(&back_cmds[i]);
	}
}

// runs the command in 'cmd'
int run_cmd(char* cmd) {
	pid_t p;
	struct cmd *parsed;

	// if the "enter" key is pressed
	// just print the promt again
	if (cmd[0] == END_STRING)
		return 0;

	// cd built-in call
	if (cd(cmd))
		return 0;

	// exit built-in call
	if (exit_shell(cmd))
		return EXIT_SHELL;

	// pwd buil-in call
	if (pwd(cmd))
		return 0;

	// parses the command line
	parsed = parse_line(cmd);

	// forks and run the command
	if ((p = fork()) == 0) {

		// keep a reference
		// to the parsed pipe cmd
		// so it can be freed later
		if (parsed->type == PIPE)
			parsed_pipe = parsed;

		exec_cmd(parsed);
	}

	// store the pid of the process
	parsed->pid = p;

	// background process special treatment
	// Hint:
	// - check if the process is
	// 	going to be run in the 'back'
	// - print info about it with
	// 	'print_back_info()'
	//
	if (parsed->type == BACK) {
		print_back_info(parsed);
		back_cmds[back_cmds_idx] = *parsed;
		back_cmds_idx = (++back_cmds_idx >= 10) ? 0 : back_cmds_idx;
	} else {
		// waits for the process to finish
		waitpid(p, &status, 0);

		print_status_info(parsed);

		free_command(parsed);
	}
	check_backcmds();
	return 0;
}
