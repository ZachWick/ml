//
// ml - mini list
// An `ls`-like program written as an educational exercise
//
// Copyright 2015 zach wick <zach@zachwick.com>
// Licensed under the GNU GPLv3 or later
//

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <argp.h>
#include <sys/ioctl.h>

const char *argp_program_version = "ml 0.0.2";
const char *arpg_program_bug_address = "<zach@zachwick.com>";
static char doc[] = "an ls-like program part of edutils.";
static char args_doc[] = "[FILENAME]";
static struct argp_option options[] = {
	{"long", 'l', 0, 0, "Use long output format"},
	{0}
};

struct arguments
{
	int long_output;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	// Get the `input` argument from `argp-parse` which we know is a pointer to
	// our `arguments` structure.
	struct arguments *arguments = state->input;
	
	switch(key) {
	case 'l':
		arguments->long_output = 1;
		break;
	case ARGP_KEY_ARG:
		if (state->arg_num >= 2) {
			// Too many arguments were passed to `ml`
			argp_usage (state);
		}
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// The argp parser
static struct argp argp = { options, parse_opt, args_doc, doc };


static int
_true (const struct dirent *empty)
{
	// In order to fix a compiler warning, we need to make sure that the
	// signature of our _true function matches what the scandir function
	// expects. Deshalb, we have to accept an argument that we don't use.
	return 1;
}

int
main(int argc, char **argv)
{
	// This will be our list of dirents returned by the scandir function
	struct dirent **dits;

	// The number of files/nodes that are contained in the directory
	int num_files = 0;
	int use_curr_dir = 0;
	char *dirname;
	
	// Command line argument parsing
	struct arguments arguments;
	// Default argument values
	arguments.long_output = 0;
	// Parse the arguments
	argp_parse (&argp, argc, argv, 0, 0, &arguments);

	// If a directory path is not supplied, use the present working directory
	// as a default
	use_curr_dir = argc == 2 && arguments.long_output || argc < 2;
	if (use_curr_dir)
		{
			dirname = getcwd (NULL, 0);
		}
	else
		{
			dirname = argv[argc - 1];
		}

	// Call the scandir function.
	// The 3rd param is a filter/selctor function; we want all children of the
	// directory, so we use our `_true` function to accept all children.
	// The 4th param is a sort function. We are using alphasort, which is
	// provided by the GNU stdlib
	num_files = scandir (dirname, &dits, _true, alphasort);

	if (num_files >= 0)
		{
			int count;
			for (count = 0; count < num_files; ++count)
				{
					// This is where we actually write the nodes' names to STDOUT
					if (arguments.long_output)
						{
							
						}
					else
						{
							puts(dits[count]->d_name);
						}
				}
			// Clean up the memory allocatted by scandir
			for (count = 0; count < num_files; ++count)
				{
					// Free each dirent before freeing dits as a whole
					free(dits[count]);
				}
			free(dits);
		}
	else
		{
			perror ("Error opening directory");
		}
	
	// We can't free `dirname` unless getcwd got called - which only happens
	// if a path to list is supplied by the user
	if (use_curr_dir) {
		free (dirname);
	}	
	return 0;
}

