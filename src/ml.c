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
#include <sys/ioctl.h>

#define VERSION "0.0.2"
#define AUTHOR "zach wick <zach@zachwick.com>"

static int
_true (const struct dirent *empty) {
	// In order to fix a compiler warning, we need to make sure that the
	// signature of our _true function matches what the scandir function
	// expects. Deshalb, we have to accept an argument that we don't use.
	return 1;
}

int
main(int argc, char *argv[]) {
	// This will be our list of dirents returned by the scandir function
	struct dirent **dits;

	// The number of files/nodes that are contained in the directory
	int num_files = 0;
	
	char *dirname;
	
	// If a directory path is not supplied, use the present working directory
	// as a default
	if (argc < 2) {
		dirname = getcwd (NULL, 0);
	} else {
		dirname = argv[1];
	}

	// Call the scandir function.
	// The 3rd param is a filter/selctor function; we want all children of the
	// directory, so we use our `_true` function to accept all children.
	// The 4th param is a sort function. We are using alphasort, which is
	// provided by the GNU stdlib
	num_files = scandir (dirname, &dits, _true, alphasort);

	if (num_files >= 0) {
		int count;
		for (count = 0; count < num_files; ++count) {
			// This is where we actually write the nodes' names to STDOUT
			puts(dits[count]->d_name);
		}
		// Clean up the memory allocatted by scandir
		for (count = 0; count < num_files; ++count) {
			// Free each dirent before freeing dits as a whole
			free(dits[count]);
		}
		free(dits);
	} else {
		perror ("Error opening directory");
	}	
	
	// We can't free `dirname` unless getcwd got called - which only happens
	// if a path to list is supplied by the user
	if (argc < 2) {
		free (dirname);
	}	
	return 0;
}

