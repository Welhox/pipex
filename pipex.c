/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/24 16:27:21 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*  void	arg_check(int argc)//, char **argv)

{
	//int	fd;
	if (argc != 5)
	{
		write(2, "Usage is : ./pipex file1 cmd1 cmd2 file2\n", 41);
		exit (1);
	} 
 	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("infile");
		exit (0);
	}
	close(fd); */
//}

void	child_one(t_pipex *pipex)

{
	int	fd;

	fd = open(pipex->argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(pipex->argv[1]);
		write(pipex->pipe_fd[1], "", 0);
		exit(1);
	}
	dup2(fd, 0);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	if (execve(pipex->path, pipex->cmd_array, pipex->envp) == -1)
		//perror("could not execute command\n");
		write(2, "could not execute command\n", 26);
}

void	child_two(t_pipex *pipex)

{
	int	fd;

	fd = open (pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_free_all(pipex);
		perror("outfile");
		exit(1);
	}
	dup2(fd, 1);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], 0);
	if (execve(pipex->path2, pipex->cmd_array2, pipex->envp) == -1)
		//write(2, "could not execute command\n", 26);
		perror("could not execute command\n");
}

void	ft_argadd(t_pipex *pipex, char **argv, char **envp, int pipe_fd[2])

{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_array = ft_splitter(pipex->argv[2]);
	pipex->cmd_array2 = ft_splitter(pipex->argv[3]);
	pipex->path = get_path(pipex->cmd_array[0], pipex->envp);
	pipex->path2 = get_path(pipex->cmd_array2[0], pipex->envp);
	pipex->pipe_fd[0] = pipe_fd[0];
	pipex->pipe_fd[1] = pipe_fd[1];
}

void	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex)

{
	if (pid == 0)
		child_one(pipex);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			child_two(pipex);
	}
	if (pid == 0)
	{
		wait(&pid);
		wait(&pid2);
	}
}

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];

	pid = 0;
	pid2 = 0;
	if (argc != 5)
	{
		write(2, "Usage is : ./pipex file1 cmd1 cmd2 file2\n", 41);
		exit (1);
	}
/* 	if (!envp)
	{
		perror("Error:");
		exit (1);
	} */
	//arg_check(argc);
	pipe(pipe_fd);
	ft_argadd(&pipex, argv, envp, pipe_fd);
	pid = fork();
	ft_exec(pid, pid2, &pipex);
	ft_free_all(&pipex);
	return (0);
}
/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/