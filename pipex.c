/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/13 12:52:41 by clundber         ###   ########.fr       */
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
		ft_printf("unable to open read file\n");
		exit (0);
	}
	close(fd);
	fd = open (argv[4], O_WRONLY);
	if (fd < 0)
	{
		ft_printf("unable to open write file\n");
		exit (0);
	}
	close(fd);
}

int	main(int argc, char **argv)

{
	int	pid;

	arg_check(argc, argv);

	return(1);
}


/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/