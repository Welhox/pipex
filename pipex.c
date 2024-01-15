/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/15 17:18:48 by clundber         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envv)

{
	int	pid;
	int fd;

	arg_check(argc, argv);
	
	// fork training
	int package;
	package = 0;
	int	pipe1[2];
	int	pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	pid = fork();

	if(execve(argv[2]/*array?*/, argv[1]/*array*/, envv/*array*/) == -1)
	{
		perror("could not execute command\n");

	}

	if (pid == 0) // this is the child process
	{
		read(pipe1[0], &package, sizeof(int));
		fd = open (argv[4], O_WRONLY);
		dup2(fd, 1);
		//ft_printf("Hello, this is child\n");
		ft_printf("the package number is %d\n", package);
		close(fd);
	}
	else // this is the parent process
	{
		package = 10;
		write(pipe1[1], &package, sizeof(int));
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