/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welhox <welhox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:34:07 by clundber          #+#    #+#             */
/*   Updated: 2024/01/29 22:06:58 by welhox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *pipex)

{
	int	fd;

	fd = open(pipex->argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror(pipex->argv[1]);
		//write(pipex->pipe_fd[1], "", 0);
		exit(1);
	}
	dup2(fd, 0);
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	if (execve(pipex->path, pipex->cmd_array, pipex->envp) == -1)
		perror("could not execute command one\n");
}

void	child_two(t_pipex *pipex)

{
	int	fd;

	fd = open (pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_free_all(pipex);
		perror("outfile");
		//pipex->error_code = 1;
		exit(1);
	}
	dup2(fd, 1);
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], 0);
	if (execve(pipex->path2, pipex->cmd_array2, pipex->envp) == -1)
		perror("could not execute command two\n");
	//pipex->error_code = 1;
}

void	ft_argadd(t_pipex *pipex, char **argv, char **envp, int pipe_fd[2])

{
	char	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_array = ft_splitter(pipex->argv[2]);
	pipex->cmd_array2 = ft_splitter(pipex->argv[3]);
	pipex->path = get_path(pipex->cmd_array[0], pipex->envp, ptr, i);
	pipex->path2 = get_path(pipex->cmd_array2[0], pipex->envp, ptr, i);
	pipex->pipe_fd[0] = pipe_fd[0];
	pipex->pipe_fd[1] = pipe_fd[1];
	pipex->error_code = 0;
}

int	ft_exec(pid_t pid, pid_t pid2, t_pipex *pipex)

{
	int	status;

	status = 0;
	if (pid == 0)
		child_one(pipex);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			//ft_free_all(&pipex);
			return (1);
		}
		if (pid2 == 0)
			child_two(pipex);
	}
	if (pid == 0)
	{
		waitpid(pid, &status , 1);
		waitpid(pid2, &status , 1);
		//wait(&pid2);
	}
	ft_printf("return = %d\n", status);
	return (status);
}

int		ft_argcheck(int argc, char *argv[], char *envp[])

{
	int fd;

	fd = 0;
	if (argc != 5)
	{
		ft_putstr_fd("Usage is : file cmd1 cmd2 file2\n", 2);
		exit (1);
	}
	if (!envp)
		exit (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
 	{
 		perror(argv[1]);
		exit (0);
	} 
	close (fd);
/* 	fd = open (argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
 	{
		return (2);
 		 perror(argv[1]);
		exit (1);  */
//	} 
//	close (fd);
	return (0);
}

void	ft_error(t_pipex *pipex)

{
	if (pipex->error_code == 1)
		ft_putstr_fd("this is a open error\n", 2);
	exit (1);


}

int	main(int argc, char *argv[], char *envp[])

{
	t_pipex	pipex;
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];
	int		error_code;

	error_code = 0;
	pid = 0;
	pid2 = 0;
	if (ft_argcheck(argc, argv, envp) > 0)
	{
		pipex.error_code = 1;
		ft_error(&pipex);
	}
	pipe(pipe_fd);
	ft_argadd(&pipex, argv, envp, pipe_fd);
	pid = fork();
	if (pid == -1)
	{
		ft_free_all(&pipex);
		return (1);
	}
	error_code = ft_exec(pid, pid2, &pipex);
	ft_free_all(&pipex);
	return (error_code);
}
/*
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
*/