/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/13 17:46:00 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	arg_check(int argc, char **argv)

{
	int	fd;

	if (argc != 5 || !argv[2] || !argv[3])
	{
		write(2, "Error\n", 6);	
		exit (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		//ft_printf("unable to open read file\n");
		exit (0);
	}
	close(fd);
	fd = open (argv[4], O_WRONLY);
	if (fd < 0)
	{
		perror("Error");
		exit (0);
	}
	close(fd);
}

int	main(int argc, char **argv)

{
	int	pid;
	int	pipe1[2];
	int	pipe2[2];
	int package;

	package = 10;
	arg_check(argc, argv);
	// fork training
	pipe(pipe1);
	pipe(pipe2);
	pid = fork();
	if (pid == 0) // this is the child process
	{
		read(pipe1, &foo_copy.txt, size)
		ft_printf("Hello, this is child\n");
	}
	else // this is the parent process
	{
		write(pipe1, &foo_copy.txt, size);
		//wait(&pid);
		ft_printf("and I am parent\n");
	}

	// fork training
	return(1);
}


/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/