/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2016 bingies <bingies@bingies>
 * 
 * gimo is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gimo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "myfiles.h"
int main(int argc, char* argv[]){
    char buffer[4096];
    pid_t child;
    prog_name = argv[0];
    ssize_t n, nr;
    size_t c;
    if (argc != 2)
	usage();
    child = fork();		// fork a new process
    if (child < 0){		// fork error
	fprintf(stderr, "Unknown error occured\n");
	exit (EXIT_FAILURE);
    }
    else if (child == 0){
	n = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);		// file permissions
	if (n == -1){
	    perror("open");							// open error
	    exit (EXIT_FAILURE);
	}
	while ((c=read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){		// read user input
	    nr = write(n, buffer, c);
	    if (nr == -1){
		if (errno == EIO)						// IO error
		    fprintf(stderr, "Unknown error occured\n");
	        perror("write");
		exit (EXIT_FAILURE);
	    }
	}
    }
    wait(&child);								// wait for child process to complete
    exit (EXIT_SUCCESS);
}

void usage(void){
    fprintf(stderr, "Usage: %s <file> \n", prog_name);
    exit (EXIT_FAILURE);
}

void err_sys(const char* x){						// not yet needed
    perror(x);
}
