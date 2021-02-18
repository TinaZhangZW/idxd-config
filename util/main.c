/*
 * Copyright(c) 2015-2019 Intel Corporation. All rights reserved.
 * Copyright(c) 2006 Linus Torvalds. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

/* originally copied from perf and git */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <builtin.h>

#include <util/strbuf.h>
#include <util/util.h>

int main_handle_options(const char ***argv, int *argc, const char *usage_msg,
		struct cmd_struct *cmds, int num_cmds)
{
	int handled = 0;

	while (*argc > 0) {
		const char *cmd = (*argv)[0];
		if (cmd[0] != '-')
			break;

		if (!strcmp(cmd, "--version") || !strcmp(cmd, "--help"))
			break;

		/*
		 * Shortcut for '-h' and '-v' options to invoke help
		 * and version command.
		 */
		if (!strcmp(cmd, "-h")) {
			(*argv)[0] = "--help";
			break;
		}

		if (!strcmp(cmd, "-v")) {
			(*argv)[0] = "--version";
			break;
		}

		if (!strcmp(cmd, "--list-cmds")) {
			int i;

			for (i = 0; i < num_cmds; i++) {
				struct cmd_struct *p = cmds+i;

				/* filter out commands from auto-complete */
				if (strcmp(p->cmd, "create-nfit") == 0)
					continue;
				if (strcmp(p->cmd, "test") == 0)
					continue;
				if (strcmp(p->cmd, "bat") == 0)
					continue;
				printf("%s\n", p->cmd);
			}
			exit(0);
		} else {
			fprintf(stderr, "Unknown option: %s\n", cmd);
			usage(usage_msg);
		}

		(*argv)++;
		(*argc)--;
		handled++;
	}
	return handled;
}

void main_handle_internal_command(int argc, const char **argv, void *ctx,
		struct cmd_struct *cmds, int num_cmds)
{
	const char *cmd = argv[0];
	int i;

	/* Turn "<binary> cmd --help" into "<binary> help cmd" */
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	}

	for (i = 0; i < num_cmds; i++) {
		struct cmd_struct *p = cmds+i;
		if (strcmp(p->cmd, cmd))
			continue;
		exit(p->fn(argc, argv, ctx));
	}
}
