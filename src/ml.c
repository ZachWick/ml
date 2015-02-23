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

#define VERSION "0.0.1"
#define AUTHOR "zach wick <zach@zachwick.com>"

int
main(int argc, char *argv[]) {
	DIR *dip;
	struct dirent *dit;

	int i=0;
	char *dirname;
	

	// If a directory path is not supplied, use the present working directory
	// as a default
	if (argc < 2) {
		dirname = getcwd (NULL, 0);
	} else {
		dirname = argv[1];
	}


	// Open a directory stream to dirname and make sure that it is
	// readable and valid (directory)
	if ((dip = opendir(dirname)) == NULL) {
		perror ("error at opendir");
		return 0;
	}

	// Read in the files from dirname and print
	while ((dit = readdir(dip)) != NULL) {
		i++;
		if (i == 0) {
			puts(dit->d_name);
		} else {
			puts(dit->d_name);
		}
	}
	printf("\n");

	// Close the stream to argv[1] and check for errors
	if (closedir(dip) == -1) {
		perror ("closedir");
		return 0;
	}

	// Memory cleanup
	// We can't free `dirname` unless getcwd got called - which only happens
	// if a path to list is supplied by the user
	if (argc < 2) {
		free (dirname);
	}
	
	return 1;
}

